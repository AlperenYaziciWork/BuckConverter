
#include "bsp_gpio.h"
#include "stm32f4xx_hal_gpio.h"


const gpio_pin_cfg_t PinCfgContainer[] = 
{
    {.Port = GPIOA , .Pin = GPIO_PIN_8 , .Mode = GPIO_MODE_AF_PP , .Pull = GPIO_NOPULL, .Speed = GPIO_SPEED_FREQ_LOW  }, // BUCK_PWM_OUT_PIN_ID

};
