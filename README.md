"# scenic" 
A raiz de una perdida de refrigerante por la rotura de un manguito de plastico de 7 euros, he estado a punto de quemar el motor de mi Scenic.
Afortunadamente, me di cuenta de que perdía refrigerante y, rellenando el deposito de expansión, pude llegar hasta un taller y repararlo.
Si esto me hubiera ocurrido en un viaje largo, posiblemente hubiera quemado la junta de la culata, ya que no sé de nadie que este constantemente comprobando la temperatura del motor mientras conduce. 
Para evitar que pueda volver a ocurrir, he montado un detector de nivel en el vaso de expansión de refrigerante y lo he conectado a un arduino nano.
He procurado ser lo menos invasivo posible en la mecanica del coche y he optado por utilizar un sensor de nivel de liquido sin contacto   del tipo XKC-Y25-NPN. 
Especificaciones:
Modelo: XKC-Y25-NPN
Salida de aviso: NPN
Voltaje de entrada (InVCC): cc 5-24 V
Actual: 5mA
Voltaje de salida (alto nivel): InVCC
Voltaje de salida (bajo nivel): 0 V
Corriente de salida: 1 ~ 100mA
Tiempo de respuesta: 500 mS
Temperatura de funcionamiento: 0 ~ 105 °
Espesor de inducción (sensibilidad): 0-13mm
La comunicación: RS485
Humedad: 5% ~ 100%
Material: ABS
Protección de ingreso: IP67

El sensor va pegado mediante cinta de doble cara al vaso de expansión y sujeto, además, con bridas de plastico.
La cinta de doble cara, tiene un "doble" cometido: sujetar el sensor al vaso de expansión y separarlo lo suficiente como para que el calor no afecte a su funcionamiento. Aunque, según fabricante soporta hasta 105°.
Lo he probado en un viaje largo durante esta última ola de calor (29/06/19 - 40° de máxima) y ha sobrevivido.

La señal del sensor la recoge un arduino nano, al que ademas he conectado un buzzer.
Dado que los movimientos del coche pueden provocar falsos positivos al moverse el liquido refrigerante dentro del vaso de expansión, he colocado un pequeña rutina que solo dispara el buzzer en caso de detectar la falta de refrigerante durante al menos 3 segundos.
En la practica, mediante esta rutina, no he detectado falsos positivos 
El programa es muy sencillo.
El arduino deberemos conectarlo, por ejemplo, a los cables de la toma de mechero situada al lado del conductor.
Habitualmente esta toma solo esta alimentada cuando el contacto del coche esta dado.


Este es el programa cargado en el arduino:

//25/04/2019 COMIENZO PROYECTO
//Entradas  DETECTOR NIVEL D5
//Salidas: LED D7
//         BUZZER D11

  //ENTRADA
const int Detector = 5;     //Detector nivel
// SALIDA 
const int Luz = 8;          //led detector nivel bajo
long tiempo;
long contador=0;

void setup() 
{
//configuramos los puertos
  pinMode(Luz, OUTPUT);     // led
  pinMode(Detector, INPUT);  // Detector nivel
  digitalWrite(Luz,LOW);       // 
  tiempo=millis();
  // emitimos un tritono para indicar que el sistema esta activo
  // Si conectamos el arduino a una toma que se ponga de alimentación solo cuando el coche esta arrancado
  // podremos cerciorarnos de que el sistema esta operativo.
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
 if(millis()-tiempo>3000)  // hemos detectado falta de nivel durante 3 segundos
  {
 digitalWrite(Luz,HIGH);  
 tone(11, contador++); //activa un tono 
  if (contador ==3000)contador=1000;
  }
}
