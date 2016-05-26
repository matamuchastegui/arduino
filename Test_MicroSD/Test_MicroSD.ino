/*
  Listfiles

 This example shows how print out the files in a
 directory on a SD card

 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 2 Feb 2014
 by Scott Fitzgerald

 This example code is in the public domain.

 */
#include <SPI.h>
#include <SD.h>
long int tiempo,inicio;
File root;
File myFile;//qq
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(53, OUTPUT); // Cambiar por 10 en ATMEGA328
  digitalWrite(53, HIGH); // Cambiar por 10 en ATMEGA328
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  //root = SD.open("/");
  myFile = SD.open("test.txt", FILE_WRITE); //qq
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("esto tiene test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("faia test.txt");
  }/**///qq
  //printDirectory(root, 0);

  Serial.println("done!");
}

void loop() {
  while(Serial.available()){
    char dato = Serial.read();
    //Serial.print(dato=='r');
    //Serial.print(dato=='\n');
    if(dato!='\n')
    switch(dato){
      case '{':
      if (!SD.begin(4)) {
        Serial.println("Fallo 1");
        return;
      }
      Serial.println("ok 1");
      break;
      
      case '}':
      root = SD.open("/");
      printDirectory(root, 0);
      break;

      case '-':
      digitalWrite(13,LOW);
      break;

      case '[':
        SD.remove("test.txt");
      break;

      case '*':
      Serial.println("LEER");
      myFile = SD.open("test.txt");
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      Serial.println();
      break;

      case 'P':
        myFile = SD.open("test.txt");
        Serial.println(myFile.size());
      break;

      case '1':
        myFile = SD.open("test.txt");
        Serial.println(myFile.position());
      break;
        
      case '2':
        myFile = SD.open("test.txt");
        if(Serial.available()){
          char pos = Serial.read();
          Serial.print("seek to: ");
          int sk = pos - '0';
          Serial.println(sk);
          myFile.seek(sk);
          Serial.println(myFile.position());
          Serial.println(myFile.peek());
        }
      break;

      case '3':
        myFile = SD.open("test.txt");
        Serial.println(myFile.peek());
      break;

      case '4':
        inicio = millis();
        Serial.println(inicio);
      break;

      case '5':
        tiempo = millis() - inicio;
        Serial.println(tiempo);
      break;
            
      case '+':
      digitalWrite(13,HIGH);
      break;

      default:
        /*if (!SD.begin(4)) {
          Serial.println("Fallando..");
          return;
        }*/
        myFile = SD.open("test.txt", FILE_WRITE);
        if (myFile) {
          Serial.println("Escribiendo :D");
          //myFile.println("Probando escribir joder");
          myFile.print(dato);
          myFile.close();
        }else{
          Serial.println("Oops, something is wrong");
        }
      break;
    }
  }
  if (myFile) {
    Serial.println("Cerrar");
    myFile.close();
  }
  delay(100);
  // nothing happens after setup finishes.
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}



