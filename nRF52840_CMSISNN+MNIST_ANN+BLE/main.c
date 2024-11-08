#include "main.h"


/**@brief Function for initializing the nrf log module.
 */
static void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}


/**@brief Function for initializing power management.
 */
static void power_management_init(void)
{
    ret_code_t err_code;
    err_code = nrf_pwr_mgmt_init();
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for handling the idle state (main loop).
 *
 * @details If there is no pending log operation, then sleep until next the next event occurs.
 */
void idle_state_handle(void)
{
    if (NRF_LOG_PROCESS() == false)
    {
        nrf_pwr_mgmt_run();
    }
}


/**@brief Application main function.
 */
int main(void)
{
    bool erase_bonds;


    // Initialize basic and wireless functionalities
    uart_init();
    log_init();
    timers_init();
    buttons_leds_init(&erase_bonds);
    power_management_init();
    ble_stack_init();
    gap_params_init();
    gatt_init();
    services_init();
    advertising_init();
    conn_params_init();

    saadc_sampling_event_init();
    saadc_init();
    saadc_sampling_event_enable();

    advertising_start();
    
    
    printf("\r\nAdvertising started.\r\n");
    
    // Inference using trained neural network 
    run_inference();

    // Enter main loop.
    for (;;)
    {
        //idle_state_handle();
    }


}


/**
 * @}
 */
