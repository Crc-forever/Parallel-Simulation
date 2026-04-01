#include <stddef.h>
#include <stdio.h>
#include "Fridge_Correct.h"
#include <time.h>
#include <windows.h>
#include "define.h"

static RT_MODEL_Fridge_Correct_T Fridge_Correct_M_;
static RT_MODEL_Fridge_Correct_T *const Fridge_Correct_MPtr = &Fridge_Correct_M_;
static DW_Fridge_Correct_T Fridge_Correct_DW;
static real_T Fridge_Correct_U_DOOR_SENSOR;
static real_T Fridge_Correct_U_TEMPERATURE;
static real_T Fridge_Correct_U_REF;
static real_T Fridge_Correct_Y_Out1;
static real_T Fridge_Correct_Y_Out2;
static real_T Fridge_Correct_Y_Out3;
void rt_OneStep(RT_MODEL_Fridge_Correct_T *const Fridge_Correct_M);
void rt_OneStep(RT_MODEL_Fridge_Correct_T *const Fridge_Correct_M)
{
  static boolean_T OverrunFlag = false;
  if (OverrunFlag) {
    rtmSetErrorStatus(Fridge_Correct_M, "Overrun");
    return;
  }

  OverrunFlag = true;
  Fridge_Correct_step(Fridge_Correct_M, Fridge_Correct_U_DOOR_SENSOR,
                      Fridge_Correct_U_TEMPERATURE, Fridge_Correct_U_REF,
                      &Fridge_Correct_Y_Out1, &Fridge_Correct_Y_Out2,
                      &Fridge_Correct_Y_Out3);
  OverrunFlag = false;
}

int TOTAL_STEP = 50000000;
int_T main(int_T argc, const char *argv[])
{
  RT_MODEL_Fridge_Correct_T *const Fridge_Correct_M = Fridge_Correct_MPtr;
  (void)(argc);
  (void)(argv);
  Fridge_Correct_M->dwork = &Fridge_Correct_DW;
  Fridge_Correct_initialize(Fridge_Correct_M, &Fridge_Correct_U_DOOR_SENSOR,
    &Fridge_Correct_U_TEMPERATURE, &Fridge_Correct_U_REF, &Fridge_Correct_Y_Out1,
    &Fridge_Correct_Y_Out2, &Fridge_Correct_Y_Out3);
  if (argc > 1) {
        TOTAL_STEP = atoi(argv[1]);
  }
  printf("Step: %d\n", TOTAL_STEP);
  clock_t start = clock();

  create_data_dir();
  init_buffers();

  FILE *file = fopen("../test_data.bin", "rb");
  if (file == NULL) {
      perror("we cannot open the test data file");
      return 1;
  }
  for(int i = 0; i < TOTAL_STEP; i++){
    fread(&Fridge_Correct_U_DOOR_SENSOR, sizeof(real_T), 1, file);
    fread(&Fridge_Correct_U_TEMPERATURE, sizeof(real_T), 1, file);
    fread(&Fridge_Correct_U_REF, sizeof(real_T), 1, file);
    rt_OneStep(Fridge_Correct_M);
    write_buffers(&Fridge_Correct_Y_Out1, sizeof(real_T));
    write_buffers(&Fridge_Correct_Y_Out2, sizeof(real_T));
    write_buffers(&Fridge_Correct_Y_Out3, sizeof(real_T));
  }
  write_remain_data();
  free_buffers();
  fclose(file);
  clock_t end = clock();
  double used_time = (double)(end -start) / CLOCKS_PER_SEC;
  FILE *result_file = fopen("result.txt", "w");
  if (result_file != NULL) {
        fprintf(result_file, "spent_time: %.3fsecond\n", used_time);
        fclose(result_file);
  }
  Fridge_Correct_terminate(Fridge_Correct_M);
  return 0;
}
