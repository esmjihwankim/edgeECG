#include "nn.h"

/*****************************************************/
/* Neural Network Implementation                      / 
/*****************************************************/
static q15_t fc1_wt[FC1_IN_DIM*FC1_OUT_DIM] = FC1_WT;
static q15_t fc1_bias[FC1_OUT_DIM] = FC1_BIAS;

static q15_t fc2_wt[FC2_IN_DIM*FC2_OUT_DIM] = FC2_WT;
static q15_t fc2_bias[FC2_OUT_DIM] = FC2_BIAS;

q15_t reference_fc1_output[100] = FC1; 
q15_t reference_fc2_output[10] = FC2;

q15_t col_buffer[576];
//q15_t scratch_buffer[65408*2];
q15_t scratch_buffer[28*28];

q15_t input_data[784] = INPUT_DATA;
q15_t output_data[784];



void run_inference(void)
{
    q15_t* buffer1 = scratch_buffer;
    q15_t* buffer2 = buffer1 + 100; 
    int i;
    arm_fully_connected_q15_opt(input_data, fc1_wt, FC1_IN_DIM, FC1_OUT_DIM, FC1_BIAS_LSHIFT, FC1_OUT_RSHIFT, fc1_bias, buffer1, (q15_t*)col_buffer);
    //printf("fc1 output\r\n"); 
    //for (i = 0; i < 100; i++)
    //{
    //    printf("%d:::%d\r\n", buffer1[i], reference_fc1_output[i]);
    //}

    arm_relu_q15(buffer1, FC1_OUT_DIM);


    printf("fc2 output\r\n"); 
    arm_fully_connected_q15_opt(buffer1, fc2_wt, FC2_IN_DIM, FC2_OUT_DIM, FC2_BIAS_LSHIFT, FC2_OUT_RSHIFT, fc2_bias, output_data, (q15_t*)col_buffer);
    for (int i = 0; i < 10; i++)
    {
        printf("%d:::%d\r\n", output_data[i], reference_fc2_output[i]);
    }

}