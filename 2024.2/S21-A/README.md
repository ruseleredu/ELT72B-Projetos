## Descrição do Projeto

### Imagem do projeto


![TinkerCAD](./tinkercad.png)

### Links
TinkerCAD https://www.tinkercad.com/things/eZmAxRONFXx-medidor-de-pilhas?sharecode=2A9g0fhiyTN-vLMt5JNUmlcjfOtfdrquhSZ17qqogYI

YouTube

## Código do Arduino

```c
//Definição dos pinos
 
#define pinoPilhas9V A2 //Analógicos
#define pinoPilhas1V5 A0
 
#define pinoBotaoEsq 4  //Digitais
#define pinoBotaoMeio 5
#define pinoBotaoDir 6
#define AmpOp 7
 
//Incluir livraria do LCD
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27, 16, 2); //Declaração do objeto lcd
 
//Declaração de Variáveis
int leituraPinoBotaoEsq, leituraPinoBotaoMeio, leituraPinoBotaoDir;
int debouce = 200, porc15V, porc9V;
float offsetTensaoPinoPilhas1V5 = 0.20;
float leituraPinoPilhas1V5, leituraPinoPilhas9V, tensaoPinoPilhas1V5, tensaoPinoPilhas9V;
bool modoPilhas1V5, modoPilhas9V;
 
void setup() {
  //Serial.begin(9600);
  pinMode(pinoPilhas9V, INPUT);
  pinMode(pinoPilhas1V5, INPUT);
  pinMode(pinoBotaoEsq, INPUT);
  pinMode(pinoBotaoMeio, INPUT);
  pinMode(pinoBotaoDir, INPUT);
  pinMode(AmpOp, OUTPUT);
  digitalWrite(AmpOp, HIGH);
  lcd.init();
  lcd.backlight();
  selecionarTipoPilha();
}
 
void loop() {
  leituraPinoBotaoMeio = digitalRead(pinoBotaoMeio);
  if (leituraPinoBotaoMeio) {
    delay(debouce);
    selecionarTipoPilha();
  }
  if (modoPilhas1V5) {
    leituraPinoPilhas1V5 = analogRead(pinoPilhas1V5);
    tensaoPinoPilhas1V5 = leituraPinoPilhas1V5 * (5.0 / 1023);
    porc15V = ((tensaoPinoPilhas1V5/1.5)*100);
    if (tensaoPinoPilhas1V5 < 0.5) {
      tensaoPinoPilhas1V5 = 0.00;
      porc15V = ((tensaoPinoPilhas1V5/1.5)*100);
    }
    lcd.setCursor(1, 0);
    lcd.print("TENSAO MEDIDA:");
    lcd.setCursor(2, 1);
    lcd.print(tensaoPinoPilhas1V5);
    lcd.print("V [");
    lcd.print(porc15V);
    lcd.print("%] ");
  } else if (modoPilhas9V) {
    leituraPinoPilhas9V = analogRead(pinoPilhas9V);
    tensaoPinoPilhas9V = leituraPinoPilhas9V * (9.0 / 575);
    porc9V = ((tensaoPinoPilhas9V/9)*100);
      lcd.setCursor(1, 0);
      lcd.print("TENSAO MEDIDA:");
      lcd.setCursor(2, 1);
      lcd.print(tensaoPinoPilhas9V);
      lcd.print("V [");
      lcd.print(porc9V);
      lcd.print("%] ");
    //}
  }
  delay(300);
}
 
void selecionarTipoPilha() {
  digitalWrite(AmpOp, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Selecione Medidor:");
  lcd.setCursor(0, 1);
  lcd.print("<=Pilha"); 
  lcd.setCursor(9, 1); 
  lcd.print("Bater=>");
  lcd.setCursor(2, 2); 
  lcd.print("1,5V");
  lcd.setCursor(13, 2); 
  lcd.print("9V");
  do {
    leituraPinoBotaoEsq = digitalRead(pinoBotaoEsq);
    leituraPinoBotaoDir = digitalRead(pinoBotaoDir);
  }
  while (leituraPinoBotaoEsq == 0 && leituraPinoBotaoDir == 0);
  if (leituraPinoBotaoDir == 1) {
    delay(debouce);
    modoPilhas1V5 = false;
    modoPilhas9V = true;
    digitalWrite(AmpOp, LOW);
  } else if (leituraPinoBotaoEsq == 1) {
    delay(debouce);
    /*
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("ATENCAO!");
    lcd.setCursor(1, 1);
    lcd.print("TENSAO MAXIMA:9V");
    */
    modoPilhas1V5 = true;
    modoPilhas9V = false;
    
    //delay(2000);
  }
  delay(debouce);
  lcd.clear();
}

```
