
// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize digital pin 13 as an output.
  pinMode(D7, OUTPUT);
}

// the loop function runs over and over again forever
void loop() 
{
  digitalWrite(D7, HIGH);   // liga  o LED! (HIGH is the voltage level, +5V)
  delay(1000);              // espera um segundo
  digitalWrite(D7, LOW);    // desliga o LED! 
  delay(1000);              // espera um segundo
}
