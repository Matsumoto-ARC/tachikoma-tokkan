#include <Servo.h>

#define SERVO_PIN1   (3) /* SERVO_PIN1  */
#define SERVO_PIN2   (5)
#define SERVO_PIN3   (6)
#define SERVO_PIN4   (9)
#define SERVO_PIN5   (10)

#define BASE_SERVO_INIT_ANGLE   (90)
#define ELBOW_SERVO_INIT_ANGLE  (90)
#define WRIST_SERVO_INIT_ANGLE  (90)
#define FINGER_SERVO_INIT_ANGLE (90)

/* 関数定義 */
void calc_format(String, int *, int *, int *, int *);
void Digital_Button_Check(int, int);
void Analog_Button_Check(int, int);
void Operation_Servo(void);
void Operateion_Motor(void);

/* Global変数 */
Servo   base_servo, elbow_servo, wrist_servo, finger_servo;
int start_bt, select_bt, l1_bt, r1_bt, triangle_bt, circle_bt, square_bt, cross_bt;

void setup(){
    Serial.begin(9600);
    Serial.setTimeout(5);
    Serial.flush();

    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    /* それぞれのサーボに割り当てるGPIO PINを設定 */
/*     base_servo.attach(SERVO_PIN1);
    elbow_servo.attach(SERVO_PIN2);
    wrist_servo.attach(SERVO_PIN3);
    finger_servo.attach(SERVO_PIN4); */

    /* それぞれのサーボの初期角度を設定 */
/*     base_servo.write(BASE_SERVO_INIT_ANGLE);
    elbow_servo.write(ELBOW_SERVO_INIT_ANGLE);
    wrist_servo.write(WRIST_SERVO_INIT_ANGLE);
    finger_servo.write(FINGER_SERVO_INIT_ANGLE); */
}

void loop(){
    String  read_data;
    int bt_type = 0, bt_num = 0, bt_val1 = 0, bt_val2 = 0;

    read_data = Serial.readStringUntil('\n');
    if (read_data != ""){
        // Serial.println(read_data);  /* debug用 */
        calc_format(read_data, &bt_type, &bt_num, &bt_val1, &bt_val2);
    }
    if (bt_type == 1) {
        Digital_Button_Check(bt_num, bt_val1);
        Operation_Servo();
    } else if (bt_type == 2) {
        Analog_Button_Check(bt_num, bt_val2);
        Operateion_Motor();
    }
    delay(10);
}

void calc_format(String data, int *type, int *num, int *val1, int *val2){
    int len, i, hit_index;
    String ds3_type, ds3_num, ds3_val1, ds3_val2;

    len = data.length();
    if (len == 4) {
        ds3_type = data.substring(0, 1);
        ds3_num = data.substring(1, 3);
        ds3_val1 = data.substring(3, 4);
        
        *type = (int)ds3_type.toInt();
        *num = (int)ds3_num.toInt();
        *val1 = (int)ds3_val1.toInt(); 
        Serial.println(*val1); 
    }else if (len == 9){
        ds3_type = data.substring(0, 1);
        ds3_num = data.substring(1, 3);

        if (data.indexOf('-', 3) != -1) {
            /* 負の値 */ 
            hit_index = data.lastIndexOf('-'); 
            ds3_val2 = data.substring(hit_index, len);
            // Serial.println(data.substring(hit_index, len));
        } else {
            /* 正の値 */
            ds3_val2 = data.substring(4, len);
            // Serial.println(data.substring(4, len));
        }
        *type = (int)ds3_type.toInt();
        *num = (int)ds3_num.toInt();
        *val2 = (int)ds3_val2.toInt();        
        Serial.println(*val2); 
    }
}

void Digital_Button_Check(int num, int val){

    switch (num) {
        case 0:     /* SELCTボタン */
            if (val == 1){
                select_bt = 1;
            } else if (val == 0) {
                select_bt = 0;
            }
            break;
        case 3:     /* STARTボタン */
            if (val == 1){
                start_bt = 1;
            } else if (val == 0) {
                start_bt = 0;
            }
            break;
        case 10:    /* L1ボタン */
            if (val == 1) {
                l1_bt = 1;
            } else if (val == 0) {
                l1_bt= 0;
            }
            break;
        case 11:    /* R1ボタン */
            if (val == 1) {
                r1_bt = 1;
            } else if (val == 0) {
                r1_bt = 0;
            }
            break;
        case 12:    /* △ボタン */
            Serial.println(12);     /* debug用 */
            if (val == 1) {
                triangle_bt = 1:
            } else if (val == 0) {
                triangle_bt = 0;
            }
            break;
        case 13:    /* ○ボタン */
            Serial.println(13);     /* debug用 */
            if (val == 1) {
                circle_bt = 1;
            } else if (val == 0) {
                circle_bt = 0;
            }
            break;
        case 14:    /* □ボタン */
            Serial.println(14);     /* debug用 */
            if (val == 1) {
                square_bt = 1;
            } else if (val == 0) {
                square_bt = 0;
            }
            break;
        case 15:    /* ×ボタン */
            Serial.println(15);     /* debug用 */
            if (val == 1) {
                cross_bt = 1;
            } else if (val == 0) {
                cross_bt = 0;
            }
            break;
        default:    /* その他ボタン(十字キー, L2, R2, L3, R3) */
            break;
    }
}

void Operateion_Servo(void) {
    if (triangle_bt == 1 && (l1_bt == 1 && r1_bt != 1))  {

    } else if (triangle_bt == 1 && (l1_bt != 1 && r1_bt == 1)) {

    } else {

    }
}

void Operateion_Motor(void) {

}