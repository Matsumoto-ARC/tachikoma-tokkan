#ifndef __HEADER_H__    /* インクルードガード */
#define __HEADER_H__    

#include <string.h>
#include "Arduino.h"

#if defined ARDUINO_AVR_UNO    /* 書き込み先がUNOの場合 */

    /* サーボのGPIO番号を設定(全て490Hz) */
    #define SERVO_PIN1   (3)    /* ハンド軸1 MG996R */
    #define SERVO_PIN2   (9)    /* ハンド軸2 MG996R */
    #define SERVO_PIN3   (10)   /* ハンド軸3 FT5335M */
    #define SERVO_PIN4   (11)   /* ハンド軸4 FT5335M */

    /* モーターのGPIO番号を設定 */
    #define MOTOR_PIN1  (5)     /* 左モーターの動作速度 制御用 */
    #define MOTOR_PIN2  (6)     /* 右モーターの動作速度 制御用 */
    #define MOTOR_PIN3  (7)     /* 左モーターの(IN1) 制御用 */
    #define MOTOR_PIN4  (8)     /* 左モーターの(IN2) 制御用 */
    #define MOTOR_PIN5  (12)    /* 右モーターの(IN1) 制御用 */
    #define MOTOR_PIN6  (13)    /* 右モーターの(IN2) 制御用 */

#elif defined ARDUINO_SAM_DUE   /* 書き込み先がDUEの場合 */

    #define SERVO_PIN1   (5)    /* ハンド軸4 FT5335M */
    #define SERVO_PIN2   (4)    /* ハンド軸3 FT5335M */
    #define SERVO_PIN3   (3)    /* ハンド軸2 MG996R */
    #define SERVO_PIN4   (2)    /* ハンド軸1 MG996R */

    #define MOTOR_PIN1  (6)     /* 左モーターの動作速度 制御用 */
    #define MOTOR_PIN2  (7)     /* 右モーターの動作速度 制御用 */
    #define MOTOR_PIN5  (23)    /* 右モーターの(IN1) 制御用 */
    #define MOTOR_PIN6  (24)    /* 右モーターの(IN2) 制御用 */
    #define MOTOR_PIN3  (25)    /* 左モーターの(IN1) 制御用 */
    #define MOTOR_PIN4  (26)    /* 左モーターの(IN2) 制御用 */
#endif

/* 左右旋回時間 */
#define MOTOR_ACTION_TIME   (2)  /* max 510(255*2)msec */

/* サーボの初期角度を設定 TBD(サーボの仕様で以下の値を決定する)*/
#define BASE_SERVO_INIT_ANGLE   (1500)
#define ELBOW_SERVO_INIT_ANGLE  (1500)
#define WRIST_SERVO_INIT_ANGLE  (1500)
#define FINGER_SERVO_INIT_ANGLE (1500)

#define BASE_SERVO_MAX_ANGLE    (2400)
#define WRIST_SERVO_MAX_ANGLE   (2400)
#define ELBOW_SERVO_MAX_ANGLE   (2400)
#define FINGER_SERVO_MAX_ANGLE  (2400)

#define BASE_SERVO_MIN_ANGLE    (800)
#define ELBOW_SERVO_MIN_ANGLE   (800)
#define WRIST_SERVO_MIN_ANGLE   (800)
#define FINGER_SERVO_MIN_ANGLE  (800)

/* Error No */
enum ERROR_NO {
    SERIAL_COMM_ERROR = 1,
    SERVO_MOVE_ERROR,
};

struct SERIAL_DATA {
    String  serial_type;
    String  serial_num;
    String  serial_val;

    /* メンバイニシャライザ */
    SERIAL_DATA(): serial_type(""), serial_num(""), serial_val("") {}
};

struct BUTTON_DATA {
    int     button_type;
    int     button_num;
    int     button_val1;
    int     button_val2;

    /* メンバイニシャライザ */
    BUTTON_DATA(): button_type(0), button_num(0), button_val1(0), button_val2(0) {}
};

struct DIGITAL_BUTTON {
    bool    select;
    bool    l3;
    bool    r3;
    bool    start;
    bool    up;
    bool    right;
    bool    down;
    bool    left;
    bool    l2;
    bool    r2;
    bool    l1;
    bool    r1;
    bool    triangle;
    bool    circle;
    bool    cross;
    bool    square;
    bool    ps;

    /* メンバイニシャライザ */
    DIGITAL_BUTTON():   select(false), l3(false), r3(false), start(false), up(false), right(false), down(false), left(false), 
                        l2(false), r2(false), l1(false), r1(false), triangle(false), circle(false), cross(false), square(false), ps(false) {}
};

struct ANALOG_STICK {
    bool    l3_left;
    bool    l3_right;
    bool    l3_up;
    bool    l3_down;
    bool    r3_left;
    bool    r3_right;
    bool    r3_up;
    bool    r3_down;

    /* メンバイニシャライザ */
    ANALOG_STICK(): l3_left(false), l3_right(false), l3_up(false), l3_down(false), 
                    r3_left(false), r3_right(false), r3_up(false), r3_down(false) {}
};

struct ANALOG_STICK_VAL {
    unsigned int    l3_left_val;
    unsigned int    l3_right_val;
    unsigned int    l3_up_val;
    unsigned int    l3_down_val;
    unsigned int    r3_left_val;
    unsigned int    r3_right_val;
    unsigned int    r3_up_val;
    unsigned int    r3_down_val;

    /* メンバイニシャライザ */
    ANALOG_STICK_VAL(): l3_left_val(0), l3_right_val(0), l3_up_val(0), l3_down_val(0),
                        r3_left_val(0), r3_right_val(0), r3_up_val(0), r3_down_val(0) {}
};

struct SERVO_ANGLE {
    unsigned int    base;
    unsigned int    elbow;
    unsigned int    wrist;
    unsigned int    finger;

    /* メンバイニシャライザ */
    SERVO_ANGLE():  base(BASE_SERVO_INIT_ANGLE), elbow(ELBOW_SERVO_INIT_ANGLE), 
                    wrist(WRIST_SERVO_INIT_ANGLE), finger(FINGER_SERVO_INIT_ANGLE) {}
};

/* Global変数のプロトタイプ宣言 */
// extern ANALOG_STICK_VAL  gcl_motor_val;

/* Global関数のプロトタイプ宣言 */
extern void                 gfunc_serial_init(void);
extern void                 gfunc_serial_read(BUTTON_DATA *);
extern void                 gfunc_controler_button_check(BUTTON_DATA, DIGITAL_BUTTON *);
extern ANALOG_STICK_VAL     gfunc_controler_analog_check(BUTTON_DATA, ANALOG_STICK *);
extern void                 gfunc_servo_init(void);
extern void                 gfunc_servo_operation(DIGITAL_BUTTON);
extern void                 gfunc_servo_stop(void);
extern void                 gfunc_motor_init(void);
extern void                 gfunc_motor_operation(ANALOG_STICK, ANALOG_STICK_VAL);
extern void                 gfunc_motor_stop(void);
extern void                 gfunc_led_init(void);
extern void                 gfunc_led_operation(void);
extern void                 gfunc_led_error_blink(unsigned int);

#endif