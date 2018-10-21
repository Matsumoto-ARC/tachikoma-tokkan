#include "header.h"
#include "Arduino.h"

/* シリアルデータとボタンの対応 */
enum DIGITAL_BUTTON_NUM {
    SELECT_BUTTON = 0,  /* 0 */
    L3_BUTTON,          /* 1 */
    R3_BUTTON,          /* 2 */
    START_BUTTON,       /* 3 */
    UP_BUTTON,          /* 4 */
    RIGHT_BUTTON,       /* 5 */
    DOWN_BUTTON,        /* 6 */
    LEFT_BUTTON,        /* 7 */
    L2_BUTTON,          /* 8 */
    R2_BUTTON,          /* 9 */
    L1_BUTTON,          /* 10 */
    R1_BUTTON,          /* 11 */
    TRIANGLE_BUTTON,    /* 12 */
    CIRCLE_BUTTON,      /* 13 */
    CROSS_BUTTON,       /* 14 */
    SQUARE_BUTTON,      /* 15 */
    PS_BUTTON           /* 16 */
};

/* シリアルデータとアナログスティックの対応 */
enum ANALOG_STICK_NUM {
    L3_STICK_HORIZONTAL = 0,    /* 0 */
    L3_STICK_VERTICAL,          /* 1 */
    R3_STICK_HORIZONTAL,        /* 2 */
    R3_STICK_VERTICAL           /* 3 */
};

void gfunc_controler_button_check(BUTTON_DATA tcl_bt_data, DIGITAL_BUTTON *tcl_digi_bt){

    switch (tcl_bt_data.button_num) {
        case SELECT_BUTTON:     /* SELCTボタン */
            if (tcl_bt_data.button_val1 != 0){
                tcl_digi_bt->select = true;
                digitalWrite(LED_PIN2, HIGH);
            } else if (tcl_bt_data.button_val1 == 0) {
                tcl_digi_bt->select = false;
                digitalWrite(LED_PIN2, LOW);
            }
            // Serial.println(tcl_digi_bt->select); /* debug用 */
            break;
        case START_BUTTON:     /* STARTボタン */
            if (tcl_bt_data.button_val1 != 0){
                tcl_digi_bt->start = true;
                digitalWrite(LED_PIN1, HIGH);
            } else if (tcl_bt_data.button_val1 == 0) {
                tcl_digi_bt->start = false;
                digitalWrite(LED_PIN1, LOW);
            }
            // Serial.println(tcl_digi_bt->start);  /* debug用 */
            break;
        case L1_BUTTON:    /* L1ボタン */
            if (tcl_bt_data.button_val1 != 0) {
                tcl_digi_bt->l1 = true;
            } else if (tcl_bt_data.button_val1 == 0) {
                tcl_digi_bt->l1 = false;
            }
            // Serial.println(tcl_digi_bt->l1);     /* debug用 */
            break;
        case R1_BUTTON:    /* R1ボタン */
            if (tcl_bt_data.button_val1 != 0) {
                tcl_digi_bt->r1 = true;
            } else if (tcl_bt_data.button_val1 == 0) {
                tcl_digi_bt->r1 = false;
            }
            // Serial.println(tcl_digi_bt->r1);     /* debug用 */
            break;
        case TRIANGLE_BUTTON:    /* △ボタン */
            if (tcl_bt_data.button_val1 != 0) {
                tcl_digi_bt->triangle = true;
            } else if (tcl_bt_data.button_val1 == 0) {
                tcl_digi_bt->triangle = false;
            }
            // Serial.println(tcl_digi_bt->triangle);   /* debug用 */
            break;
        case CIRCLE_BUTTON:    /* ○ボタン */
            if (tcl_bt_data.button_val1 != 0) {
                tcl_digi_bt->circle = true;
                gfunc_led_error_blink(1);
            } else if (tcl_bt_data.button_val1 == 0) {
                tcl_digi_bt->circle = false;
                gfunc_led_error_blink(0);
            }
            // Serial.println(tcl_digi_bt->circle);     /* debug用 */
            break;
        case CROSS_BUTTON:    /* ×ボタン */
            if (tcl_bt_data.button_val1 != 0) {
                tcl_digi_bt->cross = true;
                gfunc_led_error_blink(2);
            } else if (tcl_bt_data.button_val1 == 0) {
                tcl_digi_bt->cross = false;
                gfunc_led_error_blink(0);
            }
            // Serial.println(tcl_digi_bt->cross);      /* debug用 */
            break;
        case SQUARE_BUTTON:    /* □ボタン */
            if (tcl_bt_data.button_val1 != 0) {
                tcl_digi_bt->square = true;
            } else if (tcl_bt_data.button_val1 == 0) {
                tcl_digi_bt->square = false;
            }
            // Serial.println(tcl_digi_bt->square);     /* debug用 */
            break;
        case PS_BUTTON:
            if (tcl_bt_data.button_val1 != 0) {
                tcl_digi_bt->ps = true;
            } else if (tcl_bt_data.button_val1 == 0) {
                tcl_digi_bt->ps = false;
            }
            // Serial.println(tcl_digi_bt->ps);     /* debug用 */        
        default:    /* その他ボタン(十字キー, L2, R2, L3, R3) */
            break;
    }
}

ANALOG_STICK_VAL gfunc_controler_analog_check(BUTTON_DATA tcl_bt_data, ANALOG_STICK *tcl_ana_st){

    ANALOG_STICK_VAL  tcl_motor_val;

    switch (tcl_bt_data.button_num) {
        case L3_STICK_HORIZONTAL:     /* L3 Stick Left or Right */
            if (tcl_bt_data.button_val2 < 0){
                tcl_ana_st->l3_left = true;
                tcl_ana_st->l3_right = false;
                
                tcl_motor_val.l3_left_val = tcl_bt_data.button_val2 * -1;   /* 値を反転させる */
            } else if (tcl_bt_data.button_val2 > 0) {
                tcl_ana_st->l3_left = false;
                tcl_ana_st->l3_right = true;

                tcl_motor_val.l3_right_val = tcl_bt_data.button_val2;
            } else {
                tcl_ana_st->l3_left = false;
                tcl_ana_st->l3_right = false;

                tcl_motor_val.l3_left_val = 0;
                tcl_motor_val.l3_right_val = 0;
            }
            // Serial.println(tcl_ana_st->l3_left);     /* debug用 */
            // Serial.println(tcl_ana_st->l3_left);     /* debug用 */
            break;
        case L3_STICK_VERTICAL:     /* L3 Stick Up or Down */
            if (tcl_bt_data.button_val2 < 0){
                tcl_ana_st->l3_up = true;
                tcl_ana_st->l3_down = false;

                tcl_motor_val.l3_up_val = tcl_bt_data.button_val2 * -1;   /* 値を反転させる */
            } else if (tcl_bt_data.button_val2 > 0) {
                tcl_ana_st->l3_up = false;
                tcl_ana_st->l3_down = true;

                tcl_motor_val.l3_down_val = tcl_bt_data.button_val2;
            } else {
                tcl_ana_st->l3_up = false;
                tcl_ana_st->l3_down = false;

                tcl_motor_val.l3_up_val = 0;
                tcl_motor_val.l3_down_val = 0;                
            }
            // Serial.println(tcl_ana_st->l3_up);       /* debug用 */
            // Serial.println(tcl_ana_st->l3_down);     /* debug用 */
            break;
        case R3_STICK_HORIZONTAL:     /* R3 Stick Left or Right */
            if (tcl_bt_data.button_val2 < 0){
                tcl_ana_st->r3_left = true;
                tcl_ana_st->r3_right = false;

                tcl_motor_val.r3_left_val = tcl_bt_data.button_val2 * -1;   /* 値を反転させる */
            } else if (tcl_bt_data.button_val2 > 0) {
                tcl_ana_st->r3_left = false;
                tcl_ana_st->r3_right = true;

                tcl_motor_val.r3_right_val = tcl_bt_data.button_val2;
            } else {
                tcl_ana_st->r3_left = false;
                tcl_ana_st->r3_right = false;

                tcl_motor_val.r3_left_val = 0;
                tcl_motor_val.r3_right_val = 0;                
            }
            // Serial.println(tcl_ana_st->r3_left);     /* debug用 */
            // Serial.println(tcl_ana_st->r3_left);     /* debug用 */
            break;
        case R3_STICK_VERTICAL:     /* R3 Stick Up or Down */
            if (tcl_bt_data.button_val2 < 0){
                tcl_ana_st->r3_up = true;
                tcl_ana_st->r3_down = false;

                tcl_motor_val.r3_up_val = tcl_bt_data.button_val2 * -1;   /* 値を反転させる */
            } else if (tcl_bt_data.button_val2 > 0) {
                tcl_ana_st->r3_up = false;
                tcl_ana_st->r3_down = true;

                tcl_motor_val.r3_down_val = tcl_bt_data.button_val2;
            } else {
                tcl_ana_st->r3_up = false;
                tcl_ana_st->r3_down = false;

                tcl_motor_val.r3_up_val = 0;
                tcl_motor_val.r3_down_val = 0;                     
            }
            // Serial.println(tcl_ana_st->r3_up);       /* debug用 */
            // Serial.println(tcl_ana_st->r3_down);     /* debug用 */
            break;                        
        default:    /* ありえないルート */
            break;
    }

    return tcl_motor_val;
}