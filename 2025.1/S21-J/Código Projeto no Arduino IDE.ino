#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN  D8
#define RST_PIN D4
#define RED_PIN    D3
#define GREEN_PIN  D0
#define BUZZER_PIN D2
#define SERVO_PIN  D1

MFRC522 rfid(SS_PIN, RST_PIN);
Servo meuServo;

const byte tag_valida_1[4] = {0xA2, 0x3E, 0x86, 0x1D};
const byte tag_valida_2[4] = {0xA3, 0x81, 0x17, 0xA3};

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, HIGH);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  apagaLED();

  delay(100);               
  meuServo.attach(SERVO_PIN);
  meuServo.write(0);        // Posiciona servo em 0 graus (fechado)
  delay(1000);              // Aguarda servo se posicionar
  meuServo.detach();        // Desliga sinal PWM para evitar movimento indesejado

  Serial.println("Sistema pronto. Servo na posição 0 graus.");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    delay(250);
    return;
  }

  Serial.print("UID lido: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  if (rfid.uid.size == 4 && (comparaUID(tag_valida_1, 4) || comparaUID(tag_valida_2, 4))) {
    Serial.println("TAG VÁLIDA - Abrindo servo...");
    acendeLED(1, 0);
    buzina(500, false);

    meuServo.attach(SERVO_PIN);
    meuServo.write(180);
    Serial.println("Servo abrindo a fechadura.");
    delay(2000);
    meuServo.detach();
    delay(2000);
    meuServo.attach(SERVO_PIN);
    meuServo.write(0);
    Serial.println("Servo fechando a fechadura.");
    delay(2000);
    meuServo.detach();

  } else {
    Serial.println("TAG INVÁLIDA - Sem ação no servo.");
    acendeLED(0, 1);
    buzinaNegado();  
  }

  apagaLED();
  delay(500);

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

bool comparaUID(const byte *ref, byte tamanho) {
  if (rfid.uid.size != tamanho) return false;
  for (byte i = 0; i < tamanho; i++) {
    if (rfid.uid.uidByte[i] != ref[i]) return false;
  }
  return true;
}

void acendeLED(bool vermelho, bool verde) {
  digitalWrite(RED_PIN, vermelho ? HIGH : LOW);
  digitalWrite(GREEN_PIN, verde ? HIGH : LOW);
}

void apagaLED() {
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
}

void buzina(int tempo_ms, bool pulsando) {
  if (!pulsando) {
    digitalWrite(BUZZER_PIN, LOW);
    delay(tempo_ms);
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    int tempo_total = 0;
    while (tempo_total < tempo_ms) {
      digitalWrite(BUZZER_PIN, LOW);
      delay(150);
      digitalWrite(BUZZER_PIN, HIGH);
      delay(150);
      tempo_total += 300;
    }
  }
}

void buzinaNegado() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, LOW);
    delay(300);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
  }
}
