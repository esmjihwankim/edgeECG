#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"

#include "arm_math.h"
#include "arm_nnfunctions.h"

#include "inputs.h"
#include "weights.h"
#include "parameters.h"


/**
 * @brief Function for application main entry.
 */

static q7_t conv1_wt[(CONV1_PADDING + CONV1_STRIDE) * CONV1_IM_DIM * CONV1_OUT_CH] = CONV1_WT;
static q7_t conv1_bias[CONV1_OUT_CH] = CONV1_BIAS;


q7_t col_buffer[2 * 5 * 5 * 32 * 2]; 
q7_t scratch_buffer [45 * 45 * 32 * 2]; 

uint8_t image_data[CONV1_IM_CH * CONV1_IM_DIM * CONV1_IM_DIM] = IMG_DATA; 

int main(void)
{
    q7_t *img_buffer1 = scratch_buffer; 
    q7_t *img_buffer2 = img_buffer1 + 45 * 45 * 32; 

    //int mean_data = INPUT_MEAN_SHIFT;
    //unsigned int scale_data = INPUT_RIGHT_SHIFT;
    //for (int i=0;i<45 * 45; i+=1) {
    //  img_buffer2[i] =   (q7_t)__SSAT( ((((int)image_data[i]   - mean_data)<<7) + (0x1<<(scale_data-1))) >> scale_data, 8);
    //} 

    //arm_convolve_HWC_q7_fast(img_buffer2, CONV1_IM_DIM, CONV1_IM_CH, conv1_wt, CONV1_OUT_CH, CONV1_KER_DIM, CONV1_PADDING,
    //                          CONV1_STRIDE, conv1_bias, CONV1_BIAS_LSHIFT, CONV1_OUT_RSHIFT, img_buffer1, CONV1_OUT_DIM,
    //                          (q15_t *) col_buffer, NULL);
    
}

/**
 *@}
 **/
