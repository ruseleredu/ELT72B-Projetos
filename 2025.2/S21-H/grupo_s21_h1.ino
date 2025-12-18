// ----------------------------
// PINAGEM
// ----------------------------
#define MOTOR 13
#define LED_VERDE 11
#define LED_VERMELHO 12

// Entradas BCD do CD4511 (A = LSB)
#define BCD_A 5
#define BCD_B 6
#define BCD_C 7
#define BCD_D 8

#define TRIG 9
#define ECHO 10

// ----------------------------
// PARÂMETROS
// ----------------------------
const float LIMITE_CM = 15.0;   // distância de ativação (em cm)
const int TEMPO_FLUXO = 9;     // segundos de funcionamento do motor
const int ESPERA_POS_DETECCAO_MS = 1000; // espera antes de ligar motor (1s)
const int ESPERA_REENTRADA_MS = 3000;    // espera quando objeto permanece (3s)

// ----------------------------
// Funções auxiliares
// ----------------------------

// Escreve número (0..9) nas entradas BCD do CD4511.
// Observação: A = LSB (bit 0) ligado ao pino BCD_A (Arduino 5)
void escreveBCD(int n) {
  n = constrain(n, 0, 9);
  digitalWrite(BCD_A, (n >> 0) & 1); // bit 1 (LSB)
  digitalWrite(BCD_B, (n >> 1) & 1); // bit 2
  digitalWrite(BCD_C, (n >> 2) & 1); // bit 4
  digitalWrite(BCD_D, (n >> 3) & 1); // bit 8 (MSB)
}

// "Desliga" o display colocando as entradas BCD em 0.
// Observação: com CD4511 isso mostrará '0' (se quiser apagar completamente,
// é preciso controlar o pino BL/BI do CI; aqui mantemos 0 por simplicidade).
void limpaDisplay() {
  escreveBCD(0);
  digitalWrite(BCD_A, LOW);
  digitalWrite(BCD_B, LOW);
  digitalWrite(BCD_C, LOW);
  digitalWrite(BCD_D, LOW);
}

// Lê distância única do HC-SR04 com timeout (em us). Retorna distância em cm.
// timeout_us: tempo máximo que pulseIn espera (ex: 25000 -> 25 ms)
float leituraUltrassonicaUmaLeitura(unsigned long timeout_us = 25000UL) {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  unsigned long duracao = pulseIn(ECHO, HIGH, timeout_us);
  if (duracao == 0) return 999.0; // timeout - retorna valor grande
  return duracao * 0.0343f / 2.0f;
}

// Faz média de N leituras para estabilizar leitura do HC-SR04.
float distanciaMedia(int amostras = 3, unsigned long timeout_us = 25000UL) {
  float soma = 0.0;
  int validas = 0;
  for (int i = 0; i < amostras; i++) {
    float d = leituraUltrassonicaUmaLeitura(timeout_us);
    if (d < 900.0) { // considerar válidas leituras menores que 900 cm
      soma += d;
      validas++;
    }
    delay(20); // pequena pausa entre leituras
  }
  if (validas == 0) return 999.0;
  return soma / validas;
}

// ----------------------------
// SETUP
// ----------------------------
void setup() {
  pinMode(MOTOR, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  pinMode(BCD_A, OUTPUT);
  pinMode(BCD_B, OUTPUT);
  pinMode(BCD_C, OUTPUT);
  pinMode(BCD_D, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Estado inicial
  digitalWrite(MOTOR, LOW);
  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_VERMELHO, LOW);
  limpaDisplay();

  Serial.begin(9600);
  Serial.println("Sistema inicializado");
}

// ----------------------------
// LOOP PRINCIPAL
// ----------------------------
void loop() {
  // Leitura filtrada: média de 3 leituras
  float dist = distanciaMedia(3);
  Serial.print("Distancia (cm): ");
  Serial.println(dist);

  // Se está mais longe que LIMITE => disponível (LED verde)
  if (dist > LIMITE_CM) {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(MOTOR, LOW);
    limpaDisplay();
    delay(150); // pequena pausa para reduzir taxa de leitura
    return;
  }

  // Se chegou aqui: objeto detectado a <= LIMITE_CM
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, HIGH);

  // Espera 1 segundo antes de ligar motor (conforme especificado)
  delay(ESPERA_POS_DETECCAO_MS);
  digitalWrite(MOTOR, HIGH);

  // Contagem regressiva no display (9 → 0)
  for (int t = TEMPO_FLUXO; t >= 0; t--) {
    escreveBCD(t);
    Serial.print("Contagem: ");
    Serial.println(t);
    delay(1000);
  }

  // Desliga motor e limpa display
  digitalWrite(MOTOR, LOW);
  limpaDisplay();

  // Se o objeto ainda está presente, aguarda 3 segundos antes de rearmar
  float distPos = distanciaMedia(3);
  Serial.print("Dist após fluxo (cm): ");
  Serial.println(distPos);
  if (distPos <= LIMITE_CM) {
    Serial.println("Objeto ainda presente -> aguardando 3s");
    delay(ESPERA_REENTRADA_MS);
  }

  // Volta ao loop: LED verde será ligado na próxima iteração se estiver livre
}