// PROGMEN - Utilidade/Explicação
// utilizar a função F() para dar print em msgs, pois F() armazena na memória flash, 
// diminuindo a quantidade de bytes utlizadas na placa arduino. Após utilizada, é desalocada da flash.
// Exemplo: Serial.println(F("Olá Mundo!"));
// Exemplo2: String meuTexto = F("1"); // não funciona com inteiro, somente com String.
// Exemplo3: Serial.println(F(meuTexto)); // nesse caso não adianta pois a varável já foi setada na memória, então já ocupou o espaço.

#include <Keypad.h>
#include <Ethernet.h>
#include <SD.h>

//bool digitandoSenha = false;
//bool redefinirSenha = false;
//String senhaCorreta = "1234";

File myFile;
int i = 0;
const int ledVermelho = A3;
const int ledVerde = A4;
const int ledAzul = A5;
char key;
char mascara = 'x';
String mascaraFinal;
String senhaDigitada;
boolean digitando;
char option;
const byte ROWS = 4;
const byte COLS = 3;
bool aguardandoOpcao;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {5, A1, 3, A0};
byte colPins[COLS] = {8, 7, 6};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


// =======================================================================
// declarando as variáveis
int sensorPin = 9;    // select the input pin for the potentiometer
int sensorValue;  // variable to store the value coming from the sensor
long startTime; // variável do cronometro.
const int duration = 500; // duração do alarme
const int buzPin = A2; // pino do buzzer.
int frequency; // frequencia do alarme
int sensorValuePrev = 0;
// =======================================================================


void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(sensorPin, INPUT); // declarando o pino de entrada do infravermelho
  pinMode(buzPin, OUTPUT); // declarando o pino de saida do buzzer
  while (!Serial) {
  }
  //funcaoPrintMenu();
  Serial.println("Digite * para iniciar");
}


void loop() {

  //  //sensorValue = analogRead(sensorPin); // para pegar maior frequencia e até mesmo o calor do corpo.
  //  sensorValue = digitalRead(sensorPin); // lendo o infravemelho e armazenando em uma variável
  //
  //  if (sensorValue && !sensorValuePrev) {
  //    startTime = millis(); // inicia o cronometro
  //    digitando = true;
  //  }
  //  Serial.println(sensorValue); // "printando" o valor do infra
  //  timer(); // chamando a função para disparar o alarme
  //  sensorValuePrev = sensorValue;

  key = keypad.getKey();

  if (digitando && key && key != '*') {
    if (key == '#') {
      Serial.print("option: "); Serial.println(option);
      funcaoEndSenha();
    } else {
      funcaoDigitando();
    }
  }

  if (aguardandoOpcao) {
    //Serial.println(aguardandoOpcao);
    if (key) {
      if (key == '1' || key == '2' || key == '3') {
        option = key;
        Serial.println("Digite a senha");
        //i++;
        digitando = true;
        aguardandoOpcao = false;
      } else {
        Serial.println("Opcao invalida");

      }
    }
  }

  if (key == '*' && !digitando) {
    senhaDigitada = "";
    mascaraFinal = "";
    aguardandoOpcao = true;
    funcaoPrintMenu();
  }

}

/////////////////////////////////////////////////////////////////////////////////
//FUNÇÕES
/////////////////////////////////////////////////////////////////////////////////

/*Função Imprime Menu*/
void funcaoPrintMenu () {
  Serial.println("Digite a opção desejada:");
  Serial.println("1 - Ativar alarme");
  Serial.println("2 - Desativar alarme");
  Serial.println("3 - Redefinir senha");
}


/*Função Digitando Senha - Armazenando input*/
void funcaoDigitando() {
  analogWrite(ledVermelho, 0);
  analogWrite(ledVerde, 0);
  analogWrite(ledAzul, 0);
  senhaDigitada += key;
  mascaraFinal += mascara;
  Serial.print("Senha digitada: ");
  Serial.println(senhaDigitada);
}


/*Função Finalizando de Digitar Senha - End*/
void funcaoEndSenha() {
  analogWrite(ledVermelho, 0);
  analogWrite(ledVerde, 0);
  analogWrite(ledAzul, 0);
  Serial.println("Finalizou senha.");

  switch (option) {
    case '1':
    case '2':
      //funcaoAtivarDesativarAlarme();
      Serial.println("Ativar/Desativar Alarme");
      break;
    case '3':
      //funcaoRedefinirSenha();
      Serial.println("Redefinir Senha");
      break;
    default:
      Serial.println("Deu bosta!!!!");
  }
  digitando = false;
}

/*Função Ativar Alarme - option 1*/
void funcaoAtivarAlarme() {

}

/*Função Gravar info no SD*/
//String funcaoGravarSD(String senhaRedefinida) {
//  if (!SD.begin(4)) {
//    Serial.println("initialization failed!");
//    while (1);
//  }
//  Serial.println("initialization done.");
//
//  myFile = SD.open("senhas.txt", FILE_WRITE);
//
//  if (myFile) {
//    Serial.print("Writing to senhas.txt...");
//    myFile.println(senhaRedefinida);
//    // close the file:
//    myFile.close();
//    Serial.println("done.");
//  } else {
//    // if the file didn't open, print an error:
//    Serial.println("error opening senhas.txt");
//  }
//}


// =======================================================================
void timer() { // função de dispara o alarme

  if (millis() >= (startTime + 10000) && millis() <= (startTime + 20000)) {
    // acrescentar a senha // se o tempo for maior que 10 seg e menor 20 seg, dispara o alarme
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

  noTone(buzPin); // desligar o buzzer/alarme

}
// =======================================================================


//*******************************************************************************
//FUNÇÕES MORTASSSS *************************************************************
//*******************************************************************************

/*Função Começando a Digitar Senha - Start*/
//void funcaoStartSenha() {
//  analogWrite(ledVermelho, 0);
//  analogWrite(ledVerde, 0);
//  analogWrite(ledAzul, 0);
//  senhaDigitada = ""; // Limpar a senha.
//  mascaraFinal = ""; // Limpar a quantidade de * digitados.
//  digitandoSenha = true;
//  Serial.println("Insira a senha e aperte # para finalizar.");
//}


/*Função Redefinindo a Senha - Armazenando input*/
//void funcaoRedefinirSenha() {
//  analogWrite(ledVermelho, 0);
//  analogWrite(ledVerde, 0);
//  analogWrite(ledAzul, 0);
//  Serial.println("Digite sua nova senha com 6 dígitos");
//  redefinirSenha = true;
//  for (int i = 0; i >= 5; i++) {
//    Serial.println("Entrou no For" + i);
//    key = keypad.getKey();
//    senhaNova += key; // variável senhaDigitada recebe valor da variável key, vai concatenando tudo que for digitado.
//  }
//  Serial.println(senhaNova);
//  if (senhaNova == senhaCorreta) {
//    Serial.println("Nova senha nao pode ser igual a anterior");
//  } else if (senhaNova != senhaCorreta) {
//    Serial.println("Nova senha definida com sucesso");
//    senhaCorreta = senhaNova;
//    funcaoGravarSD(senhaCorreta);
//    redefinirSenha = false;
//    exit(0);
//  }
//}
//
//  if (senhaDigitada == senhaCorreta) {
//    if (statusAlarme = 0) {
//      analogWrite(ledVermelho, 0);
//      analogWrite(ledVerde, 0);
//      analogWrite(ledAzul, 255);
//      statusAlarme = 1;
//      //      digitalWrite(ledVerde, HIGH);
//      //      digitalWrite(ledVermelho, LOW);
//      Serial.println("Alarme ativado.");
//    } else {
//      Serial.println("Alarme desativado.");
//      statusAlarme = 0;
//      analogWrite(ledVermelho, 0);
//      analogWrite(ledVerde, 255);
//      analogWrite(ledAzul, 0);
//      //      digitalWrite(ledVerde, HIGH);
//      //      digitalWrite(ledVermelho, LOW);
//      //      delay(100);
//      //      digitalWrite(ledVerde, HIGH);
//      //      digitalWrite(ledVermelho, LOW);
//    }
//
//    ///////////////////////////////////////
//    //ADICIONAR FUNCAO PARA DESLIGAR BUZZER
//
//    ///////////////////////////////////////
//    //ADICIONAR FUNCAO PARA ZERAR TEMPORIZADOR
//
//    delay(100);
//    exit(0);
//    //funcaoPararDeTocarAlarme();
//  }


/*Função Senha Incorreta*/
//void funcaoSenhaIncorreta() {
//  if (senhaDigitada != senhaCorreta && count < 2) {
//    count = count + 1;
//    analogWrite(ledVermelho, 255);
//    analogWrite(ledVerde, 0);
//    analogWrite(ledAzul, 0);
//    Serial.println("Senha incorreta. Digite * para tentar novamente");
//    Serial.print("Tentativa: ");
//    Serial.println(count);
//  } else if (senhaDigitada != senhaCorreta && count >= 2) {
//    analogWrite(ledVermelho, 255);
//    analogWrite(ledVerde, 0);
//    analogWrite(ledAzul, 0);
//    Serial.print("Tentativa: ");
//    Serial.println(count + 1);
//    Serial.println("Senha bloqueada. Contate a seguradora.");
//
//    ///////////////////////////////////////
//    //ADICIONAR FUNCAO PARA TOCAR BUZZER
//
//    delay(100);
//    exit(0);
//    //funcaoTocarAlarmeLoucamente();
//  }
//}


/*Função Verificação do Status do Alarme*/
//int funcaoStatusAlarme(int statusAlarme) {
//  digitalWrite(ledVerde, LOW);
//  digitalWrite(ledVermelho, LOW);
//  if (statusAlarme = 0) {
//    Serial.println("Alarme Desativado 0");
//    return 0;
//  }
//  else {
//    Serial.println("Alarme Ativado 1");
//    return 1;
//  }
//}


//*******************************************************************************
