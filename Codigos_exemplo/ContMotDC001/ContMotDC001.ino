/*  ---------------------------------------------
  Controle de Motor DC - Código 001
  -----------------------------------------------
  Motor Controlado por Arduino
  Malha Aberta Simples
    
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
  10.Alguns Jumpers (12x M-M) e (03x M-F)
  
  -----------------------------------------------
  Criado por: Fábio Meneghetti Ugulino de Araújo
  Em: Abril de 2023
  -----------------------------------------------*/

int potPin = A0;                    // Usar pino analógico A0 para leitura do Potenciômetro
int in1PtHPin = 7;                  // Usar pino digital 7  p/ entrada 1 da Ponte H
int in2PtHPin = 6;                  // Usar pino digital 6 p/ entrada 2 da Ponte H
int enablePtHPin = 5;               // Usar pino digital 12 para habilitar a Ponte H

void setup(){
  Serial.begin(9600);
  pinMode(in1PtHPin, OUTPUT);       // Configura o pino da entrada 1 da Ponte H como Saída
  pinMode(in2PtHPin, OUTPUT);       // Configura o pino da entrada 2 da Ponte H como Saída
  pinMode(enablePtHPin, OUTPUT);    // Configura o pino que habilita a Ponte H como Saída
}
   
void loop() {
  int valPot = analogRead(potPin);        // Faz a leitura do Potenciômetro
  int vel = map(valPot,0,1023,-255,255);  // Converte de 0 à 1024 para -255 à 255
  int PWM = min(abs(vel), 255);           // Calcula o PWM entre 0 e 255
  Serial.print("valPot = ");
  Serial.println(valPot);
  Serial.print("PWM = ");
  Serial.println(PWM); 
  if (vel >= 0) {                         // SE a variável 'vel' for maior ou igual a 0
    digitalWrite(in1PtHPin, LOW);         // ENTÃO envia um nivel ALTO para a entrada 1,
    digitalWrite(in2PtHPin, HIGH); }      // Envia um nivel BAIXO para a entrada 2,
  else {                                  // SENÃO (variável PWM <= 0)
    digitalWrite(in1PtHPin, HIGH);        // ENTÃO envia um nivel BAIXO para a entrada 1,
    digitalWrite(in2PtHPin, LOW); }       // Envia um nivel ALTO para a entrada 2,
  analogWrite(enablePtHPin, PWM);         // e envia o valor de PWM para o enable da Ponte H 
}
