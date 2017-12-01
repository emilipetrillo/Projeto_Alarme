// =======================================================================
// declarando as variáveis
int sensorPin = A1;    // select the input pin for the potentiometer
int sensorValue;  // variable to store the value coming from the sensor
long startTime; // variável do cronometro.
const int duration = 500; // duração do alarme
const int buzPin = A2; // pino do buzzer.
int frequency; // frequencia do alarme
// =======================================================================

// =======================================================================
void setup() {
  Serial.begin(9600); // iniciando a tela de Serial
  pinMode(A1, INPUT); // declarando o pino de entrada do infravermelho
  pinMode(buzPin, OUTPUT); // declarando o pino de saida do buzzer
}
// =======================================================================

// =======================================================================
void loop() {
  sensorValue = analogRead(sensorPin); // para pegar maior frequencia e até mesmo o calor do corpo.
  sensorValue = digitalRead(sensorPin); // lendo o infravemelho e armazenando em uma variável
  Serial.println(sensorValue); // "printando" o valor do infra
  timer(); // chamando a função para disparar o alarme
}
// =======================================================================

// =======================================================================
void timer() { // função de dispara o alarme
  if (sensorValue != 0) { // se o sensor infra for interrompido, ou seja, virar 1
    startTime = millis(); // inicia o cronometro
    Serial.println(startTime / 1000); // printa na tela em segundos
    if (startTime > 10000 && startTime < 20000) { // acrescentar a senha // se o tempo for maior que 10 seg e menor 20 seg, dispara o alarme
      // Nestes FOR ajusta o buzzer para fazer o som de uma sirene/alarme
      for (frequency = 150; frequency < 1800; frequency += 1) {
        tone(buzPin, frequency, duration);// acionar o buzzer.
        delay (1);
      }
      for (frequency = 1800; frequency < 150; frequency -= 1) {
        tone(buzPin, frequency, duration);// acionar o buzzer.
        delay (1);
      }
    }
    if (startTime > 20000) {
      // chamar a função de SMS
      noTone(buzPin); // desligar o buzzer/alarme
    }
  } else { // se o sensor infra não for interrompido, ou seja, permanecer 0.
    noTone(buzPin); // O alarme/buzzer não dispara
    startTime = 0; // e o tempo fica 0.
  }
}
// =======================================================================

