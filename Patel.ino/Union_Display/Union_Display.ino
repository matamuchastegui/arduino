int Valor = 56789; 
char Digitos [10]; 
int i; 
void setup() {
  Serial.begin(9600);
  Serial.println("Start");

}

void loop() {
  sprintf (Digitos, "%d", Valor); 
  for (i = 0; Digitos [i] != NULL; ++i) 
  {
    printf ("%c\n", Digitos [i]); 
    Serial.println(Digitos[i]);
  }
     
  //return 0; 

}
