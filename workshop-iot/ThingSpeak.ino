
// Workshop de Introducao ao NodeMCU - Arduino Day Recife 2017
// Eronides Neto:  eron93@gmail.com 

#include <ESP8266WiFi.h>  //Biblioteca da IDE. 
 
// Definicao de variaveis de REDE Wi-Fi
#define SSID_REDE     "iPhone de Eron"                //coloque aqui o nome da rede que se deseja conectar
#define SENHA_REDE    "eronides"          //coloque aqui a senha da rede que se deseja conectar
#define INTERVALO_ENVIO_THINGSPEAK  2000    //intervalo entre envios de dados ao ThingSpeak (em ms)

// Constantes 
char EnderecoAPIThingSpeak[] = "api.thingspeak.com";
String ChaveEscritaThingSpeak = "BZOUA5HC8ZU2R2IB";          // <-------- Coloque aqui sua chave de escrita do ThingSpeak
long lastConnectionTime; 
WiFiClient client;
 
void EnviaInformacoesThingspeak(String StringDados);
void FazConexaoWiFi(void);
 
//Função: envia informações ao ThingSpeak
void EnviaInformacoesThingspeak(String StringDados)
{
    if (client.connect(EnderecoAPIThingSpeak, 80))
    {         
        //faz a requisição HTTP ao ThingSpeak
        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: "+ChaveEscritaThingSpeak+"\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(StringDados.length());
        client.print("\n\n");
        client.print(StringDados);
   
        lastConnectionTime = millis();
        Serial.println("- Informações enviadas ao ThingSpeak!");
     }   
}
 
//Função: faz a conexão WiFI
void FazConexaoWiFi(void)
{
    client.stop();
    Serial.println("Conectando-se à rede WiFi...");
    Serial.println();  
    delay(1000);
    WiFi.begin(SSID_REDE, SENHA_REDE);
 
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }
 
    Serial.println("");
    Serial.println("WiFi connectado com sucesso!");  
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
 
    delay(1000);
}
 
void setup()
{  
    Serial.begin(9600);
    lastConnectionTime = 0; 
    FazConexaoWiFi();
    Serial.println("ESP8266 NodeMCU com ThingSpeak");
}
 
// Main loop
void loop()
{   char FieldUmidade[11];
    //Força desconexão ao ThingSpeak (se ainda estiver desconectado)
    if (client.connected())
    {
        client.stop();
        Serial.println("- Desconectado do ThingSpeak");
        Serial.println();
    }
     
    //verifica se está conectado no WiFi e se é o momento de enviar dados ao ThingSpeak
    if(!client.connected() && 
      (millis() - lastConnectionTime > INTERVALO_ENVIO_THINGSPEAK))
    {
        sprintf(FieldUmidade,"field1=%d",analogRead(A0));
        EnviaInformacoesThingspeak(FieldUmidade);
    }
 
     delay(1000);
}
