#include "Arduino.h"
#include "header.h"

/* 変数のプロトタイプ宣言 */
static ANALOG_STICK_VAL scl_motor_val_old;

void gfunc_motor_init(void) {

    pinMode(MOTOR_PIN1, OUTPUT);    /* 左モーター */
    pinMode(MOTOR_PIN2, OUTPUT);    /* 右モーター */
    pinMode(MOTOR_PIN3, OUTPUT);    /* 左モーター:IN1 */
    pinMode(MOTOR_PIN4, OUTPUT);    /* 左モーター:IN2 */
    pinMode(MOTOR_PIN5, OUTPUT);    /* 右モーター:IN1 */
    pinMode(MOTOR_PIN6, OUTPUT);    /* 右モーター:IN2 */

    /* 停止 */
    analogWrite(MOTOR_PIN1, 0);
    analogWrite(MOTOR_PIN2, 0);
    digitalWrite(MOTOR_PIN3, LOW);  
    digitalWrite(MOTOR_PIN4, LOW);
    digitalWrite(MOTOR_PIN5, LOW);  
    digitalWrite(MOTOR_PIN6, LOW);
}

/* TBD(他のメンバーの意見を聞いてから再実装) */
void gfunc_motor_operation(ANALOG_STICK tcl_ana_st, ANALOG_STICK_VAL tcl_motor_val) {

    unsigned int tui_motor_conv_val = 0;
    unsigned int tui_motor_action_time = 0;

    if (tcl_ana_st.l3_up != false) {  /* 前進 */
        /* モーターの制御を書く */
        if ((tcl_ana_st.l3_left != false) && (tcl_motor_val.l3_left_val > 10000)) {  /* 左方向に修正 */
            if (scl_motor_val_old.l3_left_val != tcl_motor_val.l3_left_val) {   /* 前回と値が違う時だけ更新 */
                tui_motor_conv_val = (int)tcl_motor_val.l3_left_val / 128.5;
                tui_motor_action_time = tui_motor_conv_val * MOTOR_ACTION_TIME;
                analogWrite(MOTOR_PIN2, tui_motor_conv_val);     /* 右モーター回転速度 */
                delay(tui_motor_action_time);
            } else {
                tui_motor_conv_val = (int)tcl_motor_val.l3_up_val / 128.5;
                analogWrite(MOTOR_PIN1, tui_motor_conv_val);
                analogWrite(MOTOR_PIN2, tui_motor_conv_val);
            }
        } else if ((tcl_ana_st.l3_right != false) && (tcl_motor_val.l3_right_val > 10000)) { /* 右方向に修正 */
            if (scl_motor_val_old.l3_right_val != tcl_motor_val.l3_right_val) {   /* 前回と値が違う時だけ更新 */
                tui_motor_conv_val = (int)tcl_motor_val.l3_right_val / 128.5;
                tui_motor_action_time = tui_motor_conv_val * MOTOR_ACTION_TIME;
                analogWrite(MOTOR_PIN1, tui_motor_conv_val);     /* 左モーター回転速度 */
                delay(tui_motor_action_time);
            } else {
                tui_motor_conv_val = (int)tcl_motor_val.l3_up_val / 128.5;
                analogWrite(MOTOR_PIN1, tui_motor_conv_val);
                analogWrite(MOTOR_PIN2, tui_motor_conv_val); 
            }
        } else {
            tui_motor_conv_val = (int)tcl_motor_val.l3_up_val / 128.5;
            analogWrite(MOTOR_PIN1, tui_motor_conv_val);
            analogWrite(MOTOR_PIN2, tui_motor_conv_val);             
        }
        /* 以下設定はモータードライバーとの配線次第で変更が必要 */
        digitalWrite(MOTOR_PIN3, HIGH);     /* 左モーター:IN1をHIGHに設定 */
        digitalWrite(MOTOR_PIN4, LOW);      /* 左モーター:IN2をLOWに設定 */
        digitalWrite(MOTOR_PIN5, LOW);      /* 右モーター:IN1をLOWに設定 */
        digitalWrite(MOTOR_PIN6, HIGH);     /* 右モーター:IN2をHIGHに設定 */
    } else if (tcl_ana_st.l3_down != false) {    /* 後進 */
        /* モーターの制御を書く */
        tui_motor_conv_val = (int)tcl_motor_val.l3_down_val / 128.5;
        analogWrite(MOTOR_PIN1, tui_motor_conv_val);
        analogWrite(MOTOR_PIN2, tui_motor_conv_val);

        /* 以下設定はモータードライバーとの配線次第で変更が必要 */
        digitalWrite(MOTOR_PIN3, LOW);       /* 左モーター:IN1をLOWに設定 */
        digitalWrite(MOTOR_PIN4, HIGH);      /* 左モーター:IN2をHIGHに設定 */
        digitalWrite(MOTOR_PIN5, HIGH);      /* 右モーター:IN1をHIGHに設定 */
        digitalWrite(MOTOR_PIN6, LOW);       /* 右モーター:IN2をLOWに設定 */
    } else if (tcl_ana_st.l3_left != false) {
        if (((tcl_ana_st.l3_up != false) && (tcl_motor_val.l3_up_val < 10000)) || \
            ((tcl_ana_st.l3_down != false) && (tcl_motor_val.l3_down_val < 10000))) {
            tui_motor_conv_val = (int)tcl_motor_val.l3_left_val / 128.5;
            analogWrite(MOTOR_PIN1, tui_motor_conv_val);     /* 左モーター回転速度 */
            analogWrite(MOTOR_PIN2, tui_motor_conv_val);     /* 右モーター回転速度 */

            /* 以下設定はモータードライバーとの配線次第で変更が必要 */
            digitalWrite(MOTOR_PIN3, LOW);       /* 左モーター:IN1をLOWに設定 */
            digitalWrite(MOTOR_PIN4, HIGH);      /* 左モーター:IN2をHIGHに設定 */
            digitalWrite(MOTOR_PIN4, LOW);      /* 右モーター:IN1をLOWに設定 */
            digitalWrite(MOTOR_PIN3, HIGH);       /* 右モーター:IN2をHIGHに設定 */
        } else {
            tui_motor_conv_val = (int)tcl_motor_val.l3_left_val / 128.5;
            analogWrite(MOTOR_PIN1, tui_motor_conv_val);     /* 左モーター回転速度 */
            analogWrite(MOTOR_PIN2, tui_motor_conv_val);     /* 右モーター回転速度 */

            /* 以下設定はモータードライバーとの配線次第で変更が必要 */
            digitalWrite(MOTOR_PIN3, LOW);       /* 左モーター:IN1をLOWに設定 */
            digitalWrite(MOTOR_PIN4, HIGH);      /* 左モーター:IN2をHIGHに設定 */
            digitalWrite(MOTOR_PIN4, LOW);      /* 右モーター:IN1をLOWに設定 */
            digitalWrite(MOTOR_PIN3, HIGH);       /* 右モーター:IN2をHIGHに設定 */
        }
    } else if (tcl_ana_st.l3_right != false) {
        if (((tcl_ana_st.l3_up != false) && (tcl_motor_val.l3_up_val < 10000)) || \
            ((tcl_ana_st.l3_down != false) && (tcl_motor_val.l3_down_val < 10000))) {
            tui_motor_conv_val = (int)tcl_motor_val.l3_right_val / 128.5;
            analogWrite(MOTOR_PIN1, tui_motor_conv_val);     /* 左モーター回転速度 */
            analogWrite(MOTOR_PIN2, tui_motor_conv_val);     /* 右モーター回転速度 */

            /* 以下設定はモータードライバーとの配線次第で変更が必要 */
            digitalWrite(MOTOR_PIN3, HIGH);       /* 左モーター:IN1をHIGHに設定 */
            digitalWrite(MOTOR_PIN4, LOW);      /* 左モーター:IN2をLOWに設定 */
            digitalWrite(MOTOR_PIN4, HIGH);      /* 右モーター:IN1をHIGHに設定 */
            digitalWrite(MOTOR_PIN3, LOW);       /* 右モーター:IN2をLOWに設定 */
        } else {
            tui_motor_conv_val = (int)tcl_motor_val.l3_right_val / 128.5;
            analogWrite(MOTOR_PIN1, tui_motor_conv_val);     /* 左モーター回転速度 */
            analogWrite(MOTOR_PIN2, tui_motor_conv_val);     /* 右モーター回転速度 */

            /* 以下設定はモータードライバーとの配線次第で変更が必要 */
            digitalWrite(MOTOR_PIN3, HIGH);       /* 左モーター:IN1をHIGHに設定 */
            digitalWrite(MOTOR_PIN4, LOW);      /* 左モーター:IN2をLOWに設定 */
            digitalWrite(MOTOR_PIN4, HIGH);      /* 右モーター:IN1をHIGHに設定 */
            digitalWrite(MOTOR_PIN3, LOW);       /* 右モーター:IN2をLOWに設定 */
        }
    } else {
        analogWrite(MOTOR_PIN1, 0);
        analogWrite(MOTOR_PIN2, 0);

        digitalWrite(MOTOR_PIN3, LOW);
        digitalWrite(MOTOR_PIN4, LOW);
        digitalWrite(MOTOR_PIN5, LOW);
        digitalWrite(MOTOR_PIN6, LOW);
    }
    scl_motor_val_old = tcl_motor_val;
}
