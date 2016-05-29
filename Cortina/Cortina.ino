#include <SoftwareSerial.h>
SoftwareSerial BT1(0, 1); // RX | TX
const int IN3 = A4;//8; // Salidas driver motor
const int IN4 = A5;//9; // Salidas driver motor
const int pUp = 5;
const int pDown = 6;
const int topLimit = 7; // Fin de carrera
const int bottomLimit = 8; // Fin de carrera
char state = 's';
int t = 100; // Tiempo que el motor sube/baja
long int tiempo,inicio;
//File wifi;
//File datos;
//File logger;
//char* ssid = "SourceIdea";
//char* password = "develop";
//https://www.youtube.com/watch?v=GilBJy5RDlo Guardar datos en memoria EEPROM
void setup()
{
  pinMode (IN4, OUTPUT);    // Input4 conectada al pin 4
  pinMode (IN3, OUTPUT);    // Input3 conectada al pin 5
  //pinMode(0, OUTPUT);
  //pinMode(1, OUTPUT);
  Serial.begin(9600);
  pinMode(10, OUTPUT); // Cambiar por 10 en ATMEGA328 53 MEGA
  digitalWrite(10, HIGH); // Cambiar por 10 en ATMEGA328 53 MEGA
  /*while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization SD failed!");
    return;
  }
  Serial.println("initialization SD done.");
  wifi = SD.open("wifi.txt");
  if (wifi && wifi.size() > 0) {
    Serial.println("Abriendo wifi.txt");
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("falla test.txt");
  }*/
  Serial.println("READY......");
}

void up(int d) {
  if(digitalRead(topLimit) == LOW){ 
    Serial.println("SUBIENDO...");
    Serial.print('S');
    digitalWrite (IN4, HIGH);
    digitalWrite (IN3, LOW);
  }
  delay(d);
}
void down(int d) {
  if(digitalRead(bottomLimit) == LOW){ 
    Serial.println("BAJANDO...");
    Serial.print('K');
    digitalWrite (IN4, LOW);
    digitalWrite (IN3, HIGH);
  }
  delay(d);
}
void Stop() {
  Serial.print("STOP");
  digitalWrite (IN4, LOW);
  digitalWrite (IN3, LOW);
}
boolean action(){
  return Serial.available() || digitalRead(pUp) == HIGH || digitalRead(pDown) == HIGH;
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
          up(t);
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
          /*tiempo = millis() - inicio;
          posicion = posicion ; //+ - / *% calculos tiempos
          aceleracion = 
          velocidad = 
          timeToTop = timeToTop - (tiempo * );*/
        }while (!Serial.available() && digitalRead(pUp) == LOW && digitalRead(pDown) == LOW && digitalRead(topLimit) == LOW );
        Serial.print("Out of bucle");
        Stop();
        //dato = trash; // Esto no hace nada, es para que compile.
        break;
      case 'd':
        do{  
          down(t);
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
        }while (!Serial.available() && digitalRead(pUp) == LOW && digitalRead(pDown) == LOW  && digitalRead(bottomLimit) == LOW);
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
  }else{
    if(digitalRead(pUp)==HIGH){
      delay(500);
      do{
        up(t);
      }while(!action() && digitalRead(topLimit) == LOW );
    }else if (digitalRead(pDown)==HIGH){
      delay(500);
      do{
        down(t);
        if(digitalRead(bottomLimit) == HIGH){
          Serial.print(digitalRead(bottomLimit) == LOW);
          Serial.print(!action());
          Serial.println("************************************bottomlimit*********************************************");
          
        }
        if(Serial.available() || digitalRead(pUp) == HIGH || digitalRead(pDown) == HIGH){
          Serial.print("digitalRead(pUp)");
          Serial.println(digitalRead(pUp));
          Serial.print("!Serial.available()");
          Serial.println(!Serial.available());
          Serial.print("digitalRead(pDown)");
          Serial.println(digitalRead(pDown));
          
        }
      }while(!action() && digitalRead(bottomLimit) == LOW );
      Serial.println("TERMINÓ DE BAJAR");
    }
    Stop();
    delay(100);
  }
  delay(5);
}

