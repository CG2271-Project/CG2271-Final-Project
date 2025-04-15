# RTOS-Based Robotic Car (CG2271 AY24/25 S2 Project)

This project implements an RTOS-based robotic car controlled via **PS4/PS5 controllers over Bluetooth**. The main processing is handled by the **NXP KL25Z** (MKL25Z4) microcontroller, while an **ESP module** provides Bluetooth connectivity—transmitting controller commands via UART at 9600 baud to the KL25Z. The system integrates real-time control of motors, LEDs, and audio. It features two distinct driving modes and a weight distribution configuration that places most of the mass at the front, significantly enhancing turning performance. Our robot set a run time of **18.49 seconds**.

![Left View](https://github.com/CG2271-Project/CG2271-Final-Project/blob/main/Images/Left%20View.jpg)
![Top View](https://github.com/CG2271-Project/CG2271-Final-Project/blob/main/Images/Top%20View.jpg)

## Team Members

- **Edwin Hein Tun** - ESP Module (Controller Program and UART Integration)
- **Liu Jia Quan** - LED Programming
- **Low Jun Chen** - Motor Control and LED Integration
- **Ng Chee Fong** - RTOS and UART Communication
- **Viswanathan Ravisankar** - Buzzer and Main Driver Functions

## Features

### Motor Control
- **Driving Modes:**
  - **Normal Mode:**  
    Allows smooth navigation with curved and single-wheel turns. The forward-weighted design aids in better rotation during one-wheel turns.
  - **Tank Mode:**  
    Enables on-the-spot two-wheel turns for precise maneuvering in tight spaces.
- Supports movement in all four directions (Forward, Backward, Left, and Right).
- Automatically stops if no command is received.

### LED Control
- **Front LEDs (8 Green):**
  - Display a sequential “running” animation while the robot is in motion.
  - Remain fully lit when the robot is stationary.
- **Rear LEDs (8 Red):**
  - Flash at a rate of 500 ms ON/500 ms OFF when moving.
  - Flash at a faster rate of 250 ms ON/250 ms OFF when stationary.

### Audio Playback
- Continuous playback of a tune during operation.
- A unique completion tone is played at the end of the challenge run.

---

## Controller Support

The project uses the [Bluepad32](https://github.com/ricardoquesada/bluepad32) library to enable **PS4 and PS5 controller** support via Bluetooth. The controller allows you to:
- Adjust speed via the D-pad.
- Control movement and turning using joysticks and triggers.
- Toggle between driving modes (Tank Mode and Normal Mode) and change LED/audio states using dedicated buttons.

---

## RTOS Architecture Overview

The system’s architecture is built on **FreeRTOS/CMSIS-RTOS2**, which manages multiple concurrent tasks:
- **Brain Task:**  
  Processes incoming controller commands.
- **Motor Task:**  
  Manages movement based on commands and drives the motors through the **DRV8833 motor driver**.
- **LED Task:**  
  Updates the LED animations according to the robot’s movement and status.
- **Sound Task:**  
  Handles continuous audio playback, including the finish tone.

Tasks synchronize using semaphores to ensure smooth and conflict-free operation.

---

## Hardware Components

- **Main Microcontroller:** NXP KL25Z (MKL25Z4)
- **Communication Module:** ESP module (for Bluetooth connectivity, transmitting at 9600 baud via UART)
- **Motor Driver:** DRV8833
- **Motors & Chassis:** DC motors with a robust chassis design
- **LEDs:** 8 Green (front) and 8 Red (rear)
- **Controller:** PS4/PS5 Bluetooth Controller via the ESP module
- **Audio:** Piezo Buzzer

---

## Video Submission
- Watch our detailed project walkthrough and demonstration on [YouTube](https://www.youtube.com/watch?v=8EuyOW675yk)!
<!-- Embedded YouTube Video via clickable thumbnail -->
[![CG2271 RTOS-Based Robotic Car Project Video](https://img.youtube.com/vi/8EuyOW675yk/0.jpg)](https://www.youtube.com/watch?v=8EuyOW675yk)
---
