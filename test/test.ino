static String   sst_read_data;

void setup() {
    Serial1.begin(9600);
    Serial1.setTimeout(5);
    Serial1.flush();

    sst_read_data = "";

    pinMode(13, OUTPUT);
    pinMode(22, OUTPUT);
    pinMode(23, OUTPUT);
}

void loop() {
    sst_read_data = Serial.readStringUntil('\n');
    Serial.println(sst_read_data);  /* debug用 */
    if (sst_read_data != ""){
        digitalWrite(13, HIGH);
        delay(100);
        digitalWrite(13, LOW);
        delay(100);
    } else {
        digitalWrite(23, HIGH);
        delay(100);
        digitalWrite(23, LOW);
        delay(100);
    }
}
