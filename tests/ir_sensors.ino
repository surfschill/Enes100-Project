const int analogPin = A0 ;
void setup() {
    Enes.begin(9600); 
}

void loop() {
    int flameValue = analogRead(analogPin);
    Enes.print("Flame Sensor Value: ");
    Enes.println(flameValue);
    delay(100);
} // read flame sensor values (40-50 = fire on, 850-900 = fire off)