## Descrição do Projeto

### Imagem do projeto


![TinkerCAD](./tinkercad.png)

### Links
TinkerCAD

YouTube

## Código do Arduino

```c
const int dataPin = 2;   // DS
const int latchPin = 4;  // ST_CP
const int clockPin = 3;  // SH_CP
const int buzzerPin = 7;

// Mapeamento dos segmentos: 0 = apagado, 1 = aceso (cátodo comum)
byte numeros[10] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111  // 9
};

// Pinos do HC-SR04
const int trigPin = 9;
const int echoPin = 10;

// Variáveis do controle do buzzer
unsigned long previousMillis = 0;
bool buzzerState = false;
int beepInterval = 1000;            // Intervalo entre bipes
int beepOnDuration = 50;            // Duração do bip (em ms)
unsigned long beepStartMillis = 0;
bool beepActive = false;

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  long distancia = medirDistancia();  // em cm
  int numero = constrain(distancia / 10, 0, 9);

  mostrarDisplay(numero);

  // --- Controle de beep proporcional à distância ---
  // Distância de 2 a 400 cm → intervalo de 0 a 1000 ms
  beepInterval = map(distancia, 2, 400, 0, 1000);
  beepInterval = constrain(beepInterval, 0, 1000);

  unsigned long currentMillis = millis();

  if (beepInterval == 0) {
    // Objeto muito próximo: buzzer contínuo
    digitalWrite(buzzerPin, HIGH);
  } else {
    // Alternância do bip com base no tempo
    if (!beepActive && currentMillis - previousMillis >= beepInterval) {
      // Inicia um novo bip
      digitalWrite(buzzerPin, HIGH);
      beepStartMillis = currentMillis;
      previousMillis = currentMillis;
      beepActive = true;
    }

    // Desliga o bip após a duração
    if (beepActive && currentMillis - beepStartMillis >= beepOnDuration) {
      digitalWrite(buzzerPin, LOW);
      beepActive = false;
    }
  }
}

void mostrarDisplay(int num) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, numeros[num]);
  digitalWrite(latchPin, HIGH);
}

long medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracao = pulseIn(echoPin, HIGH);
  return duracao * 0.034 / 2;
}
```
