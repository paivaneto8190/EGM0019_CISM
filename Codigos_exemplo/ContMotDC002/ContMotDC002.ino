/*  ---------------------------------------------
  Controle de Motor DC - Código 002
  -----------------------------------------------
  Motor Controlado por Arduino
  Malha Aberta Simples com Monitoramento
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
const float pulsosPorVolta = 341.2;             // Número de Pulso de um canal do encoder em uma volta (resolução)
const int periodo = 100;                        // Periodo de tempo entre medições (em milissegundos)
volatile long pulsosCanalA = 0;                 // Contador de pulsos TOTAIS do Canal A do Encoder 
volatile long pulsosPorPeriodo = 0;             // Contador de pulsos POR PERÍODO do Canal A do Encoder 
volatile static unsigned long ultimoTempo = 0;  // Variável usada para testar se o período foi atingido
float pulsosPorPeriodoAux = 0;
//unsigned long tempoExibeDados1 = 0;
//unsigned long tempoFazCalculo1 = 0;
//unsigned long tempoFazCalculo2 = 0;

void setup(){ 
  Serial.begin(9600);                           // initializa a comunicação com Monitor serial
  pinMode(in1PtHPin, OUTPUT);                   // Configura o pino da entrada 1 da Ponte H como Saída
  pinMode(in2PtHPin, OUTPUT);                   // Configura o pino da entrada 2 da Ponte H como Saída
  pinMode(enablePtHPin, OUTPUT);                // Configura o pino que habilita a Ponte H como Saída
  pinMode(canalAPin, INPUT_PULLUP);             // Configura o pino do Canal A do Encoder como entrada c/ Pullup 
  pinMode(canalBPin, INPUT_PULLUP);             // Configura o pino do Canal B do Encoder como entrada c/ Pullup
  attachInterrupt(digitalPinToInterrupt(canalAPin), atualizaEncoderA, FALLING);  // Ativa interrup CanalA
}
   
void loop() {
  int valPot = analogRead(potPin);                      // Faz a leitura do Potenciômetro
  int vel = map(valPot,0,1023,-255,255);                // Converte de 0 à 1024 para -255 à 255
  int PWM = min(abs(vel), 255);                         // Calcula o PWM entre 0 e 255
  unsigned long tempo = millis();                       // Atualiza a variável tempo
  if (tempo-ultimoTempo>=periodo || ultimoTempo==0) {   // SE já se passou pelo menos um "período"
    ultimoTempo = tempo;                                // ENTÃO: atualiza a variável "ultimoTempo"
    detachInterrupt(digitalPinToInterrupt(canalAPin));  // para evitar interferências
    //tempoFazCalculo1 = millis();
    float theta = pulsosCanalA / pulsosPorVolta * 360;  // Calcula a posição angular (Theta) em graus
    float omega = ((pulsosPorPeriodo / pulsosPorVolta) * (60000 / periodo)); // Calcula a velocidade angular
    pulsosPorPeriodoAux += pulsosPorPeriodo;
    pulsosPorPeriodo = 0;                               // Reinicializa o número de pulsos por período
    //tempoFazCalculo2 = millis();
    //tempoFazCalculo2 = tempoFazCalculo2 - tempoFazCalculo1;
    attachInterrupt(digitalPinToInterrupt(canalAPin), atualizaEncoderA, FALLING); // Reabilita interrupção
    //tempoExibeDados1 = millis();
    mostraDadosMotor(5, theta, omega, PWM, valPot, pulsosPorPeriodoAux);                  // Chama função para exibição dos dados calculados
    //tempoExibeDados1 = millis() - tempoExibeDados1;
  }
  if (vel >= 0) {                                       // SE a variável 'vel' for maior ou igual a 0
    digitalWrite(in1PtHPin, LOW);                       // ENTÃO envia um nivel ALTO para a entrada 1,
    digitalWrite(in2PtHPin, HIGH); }                    // Envia um nivel BAIXO para a entrada 2,
  else {                                                // SENÃO (variável PWM <= 0)
    digitalWrite(in1PtHPin, HIGH);                      // ENTÃO envia um nivel BAIXO para a entrada 1,
    digitalWrite(in2PtHPin, LOW); }                     // Envia um nivel ALTO para a entrada 2,
    analogWrite(enablePtHPin, PWM);                       // e envia o valor de PWM para o enable da Ponte H 

  /*Serial.print("Tempo de calculo: ");
  Serial.print((float)tempoFazCalculo1/1000);
  Serial.print("\t | \t");
  Serial.print((float)tempoFazCalculo2/1000);
  Serial.print("\t | \t Tempo de exibir os dados: ");
  Serial.println((float)tempoExibeDados1/1000, 4);*/
}

void atualizaEncoderA() {                               // ISR para contar os pulsos do encoder(Canal A)
  if (digitalRead(canalAPin)==digitalRead(canalBPin)) { // SE os estados forem iguais
    pulsosCanalA++;                                     // Incrementa o contador de pulsos total do encoder
    pulsosPorPeriodo++; }                               // Incrementa o contador de pulsos por periodo
  else {                                                // SENÃO (estados diferentes)
    pulsosCanalA--;                                     // Decrementa o contador de pulsos total do encoder
    pulsosPorPeriodo--; }                               // Decrementa o contador de pulsos por periodo
}

void mostraDadosMotor(int op,float theta,float omega, float PWM, int valPot, float pulsosPorPeriodo) { // Função para apresentação de informaçcões sobre o Motor
  switch (op) {                                         // Verifica a opção escolhida
    case 1:                                             // Se foi escolhida a opção 1,
    Serial.print("Tempo: ");                            // Imprime mensagem no Monitor Serial
    Serial.print((float)ultimoTempo/1000);              // Imprime valor de ultimoTempo no Monitor Serial
    Serial.print("s");                                  // Imprime a unidade: Milisegundos
    Serial.print("\t");                                 // Imprime uma tabulação
    Serial.print("Posicao angular do Motor: ");         // Imprime mensagem no Monitor Serial
    Serial.print(theta);                                // Imprime valor de Theta no Monitor Serial
    Serial.print(" Graus");                             // Imprime a unidade: Graus
    Serial.print("\t");                                 // Imprime uma tabulação
    Serial.print("Velocidade angular do Motor: ");      // Imprime mensagem no Monitor Serial
    Serial.print(omega, 0);                             // Imprime valor de Omega no Monitor Serial
    Serial.print(" RPM");                             // Imprime a unidade: RPM
    //Adicionado pelos alunos
    Serial.print("\t");
    Serial.print("PWM: ");
    Serial.print(PWM);
    Serial.print("\t");
    Serial.print("Res: ");
    Serial.println(valPot);
    break;
  case 2:                                               // Se foi escolhida a opção 2,
    Serial.println(theta);                              // Imprime apenas o valor de Theta
  break;
  case 3:                                               // Se foi escolhida a opção 3,
    Serial.println(omega, 4);                           // Imprimeapenas  valor de Omega
  break;
  case 4:
    Serial.println(PWM);
    break;
  case 5:
    Serial.print("Tempo: ");                            // Imprime mensagem no Monitor Serial
    Serial.print((float)ultimoTempo/1000);              // Imprime valor de ultimoTempo no Monitor Serial
    Serial.print("s");                                  // Imprime a unidade: Milisegundos
    Serial.print("\t");                                 // Imprime uma tabulação
    Serial.print("Velocidade angular do Motor: ");      // Imprime mensagem no Monitor Serial
    Serial.print(omega, 0);                             // Imprime valor de Omega no Monitor Serial
    Serial.print(" RPM");                             // Imprime a unidade: RPM
    //Adicionado pelos alunos
    Serial.print("\t");
    Serial.print("PWM: ");
    Serial.print(PWM);
    Serial.print("\t Pulsos totais: ");
    Serial.print(pulsosPorPeriodo);
    Serial.print("\t");
    Serial.print("Res: ");
    Serial.println(valPot);
  default:
    break;
  }
}
