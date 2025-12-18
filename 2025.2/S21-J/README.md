## Descrição do Projeto

Link Vídeo Explicativo, Enviado no YouTube devido a praticidade:

https://youtu.be/7ZH_xzZ3nsw?si=CGUxMPaHf_brMexf

Link Tinkercad, Utilizei os equipamentos mais próximos possível:

https://www.tinkercad.com/things/bu9XV6rc51o-projeto-cauansistemasdigitais


![TinkerCAD](./Template.png)

### Links
[TinkerCAD](https://www.tinkercad.com/things/8D2X1TflrKy/editel?sharecode=20K3g4wz07Z_4x3juZV1Vb9DiEr1QI_hnzYElNrlzfw)

[YouTube](https://youtu.be/7ZH_xzZ3nsw?si=CGUxMPaHf_brMexf)


## Fluxograma em Mermaid

- https://mermaid.live/
- [State diagrams](https://mermaid.js.org/syntax/stateDiagram.html)

```mermaid
stateDiagram-v2

    [*] --> Setup

    state Setup {
        S_PinMode2_Input: pinMode(Button, INPUT)
        S_PinMode10_Output: pinMode(LED, OUTPUT)       
        S_PinMode2_Input --> S_PinMode10_Output       
    }

    Setup --> Loop: Setup Completion

    state Loop {
        L_Start: Start
        L_ReadButton: digitalRead(Button) 
  
        L_LED_ON: digitalWrite(LED, HIGH)
        L_LED_OFF: digitalWrite(LED, LOW)
        L_Delay: delay(10)

        L_Start --> L_ReadButton

        L_ReadButton --> L_LED_ON: if (HIGH)
        L_ReadButton --> L_LED_OFF: else (LOW)

        L_LED_ON --> L_Delay: Delay a little bit
        L_LED_OFF --> L_Delay: Delay a little bit

        L_Delay --> L_Start: Loop continues

    }
```

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