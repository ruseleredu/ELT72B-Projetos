const int sensorPin = A0;   // sensor de umidade
const int potPin    = A1;   // potenciômetro
const int trigPin   = 8;    // trigger do CI 555
const int ledPin    = 7;    // LED indicador

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(trigPin, HIGH); // padrão alto para o 555
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
}

void loop() {
  int umidade = analogRead(sensorPin); // leitura do sensor
  int limiar  = analogRead(potPin);    // leitura do potenciômetro

  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.print(" | Limiar: ");
  Serial.println(limiar);

  // solo seco → aciona
  if (umidade < limiar) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(trigPin, LOW);   // trigger do 555
    delay(120);
    digitalWrite(trigPin, HIGH);
    delay(2000);                  // tempo entre acionamentos
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(500);
}
