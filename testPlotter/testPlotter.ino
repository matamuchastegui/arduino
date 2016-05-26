int contador = 0;
int sen = 0;
void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  background(255, 0, 0);
}

void loop() {
  if(sen==360)
    sen = 0;
  else
    sen++;
  
  Serial.println(sin(sen));
  contador++;
  // send the value of analog input 0:
  //Serial.println(contador);
  //Serial.println(contador*2);
  // wait a bit for the analog-to-digital converter
  // to stabilize after the last reading:
  delay(10);
}
