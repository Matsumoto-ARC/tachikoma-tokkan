#include "Arduino.h"
#include "header.h"

/* 変数のプロトタイプ宣言 */
static ANALOG_STICK_VAL scl_motor_val_old;

void gfunc_motor_init(void) {

    pinMode(MOTOR_PIN1, OUTPUT);    /* 左モーター */
    pinMode(MOTOR_PIN2, OUTPUT);    /* 右モーター */
    pinMode(MOTOR_PIN3, OUTPUT);    /* 左モーター:IN1, 右モーター:IN2 */
    pinMode(MOTOR_PIN4, OUTPUT);    /* 左モーター:IN2, 右モーター:IN1 */

    /* 停止 */
    analogWrite(MOTOR_PIN1, 0);
    analogWrite(MOTOR_PIN2, 0);
    digitalWrite(MOTOR_PIN3, LOW);  
    digitalWrite(MOTOR_PIN4, LOW);
}

/* TBD(他のメンバーの意見を聞いてから再実装) */
void gfunc_motor_operation(ANALOG_STICK tcl_ana_st, ANALOG_STICK_VAL tcl_motor_val) {

    unsigned int tui_motor_conv_val = 0;
    unsigned int tui_motor_action_time = 0;

    if (tcl_ana_st.l3_up != false) {  /* 前進 */
        /* モーターの制御を書く */
        if (tcl_ana_st.l3_left != false) {  /* 左旋回 */
            if (scl_motor_val_old.l3_left_val != tcl_motor_val.l3_left_val) {   /* 前回と値が違う時だけ更新 */
                tui_motor_conv_val = (int)tcl_motor_val.l3_left_val / 128;
                tui_motor_action_time = tui_motor_conv_val * MOTOR_ACTION_TIME;
                analogWrite(MOTOR_PIN2, tui_motor_conv_val);     /* 右モーター回転回転速度 */
                delay(tui_motor_action_time);
            } else {
                tui_motor_conv_val = (int)tcl_motor_val.l3_up_val / 128;
                analogWrite(MOTOR_PIN1, tui_motor_conv_val);
                analogWrite(MOTOR_PIN2, tui_motor_conv_val);
            }
        } else if (tcl_ana_st.l3_right != false) { /* 右旋回 */
            if (scl_motor_val_old.l3_right_val != tcl_motor_val.l3_right_val) {   /* 前回と値が違う時だけ更新 */
                tui_motor_conv_val = (int)tcl_motor_val.l3_right_val / 128;
                tui_motor_action_time = tui_motor_conv_val * MOTOR_ACTION_TIME;
                analogWrite(MOTOR_PIN2, tui_motor_conv_val);     /* 右モーター回転 */
                delay(tui_motor_action_time);
            } else {
                tui_motor_conv_val = (int)tcl_motor_val.l3_up_val / 128;
                analogWrite(MOTOR_PIN1, tui_motor_conv_val);
                analogWrite(MOTOR_PIN2, tui_motor_conv_val); 
            }
        }
        digitalWrite(MOTOR_PIN3, HIGH);     /* 左モーター:IN1をHIGHに設定, 右モーター:IN2をHIGHに設定 */
        digitalWrite(MOTOR_PIN4, LOW);      /* 左モーター:IN2をLOWに設定, 右モーター:IN1をLOWに設定 */
    } else if (tcl_ana_st.l3_down != false) {    /* 後進 */
        /* モーターの制御を書く */
        tui_motor_conv_val = (int)tcl_motor_val.l3_down_val / 128;
        analogWrite(MOTOR_PIN1, tui_motor_conv_val);
        analogWrite(MOTOR_PIN2, tui_motor_conv_val);

        digitalWrite(MOTOR_PIN3, LOW);       /* 左モーター:IN1をLOWに設定, 右モーター:IN2をLOWに設定 */
        digitalWrite(MOTOR_PIN4, HIGH);      /* 左モーター:IN2をHIGHに設定, 右モーター:IN1をHIGHに設定 */
    } 
    scl_motor_val_old = tcl_motor_val;
}
