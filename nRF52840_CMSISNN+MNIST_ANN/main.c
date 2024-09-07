#include <stdint.h>
#include <string.h>
#include "nordic_common.h"
#include "nrf.h"

#include "app_timer.h"
#include "app_uart.h"
#include "nrf_pwr_mgmt.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "arm_nnfunctions.h"

#include "parameter.h"
#include "sample_input_output.h"
#include "weight.h"

/**@brief Function for initializing the nrf log module.
 */
static void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}


/*****************************************************/
/* NN Stuff                                           / 
/*****************************************************/




/**@brief Application main function.
 */
int main(void)
{
    bool erase_bonds;
    log_init();
    printf("\r\Application started.\r\n");


    q15_t input_data[784] = INPUT_DATA;
    q15_t output_data[10]; 


    static q15_t fc1_wt[FC1_IN_DIM*FC1_OUT_DIM] = FC1_WT;
    static q15_t fc1_bias[FC1_OUT_DIM] = FC1_BIAS;

    static q15_t fc2_wt[FC2_IN_DIM*FC2_OUT_DIM] = FC2_WT;
    static q15_t fc2_bias[FC2_OUT_DIM] = FC2_BIAS;

    q15_t reference_fc1_output[100] = FC1; 
    q15_t reference_fc2_output[10] = FC2;

    q15_t col_buffer[576];
    q15_t scratch_buffer[65408*2];
    int default_size = 65408;


    q15_t* buffer1 = scratch_buffer;
    q15_t* buffer2 = buffer1 + 65408;
    
    arm_fully_connected_q15_opt(input_data, fc1_wt, FC1_IN_DIM, FC1_OUT_DIM, FC1_BIAS_LSHIFT, FC1_OUT_RSHIFT, fc1_bias, buffer1, (q15_t*)col_buffer);
    arm_relu_q15(buffer1, FC1_OUT_DIM);
    arm_fully_connected_q15_opt(buffer1, fc2_wt, FC2_IN_DIM, FC2_OUT_DIM, FC2_BIAS_LSHIFT, FC2_OUT_RSHIFT, fc2_bias, output_data, (q15_t*)col_buffer);

    // Enter main loop.
    for (;;)
    {
        
    }
}


/**
 * @}
 */
