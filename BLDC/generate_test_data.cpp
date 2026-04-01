#include "rtwtypes.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint64_t next_u64(uint64_t *state)
{
  uint64_t x = *state;
  x ^= x >> 12;
  x ^= x << 25;
  x ^= x >> 27;
  *state = x;
  return x * 2685821657736338717ULL;
}

static int32_T bounded_i32(uint64_t *state, int32_T min_inclusive,
                           int32_T max_inclusive)
{
  uint64_t r = next_u64(state);
  uint32_T span = (uint32_T)(max_inclusive - min_inclusive + 1);
  uint32_T v = (uint32_T)(r % span);
  return (int32_T)(min_inclusive + (int32_T)v);
}

static int is_little_endian()
{
  const uint32_t v = 1U;
  return *((const uint8_t *)&v) == 1U;
}

static int write_step(FILE *f, const int32_T U1[32], const int32_T U2[32],
                      const int32_T U3[32], const int32_T U4[32],
                      const int32_T KT[32], const int32_T I[32],
                      const int32_T Kd[32], const int32_T Kd_4[32],
                      const int32_T KT_I[32], const int32_T Kd_3[32])
{
  if (fwrite(U1, sizeof(int32_T), 32, f) != 32) return 0;
  if (fwrite(U2, sizeof(int32_T), 32, f) != 32) return 0;
  if (fwrite(U3, sizeof(int32_T), 32, f) != 32) return 0;
  if (fwrite(U4, sizeof(int32_T), 32, f) != 32) return 0;
  if (fwrite(KT, sizeof(int32_T), 32, f) != 32) return 0;
  if (fwrite(I, sizeof(int32_T), 32, f) != 32) return 0;
  if (fwrite(Kd, sizeof(int32_T), 32, f) != 32) return 0;
  if (fwrite(Kd_4, sizeof(int32_T), 32, f) != 32) return 0;
  if (fwrite(KT_I, sizeof(int32_T), 32, f) != 32) return 0;
  if (fwrite(Kd_3, sizeof(int32_T), 32, f) != 32) return 0;

  return 1;
}

int main(int argc, char **argv)
{
  static int32_T rtU_U1[32];
  static int32_T rtU_U2[32];
  static int32_T rtU_U3[32];
  static int32_T rtU_U4[32];
  static int32_T rtU_KT[32];
  static int32_T rtU_I[32];
  static int32_T rtU_Kd[32];
  static int32_T rtU_Kd_4[32];
  static int32_T rtU_KT_I[32];
  static int32_T rtU_Kd_3[32];

  uint64_t steps = 10000000ULL;
  const char *out_path = "test_data.bin";
  if (argc >= 2) steps = (uint64_t)_strtoui64(argv[1], NULL, 10);
  if (argc >= 3) out_path = argv[2];

  if (sizeof(int32_T) != 4) {
    fprintf(stderr, "Unexpected type size: int32_T=%zu\n", sizeof(int32_T));
    return 1;
  }
  if (!is_little_endian()) {
    fprintf(stderr, "This generator assumes little-endian.\n");
    return 1;
  }

  FILE *f = fopen(out_path, "wb");
  if (!f) {
    fprintf(stderr, "Failed to open %s\n", out_path);
    return 1;
  }

  uint64_t rng = 0xCBF29CE484222325ULL;

  for (uint64_t step = 0; step < steps; step++) {
    for (int i = 0; i < 32; i++) {
      rtU_U1[i] = bounded_i32(&rng, 1000, 1999);
      rtU_U2[i] = bounded_i32(&rng, 0, 200);
      rtU_U3[i] = 0;
      rtU_U4[i] = bounded_i32(&rng, 0, 1000);

      rtU_KT[i] = bounded_i32(&rng, 0, 200);
      rtU_I[i] = bounded_i32(&rng, 0, 200);
      rtU_Kd[i] = bounded_i32(&rng, 0, 100);

      rtU_Kd_4[i] = bounded_i32(&rng, 0, 3);
      rtU_KT_I[i] = 0;
      rtU_Kd_3[i] = bounded_i32(&rng, 10, 30);
    }

    if (!write_step(f, rtU_U1, rtU_U2, rtU_U3, rtU_U4, rtU_KT, rtU_I, rtU_Kd,
                    rtU_Kd_4, rtU_KT_I, rtU_Kd_3)) {
      fprintf(stderr, "Write failed at step %llu\n",
              (unsigned long long)step);
      fclose(f);
      return 1;
    }

    if ((step % 10000ULL) == 0ULL) {
      fprintf(stdout, "step %llu/%llu\n", (unsigned long long)step,
              (unsigned long long)steps);
      fflush(stdout);
    }
  }

  fclose(f);

  const uint64_t bytes_per_step = (uint64_t)(32 * 4) * (uint64_t)10;
  fprintf(stdout, "done. bytes_per_step=%llu total_bytes=%llu\n",
          (unsigned long long)bytes_per_step,
          (unsigned long long)(bytes_per_step * steps));
  return 0;
}

