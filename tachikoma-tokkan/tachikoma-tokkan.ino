#include "header.h"

/* Static変数定義(Scope:tachikoma-tokkan.ino) */
static BUTTON_DATA      scl_result_data;
static DIGITAL_BUTTON   scl_result_button;
static ANALOG_STICK     scl_result_stick;
static ANALOG_STICK_VAL scl_motor_val;

void setup(){
    /* 初期化 */
    gfunc_led_init();
    gfunc_serial_init();
    gfunc_servo_init();
    gfunc_motor_init();
}

void loop(){
    /* Raspberry Pi3から送信されてくるシリアルデータを取得 */
    gfunc_serial_read(&scl_result_data);
    Serial.println(scl_result_data.button_type);

    /* 取得したシリアルデータからタイプを分類 */
    if (scl_result_data.button_type == 1) {     /* ディジタル値(ボタン操作)の場合 */

        /* どのボタンが押された or 離されたかチェック */
        gfunc_controler_button_check(scl_result_data, &scl_result_button);
        
    } else if (scl_result_data.button_type == 2) {  /* アナログ値(アナログスティック操作)の場合 */

        /* どのスティックを操作したかチェック */
        scl_motor_val = gfunc_controler_analog_check(scl_result_data, &scl_result_stick);

    }

    /* ボタンに対応したサーボを動作させる */
    gfunc_servo_operation(scl_result_button);

    /* アナログスティックに対応したモーターを動作させる */
    gfunc_motor_operation(scl_result_stick, scl_motor_val);

    delay(10);
}