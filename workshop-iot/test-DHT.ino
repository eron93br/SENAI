/*
 * WORKSHOP INTRODUCAO A IOT @SENAI -- 19/07/2018
 * Código para testar o sensor DHT11
*/


#include <dht.h>

dht DHT;

#define DHT11_PIN 2

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperatura = ");    // imprime no serial monitor o valor da temperatura
  Serial.println(DHT.temperature);
  Serial.print("Umididade = ");
  Serial.println(DHT.humidity);      // imprime no serial monitor o valor da umidade
  delay(1000);                       // insere um atraso de 1s
}

