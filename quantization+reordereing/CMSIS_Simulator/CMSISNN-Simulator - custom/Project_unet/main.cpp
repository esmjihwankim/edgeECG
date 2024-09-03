#include "nn.h"
#include "sample_input_output.h"
#include <iostream>
using namespace std;

void main() {
	q15_t test_input[784] = INPUT_DATA;
	q15_t test_output[10] = FC2;
	q15_t output_buffer[10];

	time_t begin_t = clock();
	run_nn(test_input, output_buffer);
	time_t finish_t = clock();
	cout << "total_time: " << (double)(finish_t - begin_t) / CLOCKS_PER_SEC << "s" << endl;
	cout << "\n\n/**********FINAL OUTPUT COMPARISON************/" << endl;
	for (int i = 0; i < 10; i++) {
		cout << "TEST OUTPUT::" << test_output[i] << "\n" << "OUTPUT BUFFER::" << output_buffer[i] << "\n" << endl;
	}

	system("pause");
}