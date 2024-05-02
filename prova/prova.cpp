#include <LiquidCrystal_I2C.h>  

LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2); 
int bt_blue_NEXT = 33;  // Define o pino para o botão azul (avançar)
int bt_green_YES = 34;  // Define o pino para o botão verde (sim)
int bt_yellow_BACK = 32;  // Define o pino para o botão amarelo (voltar)
int bt_red_CANCEL = 35;  // Define o pino para o botão vermelho (cancelar)
int h = 0, m = 0, s = 0;  
int time_setup = 1000;  
int count = 0;  
int layer = 0;  

void setup() {
  Serial.begin(115200);  
  for(int i=32;i<36;i++)
    pinMode(i,INPUT); 
  LCD.init();  // Inicializa o LCD
  LCD.backlight();  // Liga o backlight do LCD
  welcome();  // Exibe a mensagem de boas-vindas
}

void welcome() {
  LCD.clear();  // Limpa o LCD
  LCD.setCursor(1, 0);  
  LCD.print("SEJA BEM-VINDO!");  // Exibe a mensagem de boas-vindas
  delay(1000);  
  displayMenu(); 
}

void displayMenu() {
  LCD.clear();  
  LCD.setCursor(0, 0);  
  switch (layer) {  
    case 0:
      LCD.print("1. Contador");  //  opção 1 do menu
      break;
    case 1:
      LCD.print("2. Click");  // opção 2 do menu
      break;
    case 2:
      LCD.print("3. Clear");  // opção 3 do menu
      break;
  }
}

void countClick() {
  LCD.clear();  
  LCD.setCursor(0, 0);  
  LCD.print("Count Clicks"); 
  LCD.setCursor(0, 1);  
  while (true) {  
    if (digitalRead(bt_blue_NEXT) == HIGH) {  
      count++;  // Incrementa o contador de cliques
      LCD.setCursor(0,1);  
      LCD.print("Clicks: ");  // Exibe a etiqueta "Clicks: "
      LCD.print(count);  // Exibe o valor do contador
      delay(200);  
      while (digitalRead(bt_blue_NEXT) == HIGH) {} 
    }
    if (digitalRead(bt_yellow_BACK) == HIGH) {  // Verifica se o botão amarelo foi pressionado
      count = 0;  // Zera o contador de cliques
      LCD.setCursor(0, 1);  
      LCD.print("Clicks: "); 
      LCD.print(count);  // Exibe o valor zerado do contador
      delay(200);  
      return;  
    }
    if (digitalRead(bt_red_CANCEL) == HIGH) {  // Verifica se o botão vermelho foi pressionado
      exit(0);  
      LCD.clear(); 
      welcome(); 
    }
  }
}

void Clock() {
  LCD.clear();  
  LCD.setCursor(1, 0);  
  LCD.print("Clock");  // Exibe o título do relógio
  while (true) { 
    LCD.setCursor(0, 1);  
    LCD.print(h < 10 ? "0" : "");  
    LCD.print(h);  // Exibe as horas
    LCD.print(":");  // Exibe dois pontos
    LCD.print(m < 10 ? "0" : "");  // Adiciona um zero à esquerda se necessário para os minutos
    LCD.print(m);  // Exibe os minutos
    LCD.print(":");  // Exibe dois pontos
    LCD.print(s < 10 ? "0" : "");  // Adiciona um zero à esquerda se necessário para os segundos
    LCD.print(s);  // Exibe os segundos
    delay(time_setup);  
    s++;  // Incrementa os segundos
    if (s == 60) {  // Se os segundos atingirem 60
      s = 0;  // Reinicia os segundos
      m++;  // Incrementa os minutos
      if (m == 60) {  // Se os minutos atingirem 60
        m = 0;  // Reinicia os minutos
        h++;  
        if (h == 24) {  // Se as horas atingirem 24
          h = 0;  // Reinicia as horas
        }
      }
    }
    if (digitalRead(bt_blue_NEXT) == HIGH) {  // Verifica se o botão azul foi pressionado
      time_setup = 250;  
    }
    if (digitalRead(bt_yellow_BACK) == HIGH) {  // Verifica se o botão amarelo foi pressionado
      time_setup = 1000; 
    }
    if (digitalRead(bt_red_CANCEL) == HIGH) {  // Verifica se o botão vermelho foi pressionado
      LCD.clear();  
      welcome();  // Exibe a mensagem de boas-vindas
      break; 
    }
  }
}

// Função para limpar dados
void Clear() {
  LCD.clear();  // Limpa o LCD
  LCD.setCursor(0, 0);  // Define o cursor na posição (0, 0)
  LCD.print("Deseja zerar ");  // Exibe a mensagem de confirmação de zerar dados
  LCD.setCursor(0, 1);  // Define o cursor na posição (0, 1)
  LCD.print("todos os dados?");  // Exibe a mensagem de confirmação de zerar dados
  unsigned long startTime = millis();  // Armazena o tempo atual em millisegundos
  while (millis() - startTime <= 3000) {  // Loop por 3 segundos
    if (digitalRead(bt_green_YES) == HIGH) {  // Verifica se o botão verde foi pressionado
      LCD.clear();  // Limpa o LCD
      LCD.print("Dados zerados!");  // Exibe a mensagem de dados zerados
      delay(1000);  // Aguarda 1 segundo
      count = 0;  // Zera o contador de cliques
      h = m = s = 0;  // Zera o relógio
      layer = 0;  // Reinicia o menu para a opção inicial
      displayMenu();  // Exibe o menu
      return;  // Retorna após zerar os dados
    }
    if (digitalRead(bt_red_CANCEL) == HIGH) {  // Verifica se o botão vermelho foi pressionado
      LCD.clear();  // Limpa o LCD
      welcome();  // Exibe a mensagem de boas-vindas
      return;  // Retorna se o botão vermelho for pressionado
    }
  }
}

void loop() {
  while (true) {  // Loop principal
    if (digitalRead(bt_green_YES) == HIGH) {  // Verifica se o botão verde foi pressionado
      delay(100);  // Aguarda 100ms
      if (layer == 2) {  // Se a opção selecionada for "Clear"
        Clear();  // Chama a função Clear()
      } else {
        layer++;  // Incrementa a camada do menu
        if(layer==1){
          Clock();  // Chama a função Clock()
        }else if(layer==2){
          countClick();  // Chama a função countClick()
        }
        displayMenu();  // Exibe o menu
      }
    } else if (digitalRead(bt_yellow_BACK) == HIGH) {  // Verifica se o botão amarelo foi pressionado
      delay(100);  // Aguarda 100ms
      layer--;  // Decrementa a camada do menu
      if (layer < 0) layer = 0;  // Garante que a camada não seja menor que 0
      displayMenu();  // Exibe o menu
    } else if (digitalRead(bt_red_CANCEL) == HIGH) {  // Verifica se o botão vermelho foi pressionado
      delay(100);  // Aguarda 100ms
      layer = 0;  // Reinicia a camada do menu para a opção inicial
      welcome();  // Exibe a mensagem de boas-vindas
    } else if (digitalRead(bt_blue_NEXT) == HIGH) {  // Verifica se o botão azul foi pressionado
      delay(100);  // Aguarda 100ms
      layer++;  // Incrementa a camada do menu
      if (layer > 2) layer = 2;  // Garante que a camada não seja maior que 2
      displayMenu();  // Exibe o menu
    }
  }
}
