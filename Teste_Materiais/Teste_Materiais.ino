#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <String.h>
//(Adicionar LCD)

//DEFINE AS PORTAS DOS MOTORES, BUZZER E BOTAO QUE INICIA O JOGO
#define botaoMenosA 3 
#define botaoMaisA 4
#define botaoMenosL 8
#define botaoMaisL 9
#define botaoInicio 12
#define botaoLancar 11
#define motor1 A1
#define motor0 A0
#define servo 5
#define buzzer 9

int angulo = 0;
int valBotaoMenosA, valBotaoMaisA;
int valBotaoMenosL, valBotaoMaisL;
int inicia,lanca; 

Servo servoMotor;  
LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void verificarAltura(){                       //AJUSTA A DIREÇÃO (ESQUERDA/DIREITA) PARA LANCAMENTO
  
  valBotaoMenosA = digitalRead(botaoMenosA); 
  valBotaoMaisA = digitalRead(botaoMaisA); 

  if(valBotaoMaisA == HIGH ){
    
    angulo = angulo + 3;
    Serial.println("Ajuste altura okay");
  }
  if(valBotaoMenosA == HIGH){
    
    angulo = angulo - 3;
    Serial.println("Ajuste altura okay");
  }
  //definindo o valor/posição do servomotor
  servoMotor.write(angulo); 
  delay(1000);  

  
}

void verificarLateral(){                      //AJUSTA A ALTITUDE PARA LANCAMENTO
  
  valBotaoMenosL = digitalRead(botaoMenosL); 
  valBotaoMaisL = digitalRead(botaoMaisL); 

  if(valBotaoMaisL == HIGH ){
    
    digitalWrite(motor1,HIGH);
    digitalWrite(motor0, LOW);
    Serial.println("Ajuste lateral okay");
  }
  if(valBotaoMenosL == HIGH){
    
    digitalWrite(motor1,LOW);
    digitalWrite(motor0, HIGH);
    Serial.println("Ajuste lateral okay");
  }
  delay(100);  

  
}

void lancamento(){        //CONTAGEM LANCAMENTO
 
  tone(buzzer, 260);
  delay(500);
  noTone(buzzer);
  delay(1000);
  tone(buzzer, 260);
  delay(500);
  noTone(buzzer);
  delay(1000);
  tone(buzzer, 260);
  delay(1000);
  noTone(buzzer);

  Serial.println("Lancou!");
  delay(3000);
} 


void setup() {                          //IN ICIALIZA OS PINOS
 
  servoMotor.attach(servo); 
  lcd.init();
  lcd.backlight();
  
  pinMode(botaoMenosA,INPUT);
  pinMode(botaoMaisA,INPUT);
  pinMode(botaoMenosL,INPUT);
  pinMode(botaoMaisL,INPUT);
  pinMode(botaoInicio,INPUT);
  pinMode(botaoLancar,INPUT);
  pinMode(buzzer,OUTPUT);
} 

void loop() 
{ 

  inicia = digitalRead(botaoInicio);
  lanca = digitalRead(botaoLancar);
  int i = 0;

  if(inicia == HIGH){               //SE LIGAREM O BOTÃO O PROGRAMA INICIA
    while(i<6){                     //6 RODADAS ENTRE 2 JOGADORES
      if(i%2 == 0){
        lcd.clear();
        lcd.setCursor(2,1);
        lcd.print("Jogador 1");
        Serial.println("Jogador 1");
      }
      else{
        lcd.clear();
        lcd.setCursor(2,1);
        lcd.print("Jogador 2");
        Serial.println("Jogador 2");
      }
      if(lanca == HIGH){            //LANCAMENTO
        lancamento();
      }
      else{                         //ENQUANTO NÃO INICIA O LANCAMENTO, VERIFICA AS POSIÇÕES
        verificarLateral();
        verificarAltura();
      }
    }
  }
}
