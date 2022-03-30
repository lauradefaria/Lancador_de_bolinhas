#include<Servo.h>
#define potenciometro A2
#define servo1 3
#define servo2 5
int valorPotenciometro;

Servo servoEsquerda;
Servo servoDireita;

void verificarAltura(){
  valorPotenciometro = analogRead(potenciometro); 
 
  //mapeando o valor para a escala do servo (entre 0 e 45)
  valorPotenciometro = map(valorPotenciometro, 0, 1023, 0, 45); 
  Serial.println(valorPotenciometro);
  
  //definindo o valor/posição do servomotor
  servoEsquerda.write(valorPotenciometro); 
  servoDireita.write(valorPotenciometro); 
  delay(15);   

  Serial.println("Ajuste altura okay");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servoEsquerda.attach(servo1);
  servoDireita.attach(servo2);

  pinMode(potenciometro,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  verificarAltura();
  delay(3000);
}
