# Solar Tracker Simulation (C Program)
---
This project is a **C-based simulation** of a solar tracking system that reacts to
light levels from two LDR sensors and adjusts a servo motor position accordingly.
It also emulates an LCD display and temperature sensor to mimic an embedded
environment such as an Arduino-based solar tracker.

The program runs entirely in a **terminal/console environment**, allowing sensor
inputs to be entered manually for testing and demonstration.

**Live Tinkercad Simulation** 
https://www.tinkercad.com/embed/j4i6qGCD1pO

##  Features

- Simulated **LDR sensors (LDR1 & LDR2)**  
- Simulated **temperature sensor**  
- Simulated **LCD display output**  
- Simulated **servo motor (0°–180°)**  
- Fully functional **Night Mode**  
- Servo auto-adjusts based on **difference in light intensity**  
- Continuous loop with **user input**  
- Cleanly exits the program when the user chooses

##  How It Works

1. User enters:
   - LDR1 value (0–1023)
   - LDR2 value (0–1023)
   - Temperature analog value (0–1023)

2. Program calculates:
   - Light difference
   - Temperature in °C  
   - Servo angle based on light direction

3. The LCD and servo actions are displayed as console logs.

4. User chooses whether to continue or stop the program.

##  Night Mode

If both LDR readings fall below `200`, the system enters **Night Mode**:

- LCD displays `"Night Mode Active"`
- Servo automatically goes to neutral position (`90°`)
- Tracking stops until light returns

##  Servo Tracking Logic

- If the difference between LDR1 and LDR2 is **large**, servo moves fully:
  - LDR1 brighter → servo `0°`
  - LDR2 brighter → servo `180°`
  
- If difference is small, servo adjusts **gradually** toward the brighter side.

##  Example Console Output
Enter LDR1 light level (0-1023): 600
Enter LDR2 light level (0-1023): 400
Enter temperature sensor value (0-1023): 512

LCD Display: Adjusting Servo
Servo moved to 45 degrees
Servo Position set to 45 degrees based on LDR inputs
LDR1: 600 | LDR2: 400 | Temperature: 250.0 C | Servo Position: 45

##  Running the Program

Compile using GCC:

```bash
gcc solar_tracker.c -o solar_tracker
Run:

./solar_tracker
```
File Structure
```
├── solar_tracker.c    # Main simulation code
└── README.md          # Project documentation```

