#include <stdio.h>
#include <stdlib.h>
#include "rtwtypes.h"

enum { kInputsPerStep = 8 * 8 };

static int write_steps(FILE *file, uint32_T start_step, uint32_T step_count)
{
  const uint32_T values_per_step = (uint32_T)kInputsPerStep;
  const size_t total_values = (size_t)step_count * (size_t)values_per_step;
  int32_T *buffer = (int32_T *)malloc(total_values * sizeof(int32_T));
  if (buffer == NULL) {
    return 0;
  }

  for (uint32_T s = 0; s < step_count; ++s) {
    const uint32_T step_index = start_step + s;
    int32_T *step_base = buffer + ((size_t)s * (size_t)values_per_step);
    for (uint32_T port = 0; port < 8U; ++port) {
      for (uint32_T i = 0; i < 8U; ++i) {
        step_base[(port * 8U) + i] = (int32_T)(step_index + (port * 1000000U) + i);
      }
    }
  }

  const size_t written = fwrite(buffer, sizeof(int32_T), total_values, file);
  free(buffer);
  return written == total_values;
}

int main(void)
{
  _Static_assert(sizeof(int32_T) == 4, "int32_T must be 4 bytes");

  FILE *file = fopen("test_data.bin", "wb");
  if (file == NULL) {
    return 1;
  }

  const uint32_T total_steps = 10000000U;
  const uint32_T chunk_steps = 4096U;

  for (uint32_T step = 0; step < total_steps; step += chunk_steps) {
    const uint32_T remaining = total_steps - step;
    const uint32_T count = remaining < chunk_steps ? remaining : chunk_steps;
    if (!write_steps(file, step, count)) {
      fclose(file);
      return 2;
    }
  }

  fclose(file);
  return 0;
}
