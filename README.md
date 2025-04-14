# RTOS-Based Robotic Car (CG2271 AY24/25 S2 Project)

This project implements an RTOS-based robotic car controlled via **PS4/PS5 controllers over Bluetooth**. Built on an **ESP32** platform using **FreeRTOS/CMSIS-RTOS2**, the system integrates real-time motor, LED, and audio control. The design incorporates two distinct driving modes and a weight distribution that places most of the weight at the front, enhancing the robot’s turning performance. Our robot set a record with a fastest challenge run time of **18.49 seconds**.

![alt text](https://github.com/CG2271-Project/CG2271-Final-Project/blob/main/Images/Left%20View.jpg)
![alt text](https://github.com/CG2271-Project/CG2271-Final-Project/blob/main/Images/Top%20View.jpg)

## Team Members

- **Edwin Hein Tun** - ESP32 Controller Program
- **Liu Jia Quan** - LED
- **Low Jun Chen** - Motor Control and LED
- **Ng Chee Fong** - RTOS and UART
- **Viswanathan Ravisankar** - Buzzer and Main Driver

## Features

### Motor Control
- **Driving Modes:**
  - **Normal Mode:**  
    Enables smooth navigation with curved and single-wheel turns. The front-concentrated weight distribution aids in better rotation when performing a one-wheel turn.
  - **Tank Mode:**  
    Allows on-the-spot two-wheel turns for precise maneuvering in tight spaces.
- Moves in all four directions: Forward, Backward, Left, and Right.
- Automatically stops if no command is received.

### LED Control
- **Front LEDs (8 Green):**
  - Sequential "running" animation while the robot is in motion.
  - All LEDs remain continuously lit when the robot is stationary.
- **Rear LEDs (8 Red):**
  - Flash at a rate of 500 ms ON/500 ms OFF when moving.
  - Flash at a faster rate of 250 ms ON/250 ms OFF when stationary.

### Audio Playback
- Continuous playback of a tune during operation.
- A unique completion tone is played at the end of the challenge run.

---

## Controller Support

The project uses the [Bluepad32](https://github.com/ricardoquesada/bluepad32) library to support **PS4 and PS5 controllers** over Bluetooth. The controller allows you to:
- Adjust speed via the D-pad.
- Control movement and turning using the joysticks and triggers.
- Toggle between driving modes (Tank Mode and Normal Mode) and other LED/audio states using dedicated buttons.

---

## RTOS Architecture Overview

The system’s architecture uses FreeRTOS to manage multiple tasks that run concurrently:
- **Brain Task:**  
  Processes controller inputs and triggers subsequent actions.
- **Motor Task:**  
  Manages movement based on commands and drives the motors using the **DRV8833 motor driver**.
- **LED Task:**  
  Updates the LED animations according to the robot’s movement and status.
- **Sound Task:**  
  Handles the continuous audio playback, including the end-of-run tone.

Tasks synchronize via semaphores to ensure smooth and conflict-free operation.

---

## Hardware Components

- **Microcontroller:** ESP32
- **Motor Driver:** DRV8833
- **Motors & Chassis:** DC motors with a robust chassis design
- **LEDs:** 8 Green (front) and 8 Red (rear)
- **Controller:** PS4/PS5 Bluetooth Controller
- **Audio:** Piezo Buzzer

---

## Video Submission
- To be uploaded soon!
