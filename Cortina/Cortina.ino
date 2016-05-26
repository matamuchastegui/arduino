#include <SoftwareSerial.h>
SoftwareSerial BT1(0, 1); // RX | TX
int IN3 = 8;
int IN4 = 9;
int topLimit = 7; // Fin de carrera
int bottomLimit = 6; // Fin de carrera
char state = 's';
long int tiempo,inicio;
File wifi;
File datos;
File logger;
char* ssid = "SourceIdea";
char* password = "develop";
void setup()
{
  pinMode (IN4, OUTPUT);    // Input4 conectada al pin 4
  pinMode (IN3, OUTPUT);    // Input3 conectada al pin 5
  Serial.begin(9600);
  pinMode(53, OUTPUT); // Cambiar por 10 en ATMEGA328
  digitalWrite(53, HIGH); // Cambiar por 10 en ATMEGA328
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization SD failed!");
    return;
  }
  Serial.println("initialization SD done.");
  wifi = SD.open("wifi.txt");
  if (wifi) {
    Serial.println("Abriendo wifi.txt");
    if(wifi.size()==0)
      break;
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("faia test.txt");
  }
  Serial.println("READY......");
}

void up(int d) {
  Serial.println("SUBIENDO...");
  Serial.print('S');
  digitalWrite (IN4, HIGH);
  digitalWrite (IN3, LOW);
  delay(d);
}
void down(int d) {
  Serial.println("BAJANDO...");
  Serial.print('K');
  digitalWrite (IN4, LOW);
  digitalWrite (IN3, HIGH);
  delay(d);
}
void Stop() {
  Serial.println("STOP");
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  digitalWrite (IN4, LOW);
  digitalWrite (IN3, LOW);
}
void loop()
{
  char dato;
  char trash;
  if (Serial.available()) {
    dato = Serial.read();
    //Serial.print(dato);
    switch (dato) {
      case 'u':
        inicio = millis();
        do{
          up(100);
          //Serial.flush();
          if(Serial.available() && Serial.read() == 'u'){
            // Elimina datos si existen 
            while(Serial.available()){
              Serial.print("remove");
              trash = Serial.read();
              //Serial.flush();
            }
          }else if(Serial.available()){
            break;
          }
          tiempo = millis() - inicio;
          posicion = posicion ; //+-*/% calculos tiempos
          aceleracion = 
          velocidad = 
          timeToTop = timeToTop - (tiempo * );
        }while (!Serial.available() || digitalRead(topLimit)!=HIGH || ){
        Serial.print("Out of bucle");
        Stop();
        dato = trash; // Esto no hace nada, es para que compile.
        break;
      case 'd':
        do{  
          down(100);
          if(Serial.available() && Serial.read() == 'd'){
            Serial.print("BASURA____");
            while(Serial.available()){
              Serial.print("remove");
              trash = Serial.read();
            }
          }else if(Serial.available()){
            Serial.print("____-/-BREAK-/-____");
            break;
          }
        }while (!Serial.available()); // || digitalRead(bottomLimit)!=HIGH){
        Serial.print("Out of bucle");
        Stop();
        break;
      case 's':
        Serial.println('R');
        Stop();
        delay(1000);
        break;

      case '1':
        // Get position from SD Card
        Serial.write('A');
        delay(500);
        Serial.write('B');
        delay(500);
        Serial.write('C');
        delay(500);
        Serial.write('D');
        delay(500);
        Serial.write('E');
        delay(500);
        break;
    }
  }
  delay(5);
}

