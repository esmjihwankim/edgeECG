#include "main.h"
#define BUTTON_INF    11
#define DEBOUNCE_MS 150

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


void set_button(void)
{
    nrf_gpio_cfg_input(BUTTON_1, NRF_GPIO_PIN_PULLUP);
}


/**@brief Application main function.
 */
int main(void)
{
    uint32_t err_code;
    bool erase_bonds;

    // Initialize basic and wireless functionalities
    uart_init();
    log_init();
    timers_init();
    buttons_leds_init(&erase_bonds);
    power_management_init();

    //saadc_sampling_event_init();
    //saadc_init();
    //saadc_sampling_event_enable();

    //ble_stack_init();
    //gap_params_init();
    //gatt_init();
    //services_init();
    //advertising_init();
    //conn_params_init();
    //set_button();
    //advertising_start();
    
    
    printf("\r\nApplication started.\r\n");
  
    // Enter main loop.
    volatile uint32_t count = 0; 
    volatile int flag = 0;

    for (;;)
    {
        //idle_state_handle();

        if(nrf_gpio_pin_read(BUTTON_INF)==0)
        {
            flag = 1;
            while(nrf_gpio_pin_read(BUTTON_INF)==0);
        }

        if(flag == 1){
            CoreDebug->DEMCR |= 0x01000000; 
            DWT->CYCCNT = 0;
            DWT->CTRL |= 0x1;
            run_inference();
            count = DWT->CYCCNT;
            flag = 0;
            printf("Cycle count::%d\r\n", count);
            count = 0;
        }
    }
}


/**
 * @}
 */
