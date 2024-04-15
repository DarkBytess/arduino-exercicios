#define LED 13 
void setup()
{
 pinMode(LED, OUTPUT);
}
void loop()
{
 digitalWrite(LED, HIGH); 
 delay(1000); 
 digitalWrite(LED, LOW);
 y(1000); 
}