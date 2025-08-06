## Descrição do Projeto

### Imagem do projeto


![TinkerCAD](./Template.png)

### Links
[TinkerCAD](https://www.tinkercad.com/things/8D2X1TflrKy/editel?sharecode=20K3g4wz07Z_4x3juZV1Vb9DiEr1QI_hnzYElNrlzfw)

[YouTube](https://youtu.be/CrHJj4OQ6Sw?si=79bG3Z-DqjfYXIxq)

## Código do Arduino

```c
void setup()
{
  pinMode(2, INPUT);
  pinMode(10, OUTPUT);
}

void loop()
{
  // Se o botão estiver apertado:
  if (digitalRead(2) == HIGH) {
    // Ligue o LED.
    digitalWrite(10, HIGH);
    // Caso contrário,
  } else {
    // Desligue o LED.
    digitalWrite(10, LOW);
  }
  delay(10); // Delay a little bit to improve simulation performance
}
```

## Lista de componentes

| Nome | Quantidade | Componente |
|---|---|---|
| U1 | 1 |  Arduino Uno R3 |
| R1 | 1 | 470 Ω Resistor |
| D2 | 1 | Amarelo LED |
| S1 | 1 |  Botão |
| R2 | 1 | 10 kΩ Resistor |