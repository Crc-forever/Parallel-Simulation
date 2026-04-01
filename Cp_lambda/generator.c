#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    const char *filename = "test_data.bin";
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }

    long long num_steps = 100000000;
    double wind = 10.0;
    double speed = 1.0;

    srand(time(NULL));

    // Buffer to speed up writing
    size_t buffer_size = 1000000; // 1 million steps per write
    double *buffer = (double *)malloc(buffer_size * 2 * sizeof(double));
    if (!buffer) {
        perror("Failed to allocate buffer");
        fclose(fp);
        return 1;
    }

    long long steps_written = 0;
    while (steps_written < num_steps) {
        size_t current_batch = (num_steps - steps_written > buffer_size) ? buffer_size : (num_steps - steps_written);
        for (size_t i = 0; i < current_batch; i++) {
            // Random walk for wind (3.0 to 25.0)
            wind += ((double)rand() / (double)RAND_MAX - 0.5) * 0.1;
            if (wind < 3.0) wind = 3.0;
            if (wind > 25.0) wind = 25.0;

            // Speed follows wind (around wind * 0.1, 0.1 to 5.0)
            double target_speed = wind * 0.1;
            speed += (target_speed - speed) * 0.05 + ((double)rand() / (double)RAND_MAX - 0.5) * 0.02;
            if (speed < 0.1) speed = 0.1;
            if (speed > 5.0) speed = 5.0;

            buffer[i * 2] = speed;      // Generator Speed (first input)
            buffer[i * 2 + 1] = wind;   // Wind (second input)
        }
        fwrite(buffer, sizeof(double), current_batch * 2, fp);
        steps_written += current_batch;
        printf("\rProgress: %.2f%%", (double)steps_written / num_steps * 100.0);
        fflush(stdout);
    }

    free(buffer);
    fclose(fp);
    printf("\nSuccessfully generated %lld steps in %s\n", num_steps, filename);
    return 0;
}
