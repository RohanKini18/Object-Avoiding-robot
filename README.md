# 🤖 Object-Avoiding Robot (Arduino-Based)

## 📌 Description

This project is an autonomous 4-wheel robot that detects and avoids obstacles using an ultrasonic sensor. It's powered by an Arduino Uno and programmed to navigate its environment by continuously scanning for obstacles and altering its path to avoid collisions.

---

## 🧩 Components Used

- **Arduino Uno** – Main controller  
- **4-Wheel Robot Car Chassis Kit** – Includes BO motors and wheels  
- **L293D Motor Driver Shield** – Controls the four motors  
- **SG90 Servo Motor** – Rotates the ultrasonic sensor to scan surroundings  
- **HC-SR04 Ultrasonic Sensor** – Measures distance to obstacles  
- **Ultrasonic Sensor Mount** – Holds the sensor on the servo  
- **Female-to-Female Jumper Wires** – For electrical connections  

---

## ⚙️ Working Principle

- The **ultrasonic sensor** detects obstacles in front of the robot.  
- The **servo motor** rotates the sensor left and right to scan the surroundings.  
- Based on the distance readings, the Arduino decides whether to:
  - ✅ Move forward if the path is clear  
  - 🛑 Stop and scan if an obstacle is detected  
  - 🔄 Turn left or right to find a clear path  
- The **L293D motor shield** controls the direction and movement of the motors accordingly.

---

## 🔌 Power Supply Notes

- The robot should be powered by a **6V–9V battery pack** (e.g., 6x AA or 2x 18650 Li-ion batteries) for reliable performance.  
- ❌ Avoid using a standard 9V rectangular battery, as it **cannot supply sufficient current** for the motors and servo.

---

## ✅ Key Features

- 🤖 Fully autonomous obstacle avoidance  
- 👁️ Real-time environment scanning with a servo-mounted ultrasonic sensor  
- 🧱 Compact and modular design  
- 🧩 Easy to customize or extend (e.g., add Bluetooth or line-following features)  

---

## 📁 Optional Extensions

- Add Bluetooth module for manual control  
- Integrate IR sensors for edge detection or line-following  
- Use an OLED/LCD display to show distance or status

---

## 🛠️ License

This project is open-source and free to use under the [MIT License](LICENSE).

