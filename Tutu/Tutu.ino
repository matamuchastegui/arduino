long distancia;
long tiempo;
long limite = 3;

const int rele = 6;
// L293D
const int enPin = 5; // PWM se conecta al pin 1 del puente-H
const int in1Pin = 7; // Entrada 2 del puente-H
const int in2Pin = 4; // Entrada 7 del puente-H

void setup(){
  Serial.begin(9600);
  pinMode(9, OUTPUT); /*activación del pin 9 como salida: para el pulso ultrasónico*/
  pinMode(8, INPUT); /*activación del pin 8 como entrada: tiempo del rebote del ultrasonido*/
  pinMode(in1Pin, OUTPUT); 
  pinMode(in2Pin, OUTPUT);

  analogWrite(enPin, 200);
  digitalWrite(in1Pin,LOW);
  digitalWrite(in2Pin,HIGH);
  
  pinMode(rele, OUTPUT);
  digitalWrite(rele, HIGH);
}

void loop(){
  Serial.println("loop");
  if(choca()){
    Serial.println("choco");
    frenar();
    digitalWrite(rele, HIGH);
    girar();
    frenar();
    Serial.println("Avanzar");
    digitalWrite(rele, HIGH);
  }
  
  delay(500);
}

bool choca(){
  digitalWrite(9,LOW); /* Por cuestión de estabilización del sensor*/
  delayMicroseconds(5);
  digitalWrite(9, HIGH); /* envío del pulso ultrasónico*/
  delayMicroseconds(10);
  tiempo = pulseIn(8, HIGH);
  distancia= int(0.017*tiempo);
  Serial.print("Distancia: ");
  Serial.println(distancia);
  if(distancia <= limite)
    return true;
  return false;
  
}

void frenar(){
  digitalWrite(rele, LOW);
  delay(1000); 
}
void girar(){
  digitalWrite(in1Pin,HIGH);
  digitalWrite(in2Pin,LOW);
  Serial.println("girar");
  while(choca()){
    delay(1);
  }
  Serial.println("Ya no hay obstaculos");
  digitalWrite(in1Pin,LOW);
  digitalWrite(in2Pin,HIGH);
  
}

