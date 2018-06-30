#include <PCF8566.h>
#include "def.h"
unsigned char Buf[12];
unsigned long Time;

float  Vitesse;
boolean Entree;
unsigned int Kilometre = 0;
boolean Passage = true;
PCF8566 lcd(0x3e);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.init();
  pinMode(Entree, INPUT);
  attachInterrupt(0, Tours, CHANGE);
}
void Tours(void) {
  Entree = !Entree;
  Kilometre++;
}

void loop() {
  while (!Entree) {
//Debug("While", " Entree", Entree);
delay(500);
  }
  Temps();
  Delta();
  Entree = !Entree;
  Affiche(String(Vitesse) + "00" + String(Kilometre));
}


void Temps() {
  Debug("Entree", Entree);
  Time = millis();
  Debug("Temps", "Time", Time);
}

void Delta(void) {
  unsigned long delta = millis() - Time;
  Debug("Delta", "Delta", Time);
  Vitesse = (2074 / delta) * 3.6;
  Debug("Vitesse", "V", Vitesse);

}

void Buff(unsigned char Autre[12]) {
  for (int i = 0; i < sizeof(Buf); i++) {
//    Serial.print(Buf[i], HEX);
//    Serial.print(" AP ");
    Buf[i] = Buf[i] | Autre[i];
//    Serial.print(Buf[i], HEX);
//    Serial.println("");
  }
}

void Affiche(String Ch) {
  VideBuff();
  String _Ch = Ch;
  if (Ch.length() > 6) {
    Ch = "";
    for (int i = 0; i <= 6; i++) {
      Ch += _Ch.charAt(i);
    }
  }
  //    for (int i = 0; i < Ch.length(); i++) {
  //    if ( !(Ch.charAt(i) <= '0' && Ch.charAt(i) >= '9')) {
  //      _Ch;
  //    }
  //  }

  if (_Ch != "") {
    for (int i = 0; i <=4; i++) {
      char Chiffre = Ch.charAt(i) - '0';
      //    Serial.print("Chiffre : ");
      //    Serial.println(Chiffre);
      Buff(N[Chiffre][i]);
    }
    
  } else {
    for (int i = 0; i < sizeof(Buf); i++) {
      Buf[i] = Erreur[i];
    }
  }
  lcd.setMemory(Buf);
}
void VitKilo(String CH){
   
  }

void VideBuff() {
  //  Serial.println("###-VideBuff");
  for (int i = 0; i < sizeof(Buf); i++) {
    Buf[i] = 0x00;
  }
}
void Debug(String Contexte, String Ch, int Val) {
  Serial.println("##-" + Contexte + "-##");
  Serial.print(Ch + " : ");
  Serial.println(Val, DEC);
}
void Debug(String Contexte, String Ch, float Val) {
  if (Contexte == "")Serial.println("##-" + Contexte + "-##");
  Serial.print(Ch + " : ");
  Serial.println(Val, DEC);
}

void Debug(String Contexte, String Ch, unsigned long Val) {
  Serial.println("##-" + Contexte + "-##");
  Serial.print(Ch + " : ");
  Serial.println(Val, DEC);
}

void Debug(String Ch, unsigned long Val) {
  Serial.print(Ch + " : ");
  Serial.println(Val, DEC);
}










