#include <Servo.h>
#include "Arduino.h"
#include "header.h"

/* 変数のプロトタイプ宣言 */
static Servo            scl_base_servo, scl_elbow_servo, scl_wrist_servo, scl_finger_servo;

void gfunc_servo_init(void) {

    /* それぞれのサーボに割り当てるGPIOを設定(TBD) */
    scl_base_servo.attach(SERVO_PIN1);
    scl_elbow_servo.attach(SERVO_PIN2);
    scl_wrist_servo.attach(SERVO_PIN3);
    scl_finger_servo.attach(SERVO_PIN4);

    /* それぞれのサーボの初期角度を設定(TBD) */
    scl_base_servo.writeMicroseconds(BASE_SERVO_INIT_ANGLE);
    scl_elbow_servo.writeMicroseconds(ELBOW_SERVO_INIT_ANGLE);
    scl_wrist_servo.writeMicroseconds(WRIST_SERVO_INIT_ANGLE);
    scl_finger_servo.writeMicroseconds(FINGER_SERVO_INIT_ANGLE);
}

/* TBD(他のメンバーの意見を聞いてから再実装) */
void gfunc_servo_operation(DIGITAL_BUTTON tcl_digital_bt){
    SERVO_ANGLE tui_angle_now;
    SERVO_ANGLE tui_angle_old;

    if ((tcl_digital_bt.l1 != false) && (tcl_digital_bt.r1 != false)) {
        /* L1 R1が両方押されている場合は全停止 = 前回のアングルで固定 */
        scl_base_servo.writeMicroseconds(tui_angle_old.base);
        scl_elbow_servo.writeMicroseconds(tui_angle_old.elbow);
        scl_wrist_servo.writeMicroseconds(tui_angle_old.wrist);
        scl_finger_servo.writeMicroseconds(tui_angle_old.finger);        
    } else if ((tcl_digital_bt.l1 != true) && (tcl_digital_bt.r1 != true)) {
        /* L1 R1が両方離されている場合も全停止 = 前回のアングルで固定 */
        scl_base_servo.writeMicroseconds(tui_angle_old.base);
        scl_elbow_servo.writeMicroseconds(tui_angle_old.elbow);
        scl_wrist_servo.writeMicroseconds(tui_angle_old.wrist);
        scl_finger_servo.writeMicroseconds(tui_angle_old.finger);   
    } else {
        /* L1 or R1 + 何かしらのボタンで動作 */
        if ((tcl_digital_bt.triangle != false) && (tcl_digital_bt.l1 != false)) {
            /* servoの制御を書く */
            if(tui_angle_now.finger > FINGER_SERVO_MIN_ANGLE) {
                tui_angle_now.finger--;
            } else {
                /* 何もしない */
            }
        } else if ((tcl_digital_bt.triangle != false) && (tcl_digital_bt.r1 != false)) {
            /* servoの制御を書く */
            if(tui_angle_now.finger < FINGER_SERVO_MAX_ANGLE) {
                tui_angle_now.finger++;
            } else {
                /* 何もしない */
            }
        } else {
            /* 何もしない */
        }
        /* △ボタンに対応したサーボのアングルをセット */
        scl_finger_servo.writeMicroseconds(tui_angle_now.finger);

        if ((tcl_digital_bt.circle != false) && (tcl_digital_bt.l1 != false)) {
            /* servoの制御を書く */
            if(tui_angle_now.elbow > ELBOW_SERVO_MIN_ANGLE) {
                tui_angle_now.elbow--;
            } else {
                /* 何もしない */
            }
        } else if ((tcl_digital_bt.circle != false) && (tcl_digital_bt.r1 != false)) {
            /* servoの制御を書く */
            if(tui_angle_now.elbow < ELBOW_SERVO_MAX_ANGLE) {
                tui_angle_now.elbow++;
            } else {
                /* 何もしない */
            }
        } else {
            /* 何もしない */
        }
        /* ○ボタンに対応したサーボのアングルをセット */
        scl_finger_servo.writeMicroseconds(tui_angle_now.elbow);

        if ((tcl_digital_bt.cross != false) && (tcl_digital_bt.l1 != false)) {
            /* servoの制御を書く */
            if(tui_angle_now.base > BASE_SERVO_MIN_ANGLE) {
                tui_angle_now.base--;
            } else {
                /* 何もしない */
            }
        } else if ((tcl_digital_bt.cross != false) && (tcl_digital_bt.r1 != false)) {
            /* servoの制御を書く */
            if(tui_angle_now.base < BASE_SERVO_MAX_ANGLE) {
                tui_angle_now.base++;
            } else {
                /* 何もしない */
            }
        } else {
            /* 何もしない */
        }
        /* ×ボタンに対応したサーボのアングルをセット */
        scl_finger_servo.writeMicroseconds(tui_angle_now.base);

        if ((tcl_digital_bt.square != false) && (tcl_digital_bt.l1 != false)) {
            /* servoの制御を書く */
            if(tui_angle_now.wrist > WRIST_SERVO_MIN_ANGLE) {
                tui_angle_now.wrist--;
            } else {
                /* 何もしない */
            }
        } else if ((tcl_digital_bt.square != false) && (tcl_digital_bt.r1 != false)) {
            /* servoの制御を書く */
            if(tui_angle_now.wrist < WRIST_SERVO_MAX_ANGLE) {
                tui_angle_now.wrist++;
            } else {
                /* 何もしない */
            }
        } else {
            /* 何もしない */
        }
        /* □ボタンに対応したサーボのアングルをセット */
        scl_finger_servo.writeMicroseconds(tui_angle_now.wrist);
    }
    tui_angle_old = tui_angle_now;
}