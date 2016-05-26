String ordenes[]=
   {  //“AT+CWJAP=”redwifi”,”Contraseña”       // A mi esto me da problemas
      "AT+CWMODE=3",
      "AT+CIFSR" ,
      "AT+CIPMUX=1",
      "AT+CIPSERVER=1,80",
      "END"                // Para reconocer el fin de los comandos AT
   };
void setup() {
 Serial3.begin(115200);
 Serial.begin(115200);
 delay (1000);       // Para tener tiempo de arrancar la consola
 int index = 0;
 while(ordenes[index] != "END")
   {  Serial3.println(ordenes[index++]);
      while ( true)
        {   String s = GetLineWIFI();
            if ( s!= "") Serial.println(s);
            if ( s.startsWith("no change")) break;
            if ( s.startsWith("OK")) break;
            if ( s.startsWith("ready")) break;
        }
      Serial.println("....................");
   }
}
String GetLineWIFI()
   {   String S = "" ;
       if (Serial3.available())
          {    char c = Serial3.read(); ;
                while ( c != '\n' )            //Hasta que el caracter sea intro
                  {     S = S + c ;
                        delay(25) ;
                        c = Serial3.read();
                   }
                 return( S ) ;
          }
   }
void http(String output)
  {  Serial3.print("AT+CIPSEND=0,");   // AT+CIPSEND=0, num
     Serial3.println(output.length());
     if (Serial3.find(">"))            // Si recibimos la peticion del mensaje
        { Serial.println(output);
          Serial3.println(output);     //Aqui va el string
          delay(10);
          while( Serial3.available() > 0)    // Busca el OK en la respuesta 
            { if (  Serial3.find("SEND OK")  )  break;
            }
         }
  }

  void webserver(void)
   {  http("<!DOCTYPE HTML>");
      http("<html>");
      http("<head><title>LECTURAS ANALOGICAS.</title>");
      http("<meta http-equiv=\"refresh\" content=\"15\"></head>"); // Refresco
      http("<body><h1> Situacion Ambiente</h1>");

      for (int analogChannel = 0; analogChannel < 6; analogChannel++)
          {    int sensorReading = analogRead(analogChannel);
               http("    analog input ");
               http( String(analogChannel));
               http(" is ");
               http(String(sensorReading));
               http("<br />");
          }
      http("<p><em> La pagina se actualiza cada 15 segundos.</em></p></body></html>");
      delay(1);
      Serial3.println("AT+CIPCLOSE=0");
   }
   
void loop() {
   String B, C = "" ;
   char c =' ' ;
   
   if (Serial3.available())
       { c = Serial3.read() ;
         Serial.print(c);
         C = C + c ;              // Vamos montando un String con lo que entra
       }
   if (Serial.available())
        {  char c = Serial.read();
           Serial3.print(c);
        }

}
