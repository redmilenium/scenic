//25/04/2019 COMIENZO PROYECTO
//26/04/2019 CAMBIO LOS DELAYS POR MILLIS()
//02/05/2019 LA CAJA DEBE LLEVAR INTERRUPTOR DE APAGADO Y EN EL ARRANQUE, EL BUZZER EMITE 3 BIP´S
//Entradas  DETECTOR NIVEL D5
//Salidas: LED D7
//         BUZZER D11,D12

  //ENTRADA
const int Detector = 5;     //Detector nivel
// SALIDA 
const int Luz = 8;          //led detector nivel bajo
long tiempo;
long contador=0;

void setup() 
{
  pinMode(Luz, OUTPUT);     // led
  pinMode(Detector, INPUT);  // Detector nivel
  digitalWrite(Luz,LOW);       // 
  tiempo=millis();
  tone(11, 1000);
  delay(750);  
  tone(11, 3000);
  delay(750);  
  tone(11, 1000);
  delay(1000);  
  noTone(11);
}

void loop() 
{
 if (!digitalRead(Detector))
  {
  tiempo=millis();
  digitalWrite(Luz,LOW);  
  noTone(11); 
  contador=1000;
  }
 if(millis()-tiempo>3000)
  {
 digitalWrite(Luz,HIGH);  
 tone(11, contador++); //activa un tono 
  if (contador ==3000)contador=1000;
  }
}

 
