// --- CONFIGURAÇÃO DOS PINOS ---
const int botoes[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}; 
const int numBotoes = 11;

const int ledPinos[] = {A0, A1, A2, A3}; 
const int numLeds = 4;

void setup() {
  Serial.begin(9600);
  
  // Configura os botões como entrada
  for (int i = 0; i < numBotoes; i++) {
    pinMode(botoes[i], INPUT);
  }
  
  // Configura os LEDs como saída
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPinos[i], OUTPUT);
  }
  
  // Inicializa todos os LEDs apagados
  apagarLeds();
  
  Serial.println("=== SISTEMA PRONTO ===");
  Serial.println("11 botoes configurados (pinos 2-12)");
  Serial.println("Pino 12 = AND gate (ambos botoes do CI)");
  Serial.println("LEDs: A0, A1, A2, A3");
  Serial.println();
}

void loop() {
  int botaoAcionado = 0; // 0 = nenhum botão
  
  // Verifica qual botão está pressionado
  for (int i = 0; i < numBotoes; i++) {
    if (digitalRead(botoes[i]) == HIGH) {
      botaoAcionado = i + 1; // Botões numerados de 1 a 11
      break; // Pega o primeiro botão pressionado
    }
  }
  
  // Atualiza os LEDs em binário
  if (botaoAcionado > 0) {
    exibirBinario(botaoAcionado);
    
    // Mostra no Serial
    Serial.print("Botao ");
    Serial.print(botoes[botaoAcionado - 1]); // Mostra o número do pino
    Serial.print(" acionado: ");
    Serial.print(botaoAcionado);
    Serial.print(" | Binario: ");
    
    // Mostra o binário formatado
    for (int i = 3; i >= 0; i--) {
      Serial.print(bitRead(botaoAcionado, i));
    }
    Serial.println();
  } else {
    // Nenhum botão pressionado - apaga LEDs
    apagarLeds();
  }
  
  delay(100); // Pequeno delay para estabilidade
}

// Função para acender LEDs em padrão binário
void exibirBinario(int numero) {
  for (int i = 0; i < numLeds; i++) {
    // Lê o bit i do número e acende/apaga o LED correspondente
    int estadoBit = bitRead(numero, i);
    digitalWrite(ledPinos[i], estadoBit);
  }
}

// Função para apagar todos os LEDs
void apagarLeds() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPinos[i], LOW);
  }
}