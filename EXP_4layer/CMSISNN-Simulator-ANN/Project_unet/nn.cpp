#include "nn.h"
#include "weight.h"
#include "sample_input_output.h"

using namespace std;

static q15_t fc1_wt[FC1_IN_DIM*FC1_OUT_DIM] = FC1_WT;
static q15_t fc1_bias[FC1_OUT_DIM] = FC1_BIAS;

static q15_t fc2_wt[FC2_IN_DIM*FC2_OUT_DIM] = FC2_WT;
static q15_t fc2_bias[FC2_OUT_DIM] = FC2_BIAS;

q15_t reference_fc1_output[100] = FC1; 
q15_t reference_fc2_output[10] = FC2;

q15_t col_buffer[576];
q15_t scratch_buffer[65408*2];
int default_size = 65408;

void run_nn(q15_t* input_data, q15_t* output_data) {
	q15_t* buffer1 = scratch_buffer;
	q15_t* buffer2 = buffer1 + 65408;
	int j = 0; 

	// input -> buffer 1
	arm_fully_connected_q15_ref(input_data, fc1_wt, FC1_IN_DIM, FC1_OUT_DIM, FC1_BIAS_LSHIFT, FC1_OUT_RSHIFT, fc1_bias, buffer1, (q15_t*)col_buffer);
	cout << "FC1 OUTPUT COMPARISON - Reference vs Output::\n";
	j = 0;
	for (int i = 0; i < 100; i++) {
		cout << reference_fc1_output[i] << "  " << buffer1[i] << '\n';
		j++;
	}
	cout << "TOTAL OF " << j << '\n' << endl;

	arm_relu_q15(buffer1, FC1_OUT_DIM);

	// buffer1 -> output
	arm_fully_connected_q15_ref(buffer1, fc2_wt, FC2_IN_DIM, FC2_OUT_DIM, FC2_BIAS_LSHIFT, FC2_OUT_RSHIFT, fc2_bias, output_data, (q15_t*)col_buffer);
	cout << "FC2 OUTPUT COMPARISON - Reference vs Output::\n";
	j = 0;
	for (int i = 0; i < 10; i++) {
		cout << reference_fc2_output[i] << "  " << output_data[i] << '\n';
		j++;
	}
	cout << "TOTAL OF " << j << '\n' << endl;


	/*
	output data comparison is in the main function
	*/ 
}