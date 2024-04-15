
#define ledRed 8
#define ledGreen 9
#define ledYellow 10
Serial.begin(9600);

pinMode(ledRed, OUTPUT);
pinMode(ledGreen, OUTPUT);
pinMode(ledYellow,OUTPUT);
digitalWrite (ledRed, LOW);

digitalWrite (ledGreen, LOW);
digitalWrite (ledYellow, LOW);
void loop() {
while (Serial.available() > 0) {
leitura = Serial.read();
if (leitura == 'r' || leitura =='R'){
digitalWrite(ledRed,!digitalRead(ledRed));
}
else if (leitura == 'g' || leitura =='G'){ digitalWrite(ledGreen,!digitalRead(ledGreen));
}
else if (leitura == 'y' || leitura =='Y'){
digitalWrite(ledYellow,!digitalRead(ledYellow));
}
Serial.println(leitura);
}
}