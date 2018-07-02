/*
 * WORKSHOP INTRODUCAO A IOT @SENAI -- 19/07/2018
 * Código para testar o sensor DHT11
*/
#include "DHT.h"

float temperatura =0;
float umidade=0;

DHT dht(D4,DHT11);

void setup() 
{
  Serial.begin(9600);
  dht.begin(); 
  delay(2000);
}

void loop() 
{
  // lo - Aquisicao do sinais de sensores
  umidade = (int) dht.readHumidity();
  temperatura = (int)dht.readTemperature(); 
  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.print("  ");
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" *C");
  delay(2000);
}
