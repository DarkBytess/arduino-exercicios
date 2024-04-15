void setup()
{

 pinMode(CHAVE, INPUT);
 Serial.begin(9600); 
}
void loop()

 if(digitalRead(CHAVE)) 
 
 Serial.println("Botao Pressionado\n"); 
Pressionado"
 }

 else //Senão
 {
 Serial.println("Botao Despressionado\n"); // Imprime no Serial Monitor "Botão
Despressionado"
 }

 delay(250); //Delay de 250 milissegundos
}