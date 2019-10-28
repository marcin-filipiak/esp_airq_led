
#include "ESP8266WiFi.h"
#include <EEPROM.h>

struct {
    uint set = 0;
    char name_flagman[11]="";
    char ssid[32] = "";
    char pass[32] = "";
  } data;


//czyszczenie tablicy//
void clear_array(char *a, int s){
  for(int x=0;x<s;x++){
    a[x]='\0';
  }
}

#include "include/led.h"
#include <ESP8266HTTPClient.h>
#include "include/AirQ_api.h"
#include "include/wifi.h"
#include "include/config.h"

////////////menu///////////////////////
void help(){
  Serial.println("s - skanuj sieci");
  Serial.println("c - konfiguruj siec");
  Serial.println("r - rejestruj");
  Serial.println("o - czytaj konfiguracje");
  Serial.println("j - polacz z siecia");
  Serial.println("h - wyswietl to menu");
}


//////////////minuter///////////////////
int ticker = 0;
int polh = 0;
//w tym wsadzie zwraca 1 co 60 sekund
int minuter(){
  delay(10);
  ticker++;
  if (ticker > 6000){
    ticker = 0;
    return 1;
  }
  else {
    return 0;
  }
}

//////////////////////SETUP/////////////////
void setup() {
  Serial.begin(115200);
  
  EEPROM.begin(512); //ile pamieci

  pinMode(D1, OUTPUT);     
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT); // LED obok anteny (wlaczany przez LOW)
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  
  delay(300);
  
  read_config();

  if (data.set == 1){
    connect_wifi();
  }
      
 help();
}

/////////////////LOOP//////////////////
void loop() {

  //jesli minela minuta
  if (minuter() == 1){
    //doliczenie minuty do licznika 10 minut
    polh++;
      //jesli minelo 30 minut
      if (polh > 29){
          //pobranie danych jakosci powietrza
          quality();
          polh = 0;
      }
      //Serial.println("minuta");
  }
  
  //jesli przyszly dane
  if (Serial.available()>0) { 
    char z = Serial.read();
    //skanowanie sieci
    if (z == 's'){
        scan();
    }
    //konfiguruj siec
    if (z == 'c'){
      write_config();
    }
    //rejestruj
    if (z == 'r'){
      register_flagman();
    }
    //czytaj konfiguracje
    if (z == 'o'){
      read_config();
    }
    //polacz
    if (z == 'j'){
      connect_wifi();
    }
    //help
    if (z == 'h'){
      help();
    }
  }
}
