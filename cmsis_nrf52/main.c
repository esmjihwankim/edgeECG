#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"

#include "arm_math.h"
#include "arm_nnfunctions.h"

#include "inputs.h"
#include "weights.h"
#include "parameters.h"

#include "libcmsisnn.a"

/**
 * @brief Function for application main entry.
 */

 
#define DIM_HISTORY 32
#define DIM_INPUT 32
#define DIM_VEC 64

#define USE_X4

#ifndef USE_X4
static q7_t update_gate_weights[DIM_VEC * DIM_HISTORY] = UPDATE_GATE_WEIGHT_X2;
static q7_t reset_gate_weights[DIM_VEC * DIM_HISTORY] = RESET_GATE_WEIGHT_X2;
static q7_t hidden_state_weights[DIM_VEC * DIM_HISTORY] = HIDDEN_STATE_WEIGHT_X2;
#else
static q7_t update_gate_weights[DIM_VEC * DIM_HISTORY] = UPDATE_GATE_WEIGHT_X4;
static q7_t reset_gate_weights[DIM_VEC * DIM_HISTORY] = RESET_GATE_WEIGHT_X4;
static q7_t hidden_state_weights[DIM_VEC * DIM_HISTORY] = HIDDEN_STATE_WEIGHT_X4;
#endif

static q7_t update_gate_bias[DIM_HISTORY] = UPDATE_GATE_BIAS;
static q7_t reset_gate_bias[DIM_HISTORY] = RESET_GATE_BIAS;
static q7_t hidden_state_bias[DIM_HISTORY] = HIDDEN_STATE_BIAS;

static q15_t test_input1[DIM_INPUT] = INPUT_DATA1;
static q15_t test_input2[DIM_INPUT] = INPUT_DATA2; 
static q15_t test_history[DIM_HISTORY] = HISTORY_DATA; 

q15_t scratch_buffer[DIM_HISTORY * 4 + DIM_INPUT]; 

int main(void)
{
    int input_size = DIM_INPUT; 
    int history_size = DIM_HISTORY; 
    
    arm_copy_q15(test_input1, scratch_buffer + history_size, input_size); 
    
}

/**
 *@}
 **/
