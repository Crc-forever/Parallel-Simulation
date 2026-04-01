#include <stddef.h>
#include <stdio.h>
#include "Elevator_Correct.h"
#include <time.h>
#include <windows.h>
#include "define.h"

static RT_MODEL_Elevator_Correct_T Elevator_Correct_M_;
static RT_MODEL_Elevator_Correct_T *const Elevator_Correct_MPtr =
  &Elevator_Correct_M_;
static DW_Elevator_Correct_T Elevator_Correct_DW;
static real_T Elevator_Correct_U_pisua;
static real_T Elevator_Correct_Y_Out1;
static real_T Elevator_Correct_Y_Out2;
static real_T Elevator_Correct_Y_Out3;
void rt_OneStep(RT_MODEL_Elevator_Correct_T *const Elevator_Correct_M);
void rt_OneStep(RT_MODEL_Elevator_Correct_T *const Elevator_Correct_M)
{
  static boolean_T OverrunFlag = false;
  if (OverrunFlag) {
    rtmSetErrorStatus(Elevator_Correct_M, "Overrun");
    return;
  }

  OverrunFlag = true;
  Elevator_Correct_step(Elevator_Correct_M, Elevator_Correct_U_pisua,
                        &Elevator_Correct_Y_Out1, &Elevator_Correct_Y_Out2,
                        &Elevator_Correct_Y_Out3);
  OverrunFlag = false;
}

int TOTAL_STEP = 50000000;
int_T main(int_T argc, const char *argv[])
{
  RT_MODEL_Elevator_Correct_T *const Elevator_Correct_M = Elevator_Correct_MPtr;
  
  Elevator_Correct_M->dwork = &Elevator_Correct_DW;
  Elevator_Correct_initialize(Elevator_Correct_M, &Elevator_Correct_U_pisua,
    &Elevator_Correct_Y_Out1, &Elevator_Correct_Y_Out2, &Elevator_Correct_Y_Out3);
  
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
    fread(&Elevator_Correct_U_pisua, sizeof(real_T), 1, file);
    rt_OneStep(Elevator_Correct_M);
    write_buffers(Elevator_Correct_Y_Out1, sizeof(real_T));
    write_buffers(Elevator_Correct_Y_Out2, sizeof(real_T));
    write_buffers(Elevator_Correct_Y_Out3, sizeof(real_T));
    printf("%lf\n",Elevator_Correct_DW.oraingoPisua);
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
  
  Elevator_Correct_terminate(Elevator_Correct_M);
  return 0;
}
