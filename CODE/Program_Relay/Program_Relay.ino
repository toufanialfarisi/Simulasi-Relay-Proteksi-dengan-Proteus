 
/* --- THE TOUFUNNY--- */
 
const int pinADC = A0;
int sensitivitas = 100; //tegantung sensor arus yang digunakan, yang ini 5A
int nilaiadc= 00;
int teganganoffset = 2500; //nilai pembacaan offset saat tidak ada arus yang lewat
double tegangan = 00;
double nilaiarus = 00;
int PIN_BTN = 11;
int PIN_IND = 12;
int PIN_TRIP = 13;
int PIN_NORMAL = 10;
float arusSetting = 4.65;

void setup(){
Serial.begin(9600); //baud komunikasi serial monitor 9600bps
Serial.println("*SIMULASI RELAY OCR*"); //menuliskan "Hello World"
pinMode(PIN_BTN, INPUT);
pinMode(PIN_TRIP, OUTPUT);
pinMode(PIN_IND, OUTPUT);
pinMode(PIN_NORMAL, OUTPUT);

}
 
void data_olah(){
  nilaiadc = analogRead(pinADC);
  tegangan = (nilaiadc / 1024.0) * 5000;
  nilaiarus = ((tegangan - teganganoffset) / sensitivitas);
}

void trip(){
  digitalWrite(PIN_TRIP, HIGH);
  digitalWrite(PIN_IND, HIGH);
  digitalWrite(PIN_NORMAL, LOW);
  Serial.println("TRIP INITIATE");
  Serial.print("I_FAULT = ");
  Serial.print(nilaiarus);
  Serial.println(" A");
  delay(1500);
  digitalWrite(PIN_TRIP, LOW);
  digitalWrite(PIN_NORMAL, HIGH);
  Serial.println("MOTOR OFF");
  
}
 
void loop(){
   data_olah();
   int out_PIN_BTN = digitalRead(PIN_BTN);
   digitalWrite(PIN_NORMAL, HIGH);

  Serial.print("\t Arus = ");
  Serial.print(abs(nilaiarus),3);
  Serial.println("\t A ");

  if (nilaiarus > arusSetting){
      Serial.println("TRIP OF FAULT");  
      trip();
    }
  
  if(out_PIN_BTN){
    Serial.println("Terpencet");
    nilaiarus = 7;
    if (nilaiarus > arusSetting){
      trip();
    }
    else {
      Serial.println("NO TRIP");
    }
  }
  else {
    Serial.println("");
  }
}
 
