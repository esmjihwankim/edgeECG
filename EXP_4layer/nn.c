#include "nn.h"

/*****************************************************/
/* Neural Network Implementation                      / 
/*****************************************************/
 q15_t fc1_wt[FC1_IN_DIM*FC1_OUT_DIM] = FC1_WT;
 q15_t fc1_bias[FC1_OUT_DIM] = FC1_BIAS;

 q15_t fc2_wt[FC2_IN_DIM*FC2_OUT_DIM] = FC2_WT;
 q15_t fc2_bias[FC2_OUT_DIM] = FC2_BIAS;

 q15_t fc3_wt[FC3_IN_DIM*FC3_OUT_DIM] = FC3_WT;
 q15_t fc3_bias[FC3_OUT_DIM] = FC3_BIAS;

 q15_t fc4_wt[FC4_IN_DIM*FC4_OUT_DIM] = FC4_WT;
 q15_t fc4_bias[FC4_OUT_DIM] = FC4_BIAS;

q15_t col_buffer[576];
q15_t scratch_buffer[28*28];

q15_t input_data[784] = INPUT_DATA;
q15_t output_data[784];



void run_inference(void)
{
    printf("performing inference\r\n");
    q15_t* buffer1 = scratch_buffer;
    q15_t* buffer2 = buffer1 + 100; 
    int i;
    arm_fully_connected_q15_opt(input_data, fc1_wt, FC1_IN_DIM, FC1_OUT_DIM, FC1_BIAS_LSHIFT, FC1_OUT_RSHIFT, fc1_bias, buffer1, (q15_t*)col_buffer);
    arm_relu_q15(buffer1, FC1_OUT_DIM);
    arm_fully_connected_q15_opt(buffer1, fc2_wt, FC2_IN_DIM, FC2_OUT_DIM, FC2_BIAS_LSHIFT, FC2_OUT_RSHIFT, fc2_bias, buffer2, (q15_t*)col_buffer);
    arm_relu_q15(buffer2, FC2_OUT_DIM);
    arm_fully_connected_q15_opt(buffer2, fc3_wt, FC3_IN_DIM, FC3_OUT_DIM, FC3_BIAS_LSHIFT, FC3_OUT_RSHIFT, fc3_bias, buffer1, (q15_t*)col_buffer);
    arm_relu_q15(buffer1, FC3_OUT_DIM);
    arm_fully_connected_q15_opt(buffer1, fc4_wt, FC4_IN_DIM, FC4_OUT_DIM, FC4_BIAS_LSHIFT, FC4_OUT_RSHIFT, fc4_bias, output_data, (q15_t*)col_buffer);
    
    for (int i = 0; i < 10; i++)
    {
        printf("%d\r\n", output_data[i]);
    }

}