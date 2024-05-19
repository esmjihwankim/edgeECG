#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"

#define ARM_MATH_CM4
#include "arm_math.h"
#include "arm_nnfunctions.h"

#define NNMULT_DIM 128 

int main(void)
{
    
    q7_t test1[NNMULT_DIM * 2] = {0,};
    q7_t test2[NNMULT_DIM * 2] = {0,};
    q7_t test3[NNMULT_DIM * 2] = {0,};
    q7_t test4[NNMULT_DIM * 2] = {0,};
    
    q7_t * mult_out_q7 = test3;
    q7_t * mult_ref_q7 = test3 + NNMULT_DIM; 

    arm_nn_mult_q7(test1, test1+NNMULT_DIM, mult_out_q7, 5, NNMULT_DIM);
    
    
}

