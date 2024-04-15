#define botaoA 6
#define botaoB 7
#define ledXOR 8
#define ledOU 9
#define ledE 10 

boolean valA= 0;
boolean valB = 0;

void setup() 

pinMode(ledXOR, OUTPUT);

pinMode(ledOU, OUTPUT);

pinMode(ledE, OUTPUT);

/configura os pinos onde os botões estão conectados

pinMode(botaoA, INPUT);

pinMode(botaoB, INPUT);

void loop()

Lê o estado dos Botões valA digitalRead(botaoA) valB= digitalRead(botaoB).{

}