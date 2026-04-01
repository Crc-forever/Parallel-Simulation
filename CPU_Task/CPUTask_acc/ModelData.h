#pragma once



int const MODEL_ONESTEP_INPUT_DATA_LEN = 12;  // 5 * sizeof(int32_T)
int const MODEL_STATE_DATA_LEN = 81;  // 16 * sizeof(int32_T) + 17 * sizeof(int8_T)
int const MODEL_ONESTEP_OUTPUT_DATA_LEN = 8;  // 2 * sizeof(int32_T)