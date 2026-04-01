#include <stddef.h>
#include <stdio.h>            /* This example main program uses printf/fflush */
#include "Cp_Lambda_Calculation.h"     /* Model header file */
#include <time.h>
#include <windows.h>
#include "define.h"

static RT_MODEL rtM_;
static RT_MODEL *const rtMPtr = &rtM_; /* Real-time model */

/* '<Root>/Generator Speed' */
static real_T rtU_GeneratorSpeed;

/* '<Root>/Wind' */
static real_T rtU_Wind;

/* '<Root>/Percentage' */
static real_T rtY_Percentage;

/* '<Root>/Out1' */
static real_T rtY_Out1;

/* '<Root>/Out2' */
static real_T rtY_Out2;

/* '<Root>/Out3' */
static real_T rtY_Out3;

/* '<Root>/Out4' */
static real_T rtY_Out4;

/* '<Root>/Percentage Power Delivered' */
static real_T rtY_PercentagePowerDelivered;

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(RT_MODEL *const rtM);
void rt_OneStep(RT_MODEL *const rtM)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  Cp_Lambda_Calculation_step(rtM, rtU_GeneratorSpeed, rtU_Wind, &rtY_Percentage,
    &rtY_Out1, &rtY_Out2, &rtY_Out3, &rtY_Out4, &rtY_PercentagePowerDelivered);

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example main function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific. This example
 * illustrates how you do this relative to initializing the model.
 */
int TOTAL_STEP = 50000000;
int_T main(int_T argc, const char *argv[])
{
  RT_MODEL *const rtM = rtMPtr;


  /* Pack model data into RTM */

  /* Initialize model */
  Cp_Lambda_Calculation_initialize(rtM, &rtU_GeneratorSpeed, &rtU_Wind,
    &rtY_Percentage, &rtY_Out1, &rtY_Out2, &rtY_Out3, &rtY_Out4,
    &rtY_PercentagePowerDelivered);

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
    fread(&rtU_GeneratorSpeed, sizeof(real_T), 1, file);
    fread(&rtU_Wind, sizeof(real_T), 1, file);
    rt_OneStep(rtM);
    write_buffers(rtY_Percentage, sizeof(real_T));
    write_buffers(rtY_Out1, sizeof(real_T));
    write_buffers(rtY_Out2, sizeof(real_T));
    write_buffers(rtY_Out3, sizeof(real_T));
    write_buffers(rtY_Out4, sizeof(real_T));
    write_buffers(rtY_PercentagePowerDelivered, sizeof(real_T));
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
  
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
