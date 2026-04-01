#include "define.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <direct.h>
#include <string.h>
#include <atomic>
#include <condition_variable>
#include <queue>
#include <thread>
#include <mutex>
using namespace std;
#define BUFFER_NUM 50

// ˫����������
real_T *buffers[BUFFER_NUM];
int active_buf = 0;
size_t buf_pos[BUFFER_NUM];

struct WriteJob {
    size_t size;
    int buf_index;
    int file_idx;
};

static mutex g_state_mutex;
static condition_variable g_job_cv;
static condition_variable g_free_cv;
static condition_variable g_pending_cv;
static queue<WriteJob> g_job_queue;
static queue<int> g_free_queue;
static thread g_writer_thread;
static atomic<bool> g_writer_stop{false};
static atomic<bool> g_writer_started{false};
static atomic<int> g_next_fileindex{0};
static atomic<int> g_pending_jobs{0};
static int g_allocated_bufs = 0;
static bool g_in_flight[BUFFER_NUM] = {false};

static void write_job_to_disk(WriteJob job) {
    if (job.size == 0 || job.buf_index < 0 || job.buf_index >= BUFFER_NUM || buffers[job.buf_index] == NULL) {
        return;
    }

    char filename[100];
    sprintf(filename, "%s\\%09d.bin", DATA_DIR, job.file_idx);
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("�ļ�%s��ʧ��\n", filename);
        return;
    }

    fwrite(buffers[job.buf_index], 1, job.size, file);
    fclose(file);
}

static void write_raw_copy_to_disk(const void *data, size_t size) {
    if (size == 0) {
        return;
    }
    unsigned char *copy = (unsigned char *)malloc(size);
    if (copy == NULL) {
        printf("��������д��ʧ��\n");
        system("pause");
        exit(1);
    }
    memset(copy, 0, size);
    size_t safe_size = size;
    if (safe_size > sizeof(real_T)) {
        safe_size = sizeof(real_T);
    }
    memcpy(copy, data, safe_size);

    char filename[100];
    int file_idx = g_next_fileindex.fetch_add(1);
    sprintf(filename, "%s\\%09d.bin", DATA_DIR, file_idx);
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("�ļ�%s��ʧ��\n", filename);
        free(copy);
        return;
    }
    fwrite(copy, 1, size, file);
    fclose(file);
    free(copy);
}

static void writer_loop() {
    while (true) {
        WriteJob job{0, -1, 0};
        {
            unique_lock<mutex> lock(g_state_mutex);
            g_job_cv.wait(lock, [] { return g_writer_stop.load() || !g_job_queue.empty(); });
            if (g_writer_stop.load() && g_job_queue.empty()) {
                return;
            }
            job = g_job_queue.front();
            g_job_queue.pop();
        }
        write_job_to_disk(job);
        {
            lock_guard<mutex> lock(g_state_mutex);
            if (job.buf_index >= 0 && job.buf_index < BUFFER_NUM) {
                buf_pos[job.buf_index] = 0;
                g_in_flight[job.buf_index] = false;
                g_free_queue.push(job.buf_index);
            }
            g_pending_jobs.fetch_sub(1);
        }
        g_free_cv.notify_one();
        g_pending_cv.notify_all();
    }
}

static void start_writer_if_needed() {
    bool expected = false;
    if (g_writer_started.compare_exchange_strong(expected, true)) {
        g_writer_stop.store(false);
        g_writer_thread = thread(writer_loop);
    }
}

static void stop_writer_if_running() {
    if (!g_writer_started.load()) {
        return;
    }
    g_writer_stop.store(true);
    g_job_cv.notify_all();
    if (g_writer_thread.joinable()) {
        g_writer_thread.join();
    }
    g_writer_started.store(false);
}

static bool remove_from_free_queue_locked(int idx) {
    bool found = false;
    queue<int> tmp;
    while (!g_free_queue.empty()) {
        int v = g_free_queue.front();
        g_free_queue.pop();
        if (!found && v == idx) {
            found = true;
            continue;
        }
        tmp.push(v);
    }
    g_free_queue.swap(tmp);
    return found;
}

void create_data_dir() {
    if (_mkdir(DATA_DIR) == -1) {
        DWORD error = GetLastError();
        if (error != ERROR_ALREADY_EXISTS) {
            printf("����Ŀ¼ʧ�ܣ�������:%d\n", error);
            system("pause");
            exit(1);
        }
    }
}


// ��ʼ��˫������
void init_buffers(){
    start_writer_if_needed();
    lock_guard<mutex> lock(g_state_mutex);
    while (!g_job_queue.empty()) g_job_queue.pop();
    while (!g_free_queue.empty()) g_free_queue.pop();
    for (int i = 0; i < BUFFER_NUM; i++) {
        if (buffers[i] != NULL) free(buffers[i]);
        buffers[i] = NULL;
        buf_pos[i] = 0;
        g_in_flight[i] = false;
    }
    g_next_fileindex.store(0);
    g_pending_jobs.store(0);

    int initial = (BUFFER_NUM >= 2) ? 2 : 1;
    g_allocated_bufs = 0;
    for (int i = 0; i < initial; i++) {
        buffers[i] = (real_T *)malloc(BUFFER_SIZE);
        if (buffers[i] == NULL) {
            printf("��������ʼ��ʧ��\n");
            system("pause");
            exit(1);
        }
        buf_pos[i] = 0;
        g_allocated_bufs++;
    }
    active_buf = 0;
    for (int i = 1; i < g_allocated_bufs; i++) {
        g_free_queue.push(i);
    }
}

void free_buffers(){
    write_remain_data();
    stop_writer_if_running();
    lock_guard<mutex> lock(g_state_mutex);
    while (!g_job_queue.empty()) g_job_queue.pop();
    while (!g_free_queue.empty()) g_free_queue.pop();
    for(int i = 0; i< BUFFER_NUM; i++){
        if(buffers[i] != NULL) free(buffers[i]);
        buffers[i] = NULL;
        buf_pos[i] = 0;
        g_in_flight[i] = false;
    }
    g_allocated_bufs = 0;
}

// ������������д����̣��ɹ����߳�ִ�У�
void write_disk(int buf_index) {
    if (buf_index < 0 || buf_index >= BUFFER_NUM) {
        return;
    }
    start_writer_if_needed();

    size_t write_size = 0;
    int file_idx = 0;
    {
        unique_lock<mutex> lock(g_state_mutex);
        if (buffers[buf_index] == NULL || g_in_flight[buf_index]) {
            return;
        }
        remove_from_free_queue_locked(buf_index);
        write_size = buf_pos[buf_index];
        if (write_size == 0) {
            return;
        }
        g_in_flight[buf_index] = true;
        file_idx = g_next_fileindex.fetch_add(1);
        if (buf_index == active_buf) {
            int new_idx = -1;
            if (!g_free_queue.empty()) {
                new_idx = g_free_queue.front();
                g_free_queue.pop();
            } else if (g_allocated_bufs < BUFFER_NUM) {
                new_idx = g_allocated_bufs;
                buffers[new_idx] = (real_T *)malloc(BUFFER_SIZE);
                if (buffers[new_idx] == NULL) {
                    printf("��������ʼ��ʧ��\n");
                    system("pause");
                    exit(1);
                }
                buf_pos[new_idx] = 0;
                g_in_flight[new_idx] = false;
                g_allocated_bufs++;
            } else {
                g_free_cv.wait(lock, [] { return !g_free_queue.empty(); });
                new_idx = g_free_queue.front();
                g_free_queue.pop();
            }
            active_buf = new_idx;
            buf_pos[active_buf] = 0;
        }
    }

    WriteJob job{write_size, buf_index, file_idx};
    write_job_to_disk(job);

    {
        lock_guard<mutex> lock(g_state_mutex);
        buf_pos[buf_index] = 0;
        g_in_flight[buf_index] = false;
        g_free_queue.push(buf_index);
    }
    g_free_cv.notify_one();
}

// д�����ݵ������������������������л��������첽д��
void write_buffers(real_T data, size_t data_size) {
    start_writer_if_needed();
    if (data_size == 0) {
        return;
    }
    if (data_size > BUFFER_SIZE) {
        write_raw_copy_to_disk(&data, data_size);
        return;
    }
    unique_lock<mutex> lock(g_state_mutex);
    if (buffers[active_buf] == NULL) {
        buffers[active_buf] = (real_T *)malloc(BUFFER_SIZE);
        if (buffers[active_buf] == NULL) {
            printf("��������ʼ��ʧ��\n");
            system("pause");
            exit(1);
        }
        buf_pos[active_buf] = 0;
        if (active_buf >= g_allocated_bufs) g_allocated_bufs = active_buf + 1;
    }

    if (buf_pos[active_buf] + data_size > BUFFER_SIZE) {
        if (buf_pos[active_buf] > 0 && !g_in_flight[active_buf]) {
            int file_idx = g_next_fileindex.fetch_add(1);
            g_in_flight[active_buf] = true;
            g_job_queue.push(WriteJob{buf_pos[active_buf], active_buf, file_idx});
            g_pending_jobs.fetch_add(1);
            g_job_cv.notify_one();
        }

        int new_idx = -1;
        if (!g_free_queue.empty()) {
            new_idx = g_free_queue.front();
            g_free_queue.pop();
        } else if (g_allocated_bufs < BUFFER_NUM) {
            new_idx = g_allocated_bufs;
            buffers[new_idx] = (real_T *)malloc(BUFFER_SIZE);
            if (buffers[new_idx] == NULL) {
                printf("��������ʼ��ʧ��\n");
                system("pause");
                exit(1);
            }
            buf_pos[new_idx] = 0;
            g_in_flight[new_idx] = false;
            g_allocated_bufs++;
        } else {
            g_free_cv.wait(lock, [] { return !g_free_queue.empty(); });
            new_idx = g_free_queue.front();
            g_free_queue.pop();
        }
        active_buf = new_idx;
        buf_pos[active_buf] = 0;
    }

    memcpy((unsigned char *)buffers[active_buf] + buf_pos[active_buf], &data, data_size);
    buf_pos[active_buf] += data_size;
}

// д��ʣ������
void write_remain_data() {
    start_writer_if_needed();
    unique_lock<mutex> lock(g_state_mutex);
    if (buf_pos[active_buf] > 0 && !g_in_flight[active_buf]) {
        int file_idx = g_next_fileindex.fetch_add(1);
        g_in_flight[active_buf] = true;
        g_job_queue.push(WriteJob{buf_pos[active_buf], active_buf, file_idx});
        g_pending_jobs.fetch_add(1);
        g_job_cv.notify_one();

        int new_idx = -1;
        if (!g_free_queue.empty()) {
            new_idx = g_free_queue.front();
            g_free_queue.pop();
        } else if (g_allocated_bufs < BUFFER_NUM) {
            new_idx = g_allocated_bufs;
            buffers[new_idx] = (real_T *)malloc(BUFFER_SIZE);
            if (buffers[new_idx] == NULL) {
                printf("��������ʼ��ʧ��\n");
                system("pause");
                exit(1);
            }
            buf_pos[new_idx] = 0;
            g_in_flight[new_idx] = false;
            g_allocated_bufs++;
        } else {
            g_free_cv.wait(lock, [] { return !g_free_queue.empty(); });
            new_idx = g_free_queue.front();
            g_free_queue.pop();
        }
        active_buf = new_idx;
        buf_pos[active_buf] = 0;
    }

    g_pending_cv.wait(lock, [] { return g_pending_jobs.load() == 0; });
}
