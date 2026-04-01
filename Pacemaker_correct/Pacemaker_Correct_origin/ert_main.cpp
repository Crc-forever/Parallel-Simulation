#include "Pacemaker_Correct.h"
#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include "define.h"


static RT_MODEL_Pacemaker_Correct_T Pacemaker_Correct_M_;
static RT_MODEL_Pacemaker_Correct_T *const Pacemaker_Correct_MPtr =
  &Pacemaker_Correct_M_;
static B_Pacemaker_Correct_T Pacemaker_Correct_B;
static DW_Pacemaker_Correct_T Pacemaker_Correct_DW;
static real_T Pacemaker_Correct_U_VENT_Amplitude;
static real_T Pacemaker_Correct_U_Mode;
static real_T Pacemaker_Correct_Y_Out1;
static real_T Pacemaker_Correct_Y_Out2;
static real_T Pacemaker_Correct_Y_Out3;
static real_T Pacemaker_Correct_Y_Out4;
static real_T Pacemaker_Correct_Y_Out5;
static real_T Pacemaker_Correct_Y_Out6;
static real_T Pacemaker_Correct_Y_Out7;
static real_T Pacemaker_Correct_Y_Out8;
static real_T Pacemaker_Correct_Y_Out9;
static real_T Pacemaker_Correct_Y_Out10;
static real_T Pacemaker_Correct_Y_Out11;
static real_T Pacemaker_Correct_Y_Out12;
static real_T Pacemaker_Correct_Y_Out13;
static real_T Pacemaker_Correct_Y_Out14;
static real_T Pacemaker_Correct_Y_Out15;
void rt_OneStep(RT_MODEL_Pacemaker_Correct_T *const Pacemaker_Correct_M);
void rt_OneStep(RT_MODEL_Pacemaker_Correct_T *const Pacemaker_Correct_M)
{
  static boolean_T OverrunFlag = false;
  if (OverrunFlag) {
    rtmSetErrorStatus(Pacemaker_Correct_M, "Overrun");
    return;
  }

  OverrunFlag = true;
  Pacemaker_Correct_step(Pacemaker_Correct_M, Pacemaker_Correct_U_VENT_Amplitude,
    Pacemaker_Correct_U_Mode, &Pacemaker_Correct_Y_Out1,
    &Pacemaker_Correct_Y_Out2, &Pacemaker_Correct_Y_Out3,
    &Pacemaker_Correct_Y_Out4, &Pacemaker_Correct_Y_Out5,
    &Pacemaker_Correct_Y_Out6, &Pacemaker_Correct_Y_Out7,
    &Pacemaker_Correct_Y_Out8, &Pacemaker_Correct_Y_Out9,
    &Pacemaker_Correct_Y_Out10, &Pacemaker_Correct_Y_Out11,
    &Pacemaker_Correct_Y_Out12, &Pacemaker_Correct_Y_Out13,
    &Pacemaker_Correct_Y_Out14, &Pacemaker_Correct_Y_Out15);
  OverrunFlag = false;
}

int TOTAL_STEP = 50000000;
int_T main(int_T argc, const char *argv[])
{
  RT_MODEL_Pacemaker_Correct_T *const Pacemaker_Correct_M =
    Pacemaker_Correct_MPtr;
  Pacemaker_Correct_M->blockIO = &Pacemaker_Correct_B;
  Pacemaker_Correct_M->dwork = &Pacemaker_Correct_DW;
  Pacemaker_Correct_initialize(Pacemaker_Correct_M,
    &Pacemaker_Correct_U_VENT_Amplitude, &Pacemaker_Correct_U_Mode,
    &Pacemaker_Correct_Y_Out1, &Pacemaker_Correct_Y_Out2,
    &Pacemaker_Correct_Y_Out3, &Pacemaker_Correct_Y_Out4,
    &Pacemaker_Correct_Y_Out5, &Pacemaker_Correct_Y_Out6,
    &Pacemaker_Correct_Y_Out7, &Pacemaker_Correct_Y_Out8,
    &Pacemaker_Correct_Y_Out9, &Pacemaker_Correct_Y_Out10,
    &Pacemaker_Correct_Y_Out11, &Pacemaker_Correct_Y_Out12,
    &Pacemaker_Correct_Y_Out13, &Pacemaker_Correct_Y_Out14,
    &Pacemaker_Correct_Y_Out15);
  
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
    fread(&Pacemaker_Correct_U_VENT_Amplitude, sizeof(real_T), 1, file);
    fread(&Pacemaker_Correct_U_Mode, sizeof(real_T), 1, file);
    rt_OneStep(Pacemaker_Correct_M);
    write_buffers(Pacemaker_Correct_Y_Out1, sizeof(real_T));
    write_buffers(Pacemaker_Correct_Y_Out2, sizeof(real_T));
    write_buffers(Pacemaker_Correct_Y_Out3, sizeof(real_T));
    write_buffers(Pacemaker_Correct_Y_Out4, sizeof(real_T));
    write_buffers(Pacemaker_Correct_Y_Out5, sizeof(real_T));
    write_buffers(Pacemaker_Correct_Y_Out6, sizeof(real_T));
    write_buffers(Pacemaker_Correct_Y_Out7, sizeof(real_T));
    write_buffers(Pacemaker_Correct_Y_Out8, sizeof(real_T));
    write_buffers(Pacemaker_Correct_Y_Out9, sizeof(real_T));
    write_buffers(Pacemaker_Correct_Y_Out10, sizeof(real_T));
    write_buffers(Pacemaker_Correct_Y_Out11, sizeof(real_T));
    write_buffers(Pacemaker_Correct_Y_Out12, sizeof(real_T));
    write_buffers(Pacemaker_Correct_Y_Out13, sizeof(real_T));
    write_buffers(Pacemaker_Correct_Y_Out14, sizeof(real_T));
    write_buffers(Pacemaker_Correct_Y_Out15, sizeof(real_T));
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

  Pacemaker_Correct_terminate(Pacemaker_Correct_M);
  return 0;
}
