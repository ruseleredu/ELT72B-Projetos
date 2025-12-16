#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C tela(0x27, 16, 2);

String senhaDigitada = "";
String senhaSalva = "";

int tentativas = 0;
bool sistemaBloqueado = false;
unsigned long momentoDesbloqueio = 0;

bool primeiraDigitacao = true;

const byte LINHAS = 4;
const byte COLUNAS = 4;

char teclas[LINHAS][COLUNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinosLinhas[LINHAS]  = {A0, 10, 8, 7};
byte pinosColunas[COLUNAS] = {6, 5, 4, 3};

Keypad teclado = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS);

const int NAND_A = 13;
const int NAND_B = 12;
const int LED_VERDE = 2;
const int LED_VERMELHO = 11;
const int BUZZER_TONE = 9;

void beepCI() {
  digitalWrite(NAND_A, HIGH);
  digitalWrite(NAND_B, HIGH);
  delay(50);
  digitalWrite(NAND_A, LOW);
  digitalWrite(NAND_B, LOW);
}

void carregarSenha() {
  senhaSalva = "";
  bool vazia = true;

  for (int i = 0; i < 4; i++) {
    char c = EEPROM.read(i);
    if (c >= '0' && c <= '9') {
      senhaSalva += c;
      vazia = false;
    } else {
      senhaSalva += '0';
    }
  }

  if (vazia || senhaSalva == "0000") {
    senhaSalva = "4571";
    for (int i = 0; i < 4; i++) EEPROM.write(i, senhaSalva[i]);
  }
}

void salvarSenha(String novaSenha) {
  for (int i = 0; i < 4; i++) EEPROM.write(i, novaSenha[i]);
  senhaSalva = novaSenha;
}

void setup() {
  Serial.begin(9600);

  tela.init();
  tela.backlight();
  tela.clear();

  carregarSenha();

  pinMode(NAND_A, OUTPUT);
  pinMode(NAND_B, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BUZZER_TONE, OUTPUT);

  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, HIGH);
  digitalWrite(NAND_A, LOW);
  digitalWrite(NAND_B, LOW);

  tela.setCursor(0, 0);
  tela.print("T - TRANCADO");
}

void loop() {

  if (sistemaBloqueado) {
    if (millis() - momentoDesbloqueio >= 20000) {
      sistemaBloqueado = false;
      tentativas = 0;

      tela.clear();
      tela.print("DESBLOQUEADO");
      delay(1500);

      tela.clear();
      tela.print("T - TRANCADO");
      digitalWrite(LED_VERMELHO, HIGH);
    }
    return;
  }

  char tecla = teclado.getKey();

  if (tecla != NO_KEY) {

    if (tecla == 'D') {
      definirNovaSenha();
      return;
    }

    if (tecla >= '0' && tecla <= '9') beepCI();

    if (tecla >= '0' && tecla <= '9') {

      if (senhaDigitada.length() < 4) {

        if (primeiraDigitacao) {
          tela.setCursor(0, 1);
          tela.print("                ");
          tela.setCursor(0, 1);
          primeiraDigitacao = false;
        }

        senhaDigitada += tecla;
        tela.setCursor(senhaDigitada.length() - 1, 1);
        tela.print('*');
      }
    }

    if (tecla == '#') {

      if (senhaDigitada.length() < 4) {
        tela.clear();
        tela.print("4 DIGITOS!");
        delay(1500);

        tela.clear();
        tela.print("T - TRANCADO");

        senhaDigitada = "";
        primeiraDigitacao = true;
        tela.setCursor(0,1);
        tela.print("                ");
        return;
      }
      if (senhaDigitada == senhaSalva) {
        tentativas = 0;
        acessoPermitido();
      }
      else {
        tentativas++;
        acessoNegado();

        if (tentativas >= 3) bloquearSistema();
      }

      senhaDigitada = "";
      primeiraDigitacao = true;
      tela.setCursor(0,1);
      tela.print("                ");
    }
  }
}

void bloquearSistema() {
  sistemaBloqueado = true;
  momentoDesbloqueio = millis();

  tela.clear();
  tela.print("BLOQUEADO 20s");

  digitalWrite(LED_VERMELHO, HIGH);
  tone(BUZZER_TONE, 1000);
  delay(1000);
  noTone(BUZZER_TONE);
}

void definirNovaSenha() {
  senhaDigitada = "";
  primeiraDigitacao = true;

  tela.clear();
  tela.setCursor(0, 0);
  tela.print("NOVA SENHA:");
  tela.setCursor(0, 1);

  while (true) {

    char t = teclado.getKey();

    if (t >= '0' && t <= '9') {
      beepCI();

      if (senhaDigitada.length() < 4) {

        if (primeiraDigitacao) {
          tela.setCursor(0,1);
          tela.print("                ");
          tela.setCursor(0,1);
          primeiraDigitacao = false;
        }

        senhaDigitada += t;
        tela.setCursor(senhaDigitada.length()-1,1);
        tela.print('*');
      }
    }

    if (t == '#') {

      if (senhaDigitada.length() < 4) {
        tela.clear();
        tela.print("4 DIGITOS!");
        delay(1500);

        tela.clear();
        tela.print("T - TRANCADO");
        senhaDigitada = "";
        primeiraDigitacao = true;
        return;
      }

      salvarSenha(senhaDigitada);

      tela.clear();
      tela.print("SENHA SALVA");
      delay(1500);

      tela.clear();
      tela.print("T - TRANCADO");

      senhaDigitada = "";
      primeiraDigitacao = true;
      return;
    }
  }
}

void acessoPermitido() {
  tela.clear();
  tela.print("A - ABERTO");

  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_VERMELHO, LOW);

  tone(BUZZER_TONE, 2000); delay(300);
  tone(BUZZER_TONE, 2500); delay(300);
  tone(BUZZER_TONE, 3000); delay(300);
  noTone(BUZZER_TONE);

  delay(5000);

  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, HIGH);

  tela.clear();
  tela.print("T - TRANCADO");
}

void acessoNegado() {
  tela.setCursor(0, 1);
  tela.print("T - TRANCADO");

  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_VERMELHO, LOW);
    tone(BUZZER_TONE, 4000);
    delay(200);

    digitalWrite(LED_VERMELHO, HIGH);
    noTone(BUZZER_TONE);
    delay(200);
  }
}