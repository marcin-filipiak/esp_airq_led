
void led_antena(){
  digitalWrite(D4, LOW);//LED on
  delay(500);  
  digitalWrite(D4, HIGH);//LED off   
  delay(500);                      
}


void led_clear(){
  digitalWrite(D1, LOW);//LED off
  digitalWrite(D2, LOW);//LED off                   
  digitalWrite(D3, LOW);//LED off  
  digitalWrite(D5, LOW);//LED off  
  digitalWrite(D6, LOW);//LED off 
  digitalWrite(D7, LOW);//LED off
}


void led_bardzodobre(){
	led_clear();
    digitalWrite(D1, HIGH);//LED on
}

void led_dopuszczalne(){
	led_clear();
    digitalWrite(D2, HIGH);//LED on
}

void led_niezdrowe(){
	led_clear();
    digitalWrite(D3, HIGH);//LED on
}

void led_ostrzezenie(){
	led_clear();
    digitalWrite(D5, HIGH);//LED on
}

void led_alarm(){
	led_clear();
    digitalWrite(D6, HIGH);//LED on
}

void led_zagrozeniezycia(){
	led_clear();
    digitalWrite(D7, HIGH);//LED on
}
