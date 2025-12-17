#include "Servo.h"

Servo servomotor;

int motor_esquerdo = 3;
int motor_direito = 11;
int led = 2;
int ldr = A5;
int buzzer = 7;
int trig = 4;
int echo = 9;

float objeto;
unsigned long duracao;
int distancia = 0;
int ldrvalor = 0;
int posicao = 37;
int contador_led = 0;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(motor_esquerdo, OUTPUT);
  pinMode(motor_direito, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  servomotor.attach(13);

  Serial.begin(9600);
}

void loop() {
  // Acender a luz em caso de noite
  ldrvalor = analogRead(ldr);
  if (ldrvalor >= 300) {
    digitalWrite(led, LOW);
  } else {
    digitalWrite(led, HIGH);
  }

  // Medir a distância do objeto
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duracao = pulseIn(echo, HIGH,11764);
  objeto = duracao / 58.0;

  if (objeto <= 50 && objeto != 0) {
    analogWrite(motor_esquerdo, 0);
    analogWrite(motor_direito, 0);
    for (contador_led == 0; contador_led < 3; contador_led++) {
      digitalWrite(led, HIGH);
      delay(500);
      digitalWrite(led, LOW);
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
    }
    delay(100);  
  } else {
    contador_led = 0;

    // Funcionar o motor responsável por girar as rodas
    if (distancia <= 300) {

      // Funcionar o motor responsável por plantar a cada 0,5 m
      if (distancia % 50 == 0 && distancia != 0) {
        for (posicao = 37; posicao <= 110; posicao += 1) {
          servomotor.write(posicao);
          analogWrite(motor_direito, 0);
          analogWrite(motor_esquerdo, 0);
          delay(15); 
        }
        for (posicao = 110; posicao >= 37; posicao -= 1) {
          servomotor.write(posicao);
          analogWrite(motor_direito, 0);
          analogWrite(motor_esquerdo, 0);
          delay(15); 
        }
      }
      analogWrite(motor_direito, 127);
      analogWrite(motor_esquerdo, 127);
      delay(20);
      analogWrite(motor_esquerdo, 127);
      analogWrite(motor_direito, 75);
    } else {
      analogWrite(motor_direito, 0);
      analogWrite(motor_esquerdo, 0);
    }
  }

  // Calcula a distância
  distancia = distancia + 1;
  Serial.println(distancia);
  delay(10);
}