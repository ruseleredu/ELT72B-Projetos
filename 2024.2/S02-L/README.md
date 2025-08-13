## Descrição do Projeto

### Imagem do projeto


![TinkerCAD](./tinkercad.png)

### Links
TinkerCAD

YouTube

## Código do Arduino

```c
#define pin_S1 7
#define pin_S2 6
bool Sensor1 = 0;
bool Sensor2 = 0;
int velocidade = 150;
void setup(){
pinMode(M1, OUTPUT);
pinMode(M2, OUTPUT);
pinMode(dir1, OUTPUT);
pinMode(dir2, OUTPUT);
digitalWrite(dir1, LOW);
digitalWrite(dir2, LOW);
pinMode(pin_S1, INPUT);
pinMode(pin_S2, INPUT);
}
void loop(){
Sensor1 = digitalRead(pin_S1);
Sensor2 = digitalRead(pin_S2);
if((Sensor1 == 0) && (Sensor2 == 0)){
analogWrite(M1, velocidade);
analogWrite(M2, velocidade);
}
if((Sensor1 == 1) && (Sensor2 == 0)){
analogWrite(M1, 0);
analogWrite(M2, velocidade);
}
if((Sensor1 == 0) && (Sensor2 == 1)){
analogWrite(M1, velocidade);
analogWrite(M2, 0);
}
}

```
