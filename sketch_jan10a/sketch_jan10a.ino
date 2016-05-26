


#include <ESP8266WiFi.h>

const char* ssid = "Wifi Paula";
const char* password = "av259";

/*int a = 1;
int b = 50;
int c = 100;

bool flag_a;
bool flag_b;
bool flag_c;*/
int num = 2999;
String response = "";
WiFiClient client;

void setup() {
  Serial.begin(115200);
  Serial.println("SetUp...");
  pinMode(2, OUTPUT); 
  
  // iniciando conexi�n...
  
  Serial.println("Conectando a: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

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
          Serial.print("#Conectado");
          client.print("GET http://52.36.173.82/api/articles/56de0084231b51773e00c797");
          /*client.print("GET http://ioting.org/input_data.php?us=prueba&pass=prueba&ob=Maceta%20Iot&v1=");
          client.print(a);
          client.print("&v2=");
          client.print(b);
          client.print("&v3=");
          client.print(c);
          client.print(" HTTP/1.0");*/
          /*client.print(" Connection →keep-alive");
          client.print(" Content-Length →172");
          client.print(" Content-Type →application/json; charset=utf-8");
          client.print(" Date →Mon, 11 Jan 2016 20:48:57 GMT");
          client.print(" ETag →W/\"ac-pQtm6Fuhu5i09i6QTZCs9w\"");
          client.print(" Strict-Transport-Security →max-age=15778476; includeSubDomains");
          client.print(" Vary →Accept-Encoding");
          client.print(" X-Content-Type-Options →nosniff");
          client.print(" X-Download-Options →noopen");
          client.print(" X-Frame-Options →SAMEORIGIN");
          client.print(" X-XSS-Protection →1; mode=block");*/
          client.println();
          //client.println("User-Agent: ioting.org");
          client.println();
  
          Serial.println(" _Datos enviados ");
    
  
         
          delay(3000);
          while(client.available()){
            char c = client.read();
            Serial.print(" -c:");
            Serial.print(c);
            response= response + c;
            delay(1);
          }
          int contentBodyIndex = response.lastIndexOf('\n');
          Serial.println();
          Serial.println(contentBodyIndex);
          Serial.println("response");
          Serial.println(response);
           if (contentBodyIndex > 0) {
              Serial.print("subs: ");
              String result = response.substring(contentBodyIndex);
              Serial.print("result");
              Serial.println(result);
                if(result == "\n\"1\""){
                  //Encender PC
                  Serial.println("******Encender PC******");
                  digitalWrite(2,HIGH);
                  delay(1000);
                  digitalWrite(2,LOW);
                  delay(120000);
                }
              
           }
          
    }else {
          Serial.println("#Fallo en la conexion");
      }
  //}
 }
