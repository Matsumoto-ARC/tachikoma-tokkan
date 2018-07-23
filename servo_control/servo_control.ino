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
void Operation_Servo(int, int);

/* Global変数 */
Servo   base_servo, elbow_servo, wrist_servo, finger_servo;

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
        Serial.println(read_data);  /* debug用 */
        calc_format(read_data, &bt_type, &bt_num, &bt_val1, &bt_val2);
    }
    if (bt_type == 1) {
        Operation_Servo(bt_num, bt_val1);
    } else if (bt_type == 2) {
        Operateion_Motor(bt_num, bt_val2);
    }
    delay(10);
}

void calc_format(String data, int *type, int *num, int *val1, int *val2){
    int len, i;
    String ds3_type, ds3_num, ds3_val1, ds3_val2;

    len = data.length();
    if (len == 4) {
        ds3_type = data.substring(0, 1);
        ds3_num = data.substring(1, 3);
        ds3_val1 = data.substring(3, 4);
        
        *type = (int)ds3_type.toInt();
        *num = (int)ds3_num.toInt();
        *val1 = (int)ds3_val1.toInt(); 
    }else if (len == 9){
        ds3_type = data.substring(0, 1);
        ds3_num = data.substring(1, 3);
        
        for (i = 3; i++; i < len) {
            if (data.indexOf('0', 3) == -1) {
                /* 負の値 */ 
                if (data.indexOf('-', i) == -1) {
                    ds3_val2 = data.substring(i - 1, 9);
                    // Serial.println(data.substring(i - 1, 9));
                    i = 8;
                }
            } else {
                /* 正の値 */
                if (data.indexOf('0', i) == -1) {
                    ds3_val2 = data.substring(i, 9);
                    // Serial.println(data.substring(i, 9));
                    i = 8;
                }
            }
        }
        *type = (int)ds3_type.toInt();
        *num = (int)ds3_num.toInt();
        *val2 = (int)ds3_val2.toInt();         
    }

}

void Operation_Servo(int num, int val){

    switch (num) {
        case 0:     /* SELCTボタン */
            break;
        case 3:     /* STARTボタン */
            if (val == 1){
                digitalWrite(8, HIGH);
                digitalWrite(9, HIGH);
                digitalWrite(10, HIGH);
                digitalWrite(11, HIGH);
                delay(3000);
                digitalWrite(8, LOW);
                digitalWrite(9, LOW);
                digitalWrite(10, LOW);
                digitalWrite(11, LOW);  
            } else if (val == 0) {
                /* digitalWrite(8, LOW);
                digitalWrite(9, LOW);
                digitalWrite(10, LOW);
                digitalWrite(11, LOW);   */              
            }
        case 12:    /* △ボタン */
            Serial.println(12);     /* debug用 */
            if (val == 1) {
                digitalWrite(8, HIGH);
            } else if (val == 0) {
                digitalWrite(8, LOW);
            }
            break;
        case 13:    /* ○ボタン */
            Serial.println(13);     /* debug用 */
            if (val == 1) {
                digitalWrite(9, HIGH);
            } else if (val == 0) {
                digitalWrite(9, LOW);
            }
            break;
        case 14:    /* □ボタン */
            Serial.println(14);     /* debug用 */
            if (val == 1) {
                digitalWrite(10, HIGH);
            } else if (val == 0) {
                digitalWrite(10, LOW);
            }
            break;
        case 15:    /* ×ボタン */
            Serial.println(15);     /* debug用 */
            if (val == 1) {
                digitalWrite(11, HIGH);
            } else if (val == 0) {
                digitalWrite(11, LOW);
            }
            break;
        default:
            break;
    }
}

void Operateion_Motor(int, int) {

}