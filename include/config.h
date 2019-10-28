////////////zapis konfiguracji///////////
void write_config(){
  
  char z = ' ';
  char index = 0;

  clear_array(data.ssid,32);
  clear_array(data.pass,32);

  Serial.println("Podaj SSID (zakoncz znakiem ':')");
  index = 0;
  do {
    if (Serial.available()>0) {
      z = Serial.read();
      if (z != ':'){
        data.ssid[index] = z;
        index ++;
        //s_ssid = s_ssid + z;
      }
    }
  } while (z!=':');
  Serial.println("SSID:"+String(data.ssid));

  z=' ';
  Serial.println("Podaj haslo (zakoncz znakiem ':')");
  index = 0;
  do {
    if (Serial.available()>0) {
      z = Serial.read();
      if (z != ':'){
        data.pass[index] = z;
        index ++;
      }
    }
  } while (z!=':');
  Serial.println("haslo:"+String(data.pass));

  Serial.println("name_flagman:"+String(data.name_flagman));

  data.set = 1;
  
  EEPROM.put(0,data);
  EEPROM.commit();
  
}

////////////wczytaj konfiguracje/////////////
void read_config(){
  
  String ssid = "";
  String haslo = "";
  String name_flagman="";

  EEPROM.get(0,data); 
  
  ssid = data.ssid;
  haslo = data.pass;
  name_flagman = data.name_flagman;

  Serial.println(" ");
  Serial.println("SSID: "+ssid);
  Serial.println("Haslo: "+String(data.pass));
  Serial.println("name_flagman: "+name_flagman);  
}
