/*
====================================================
 ROBÔ SEGUIDOR DE LINHA

 Arduino Uno + L298N + 2 Sensores 
====================================================
*/

// Sensores
#define SENSOR_ESQ 2
#define SENSOR_DIR 3

// Ponte H L298N
#define ENA 5
#define ENB 6

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

// Velocidade dos motores
int velocidade = 180;
int velocidadeCurva = 120;

void setup() {

  pinMode(SENSOR_ESQ, INPUT);
  pinMode(SENSOR_DIR, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);

  Serial.println("================================");
  Serial.println("Seguidor de Linha");
  Serial.println("Criado por Xavier");
  Serial.println("================================");

  parar();
}

void loop() {

  int esq = digitalRead(SENSOR_ESQ);
  int dir = digitalRead(SENSOR_DIR);

  Serial.print("Esquerda: ");
  Serial.print(esq);
  Serial.print("  Direita: ");
  Serial.println(dir);

  /*
     TESTE INICIAL

     Normalmente:
     PRETO = LOW
     BRANCO = HIGH

     Caso o robô faça o contrário,
     troque LOW por HIGH abaixo.
  */

  if (esq == LOW && dir == LOW) {
    frente();
  }
  else if (esq == LOW && dir == HIGH) {
    virarEsquerda();
  }
  else if (esq == HIGH && dir == LOW) {
    virarDireita();
  }
  else {
    procurarLinha();
  }

  delay(10);
}

// =======================
// Movimento para frente
// =======================
void frente() {

  analogWrite(ENA, velocidade);
  analogWrite(ENB, velocidade);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// =======================
// Virar para esquerda
// =======================
void virarEsquerda() {

  analogWrite(ENA, velocidadeCurva);
  analogWrite(ENB, velocidade);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// =======================
// Virar para direita
// =======================
void virarDireita() {

  analogWrite(ENA, velocidade);
  analogWrite(ENB, velocidadeCurva);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// =======================
// Procurar a linha
// =======================
void procurarLinha() {

  analogWrite(ENA, 120);
  analogWrite(ENB, 120);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// =======================
// Parar motores
// =======================
void parar() {

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}