#include "nn.h"
#include "sample_input_output.h"

using namespace std;

static q15_t b1_conv1_wt[B1_CONV1_IN_CH*B1_CONV1_KER_DIM_X*B1_CONV1_KER_DIM_Y*B1_CONV1_OUT_CH] = CONV1_WT;
static q15_t b1_conv1_bias[B1_CONV1_OUT_CH] = CONV1_BIAS;

static q15_t fc1_wt[FC1_IN_DIM*FC1_OUT_DIM] = FC1_WT;
static q15_t fc1_bias[FC1_OUT_DIM] = FC1_BIAS;

static q15_t fc2_wt[FC2_IN_DIM*FC2_OUT_DIM] = FC2_WT;
static q15_t fc2_bias[FC2_OUT_DIM] = FC2_BIAS;


q15_t reference_conv1_output[784 * 4] = CONV1;
q15_t reference_fc1_output[20] = FC1; 
q15_t reference_fc2_output[10] = FC2;

q15_t col_buffer[576];
q15_t scratch_buffer[65408*2];
int default_size = 65408;

void run_nn(q15_t* input_data, q15_t* output_data) {
	q15_t* buffer1 = scratch_buffer;
	q15_t* buffer2 = buffer1 + 65408;
	int j = 0; 

	// input -> buffer1
	arm_convolve_HWC_q15_fast_nonsquare(input_data, B1_CONV1_IN_DIM_X, B1_CONV1_IN_DIM_Y, B1_CONV1_IN_CH, b1_conv1_wt, B1_CONV1_OUT_CH, B1_CONV1_KER_DIM_X, B1_CONV1_KER_DIM_Y, B1_CONV1_PAD_X, B1_CONV1_PAD_Y, B1_CONV1_STRIDE_X, B1_CONV1_STRIDE_Y, b1_conv1_bias, CONV1_BIAS_LSHIFT, CONV1_OUT_RSHIFT, buffer1, B1_CONV1_OUT_DIM_X, B1_CONV1_OUT_DIM_Y, (q15_t*)col_buffer, NULL);
	// Check Conv Output
	cout << "CONV OUTPUT COMPARISON :: ";
	j = 0;
	for (int i = 0; i < 784*4; i++) {
		if (reference_conv1_output[i] != buffer1[i]) {
			cout << buffer1[i] << ' ';
			j++; 
		}
	}
	if (j == 0) cout << "PERFECT MATCH";
	cout << '\n' << endl;
	
	// buffer1 -> buffer1 
	arm_relu_q15(buffer1, B1_CONV1_RELU_OUT_CH*B1_CONV1_RELU_OUT_DIM_X*B1_CONV1_RELU_OUT_DIM_Y);
	/*cout << "RELU OUTPUT COMPARISON :: ";
	j = 0;
	for (int i = 0; i < 784 * 4; i++) {
		if (reference_conv1_output[i] != buffer1[i]) {
			cout << buffer1[i] << ' ';
			j++;
		}
	}
	if (j == 0) cout << "PERFECT MATCH";
	cout << '\n' << endl;*/

	// buffer1 -> buffer1 
	local_maxpool_q15_HWC(buffer1, B1_POOL_IN_DIM_X, B1_POOL_IN_DIM_Y, B1_POOL_IN_CH, B1_POOL_KER_DIM_X, B1_POOL_KER_DIM_Y, B1_POOL_PAD_X, B1_POOL_PAD_Y, B1_POOL_STRIDE_X, B1_POOL_STRIDE_Y, B1_POOL_OUT_DIM_X, B1_POOL_OUT_DIM_Y, NULL, buffer2);

	// buffer2 -> buffer 1
	arm_fully_connected_q15_ref(buffer2, fc1_wt, FC1_IN_DIM, FC1_OUT_DIM, FC1_BIAS_LSHIFT, FC1_OUT_RSHIFT, fc1_bias, buffer1, (q15_t*)col_buffer);
	cout << "FC1 OUTPUT COMPARISON:: ";
	j = 0;
	for (int i = 0; i < 20; i++) {
		if (reference_fc1_output[i] != buffer1[i]) {
			cout << buffer1[i] << ' ';
			j++; 
		}
	}
	if (j == 0) cout << "PERFECT MATCH";
	cout << '\n' << endl;

	arm_relu_q15(buffer1, FC1_OUT_DIM);

	arm_fully_connected_q15_ref(buffer1, fc2_wt, FC2_IN_DIM, FC2_OUT_DIM, FC2_BIAS_LSHIFT, FC2_OUT_RSHIFT, fc2_bias, output_data, (q15_t*)col_buffer);
	
	/*
	output data comparison is in main function
	*/ 
}