#include <Servo.h>
#include <SoftwareSerial.h>

#define SERVO_PIN1   (3) /* SERVO_PIN1  */
#define SERVO_PIN2   (5)
#define SERVO_PIN3   (6)
#define SERVO_PIN4   (9)
#define SERVO_PIN5   (10)

#define BASE_SERVO_INIT_ANGLE   (90)
#define ELBOW_SERVO_INIT_ANGLE  (90)
#define WRIST_SERVO_INIT_ANGLE  (90)
#define FINGER_SERVO_INIT_ANGLE (90)

Servo   base_servo, elbow_servo, wrist_servo, finger_servo;

void setup(){
    /* それぞれのサーボに割り当てるGPIO PINを設定 */
    base_servo.attach(SERVO_PIN1);
    elbow_servo.attach(SERVO_PIN2);
    wrist_servo.attach(SERVO_PIN3);
    finger_servo.attach(SERVO_PIN4);

    /* それぞれのサーボの初期角度を設定 */
    base_servo.write(BASE_SERVO_INIT_ANGLE);
    elbow_servo.write(ELBOW_SERVO_INIT_ANGLE);
    wrist_servo.write(WRIST_SERVO_INIT_ANGLE);
    finger_servo.write(FINGER_SERVO_INIT_ANGLE);
}

void loop(){

}