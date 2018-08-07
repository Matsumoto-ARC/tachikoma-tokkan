#include <string.h>
#include "Arduino.h"
#include "header.h"

/* 定数のプロトタイプ宣言 */
const unsigned int  RETRY_MAX = 20;  

/* 変数のプロトタイプ宣言 */
static String   sst_read_data;

/* 関数のプロトタイプ宣言 */
static void     sfunc_serial_calc_format(BUTTON_DATA *);
static bool     sfunc_serial_comm_check(void);

void gfunc_serial_init(void){
    bool    tbl_comm_result = false;

    Serial.begin(9600);
    Serial.setTimeout(5);
    Serial.flush();

    sst_read_data = "";
    tbl_comm_result = sfunc_serial_comm_check();
    
    if (tbl_comm_result != true) {
        gfunc_led_error_blink(SERIAL_COMM_ERROR);
    }
}

void gfunc_serial_read(BUTTON_DATA *tcl_result_data){
     
    sst_read_data = Serial.readStringUntil('\n');
    // Serial.println(sst_read_data);  /* debug用 */
    if (sst_read_data != ""){
        sfunc_serial_calc_format(tcl_result_data);
    } else {
        tcl_result_data->button_type = 0;
        tcl_result_data->button_num = 0;
        tcl_result_data->button_val1 = 0;
        tcl_result_data->button_val2 = 0;
    }
}

/* Raspberry Piと通信チェック */
bool sfunc_serial_comm_check(void){
    bool            tbl_result = false;
    String          tst_read;
    unsigned int    tui_retry_count;

    for(tui_retry_count = 0; tui_retry_count < RETRY_MAX; tui_retry_count++){
        Serial.write(1);    /* Raspberry Piに送信 */
        tst_read = Serial.read();
        if (tst_read != "-1") {
            tbl_result = true;
            break;  /* 送受信が問題なく行われた場合、ループから出る */
        }
        delay(1000);
    }

    return tbl_result;
}

void sfunc_serial_calc_format(BUTTON_DATA *tcl_bt_data){
    int tui_len = 0, tui_hitindex = 0;
    SERIAL_DATA tcl_ds3;

    tui_len = sst_read_data.length();
    if (tui_len == 4) {
        tcl_ds3.serial_type = sst_read_data.substring(0, 1);
        tcl_ds3.serial_num = sst_read_data.substring(1, 3);
        tcl_ds3.serial_val = sst_read_data.substring(3, 4);
        
        tcl_bt_data->button_type = (int)tcl_ds3.serial_type.toInt();
        tcl_bt_data->button_num = (int)tcl_ds3.serial_num.toInt();
        tcl_bt_data->button_val1 = (int)tcl_ds3.serial_val.toInt(); 
        // Serial.println(tcl_bt_data->button_val1);    /* debug用 */
    } else if (tui_len == 9) {
        tcl_ds3.serial_type = sst_read_data.substring(0, 1);
        tcl_ds3.serial_num = sst_read_data.substring(1, 3);

        if (sst_read_data.indexOf('-', 3) != -1) {
            /* 負の値 */ 
            tui_hitindex = sst_read_data.lastIndexOf('-'); 
            tcl_ds3.serial_val = sst_read_data.substring(tui_hitindex, tui_len);
            // Serial.println(data.substring(tui_hitindex, tui_len));   /* debug用 */
        } else {
            /* 正の値 */
            tcl_ds3.serial_val = sst_read_data.substring(4, tui_len);
            // Serial.println(data.substring(4, len));  /* debug用 */
        }
        tcl_bt_data->button_type = (int)tcl_ds3.serial_type.toInt();
        tcl_bt_data->button_num = (int)tcl_ds3.serial_num.toInt();
        tcl_bt_data->button_val2 = (int)tcl_ds3.serial_val.toInt();     
        // Serial.println(tcl_bt_data->button_val2);    /* debug用 */
    }
}