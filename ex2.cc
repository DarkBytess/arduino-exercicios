int led = 9; 
int fade = 5; 
void setup() {


pinMode(led, OUTPUT);
}
void loop() {


analogWrite(led, brilho);


brilho = brilho + fade;


if (brilho == 0 || brilho == 255) {
fade = -fade ;
}


delay(30);
}