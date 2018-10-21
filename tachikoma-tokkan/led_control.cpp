#include "Arduino.h"
#include "header.h"

void gfunc_led_init(void) {
    pinMode(LED_PIN1, OUTPUT);
    pinMode(LED_PIN2, OUTPUT);
    pinMode(LED_PIN3, OUTPUT);
    pinMode(LED_PIN4, OUTPUT);
    pinMode(LED_PIN5, OUTPUT);
}

void gfunc_led_operation(unsigned int tui_msec){
    unsigned int tui_blink_count;

    for(tui_blink_count = 0; tui_blink_count < 5; tui_blink_count++){
        digitalWrite(LED_PIN1, HIGH);
        delay(tui_msec);
        digitalWrite(LED_PIN1, LOW);
        delay(tui_msec);
    }
}

void gfunc_led_error_blink(unsigned int tui_led_no){

    int i;
    switch (tui_led_no) {
        case 0:
            digitalWrite(LED_PIN1, LOW);
            digitalWrite(LED_PIN2, LOW);
            break;
        case 1: /* serial communication error */
            for(i = 0; i < 10; i++){
                digitalWrite(LED_PIN1, HIGH);
                delay(500);
                digitalWrite(LED_PIN1, LOW);
                delay(500);
            }
            break;
        case 2: /* servo init move error */
            for(i = 0; i < 10; i++){
                digitalWrite(LED_PIN2, HIGH);
                delay(500);
                digitalWrite(LED_PIN2, LOW);
                delay(500);
            }
            break;
        case 3: /* motor init move error */
                digitalWrite(LED_PIN3, HIGH);
                delay(100);
                digitalWrite(LED_PIN3, LOW);
                delay(100);
                digitalWrite(LED_PIN3, HIGH);
                delay(100);
                digitalWrite(LED_PIN3, LOW);
                delay(100);
        case 4: /* unexpected error */
            break;
        default:
            break;
    }
}