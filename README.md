# 🚗 Arduino UNO Prototype Projects 

This repository contains **two Arduino UNO–based robotic projects** built using **ultrasonic sensors and an L298N motor driver**.  
All three projects use the **same hardware setup**, and only the **control logic (code)** changes.

---

## 📌 Projects Included

1. **Obstacle Avoidance Prototype**
2. **Object Following Prototype**

---

## 🧰 Common Hardware Components (Same for 2 Projects)

- Arduino UNO  
- L298N Motor Driver Module  
- DC Motors with Robot Chassis  
- Ultrasonic Sensors × 3 (HC-SR04)  
- Li-ion Batteries × 2  
- Breadboard  
- Jumper Wires  

---

## 💻 Software Requirements

- Arduino IDE  
- USB cable for Arduino UNO  
- No external libraries required  

---

## 🔌 Hardware Connections

### 🔹 Ultrasonic Sensor Connections

| Sensor Position | Trigger Pin | Echo Pin |
|-----------------|------------|----------|
| Front / Center  | D2         | D3       |
| Left            | D7 or D9   | D8 or D10|
| Right           | D9 or D7   | D10 or D8|

> Exact left/right usage depends on project logic.

---

### 🔹 L298N Motor Driver → Arduino UNO

| L298N Pin | Arduino Pin |
|----------|-------------|
| IN1      | D11 |
| IN2      | D12 |
| IN3      | D13 |
| IN4      | D4  |
| ENA      | D5  |
| ENB      | D6  |

---

### 🔹 Power Connections

- L298N **12V** → Li-ion Battery (+)
- L298N **GND** → Battery (–)
- Arduino **GND** → L298N **GND**
- Motors → L298N **OUT1–OUT4**

⚠️ **All grounds must be connected together**

---

## 🤖 1. Obstacle Avoidance Robot

### 🔍 Description
The robot detects obstacles using **three ultrasonic sensors** and automatically changes direction to avoid collisions.

### 🧠 Working Logic
- Obstacle in front → turn left or right
- Obstacle on left → turn right
- Obstacle on right → turn left
- No obstacle → move forward

### 🎯 Features
- Continuous obstacle detection  
- Smart turning logic  
- PWM-based speed control  

---

## 🤖 2. Object Following Robot

### 🔍 Description
The robot follows a nearby object (hand or object) using **distance-based speed control**.

### 🧠 Working Logic
- Object in front → move straight
- Object on left → curve left
- Object on right → curve right
- No object → stop

### 🎯 Features
- Dynamic curve movement  
- Smooth speed adjustment  
- Stable following behavior  

---


## 🚀 How to Upload Code

1. Open **Arduino IDE**
2. Select **Board → Arduino UNO**
3. Select the correct **COM Port**
4. Open the required `.ino` file
5. Click **Upload**

---

## 📌 Notes

- Same hardware is used for 2 projects
- Only the program logic changes
- Ultrasonic sensor placement must match code comments
- Speed and distance values can be adjusted in code

---

## 🔮 Future Improvements

- Bluetooth or WiFi control
- Camera-based object tracking
- Mode switching using buttons
- PlatformIO support

## Photos

![WhatsApp Image 2025-10-23 at 17 26 06](https://github.com/user-attachments/assets/d76219a2-eaf1-403d-a914-152af973e727)


## System Architecture Diagram

<img width="1024" height="1536" alt="arduino" src="https://github.com/user-attachments/assets/3fb58fba-aa20-4f45-9da1-75d4a76fde35" />


## Obstacle avoidance using arduino

https://github.com/user-attachments/assets/df1db6ba-4b7d-4601-9c63-d5f77e0635d3


