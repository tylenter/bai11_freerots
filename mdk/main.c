#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"

// LED pins
#define LED1_PIN GPIO_Pin_0
#define LED2_PIN GPIO_Pin_1
#define LED3_PIN GPIO_Pin_2
#define LED_PORT GPIOA

// Prototypes
void GPIO_Config(void);
void LED1_Task(void *pvParameters);
void LED2_Task(void *pvParameters);
void LED3_Task(void *pvParameters);

int main(void)
{
    SystemInit();
    GPIO_Config();

    xTaskCreate(LED1_Task, "LED1_3Hz", 128, NULL, 1, NULL);
    xTaskCreate(LED2_Task, "LED2_10Hz", 128, NULL, 2, NULL);
    xTaskCreate(LED3_Task, "LED3_25Hz", 128, NULL, 3, NULL);

    vTaskStartScheduler();

    while(1);
}

void GPIO_Config(void)
{
    GPIO_InitTypeDef gpio;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    gpio.GPIO_Pin = LED1_PIN | LED2_PIN | LED3_PIN;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_PORT, &gpio);

    GPIO_ResetBits(LED_PORT, LED1_PIN | LED2_PIN | LED3_PIN);
}

// LED1 – 3Hz
void LED1_Task(void *pvParameters)
{
    
    const TickType_t xDelay = pdMS_TO_TICKS(167); 
    
    (void) pvParameters;
    for(;;)
    {
        if (GPIO_ReadOutputDataBit(LED_PORT, LED1_PIN) == Bit_RESET)
        {
            GPIO_SetBits(LED_PORT, LED1_PIN);
        }
        else
        {
            GPIO_ResetBits(LED_PORT, LED1_PIN);
        }
        vTaskDelay(xDelay);
    }
}

// LED2 – 10Hz
void LED2_Task(void *pvParameters)
{
    const TickType_t xDelay = pdMS_TO_TICKS(50);
    
    (void) pvParameters;
    for(;;)
    {
        if (GPIO_ReadOutputDataBit(LED_PORT, LED2_PIN) == Bit_RESET)
        {
            GPIO_SetBits(LED_PORT, LED2_PIN);
        }
        else
        {
            GPIO_ResetBits(LED_PORT, LED2_PIN);
        }
        vTaskDelay(xDelay);
    }
}

// LED3 – 25Hz
void LED3_Task(void *pvParameters)
{
    const TickType_t xDelay = pdMS_TO_TICKS(20); 
    
    (void) pvParameters;
    for(;;)
    {
        
        if (GPIO_ReadOutputDataBit(LED_PORT, LED3_PIN) == Bit_RESET)
        {
            GPIO_SetBits(LED_PORT, LED3_PIN);
        }
        else
        {
            GPIO_ResetBits(LED_PORT, LED3_PIN);
        }
        vTaskDelay(xDelay);
    }
}
