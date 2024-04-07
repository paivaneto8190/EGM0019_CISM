/*  ---------------------------------------------
  Controle de Motor DC - Código 003
  -----------------------------------------------
  Motor Controlado por Arduino
  Malha Fechada para o Controle PI
  da velocidade angular
    
  Material usando:
  1. 01x Palca Arduino MEGA2560
  2. 01x Protoboard Grande (830 pontos)
  3. 01x Fonte externa (12V 1A
  4. 01x Módulo Ponte H L298N
  5. 01x Motor DC 6v com Encoder
  6. 01x Regulador de tensão L7806 (6v/1A)
  7. 01x Capacitor Eletrolítico 10uF/25v
  8. 01x Capacitor cerâmico 100nF (104)
  9. 01x Potenciometro Rotativo Linear 10K
  10.Alguns Jumpers (15x M-M) e (03x M-F)
  
  -----------------------------------------------
  Criado por: Fábio Meneghetti Ugulino de Araújo
  Em: Abril de 2023
  -----------------------------------------------*/

const byte potPin = A0;                         // Usar pino analógico A0 para leitura do Potenciômetro
const byte in1PtHPin = 7;                       // Usar pino digital 7  p/ entrada 1 da Ponte H
const byte in2PtHPin = 6;                       // Usar pino digital 6 p/ entrada 2 da Ponte H
const byte enablePtHPin = 5;                    // Usar pino digital 12 para habilitar a Ponte H
const byte canalBPin = 4;                       // Usar pino digital 4 p/ Canal B do Encoder
const byte canalAPin = 3;                       // Usar pino digital 3 (c/Interrupção) p/ Canal A do Encoder
volatile bool estadoEnablePtH = 1;              // Variável usada para habilitar a Ponte H
const float pulsosPorVolta = 341.2;             // Número de Pulso que o encoder dá em uma volta (resolução)
const int periodo = 100;                        // Periodo de tempo entre medições (em milissegundos)
volatile long pulsosCanalA = 0;                 // Contador de pulsos TOTAIS do Canal A do Encoder 
volatile long pulsosPorPeriodo = 0;             // Contador de pulsos POR PERÍODO do Canal A do Encoder 
volatile static unsigned long ultimoTempo = 0;  // Variável usada para testar se o período foi atingido


void setup(){
  Serial.begin(9600);                           // initializa a comunicação com Monitor serial
  pinMode(in1PtHPin, OUTPUT);                   // Configura o pino da entrada 1 da Ponte H como Saída
  pinMode(in2PtHPin, OUTPUT);                   // Configura o pino da entrada 2 da Ponte H como Saída
  pinMode(enablePtHPin, OUTPUT);                // Configura o pino que habilita a Ponte H como Saída
  pinMode(canalAPin, INPUT_PULLUP);             // Configura o pino do Canal A do Encoder como entrada c/ Pullup 
  pinMode(canalBPin, INPUT_PULLUP);             // Configura o pino do Canal B do Encoder como entrada c/ Pullup
  attachInterrupt(digitalPinToInterrupt(canalAPin), atualizaEncoderA, FALLING);  // Ativa interrup CanalA

  delay(100);
  Serial.println();
  delay(100);
  Serial.println("Começa em 2 segundos");
  delay(2000);
}
   
void loop() {
  static float Kp = 0.1;                                // Determina o valor do ganho proporcional (Kp)
  static float Ki = 0.005;                              // Determina o valor do ganho integrativo (Ki)
  static float acaoP = 0;                               // Porção do sinal de controle proporcional ao erro
  static float acaoI = 0;                               // Porção do s. de controle prop. à integral do erro
  static float controle = acaoP + acaoI;                // Calcula o Sinal de Controle (a partir das ações)
  int sp = map(analogRead(potPin),0,1023,-160,160);     // Converte leitura do pot. em setpoint, -160 à 160RPM
  unsigned long tempo = millis();                       // Atualiza a variável tempo
  if (tempo-ultimoTempo>=periodo || ultimoTempo==0) {   // SE já se passou pelo menos um "período"
    ultimoTempo = tempo;                                // ENTÃO: atualiza a variável "ultimoTempo"
    detachInterrupt(digitalPinToInterrupt(canalAPin));  // para evitar interferências
    float theta = pulsosCanalA / pulsosPorVolta * 360;  // Calcula a posição angular (Theta) em graus
    float omega = ((pulsosPorPeriodo / pulsosPorVolta) * (60000 / periodo)); // Calcula a velocidade angular
    float erro = sp - omega;                            // Calcula o erro entre o SP e a PV
    acaoP = Kp * erro;                                  // Calcula a ação Proporcional
    acaoI += Ki * erro * periodo;                       // Calcula a ação Integrativa
    pulsosPorPeriodo = 0;                               // Reinicializa o número de pulsos por período
    attachInterrupt(digitalPinToInterrupt(canalAPin), atualizaEncoderA, FALLING); // Reabilita interrupção
    mostraDadosMotor(5, theta, omega, sp, erro, controle, acaoP, acaoI);    // Chama função para exibição dos dados calculados
  }
  controle = acaoP + acaoI;                             // Calcula o Sinal de Controle (a partir das ações)
  int PWM = min(abs(controle), 255);                    // Calcula o PWM entre 0 e 255, saturando o controle
  acionaMotor(controle, PWM);                           // Chama função que aciona o Motor
}                                                       // Fim da VOID LOOP

void acionaMotor(float controle, int PWM) {             // Função que comanda a Ponte H, p/ acionar o Motor
  if (controle >= 0) {                                  // SE o controle for maior ou igual a 0
    digitalWrite(in1PtHPin, HIGH);                       // ENTÃO envia um nivel ALTO para a entrada 1,
    digitalWrite(in2PtHPin, LOW);                      // Envia um nivel BAIXO para a entrada 2,
  } else {                                              // SENÃO (variável controle < 0)
    digitalWrite(in1PtHPin, LOW);                      // ENTÃO envia um nivel BAIXO para a entrada 1,
    digitalWrite(in2PtHPin, HIGH);                       // Envia um nivel ALTO para a entrada 2,
  }                                                     // Seja qual for o sentido de rotação,
  analogWrite(enablePtHPin, PWM);                       // Envia o valor de PWM para o enable da Ponte H 
}

void atualizaEncoderA() {                               // ISR para contar os pulsos do encoder(Canal A)
  if (digitalRead(canalAPin)==digitalRead(canalBPin)) { // SE os estados forem iguais
    pulsosCanalA++;                                     // Incrementa o contador de pulsos total do encoder
    pulsosPorPeriodo++; }                               // Incrementa o contador de pulsos por periodo
  else {                                                // SENÃO (estados diferentes)
    pulsosCanalA--;                                     // Decrementa o contador de pulsos total do encoder
    pulsosPorPeriodo--; }                               // Decrementa o contador de pulsos por periodo
}

void mostraDadosMotor(int op, float theta, float omega, int sp, float erro, float controle, float acaoP, float acaoI) 
{                                                       // Função para apresentação de informaçcões sobre o Motor
  switch (op) {                                         // Verifica a opção escolhida
    case 1:                                             // Se foi escolhida a opção 1,
    Serial.print("Tempo: ");                            // Imprime mensagem no Monitor Serial
    Serial.print((float)ultimoTempo/1000);              // Imprime valor de ultimoTempo
    Serial.print("s");                                  // Imprime a unidade: Milisegundos
    Serial.print("\t");                                 // Imprime uma tabulação
    Serial.print("Posicao angular do Motor: ");         // Imprime mensagem ...
    Serial.print(theta);                                // Imprime valor de Theta
    Serial.print(" Graus");                             // Imprime a unidade: Graus
    Serial.print("\t");                                 // Imprime uma tabulação
    Serial.print("Velocidade angular do Motor: ");      // Imprime mensagem ...
    Serial.print(omega, 0);                             // Imprime valor de Omega
    Serial.println(" RPM");                             // Imprime a unidade: RPM
    break;
  case 2:                                               // Se foi escolhida a opção 2,
    Serial.println(theta);                              // Imprime apenas o valor de Theta
  break;
  case 3:                                               // Se foi escolhida a opção 3,
    Serial.println(omega, 4);                           // Imprimeapenas  valor de Omega
  break;
  case 4:                                               // Se foi escolhida a opção 4,
    Serial.print("Tempo: ");                            // Imprime mensagem ...
    Serial.print((float)ultimoTempo/1000);              // Imprime valor de ultimoTempo
    Serial.print("s");                                  // Imprime a unidade: Milisegundos
    Serial.print("\t");                                 // Imprime uma tabulação
    Serial.print("Setpoint: ");                         // Imprime mensagem ...
    Serial.print(sp);                                   // Imprime o SP 
    Serial.print(" Graus");                             // Imprime a unidade: Graus
    Serial.print("\t");                                 // Imprime uma tabulação
//    Serial.print("\t");                               // Imprime uma tabulação
    Serial.print("Pos.: ");                             // Imprime mensagem no Monitor Serial
    Serial.print(theta);                                // Imprime valor de Theta no Monitor Serial
    Serial.print(" Graus");                             // Imprime a unidade: Graus
    Serial.print("\t");                                 // Imprime uma tabulação
//    Serial.print("\t");                               // Imprime uma tabulação
    Serial.print("erro: ");                             // Imprime mensagem ...
    Serial.print(erro);                                 // Imprime o erro
    Serial.println(" Graus");                           // Imprime a unidade: Graus
    break;
  case 5:                                               // Se foi escolhida a opção 5, 
    Serial.print("Tempo: ");                            // Imprime mensagem ...
    Serial.print((float)ultimoTempo/1000, 1);           // Imprime valor de ultimoTempo 
    Serial.print("s");                                  // Imprime a unidade: Milisegundos
    Serial.print("\t");                                 // Imprime uma tabulação
    Serial.print("Setpoint: ");                         // Imprime mensagem ...
    Serial.print(sp);                                   // Imprime o SP 
    Serial.print(" RPM");                               // Imprime a unidade: RPM
    Serial.print("\t");                                 // Imprime uma tabulação
    Serial.print("\t");                                 // Imprime uma tabulação
    Serial.print("Vel.: ");                             // Imprime mensagem ...
    Serial.print(omega, 0);                             // Imprime valor de Omega 
    Serial.print(" RPM");                               // Imprime a unidade: RPM
//    Serial.print("\t");                                 // Imprime uma tabulação
    Serial.print("\t");                                 // Imprime uma tabulação
    Serial.print("erro: ");                             // Imprime mensagem ...
    Serial.print(erro);                                 // Imprime o erro
    Serial.print(" RPM");                               // Imprime a unidade: RPM
    Serial.print("\t");                                 // Imprime uma tabulação
    Serial.print("\t");                                 // Imprime uma tabulação
    Serial.print("Controle: ");                         // Imprime mensagem ...
    Serial.print(controle);                           // Imprime o sinal de controle
    Serial.print("\t");                                 // Imprime uma tabulação
    Serial.print("AcaoP: ");                         // Imprime mensagem ...
    Serial.print(acaoP);                           // Imprime o sinal de controle
    Serial.print("\t");                                 // Imprime uma tabulação
    Serial.print("AcaoI: ");                         // Imprime mensagem ...
    Serial.println(acaoI);                           // Imprime o sinal de controle
    break;
   }
}
