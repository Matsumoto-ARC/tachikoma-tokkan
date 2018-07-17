#define led (12)
void setup(){
    // 
    Serial.begin(9600);
    pinMode(led, OUTPUT);
}

void loop(){
    //
    digitalWrite(led, HIGH);
    Serial.println(1);
    delay(1000);
    digitalWrite(led, LOW);
    Serial.println(0);
    delay(1000);
}