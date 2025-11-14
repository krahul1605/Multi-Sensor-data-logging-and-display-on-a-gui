Multi Sensor Data Logging and Display Using Python GUI
1.Introduction and Problem Definition 

This project aims to build a multi-sensor embedded telemetry platform capable of acquiring, processing, and visualizing real time data.
The system integrates three major sensors MPU6050 (Inertial Measurement Unit), MAX30102(Heart Rate & SpO2), and BMP280(Environmental Sensor) using an STM32 microcontroller.
An aviation-style GUI was developed in Python using Tkinter, which includes an artificial horizon similar to those found in aircraft cockpit displays.
The GUI receives continuous sensor data via UART and visualizes roll, pitch, acceleration, heart rate, SpO2, temperature, pressure, and altitude.

System Requirements: - 
oReal-time multi-sensor data acquisition
oDeterministic timing using FreeRTOS
oAviation-style real-time GUI
oUART-based communication with error handling
oStable heart rate 
oSpO2 computation

2.System Design and Architecture 
The system architecture follows a modular design where each sensor is managed by a             dedicated FreeRTOS task. Data is transferred throughqueues and displayed on an ST7735 TFT display as well as streamed to the Python GUI.
Microcontroller Peripherals Used:
I2C1 – MPU6050, MAX30102, BMP280
SPI1 – ST7735 TFT LCD 
UART2 – Real-time telemetry stream
TIM4 – Periodic time base for tasks
GPIO – Status LED
Functional Blocks:
Data Acquisition Layer (sensors)
FreeRTOS Task Scheduling Layer
Queue-based Data Transfer Layer
LCD Display Layer
UART Communication Layer
Python GUI Visualization Layer

3.Implementation and RTOS Integration 
FreeRTOS tasks were created for MPU6050, MAX30102, BMP280, LCD updates, and heartbeat status. Queues ensure non-blocking inter-task data transfer. The Python GUI integrates gyro data for roll and pitch computation, generating an artificial horizon. Heart rate and SpO2 estimation use peak detection and ratio analysis.
Task Structure
MPU Task – Reads ax/ay/az & gx/gy/gz at 1 Hz
MAX30102 Task – Reads IR/RED values and ratio at 1 Hz
BMP280 Task – Reads temperature, pressure, altitude at 3 Hz
LCD Task – Updates ST7735 screen at 1 Hz 
Heartbeat Task – Toggles LED at 2 Hz

RTOS Features Used:
Task scheduling 
Queues for inter-task data transfer
Deterministic execution periods
Non-blocking I2C UART

Python GUI:
The Python GUI uses Tkinter Canvas for an artificial horizon display. Integrated gyro data is used to compute roll and pitch.
