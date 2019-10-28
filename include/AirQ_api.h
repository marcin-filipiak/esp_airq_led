
void quality(){
  if (WiFi.status() == WL_CONNECTED) { 

	led_antena();

    String fn = data.name_flagman;
        
    HTTPClient http; 
    http.begin("http://api.noweenergie.org/index.php?AirQ/quality/"+fn);  
    int httpCode = http.GET();             
    if (httpCode > 0) {                    
      String payload = http.getString();   
      Serial.println(":"+payload+":");            

      if (payload.substring(0) == "err") { 
          //TODO: brak odczytu
      }
      // bardzo dobre
      if (payload.substring(0) == "0") { 
		led_bardzodobre();
      }
      //dopuszczalne
      if (payload.substring(0) == "1") { 
         led_dopuszczalne();
      }
      //niezdrowe dla wrazliwych
      if (payload.substring(0) == "2") { 
		 led_niezdrowe();
      }
      //ostrzezenie zdrowotne
      if (payload.substring(0) == "3") { 
         led_ostrzezenie();
      }
      //poziom alarmowy
      if (payload.substring(0) == "4") { 
		led_alarm();
      }
      //zagrozenie zycia
      if (payload.substring(0) == "5") { 
		led_zagrozeniezycia();
      }
      
    }
    http.end();                           
  }
}

///////////Rejestruj flagmana////////////////////////
void register_flagman(){
  if (WiFi.status() == WL_CONNECTED) {

	led_antena();

    Serial.println("Rejestrowanie...");
        
    HTTPClient http;  
    http.begin("http://api.noweenergie.org/index.php?AirQ/register_flagman");  
    int httpCode = http.GET();            
    if (httpCode > 0) {                    
      String rf = http.getString();  
      Serial.println("name_flagman: "+String(rf));             

      //zapisanie name_flagman do pamieci
      clear_array(data.name_flagman,11);
      for(int x=0;x<11;x++){
        data.name_flagman[x] = rf[x];
      }
      EEPROM.put(0,data);
      EEPROM.commit();

    }
    http.end();                            
  }  
}
