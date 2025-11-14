#ifndef FREERTOS_TASKS_H
#define FREERTOS_TASKS_H

#include <stdint.h>
#include "bmp280.h"

// data structures sent between tasks
typedef struct {
    float ax, ay, az;
    float gx, gy, gz;
    float temp;
} mpu_data_t;

typedef struct {
    uint32_t red;
    uint32_t ir;
    float ratio;
} max30102_data_t;

typedef struct {
    float temp;
    float pressure;
    float altitude;
} bmp_data_t;

// handles (extern so main.c can use if needed)
extern TaskHandle_t xMPUTaskHandle;
extern TaskHandle_t xMAX30102TaskHandle;
extern TaskHandle_t xBMP280TaskHandle;
extern TaskHandle_t xLCDTaskHandle;
extern TaskHandle_t xHeartbeatTaskHandle;

// queues
extern QueueHandle_t qMPU;
extern QueueHandle_t qMAX30102;
extern QueueHandle_t qBMP280;

// initialization function
void FREERTOS_TasksInit(void);

#endif // FREERTOS_TASKS_H
