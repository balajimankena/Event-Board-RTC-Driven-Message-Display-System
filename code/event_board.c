#include <lpc214x.h>
#include "lcd.h"
#include "keypad.h"
#include "rtc.h"
#include "adc.h"

#define TOTAL_MESSAGES 10

typedef struct {
    unsigned char hour;
    unsigned char minute;
    char text[80];
    unsigned char enabled; // 1 = show, 0 = skip
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

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i=0; i<ms; i++) {
        for(j=0; j<2000; j++);
    }
}

void displayTimeAndTemp() {
    char buf[16];
    int hour, minute, second;
    float temp;

    rtc_get_time(&hour, &minute, &second);
    temp = lm35_read(); // Read temperature from LM35

    lcd_cmd(0x80);
    sprintf(buf, "%02d:%02d:%02d", hour, minute, second);
    lcd_str(buf);

    lcd_cmd(0xC0);
    sprintf(buf, "Temp: %.1f C", temp);
    lcd_str(buf);
}

void checkAndDisplayMessages() {
    int hour, minute, second;
    rtc_get_time(&hour, &minute, &second);

    for(int i = 0; i < TOTAL_MESSAGES; i++) {
        if(messageList[i].enabled &&
           messageList[i].hour == hour &&
           messageList[i].minute == minute) {

            IOSET0 = (1<<10); // Green LED ON
            IOCLR0 = (1<<11); // Red LED OFF

            lcd_cmd(0x01); // Clear LCD
            lcd_str(messageList[i].text);
            delay_ms(5000); // Keep message for 5 seconds
            return;
        }
    }

    // No active message
    IOSET0 = (1<<11); // Red LED ON
    IOCLR0 = (1<<10); // Green LED OFF
    displayTimeAndTemp();
}

void adminMode() {
    lcd_cmd(0x01);
    lcd_str("Enter Password:");
    char entered[5];
    keypad_get_string(entered, 4);

    if(strcmp(entered, "1234") == 0) {
        lcd_cmd(0x01);
        lcd_str("Admin Mode");
        delay_ms(1000);
        // Add time editing & message enabling/disabling logic here
    } else {
        lcd_cmd(0x01);
        lcd_str("Wrong Password");
        delay_ms(1000);
    }
}

int main() {
    // Init Peripherals
    lcd_init();
    rtc_init();
    adc_init();
    keypad_init();

    // Configure LEDs as output
    IODIR0 |= (1<<10) | (1<<11);

    while(1) {
        // Check for Admin Mode Trigger (External Interrupt)
        if((IOPIN0 & (1<<12)) == 0) { // Assuming switch on P0.12
            adminMode();
        }
        checkAndDisplayMessages();
        delay_ms(1000);
    }
}
