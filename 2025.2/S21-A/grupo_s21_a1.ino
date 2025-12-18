#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//LCD I2C 
LiquidCrystal_I2C lcd(0x27, 16, 2);

//TECLADO
const byte LINHAS = 4;
const byte COLUNAS = 4;

char teclas[LINHAS][COLUNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinosLinhas[LINHAS]  = {13, 12, 11, 10};
byte pinosColunas[COLUNAS] = {9, 8, 7, 6};

Keypad teclado = Keypad(makeKeymap(teclas),
                        pinosLinhas,
                        pinosColunas,
                        LINHAS,
                        COLUNAS);

// CONTROLE DE ACESSO USANDO LED
String senha   = "1234";
String entrada = "";

int senhaOK   = A2;   // LED VERDE ABRIR 
int ledErro   = A3;   // LED VERMELHO SENHA INCORRETA
int ledAmarelo = A1;  // LED AMARELO ACIONAR BOTÃO

//CONTROLE DE TEMPO 
unsigned long tempoInicio = 0;
const unsigned long TEMPO_LIBERADO = 3000; // 3 SEGUNDOS
bool acessoAtivo = false;

void setup() {
  pinMode(senhaOK, OUTPUT);
  pinMode(ledErro, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);

  digitalWrite(senhaOK, LOW);
  digitalWrite(ledErro, LOW);
  digitalWrite(ledAmarelo, LOW);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Digite a senha");
}

void loop() {
  

//CONTROLE DO TEMPO 
  
  if (acessoAtivo) {
    if (millis() - tempoInicio >= TEMPO_LIBERADO) {
      acessoAtivo = false;

      digitalWrite(senhaOK, LOW);
      digitalWrite(ledAmarelo, LOW);

      lcd.clear();
      lcd.print("Digite a senha");
    }
  }

  // LEITURA DO TECLADO 
  char tecla = teclado.getKey();

  if (tecla && !acessoAtivo) {

    if (tecla == '#') {

      if (entrada == senha) {

        digitalWrite(senhaOK, HIGH);
        digitalWrite(ledErro, LOW);
        digitalWrite(ledAmarelo, HIGH);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Acesso");
        lcd.setCursor(0,1);
        lcd.print("LIBERADO");

        tempoInicio = millis();
        acessoAtivo = true;
      }
      else {

        digitalWrite(senhaOK, LOW);
        digitalWrite(ledErro, HIGH);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Senha");
        lcd.setCursor(0,1);
        lcd.print("INCORRETA");

        tempoInicio = millis();
        acessoAtivo = true;
      }

      entrada = "";
    }

    else if (tecla == '*') {
      entrada = "";
      lcd.clear();
      lcd.print("Digite a senha");
    }

    else {
      entrada += tecla;
      lcd.setCursor(0,1);
      lcd.print(entrada);
    }
  }
}
