#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    const char *filename = "test_data.csv";
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }

    long long num_steps = 100000000;
    double wind = 10.0;
    double speed = 1.0;

    srand(time(NULL));

    setvbuf(fp, NULL, _IOFBF, 1 << 20);
    fprintf(fp, "time,generator_speed,wind\n");

    long long steps_written = 0;
    while (steps_written < num_steps) {
        size_t buffer_size = 1000000;
        size_t remaining = (size_t)(num_steps - steps_written);
        size_t current_batch = remaining > buffer_size ? buffer_size : remaining;
        for (size_t i = 0; i < current_batch; i++) {
            wind += ((double)rand() / (double)RAND_MAX - 0.5) * 0.1;
            if (wind < 3.0) wind = 3.0;
            if (wind > 25.0) wind = 25.0;

            double target_speed = wind * 0.1;
            speed += (target_speed - speed) * 0.05 + ((double)rand() / (double)RAND_MAX - 0.5) * 0.02;
            if (speed < 0.1) speed = 0.1;
            if (speed > 5.0) speed = 5.0;

            long long t = steps_written + (long long)i;
            fprintf(fp, "%lld,%.8f,%.8f\n", t, speed, wind);
        }
        steps_written += current_batch;
        printf("\rProgress: %.2f%%", (double)steps_written / num_steps * 100.0);
        fflush(stdout);
    }

    fclose(fp);
    printf("\nSuccessfully generated %lld steps in %s\n", num_steps, filename);
    return 0;
}
