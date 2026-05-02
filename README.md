Autonomous Navigation Robot
Master's Project - 1st Semester

📺 Watch the Demo
Please click on the file IMG_8656.MOV at the top of this page to see the robot successfully avoiding obstacles in real-time.

📝 Project Goal
I built this robot to handle two main tasks:

Obstacle Avoidance: It uses ultrasonic sensors to "see" objects. If something is in the way, the robot automatically turns to find a clear path.

Boundary Safety: It uses an IR sensor to detect black lines. If it reaches a boundary, it stops immediately to prevent a collision or fall.

🛠 Tools Used
Brain: Arduino Microcontroller

Sensors: Ultrasonic (for distance) and IR (for floor detection)

Movement: Dual DC Motors and L298N Driver

⚙️ How It Works
The code constantly checks the distance in front of the robot.

If an object is closer than 20cm, the robot stops one wheel and spins the other to turn away.

It is a fully autonomous "sense-and-act" system.
