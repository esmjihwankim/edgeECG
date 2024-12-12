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



int ssat(int a, const int bit) {
	int clip_value = a;
	if (a > (0x1 << (bit - 1))-1) {
		clip_value = (0x1 << (bit - 1)) - 1;
	}
	else if (a < -(0x1 << (bit - 1))) {
		clip_value = -(0x1 << (bit - 1));
	}
	return clip_value;
};


void arm_fully_connected_q15_ref(const q15_t * pV,  // pointer to vector
	const q15_t * pM,  // pointer to matrix
	const uint16_t dim_vec,    // length of the vector
	const uint16_t num_of_rows,    // numCol of A
	const uint16_t bias_shift, // amount of left-shift for bias
	const uint16_t out_shift,  // amount of right-shift for output
	const q15_t * bias, q15_t * pOut,  // output operand
	q15_t * vec_buffer)
{
	for (int i = 0; i < num_of_rows; i++)
	{

		int       ip_out = bias[i] << bias_shift;
		for (int j = 0; j < dim_vec; j++)
		{
			ip_out += pV[j] * pM[i * dim_vec + j];
		}
		pOut[i] = (q15_t)ssat((ip_out >> out_shift), 16);
	}
}


void arm_relu_q15_ref(q15_t * data, uint16_t size)
{
	uint16_t  i;

	for (i = 0; i < size; i++)
	{
		if (data[i] < 0)
			data[i] = 0;
	}
}



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