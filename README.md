# Event-Board-RTC-Driven-Message-Display-System
This project is a **real-time automated message display system** built using the **LPC2148 ARM7 microcontroller**.   It displays predefined messages on a 16x2 LCD at specific times using the on-chip **RTC (Real Time Clock)**.   Messages scroll across the LCD and can be managed through a secure **Admin Mode**.

## Features
- Displays predefined messages at scheduled times.
- Secure **Admin Mode** using external interrupt, keypad, and password protection.
- Real-time clock display when no scheduled message is active.
- Room temperature measurement via **LM35** sensor (using LPC2148 ADC).
- Green LED indicates an active scheduled message display.
- Red LED indicates idle display mode.
- Admin Mode allows:
  - Editing current time.
  - Enabling/disabling specific messages for the day.

## Technologies & Tools
- **Language:** Embedded C
- **Microcontroller:** LPC2148 (ARM7)
- **Software Tools:** Keil µVision, Flash Magic
- **Peripherals:** LCD (16x2), Keypad, LM35, LEDs, Buzzer

## Block Diagram
![Block Diagram](images/block_diagram.png)

## Hardware Requirements
- LPC2148 ARM7 Microcontroller
- 16x2 LCD Display
- Keypad
- LM35 Temperature Sensor
- LEDs (Red & Green)
- Buzzer
- Push Switch (External Interrupt)
- Power Supply

## Software Requirements
- Keil µVision
- Flash Magic
- Embedded C

## Project Workflow
1. System runs in normal mode, displaying either scheduled messages or real-time clock + temperature.
2. At scheduled time, matching messages scroll on LCD, green LED turns ON.
3. If no message is scheduled, red LED turns ON, clock and temperature are displayed.
4. Admin Mode can be accessed via external interrupt switch and correct password:
   - Allows editing RTC time.
   - Allows enabling/disabling specific messages for the day.
5. All messages are stored in an array in program memory and can be modified in Admin Mode.

## Data Structure for Messages
```c
#define TOTAL_MESSAGES 10
typedef struct {
    u8 hour;
    u8 minute;
    char text[80];
    u8 enabled; // 1 = show, 0 = skip
} Message;

Message messageList[TOTAL_MESSAGES] = {
 {7, 45, "Good Morning! Classes Start Soon", 1},
 {13, 45, "C Programming Session in Class room number 2", 1},
 {10, 15, "C module theory exam in 4th floor lab1", 1},
 {10, 15, "C module lab exam in 4th floor lab2 and middle lab at 10:30AM", 1},
 {12, 45, "Lunch Break from 1PM – 2PM", 1},
 {9, 45, "ARM Workshop on external interrupts in LAB1 at 10AM", 1},
 {9, 45, "ARM kit issue time from 10AM – 10:30AM in middle lab", 1},
 {15, 15, "Only 15 mins break time for next ARM session", 1},
 {17, 00, "Revise today’s Class programs at home!", 1},
 {17, 45, "End of Day – See You Tomorrow!", 1}
};

Author
C N Sri Balaji Vara Prasad Mankena
