#include <stdio.h>
#include <stdlib.h>

#define TOTAL_GROUPS 100000000

typedef enum {
    EMPTY = 0,
    ONLY_1,
    BOTH
} State;

void write_op(FILE *fp, int op, int val, int new_val) {
    fwrite(&op, sizeof(int), 1, fp);
    fwrite(&val, sizeof(int), 1, fp);
    fwrite(&new_val, sizeof(int), 1, fp);
}

int main() {
    FILE *fp = fopen("test_data.bin", "wb");
    if (!fp) return 1;

    srand(123456);
    State state = EMPTY;

    for (long i = 0; i < TOTAL_GROUPS; i++) {
        switch (state) {
        case EMPTY:
            write_op(fp, 1, 1, 0);   // add 1
            state = ONLY_1;
            break;

        case ONLY_1:
            if (rand() & 1) {
                write_op(fp, 2, 1, 0); // delete 1
                state = EMPTY;
            } else {
                write_op(fp, 1, 2, 0); // add 2
                state = BOTH;
            }
            break;

        case BOTH:
            write_op(fp, 2, 2, 0);   // delete 2 only
            state = ONLY_1;
            break;
        }
    }

    fclose(fp);
    return 0;
}
