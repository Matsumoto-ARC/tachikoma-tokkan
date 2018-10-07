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

    switch (tui_led_no) {
        case 1: /* serial communication error */
            while(1){
                digitalWrite(LED_PIN1, HIGH);
                delay(500);
                digitalWrite(LED_PIN1, LOW);
                delay(500);
            }
            break;
        case 2: /* servo init move error */
            while(1){
                digitalWrite(LED_PIN2, HIGH);
                delay(500);
                digitalWrite(LED_PIN2, LOW);
                delay(500);
            }
            break;
        case 3: /* motor init move error */
            while(1){
                digitalWrite(LED_PIN3, HIGH);
                delay(500);
                digitalWrite(LED_PIN3, LOW);
                delay(500);
            }
        case 4: /* unexpected error */
            break;
        default:
            break;
    }
}