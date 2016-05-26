int Valor;
int num1 = 1602;
char array[4];
String Sensor;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);Serial.begin(9600);
  Serial.println("Begin...");
}

void loop() {
  delay(1000);
  int asd = 47;
  int asd2 = 4;
  
  array[2] = asd2 != 5 ? asd2 :asd;
  Serial.print("TESTEANDO ");
  Serial.println(array[2]);
  Serial.println("****************************");
  Sensor =  String(asd);
  array[0] = Sensor.charAt(3); 
  array[1] = Sensor.charAt(2); 
  array[2] = Sensor.charAt(1); 
  array[3] = Sensor.charAt(0); 
  Serial.print("centena: ");
  Serial.println(array[0]);
  Serial.print("decena: ");
  Serial.println(array[1]);
  Serial.print("unidad: ");
  Serial.println(array[2]);
  Serial.print("asd: ");
  Serial.println(array[3]);
  if(!array[3])
    Serial.print("esto viene muy bien");
    
  

}
