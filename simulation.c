#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Definitions
#define LDR1_PIN 0
#define LDR2_PIN 1
#define TEMP_SENSOR_PIN 2
#define SERVO_PIN 9
#define NIGHT_MODE_THRESHOLD 200
#define MAX_LIGHT_DIFFERENCE 200

// Variables
int initial_position = 90;
bool isNightModeActive = false;

// Simulated LCD and Servo functions
void lcd_init() { printf("LCD Initialized\n"); }
void lcd_backlight_on() { printf("LCD Backlight ON\n"); }
void lcd_set_cursor(int row, int col) { printf("LCD Cursor set to row %d, col %d\n", row, col); }
void lcd_print(const char* message) { printf("LCD Display: %s\n", message); }
void lcd_clear() { printf("LCD Cleared\n"); }

void servo_attach(int pin) { printf("Servo attached to pin %d\n", pin); }
void servo_write(int position) { printf("Servo moved to %d degrees\n", position); }

void setup() {
    servo_attach(SERVO_PIN);
    servo_write(initial_position);

    printf("LDR1 (A0) and LDR2 (A1) set as INPUT\n");
    printf("Serial Communication started at 9600 baud\n");

    lcd_init();
    lcd_backlight_on();
    lcd_set_cursor(0, 0);
    lcd_print("Initializing...");
    printf("Delay for 2 seconds\n");
    lcd_clear();
}

void loop() {
    int lightLevel1, lightLevel2, tempValue;

    // User input
    printf("Enter LDR1 light level (0-1023): ");
    scanf("%d", &lightLevel1);

    printf("Enter LDR2 light level (0-1023): ");
    scanf("%d", &lightLevel2);

    printf("Enter temperature sensor value (0-1023): ");
    scanf("%d", &tempValue);

    int lightDifference = abs(lightLevel1 - lightLevel2);
    float temperature = (tempValue / 1024.0) * 500.0;

    int servoPosition;

    lcd_set_cursor(0, 0);
    printf("Temp: %.1f C\n", temperature);

    if (lightLevel1 < NIGHT_MODE_THRESHOLD && lightLevel2 < NIGHT_MODE_THRESHOLD) {
        isNightModeActive = true;
        lcd_set_cursor(0, 1);
        lcd_print("Night Mode Active");
        servoPosition = 90;
    } else {
        isNightModeActive = false;
        lcd_set_cursor(0, 1);
        lcd_print("Adjusting Servo");

        if (lightDifference > MAX_LIGHT_DIFFERENCE) {
            if (lightLevel1 > lightLevel2) {
                servoPosition = 0;
            } else {
                servoPosition = 180;
            }
        } else {
            servoPosition = 90 + (lightDifference * 90 / MAX_LIGHT_DIFFERENCE) * 
                                   (lightLevel1 > lightLevel2 ? -1 : 1);

            if (servoPosition < 0) servoPosition = 0;
            if (servoPosition > 180) servoPosition = 180;
        }
    }

    servo_write(servoPosition);

    printf("Servo Position set to %d degrees based on LDR inputs\n", servoPosition);
    printf("LDR1: %d | LDR2: %d | Temperature: %.1f C | Servo Position: %d\n",
           lightLevel1, lightLevel2, temperature, servoPosition);

    char cont;
    printf("Do you want to continue? (y/n): ");
    scanf(" %c", &cont);

    if (cont == 'n' || cont == 'N') {
        printf("Stopping program.\n");
        exit(0);
    }

    printf("Delay for 1 second\n");
}

int main() {
    setup();

    while (1) {
        loop();
    }

    return 0;
}
