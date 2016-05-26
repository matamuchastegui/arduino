


#include <ESP8266WiFi.h>

const char* ssid = "Wifi Paula";
const char* password = "av259";

int num = 2999;
String response = "";
WiFiClient client;

void setup() {
  Serial.begin(115200);
  Serial.println("SetUp...");
  pinMode(2, OUTPUT); 
  
  // iniciando conexión...
  
  Serial.println("Conectando a: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        digitalWrite(2,HIGH);
        delay(100);
        digitalWrite(2,LOW);
    }
    digitalWrite(2,HIGH);
    delay(1000);
    digitalWrite(2,LOW);
    delay(100);
    Serial.println("Conectado a Red WI-FI");
    Serial.println(ssid);
    Serial.print("La Ip de la placa es: ");
    Serial.println(WiFi.localIP());
}

void loop() {
  Serial.println("loop");
  //num ++;
  /*if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }*/
  //if(num % 3000 == 0){
    if (client.connect("52.36.173.82", 80)>0) {
          digitalWrite(2,HIGH);
          delay(3000);
          digitalWrite(2,LOW);
          Serial.print("#Conectado");
          client.print("GET http://52.36.173.82/api/articles/56de0084231b51773e00c797");
          client.println();
          client.println();
  
          Serial.print(" _Datos enviados ");
    
          delay(3000);
          bool turnOn = false;
          while(client.available() && !turnOn){
            char c = client.read();
            Serial.print(" -c:");
            Serial.println(c);
            if(c == '1'){
              turnOn = true;
              //Encender PC
              Serial.println("******Encender PC******");
              digitalWrite(2,HIGH);
              delay(1000);
              digitalWrite(2,LOW); 
              delay(30000);
            }
            else{
              if(c == '0'){
                Serial.println(" -A- ");
                digitalWrite(2,HIGH);
                delay(300);
                digitalWrite(2,LOW);
                delay(600);
                digitalWrite(2,HIGH);
                delay(100);
                digitalWrite(2,LOW);
                delay(100);
                digitalWrite(2,HIGH);
                delay(100);
                digitalWrite(2,LOW);
                delay(100);
              }
              
            }
            delay(1);
          }
          
    }else {
          Serial.println("#Fallo en la conexion");
          digitalWrite(2,HIGH);
          delay(3000);
          digitalWrite(2,LOW);
          delay(100);
          digitalWrite(2,HIGH);
          delay(100);
          digitalWrite(2,LOW);
          delay(100);
          digitalWrite(2,HIGH);
          delay(3000);
          digitalWrite(2,LOW);
          delay(100);
      }
  //}
 }
