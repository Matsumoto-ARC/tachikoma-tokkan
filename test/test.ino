#include <Servo.h>

Servo myservo;

boolean clockWise = true;   //DCモーターの回転方向（true:右、false:左）
int val = 0;    //デューティー比

const int SERVO_MAX_ANGLE = 180; //サーボモーター最大値（180deg）
const int SERVO_MIN_ANGLE = 0; //サーボモーター最小値（0deg）
boolean SVclock = true;     //サーボモーターの回転方向
int SVAngle = 0;

void DCMotor(void);     //DCモーター制御
void SVMotor(void);     //サーボモーター制御

void setup() {
    /*DCモーター*/
    pinMode(23, OUTPUT);    //右DCモータ IN1
    pinMode(24, OUTPUT);    //右DCモータ IN2
    pinMode(25, OUTPUT);    //左DCモータ IN1
    pinMode(26, OUTPUT);    //左DCモータ IN2

    analogWrite(6, val);    //右モータードライバ
    analogWrite(7, val);    //左モータードライバ
    digitalWrite(23, LOW);
    digitalWrite(24, LOW);
    digitalWrite(25, LOW);
    digitalWrite(26, LOW);

    /*サーボモーター*/
    myservo.attach(2);
    myservo.write(SVAngle);
}

void loop() {
    DCMotor();
    SVMotor();
}
/*DCモーター制御*/
void DCMotor() {
    if(clockWise==true) {
        //右回転
        digitalWrite(23, HIGH);
        digitalWrite(24, LOW);
        digitalWrite(25, LOW);
        digitalWrite(26, HIGH);
        for(val=0;val<255;val++) {
            analogWrite(6, val);
            analogWrite(7, val);
        }
        clockWise = false;
    }
    else {
        //左回転
        digitalWrite(23, LOW);
        digitalWrite(24, HIGH);
        digitalWrite(25, HIGH);
        digitalWrite(26, LOW);
        for(val=0;val<255;val++) {
            analogWrite(6, val);
            analogWrite(7, val);
        }
        clockWise = true;
    }
    delay(1000);
}
/*サーボモーター制御*/
void SVMotor() {
    if(SVclock==true) {
        while(SVAngle<SERVO_MAX_ANGLE) {   //角度が最大値（180deg）に達するまで
            myservo.write(SVAngle);
            SVAngle++;
        }
        SVclock = false;
    }
    else {
        while(SVAngle>SERVO_MIN_ANGLE) {   //角度が最小値（0deg）に達するまで
            myservo.write(SVAngle);
            SVAngle--;
        }
        SVclock = true;
    }
    delay(1000);
}