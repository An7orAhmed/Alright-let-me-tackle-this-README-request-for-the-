# Smart Security Entrance System with Access Control

## Overview
A smart entrance control system using Arduino that combines presence detection, temperature screening, and access management. Designed for secure environments requiring health checks (e.g., fever detection) before entry.

## Features
- 👥 Dual IR sensor people counting
- 🌡️ MLX90614 non-contact temperature screening
- 🚪 Ultrasonic sensor (HC-SR04) for proximity detection
- 🔔 Visual feedback via 16x2 LCD + audible alerts
- 🔒 Servo-controlled physical gate mechanism
- 📊 Automatic people counting with entry validation

## Hardware Pin Configuration
| Component        | Arduino Pin |
|------------------|-------------|
| IR Sensor 1      | A0          |
| IR Sensor 2      | A1          |
| Servo Motor      | 3           |
| Buzzer           | 4           |
| Ultrasonic Trig  | 5           |
| Ultrasonic Echo  | 6           |
| LCD RS           | 12          |
| LCD E            | 11          |
| LCD D4-D7        | 10,9,8,7    |

*Note: Connection diagrams in project PDFs may show illustrative representations rather than exact wiring.*

## System Workflow
1. **Idle State**: 
   - Displays total entries
   - Monitors ultrasonic sensor for approaching users

2. **Presence Detection**:
   - Activates when object detected 5-25cm away
   - 10-second timeout for approach confirmation

3. **Health Check**:
   - Requires IR beam break confirmation
   - Measures body temperature (℉) via thermal sensor
   - Threshold: 100°F (customizable in code)

4. **Access Control**:
   - **
