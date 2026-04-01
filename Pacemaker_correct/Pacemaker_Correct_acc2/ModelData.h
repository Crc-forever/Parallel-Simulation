#pragma once



int const MODEL_ONESTEP_INPUT_DATA_LEN = 16;  // 2 * sizeof(real_T)
int const MODEL_STATE_DATA_LEN = 22;  // 2 * sizeof(uint8_T) + uint32_t +2*real_t
int const MODEL_ONESTEP_OUTPUT_DATA_LEN = 120;  // 15 * sizeof(real_T)