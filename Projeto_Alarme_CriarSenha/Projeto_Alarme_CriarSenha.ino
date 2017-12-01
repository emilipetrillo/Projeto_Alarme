#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
char createPass;
byte rowPins[ROWS] = {5, 4, 3, A0};
byte colPins[COLS] = {8, 7, 6};
String password;
String pass;
char mask = '*';
int count = 0;
bool typingPass;
String confirmPass;
char validPass;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  Serial.println("Aperte * para iniciar");
  //delay(2000);
}

void loop() {
  createPass = keypad.getKey();

  if (createPass) {
    if (createPass == '*') {
      typingPass = true;
      password = "";
      pass = "";
      //      Serial.println(createPass);
      Serial.println("Digite sua senha e aperte # para finalizar");
      return;
    }

    else if (typingPass && createPass != '#') {
      password += createPass;
      pass += mask;
      Serial.print("Senha digitada: ");
      Serial.println(pass);
      Serial.print("Senha digitada do password: ");
      Serial.println(password);
    }

    else if (createPass == '#') {
      Serial.println("Para confirma sua senha tecle ##");
      while (count < 2) {
        count++;
        confirmPass += createPass;
        Serial.println("count: ");
        Serial.println(count);
        Serial.println("confirmPass: ");
        Serial.println(confirmPass);
      }
      if (confirmPass == "##") {
        Serial.println("aqui");
        createPass = "";
      }
    }
  }
  //      if (validPass == '1') {
  //        validPass = keypad.getKey();
  //        Serial.print("validPass: ");
  //        Serial.print(validPass);
  //      }
  //      else
  //        Serial.print("confirmPass: ");
  //        Serial.println(confirmPass);
  //        typingPass = false;
  //        Serial.println("Senha finalizada");
}




//void newPass() {
//  //createPass = keypad.getKey();
//  password += createPass;
//  Serial.print("Password:");
//  Serial.println(password);
//}

