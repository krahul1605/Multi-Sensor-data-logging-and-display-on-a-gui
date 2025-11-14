/* main.c - FreeRTOS version (replace your existing main) */
#include "main.h"
#include "freertos_tasks.h"
#include "st7735.h"
#include "max30102.h"
#include "bmp280.h"
#include <stdio.h>

/* Externals from CubeMX-generated peripheral init */
extern I2C_HandleTypeDef hi2c1;
extern SPI_HandleTypeDef hspi1;
extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart2;

/* Globals (reuse from your original code) */
BMP280_HandleTypedef bmp280;
uint8_t max30102_ready = 0;
uint8_t bmp280_ready = 0;
uint8_t mpu6050_ready = 0;
uint8_t lcd_ready = 0;

/* Forward prototypes for your original functions */
void SystemClock_Config(void);
int _write(int file, char *ptr, int len);
void MPU6050_Init(void);
int MAX30102_Init(I2C_HandleTypeDef *hi2c);
int bmp280_init(BMP280_HandleTypedef *dev);

/* main */
int main(void)
{
    HAL_Init();
    SystemClock_Config();

    /* Initialize peripherals */
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_I2C1_Init();
    MX_TIM4_Init();
    MX_SPI1_Init();

    /* Basic prints */
    printf("\r\n========================================\r\n");
    printf("  Triple Sensor System - FreeRTOS\r\n");
    printf("========================================\r\n\r\n");

    /* Initialize LCD */
    printf("Initializing ST7735 LCD...\r\n");
    ST7735_Init();
    ST7735_SetRotation(1);
    lcd_ready = 1;
    printf("  LCD Initialization: SUCCESS\r\n\r\n");

    /* Display header and prepare */
    LCD_DisplayHeader();

    /* Initialize sensors (synchronously once before tasks start) */
    printf("Initializing MPU6050...\r\n");
    MPU6050_Init(); // sets mpu6050_ready

    /* MAX30102 init */
    printf("Checking MAX30102... ");
    uint8_t part_id = 0;
    if (HAL_I2C_Mem_Read(&hi2c1, 0xAE, 0xFF, 1, &part_id, 1, 1000) == HAL_OK) {
        printf("I2C OK, part 0x%02X\n", part_id);
        if (part_id == 0x15) {
            if (MAX30102_Init(&hi2c1) == 0) {
                max30102_ready = 1;
                printf("MAX30102 init success\n");
            }
        }
    } else {
        printf("MAX30102 I2C failed\n");
    }

    /* BMP280 init */
    bmp280.i2c = &hi2c1;
    bmp280.addr = BMP280_I2C_ADDR_PRIM;
    if (bmp280_init(&bmp280) == BMP280_OK) {
        bmp280_ready = 1;
        printf("BMP280 init success\n");
    } else {
        printf("BMP280 init failed\n");
    }

    /* Show sensor status on LCD */
    LCD_DisplaySensorStatus();

    /* Initialize FreeRTOS objects and create tasks */
    FREERTOS_TasksInit();

    /* Start scheduler */
    vTaskStartScheduler();

    /* Should never reach here */
    for(;;);
}

/* Retarget printf to UART */
int _write(int file, char *ptr, int len) {
    HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
    return len;
}

/* Keep your SystemClock_Config(), Error_Handler() and other callbacks as they were */
