## Descrição do Projeto
Um elevador de 3 andares que recebe os inputs por botões e que mostra a troca de
andares num 7 seguimentos;
3 botões que são utilizados para dizer qual andar que tem a intenção de ir; um diplay de 7
segmentos que mostra qual andar está e a troca de andares; um CI CD4511 que facilita a
interface do CI com o arduino; resistores de 1k ohm e 150 ohm que servem para regular a
potência exercida nos componentes

### Imagem do projeto

![TinkerCAD](./tinkercad.png)

### Links
TinkerCAD

YouTube

## Código do Arduino

```c
#include<Servo.h>
const int A = 4; // Primeiramente setamos os 4 pinos do CI 4511
const int B = 5;
const int C = 6;
const int D = 7;

int bt=0;
int bt1=0;
int bt2=0;
int current_floor=1;

void setup(){
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  digitalWrite(A, 1);
  digitalWrite(B, 0);
  digitalWrite(C, 0);
  digitalWrite(D, 0);
}

void go_through_2_floor(){
  delay(500);
  digitalWrite(A, 0); //acende os leds que representam o número 2
  digitalWrite(B, 1);
  digitalWrite(C, 0);
  digitalWrite(D, 0);
  delay(500);
}

void loop(){
  bt=digitalRead(A0);  
  bt1=digitalRead(A1);
  bt2=digitalRead(A2);
  
  if(bt==1){
    if (current_floor==3) {
      go_through_2_floor();
    } else {
      delay(500);
    }
    digitalWrite(A, 1); //acende os leds que representam o número 1
    digitalWrite(B, 0);
    digitalWrite(C, 0);
    digitalWrite(D, 0);
    current_floor=1;
  }
  if(bt1==1){
    delay(500);
    digitalWrite(A, 0); //acende os leds que representam o número 2
    digitalWrite(B, 1);
    digitalWrite(C, 0);
    digitalWrite(D, 0);
    current_floor=2;
  }
  if(bt2==1){
    if (current_floor==1) {
      go_through_2_floor();
    } else {
      delay(500);
    }
    digitalWrite(A, 1); //acende os leds que representam o número 3
    digitalWrite(B, 1);
    digitalWrite(C, 0);
    digitalWrite(D, 0);
    current_floor=3;
  }
}
```
