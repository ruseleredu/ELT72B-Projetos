## Descrição do Projeto
Trator com plantadeira autônoma controlado por Arduino, capaz de realizar o plantio automático, operar à noite e parar por segurança ao detectar obstáculos.

![TinkerCAD](./Template.png)

## Links
[TinkerCAD](https://www.tinkercad.com/things/9NdJrxBrmlD-grupo-s21-i/editel?returnTo=%2Fthings%2F9NdJrxBrmlD-grupo-s21-i)


[YouTube](https://www.youtube.com/watch?v=DndeYzf7MWc)

## Fluxograma em Mermaid

- https://mermaid.live/
- [State diagrams](https://mermaid.js.org/syntax/stateDiagram.html)

```mermaid
flowchart TD
    A["Início"] --> B["setup()"]
    B --> B1["Configura pinos"]
    B1 --> B2["Anexa servo no pino 13"]
    B2 --> B3["Inicializa Serial"]
    B3 --> C["loop()"]

    %% LDR
    C --> D["Ler valor do LDR"]
    D --> E{"É noite? < 300"}
    E -- Sim --> F["Ligar LED"]
    E -- Não --> G["Desligar LED"]

    %% Ultrassônico
    F --> H["Disparar sensor ultrassônico"]
    G --> H
    H --> I["Calcular distância do objeto"]

    %% Objeto próximo
    I --> J{"Objeto ≤ 50 cm?"}
    J -- Sim --> K["Parar motores"]
    K --> L["Piscar LED e buzzer 3x"]
    L --> M["Delay"]
    M --> C

    %% Objeto longe
    J -- Não --> N["Reset contador LED"]
    N --> O{"Distância ≤ 300?"}

    %% Movimento normal
    O -- Sim --> P{"Distância múltipla de 50?"}
    P -- Sim --> Q["Acionar servo para plantio"]
    Q --> R["Servo vai de 37° a 110°"]
    R --> S["Servo retorna de 110° a 37°"]
    S --> T["Ligar motores"]

    P -- Não --> T

    %% Fora do limite
    O -- Não --> U["Parar motores"]

    %% Final do ciclo
    T --> V["Incrementar distância"]
    U --> V
    V --> W["Enviar distância via Serial"]
    W --> X["Delay"]
    X --> C
```

## Lista de componentes

| Nome | Quantidade | Componente |
| --- | --- | --- |
| BAT1 | 1 | Bateria 9V |
| D1, D2 | 2 | Branco LED |
| PIEZO1 | 1 | Piezo |
| R1 | 1 | Fotorresistor |
| SERVO1 | 1 | Posicional Micro servo |
| U1 | 1 | Arduino Uno R3 |
| R2 | 1 | 20 kΩ Resistor |
| R4 | 1 | 150 Ω Resistor |
| DIST3 | 1 | Sensor de distância ultrassônico (quatro pinos) |
| R9, R3 | 2 | 620 Ω Resistor |
| T2, T1 | 2 | Transistor NPN (BJT) |
| M2, M3 | 2 | Motor CC |
| U2 | 1 | Inversor hexadecimal |