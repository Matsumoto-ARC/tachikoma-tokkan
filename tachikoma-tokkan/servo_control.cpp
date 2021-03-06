#include <Servo.h>
#include "Arduino.h"
#include "header.h"

/* 変数のプロトタイプ宣言 */
static Servo        scl_base_servo, scl_elbow_servo, scl_wrist_servo, scl_finger_servo;
static SERVO_ANGLE  scl_angle_now, scl_angle_old;

/* 関数のプロトタイプ宣言 */
static bool     sfunc_servo_check(void);

void gfunc_servo_init(void) {
    bool            tbl_servo_result = false;
    unsigned int    tui_error_no = 0;

    /* それぞれのサーボの初期角度を設定(TBD) */
    scl_finger_servo.writeMicroseconds(FINGER_SERVO_INIT_ANGLE);
    delay(1000);
    scl_wrist_servo.writeMicroseconds(WRIST_SERVO_INIT_ANGLE);
    delay(1000);
    scl_elbow_servo.writeMicroseconds(ELBOW_SERVO_INIT_ANGLE);
    delay(1000);
    scl_base_servo.writeMicroseconds(BASE_SERVO_INIT_ANGLE);
    delay(1000);

    /* それぞれのサーボに割り当てるGPIOを設定(TBD) */
    scl_base_servo.attach(SERVO_PIN1);
    scl_elbow_servo.attach(SERVO_PIN2);
    scl_wrist_servo.attach(SERVO_PIN3);
    scl_finger_servo.attach(SERVO_PIN4);
    

    /*  tbl_servo_result = sfunc_servo_check();
    if (tbl_servo_result != true) {
        gfunc_led_error_blink(SERVO_MOVE_ERROR);
    } */

}

bool sfunc_servo_check(void) {

}

/* TBD(他のメンバーの意見を聞いてから再実装) */
void gfunc_servo_operation(DIGITAL_BUTTON tcl_digital_bt){

    /* elbow及びwristの下限値 */
    unsigned int elbow_servo_min_angle = 0;
    unsigned int wrist_servo_min_angle = 0;
    
    /* Startが押された場合、全サーボを初期位置に戻す */
    if (tcl_digital_bt.start != false) {
        scl_angle_now.base = BASE_SERVO_INIT_ANGLE;
        scl_angle_now.elbow = ELBOW_SERVO_INIT_ANGLE;
        scl_angle_now.wrist = WRIST_SERVO_INIT_ANGLE;
        scl_angle_now.finger = FINGER_SERVO_INIT_ANGLE;
    }

    if ((tcl_digital_bt.l1 != false) && (tcl_digital_bt.r1 != false)) {
        /* L1 R1が両方押されている場合は全停止 = 前回のアングルで固定 */
        scl_base_servo.writeMicroseconds(scl_angle_old.base);
        scl_elbow_servo.writeMicroseconds(scl_angle_old.elbow);
        scl_wrist_servo.writeMicroseconds(scl_angle_old.wrist);
        scl_finger_servo.writeMicroseconds(scl_angle_old.finger);        
    } else if ((tcl_digital_bt.l1 == false) && (tcl_digital_bt.r1 == false)) {
        /* L1 R1が両方離されている場合も全停止 = 前回のアングルで固定 */
        scl_base_servo.writeMicroseconds(scl_angle_old.base);
        scl_elbow_servo.writeMicroseconds(scl_angle_old.elbow);
        scl_wrist_servo.writeMicroseconds(scl_angle_old.wrist);
        scl_finger_servo.writeMicroseconds(scl_angle_old.finger);   
    } else {
        /* L1 or R1 + 何かしらのボタンで動作 */
        if ((tcl_digital_bt.triangle != false) && (tcl_digital_bt.l1 != false)) {
            /* servoの制御を書く */
            if(scl_angle_now.finger < FINGER_SERVO_MAX_ANGLE) {
                scl_angle_now.finger += 5;
            } else {
                /* 何もしない */
            }
        } else if ((tcl_digital_bt.triangle != false) && (tcl_digital_bt.r1 != false)) {
            /* servoの制御を書く */
            if(scl_angle_now.finger > FINGER_SERVO_MIN_ANGLE) {
                scl_angle_now.finger -= 5;
            } else {
                /* 何もしない */
            }
        } else {
            /* 何もしない */
        }

        if ((tcl_digital_bt.circle != false) && (tcl_digital_bt.l1 != false)) {
            /* servoの制御を書く */
            if(scl_angle_now.elbow < ELBOW_SERVO_MAX_ANGLE) {
                scl_angle_now.elbow += 5;
            } else {
                /* 何もしない */
            }
        } else if ((tcl_digital_bt.circle != false) && (tcl_digital_bt.r1 != false)) {
            /* elbowの下限値を決める */
            elbow_min_angle = gfunc_servo_elbowMinAngle((unsigned int)scl_angle_now.wrist);
            /* servoの制御を書く */
            /*  if(scl_angle_now.elbow > ELBOW_SERVO_MIN_ANGLE) {   */
            if(scl_angle_now.elbow > elbow_servo_min_angle) {
                scl_angle_now.elbow -= 5;
            } else {
                /* 何もしない */
            }
        } else {
            /* 何もしない */
        }

        if ((tcl_digital_bt.cross != false) && (tcl_digital_bt.l1 != false)) {
            /* servoの制御を書く */
            if(scl_angle_now.base < BASE_SERVO_MAX_ANGLE) {
                scl_angle_now.base += 5;
            } else {
                /* 何もしない */
            }
        } else if ((tcl_digital_bt.cross != false) && (tcl_digital_bt.r1 != false)) {
            /* servoの制御を書く */
            if(scl_angle_now.base > BASE_SERVO_MIN_ANGLE) {
                scl_angle_now.base -= 5;
            } else {
                /* 何もしない */
            }
        } else {
            /* 何もしない */
        }

        if ((tcl_digital_bt.square != false) && (tcl_digital_bt.l1 != false)) {
            /* servoの制御を書く */
            if(scl_angle_now.wrist < WRIST_SERVO_MAX_ANGLE) {
                scl_angle_now.wrist += 15;
            } else {
                /* 何もしない */
            }
        } else if ((tcl_digital_bt.square != false) && (tcl_digital_bt.r1 != false)) {
            /* wristの下限値を決める */
            wrist_servo_min_angle = gfunc_servo_wristMinAngle((unsigned int)scl_angle_now.elbow);
            /* servoの制御を書く */
            /*  if(scl_angle_now.wrist > WRIST_SERVO_MIN_ANGLE) {   */
            if(scl_angle_now.wrist < wrist_servo_min_angle) {
                scl_angle_now.wrist -= 15;
            } else {
                /* 何もしない */
            }
        } else {
            /* 何もしない */
        }
        /* アングルを更新 */
        scl_base_servo.writeMicroseconds(scl_angle_now.base);
        scl_finger_servo.writeMicroseconds(scl_angle_now.finger);
        scl_elbow_servo.writeMicroseconds(scl_angle_now.elbow);
        scl_wrist_servo.writeMicroseconds(scl_angle_now.wrist);
    }
    scl_angle_old = scl_angle_now;
}

void gfunc_servo_stop(void) {
    /* 初期位置をセット */
    /* scl_angle_now.base = BASE_SERVO_INIT_ANGLE;
    scl_angle_now.elbow = ELBOW_SERVO_INIT_ANGLE;
    scl_angle_now.wrist = WRIST_SERVO_INIT_ANGLE;
    scl_angle_now.finger = FINGER_SERVO_INIT_ANGLE; */

    /* 初期位置を保持 */
    scl_base_servo.writeMicroseconds(scl_angle_now.base);
    scl_elbow_servo.writeMicroseconds(scl_angle_now.elbow);
    scl_wrist_servo.writeMicroseconds(scl_angle_now.wrist);
    scl_finger_servo.writeMicroseconds(scl_angle_now.finger);   
}

/* wristの現在値からelbowの下限値を算出（詳しい値は稼働させながら決定） */
unsigned int gfunc_servo_elbowMinAngle(unsigned int tui_wrist) {
    unsigned int tui_min_angle;
    
    if(tui_wrist > 1000) {
        /* wristが下限値に達していない場合、ELBOW_SERVO_MIN_ANGLEの値をそのまま使用 */
        tui_min_angle = ELBOW_SERVO_MIN_ANGLE;  //(=600)
    } else {
        tui_min_angle = 800;
    }
    
    return tui_min_angle;
}

/* elbowの現在値からwristの下限値を算出（詳しい値は稼働させながら決定） */
unsigned int gfunc_servo_wristMinAngle(unsigned int tui_elbow) {
    unsigned int tui_min_angle;
    
    if(tui_elbow < 1000) {
        /* wristが下限値に達していない場合、WRIST_SERVO_MIN_ANGLEの値をそのまま使用 */
        tui_min_angle = WRIST_SERVO_MIN_ANGLE;  //(=800)
    } else {
        tui_min_angle = 1000;
    }
    
    return tui_min_angle;
}
