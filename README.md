# Autonomous Navigation & Edge Detection Robot

This project is a custom-built autonomous mobile platform designed to navigate dynamic environments. Using a combination of ultrasonic distance sensing and infrared (IR) threshold detection, the robot performs real-time path planning and executes safety-stop protocols when it encounters boundaries.

### Project in Action
**[Click here to watch the Demo Video](./IMG_8656.MOV)** *(Note: If the link doesn't open directly, please select `IMG_8656.MOV` from the file list at the top of this repository.)*


## Control Logic & Features
The robot operates on a continuous **Sense-Think-Act** loop, prioritizing safety and obstacle negotiation through the following systems:

### 1. Dual-Channel Obstacle Negotiation
The system uses two ultrasonic sensors to monitor spatial clearance. Rather than just stopping, the code implements a **Differential Pivot Logic**:
* **Sensor 1 (Left):** If an object is detected within 20cm, the robot halts the left motor and rotates the right motor, pivoting the chassis away from the obstacle.
* **Sensor 2 (Right):** Similarly, if the right sensor triggers, the robot pivots in the opposite direction.
* This ensures the robot stays in motion rather than getting stuck in corners or dead-ends.

### 2. High-Priority Safety Interrupt (IR Sensing)
To prevent the robot from falling off surfaces or crossing restricted zones, I implemented an **IR-based "Kill Switch"**:
* The system constantly polls an analog IR sensor against a `BLACK_THRESHOLD`.
* If a boundary is detected, the software immediately breaks the loop, triggers a `stopMotors()` command, and halts all processes for 1 second to ensure stability before re-evaluating the path.

### 3. Motor Control Pipeline
I utilized an **L298N H-Bridge driver** to manage two DC motors. The code uses PWM (Pulse Width Modulation) via `analogWrite` to maintain consistent torque and speed (set at a balanced 127/255 duty cycle) for smooth navigation.


## Hardware & Tech Stack
* **Processor:** Arduino (Atmega328P)
* **Sensing:** 2x HC-SR04 Ultrasonic Sensors, Analog IR Reflectance Sensor
* **Actuation:** Dual DC Motors via L298N Driver
* **Language:** C++ (Arduino Framework)

## Code Highlights
* **Modular Architecture:** The code is organized into specific functions like `measureDistance()`, `rotateMotorA()`, and `stopMotors()`. This makes the system easy to debug and scalable for future sensor integration.
* **Telemetry:** I integrated Serial communication to provide real-time feedback on sensor triggers, which was essential during the calibration of the `BLACK_THRESHOLD` for the IR sensor.
* **Expansion Ready:** The current pin definitions include speed sensor inputs (encoders), providing the foundation for future PID control implementation to ensure perfectly straight tracking.

