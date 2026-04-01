#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"

static void fill_step_inputs(size_t step_index, int32_T first_pass[32],
                             int16_T auto_manual_switch[32])
{
  size_t i;
  for (i = 0; i < 32; i++) {
    uint32_T x = (uint32_T)step_index * 1664525U + (uint32_T)i * 1013904223U;
    first_pass[i] = (int32_T)((int32_T)(x % 2000000001U) - 1000000000);
    auto_manual_switch[i] = (int16_T)((int32_T)(((uint32_T)step_index * 7U +
      (uint32_T)i * 13U) & 65535U) - 32768);
  }
}

int main(void)
{
  const size_t steps = 10000000U;
  const size_t chunk_steps = 4096U;
  const size_t step_bytes = (size_t)32U * sizeof(int32_T) +
    (size_t)32U * sizeof(int16_T);

  FILE *fp = fopen("test_data.bin", "wb");
  if (fp == NULL) {
    fprintf(stderr, "failed to open output file: test_data.bin\n");
    return 1;
  }

  if ((sizeof(int32_T) != 4U) || (sizeof(int16_T) != 2U) ||
      (sizeof(uint32_T) != 4U)) {
    fprintf(stderr, "unexpected type sizes: int32_T=%zu int16_T=%zu uint32_T=%zu\n",
            sizeof(int32_T), sizeof(int16_T), sizeof(uint32_T));
    fclose(fp);
    return 2;
  }

  {
    unsigned char *buffer = (unsigned char *)malloc(step_bytes * chunk_steps);
    if (buffer == NULL) {
      fprintf(stderr, "failed to allocate buffer\n");
      fclose(fp);
      return 3;
    }

    size_t step = 0U;
    while (step < steps) {
      size_t this_chunk = steps - step;
      if (this_chunk > chunk_steps) {
        this_chunk = chunk_steps;
      }

      size_t s;
      for (s = 0U; s < this_chunk; s++) {
        int32_T first_pass[32];
        int16_T auto_manual_switch[32];
        unsigned char *p = buffer + (step_bytes * s);

        fill_step_inputs(step + s, first_pass, auto_manual_switch);
        (void)memcpy(p, first_pass, (size_t)32U * sizeof(int32_T));
        p += (size_t)32U * sizeof(int32_T);
        (void)memcpy(p, auto_manual_switch, (size_t)32U * sizeof(int16_T));
      }

      if (fwrite(buffer, step_bytes, this_chunk, fp) != this_chunk) {
        fprintf(stderr, "failed to write output file\n");
        free(buffer);
        fclose(fp);
        return 4;
      }

      step += this_chunk;
    }

    free(buffer);
  }

  if (fclose(fp) != 0) {
    fprintf(stderr, "failed to close output file\n");
    return 5;
  }

  return 0;
}

