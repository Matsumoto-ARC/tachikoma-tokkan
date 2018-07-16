void setup(){
    // 
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
    // 
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println(1);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println(0);
    delay(1000);
}