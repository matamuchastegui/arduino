const int A=2;
const int B=3;
const int C=4;
const int D=5;

const int E1=9;
const int E2=6;
const int E3=7;
const int E4=8;

int tiempo = 3; // 200

void setup() {
  pinMode(A, OUTPUT); 
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT); 
  
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(E3, OUTPUT);
  pinMode(E4, OUTPUT);
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
  digitalWrite(E3, LOW);
  digitalWrite(E4, LOW);
 
}

void loop() {
  for(int i = 0; i < 10; i++) // UNIDAD DE MIL
  {
    for(int m = 0; m < tiempo; m++){
      to_BCD(0,E1);
      to_BCD(0,E2);
      to_BCD(0,E3);
      to_BCD(i,E4);
    }
    for(int j = 0; j < 10; j++) // CENTENA
    {
      for(int m = 0; m < tiempo; m++){
        to_BCD(0,E1);
        to_BCD(0,E2);
        to_BCD(j,E3);
        to_BCD(i,E4);
      }
      for(int k = 0; k < 10; k++) // DECENA
      {
        for(int m = 0; m < tiempo; m++){
          to_BCD(0,E1);
          to_BCD(k,E2);
          to_BCD(j,E3);
          to_BCD(i,E4);
        }
        for(int l = 1; l < 10; l++) // UNIDAD
        {
          for(int m = 0; m < tiempo; m++){
            to_BCD(l,E1);
            to_BCD(k,E2);
            to_BCD(j,E3);
            to_BCD(i,E4);
          }
        }
      }
    }
  } // Fin Unidad de mil
}
void activo(int enable)
{
  digitalWrite(E1,HIGH);
  digitalWrite(E2,HIGH);
  digitalWrite(E3,HIGH);
  digitalWrite(E4,HIGH);
  digitalWrite(enable,LOW);
}
void to_BCD(int count, int enable)
{
    activo(enable);
    delay(200); // 1
    
    if (count == 0) //write 0000
    {
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
    }
     
    if (count == 1) //write 0001
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
    }
     
    if (count == 2) //write 0010
    {
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
    }
     
    if (count == 3) //write 0011
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
    }
     
    if (count == 4) //write 0100
    {
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
    }
     
    if (count == 5) //write 0101
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
    }
     
    if (count == 6) //write 0110
    {
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
    }
     
    if (count == 7) //write 0111
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
    }
     
    if (count == 8) //write 1000
    {
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
    }
     
    if (count == 9) //write 1001
    {
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
    } 
    
}
