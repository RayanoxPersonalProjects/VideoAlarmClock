void Log(String text, int valueToInsert) {
  String te = text;
  te.replace("%d", String(valueToInsert));
  Serial.println(te);
}
void Log(String text, unsigned long valueToInsert) {
  String te = text;
  te.replace("%lu", String(valueToInsert));
  Serial.println(te);
}

void Log(String text, char* valueToInsert) {
  String te = text;
  te.replace("%s", valueToInsert);
  Serial.println(te);
}
void Log(String text, String valueToInsert) {
  String te = text;
  te.replace("%s", valueToInsert);
  Serial.println(te);
}

// External notifications (trough LED)
void blinkLED(int pin, int countSwitchOn, double frequency) {
  int j;
  double t = 1/frequency;
  Serial.print("frequency = ");
  Serial.println(frequency);
  Serial.print("t = ");
  Serial.println(t);
  for(j = 0; j < countSwitchOn; j++) {
    
    Serial.print("LED (PIN ");
    Serial.print(pin);
    Serial.println("): ON");
    
    
    digitalWrite(pin, HIGH);
    delay(t * 1000);
    digitalWrite(pin, LOW);

    Serial.print("LED (PIN ");
    Serial.print(pin);
    Serial.println("): OFF");
    
    if(j+1 < countSwitchOn) {
      delay(t * 1000);
    }
  }
}
