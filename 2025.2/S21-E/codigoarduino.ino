// -----------------------------------------
// PINOS DO CD4511 (Entradas BCD)
// -----------------------------------------
const int pinoA = 4;
const int pinoB = 5;
const int pinoC = 6;
const int pinoD = 7;

// -----------------------------------------
// PINO DO BUZZER
// -----------------------------------------
const int buzzer = 2;

// -----------------------------------------
// BOTÃO (na casa 3)
// -----------------------------------------
const int botao = 3;

// Variável que será atualizada pelo botão
int MENORZIN = 940;   

// -----------------------------------------
// PINOS DOS POTENCIOMETROS
// -----------------------------------------
const int pinosPot[] = {A0, A1, A2, A3};
const int totalPot = 4;

void setup() {
  pinMode(pinoA, OUTPUT);
  pinMode(pinoB, OUTPUT);
  pinMode(pinoC, OUTPUT);
  pinMode(pinoD, OUTPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(botao, INPUT_PULLUP);  // botão com pull-up interno

  Serial.begin(9600);
}

// -----------------------------------------
// FUNÇÃO PARA ENVIAR NÚMERO AO CD4511
// -----------------------------------------
void escreveNoDisplay(int numero) {
  numero = constrain(numero, 0, 9);

  digitalWrite(pinoA, numero & 0x01);
  digitalWrite(pinoB, numero & 0x02);
  digitalWrite(pinoC, numero & 0x04);
  digitalWrite(pinoD, numero & 0x08);
}

void loop() {
  int menorValor = 1023;
  int valores[4];

  // Lê todos os potenciômetros e detecta o menor
  for (int i = 0; i < totalPot; i++) {
    valores[i] = analogRead(pinosPot[i]);
    if (valores[i] < menorValor) {
      menorValor = valores[i];
    }
  }

  // -----------------------------------------
  // SE O BOTÃO FOR APERTADO → atualiza MENORZIN
  // -----------------------------------------
  if (digitalRead(botao) == LOW) { 
    delay(50); // debounce simples
    if (digitalRead(botao) == LOW) { // confirma pressionamento
      MENORZIN = menorValor - 100; // salva novo limite
      Serial.print(">>> NOVO MENORZIN DEFINIDO: ");
      Serial.println(MENORZIN);
      delay(400); // evita múltiplas gravações
    }
  }

  // -----------------------------------------
  // REGRA DE TOLERÂNCIA PARA O NÚMERO 9
  // -----------------------------------------
  int numeroDisplay;

  if (menorValor >= MENORZIN) {
    numeroDisplay = 9;     // trava em 9
  } else {
    numeroDisplay = map(menorValor, 0, MENORZIN - 1, 0, 8);
  }

  escreveNoDisplay(numeroDisplay);

  // -----------------------------------------
  // MONITOR SERIAL
  // -----------------------------------------
  Serial.print("P0: "); Serial.print(valores[0]);
  Serial.print(" | P1: "); Serial.print(valores[1]);
  Serial.print(" | P2: "); Serial.print(valores[2]);
  Serial.print(" | P3: "); Serial.print(valores[3]);
  Serial.print(" | MENOR: "); Serial.print(menorValor);
  Serial.print(" | MENORZIN: "); Serial.print(MENORZIN);
  Serial.print(" | DISPLAY: "); Serial.println(numeroDisplay);

  // -----------------------------------------
  // BUZZER → som sempre agudo (2000 Hz)
  // -----------------------------------------
  int intervalo = map(menorValor, 0, 1023, 50, 800);

  if (numeroDisplay < 9) {
    tone(buzzer, 2000);
    delay(intervalo);
    noTone(buzzer);
    delay(intervalo);
  } else {
    noTone(buzzer);
    delay(200);
  }
}
