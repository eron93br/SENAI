#include <ESP8266WiFi.h>  //essa biblioteca já vem com a IDE. Portanto, não é preciso baixar nenhuma biblioteca adicional

//defines
#define SSID_REDE     " "  //coloque aqui o nome da rede que se deseja conectar
#define SENHA_REDE    "  "  //coloque aqui a senha da rede que se deseja conectar
#define INTERVALO_ENVIO_THINGSPEAK  450000  //intervalo entre envios de dados ao ThingSpeak (em ms)

//constantes e variáveis globais
char EnderecoAPIThingSpeak[] = "api.thingspeak.com";
String ChaveEscritaThingSpeak = "KGFP6X4JQTJZFIAP";
long lastConnectionTime; 
WiFiClient client;

//prototypes
void EnviaInformacoesThingspeak(String StringDados);
void FazConexaoWiFi(void);
float FazLeituraUmidade(void);

/*
 * Implementações
 */

//Função: envia informações ao ThingSpeak
//Parâmetros: String com a  informação a ser enviada
//Retorno: nenhum
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
//Parâmetros: nenhum
//Retorno: nenhum
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
    Serial.println("Planta IoT com ESP8266 NodeMCU");
    delay(100);
    pinMode(pinopir, INPUT); //Define pino sensor como entrada
    Serial.begin(9600);
}

//loop principal
void loop()
{

    char FieldUmidade[11];
    
    //Força desconexão ao ThingSpeak (se ainda estiver desconectado)
    if (client.connected())
    {
        client.stop();
        Serial.println("- Desconectado do ThingSpeak");
        Serial.println();
    }

    int contador=0;
    int cont = 0;
  
    while(cont<45)
    {
      acionamento = digitalRead(pinopir); //Le o valor do sensor PIR
      if (acionamento == LOW) //Sem movimento, mantem rele desligado
      {
         Serial.println("Parado");
      }
      else //Caso seja detectado um movimento, aciona o rele
       {
         Serial.println("Movimento !!!");
         contador = contador + 1; // adiciona o numero de deteccoes de movimento
       }
        delay(1000);
       contador = contador + 1;
     }
    
    //verifica se está conectado no WiFi e se é o momento de enviar dados ao ThingSpeak
    if(!client.connected() && 
      (millis() - lastConnectionTime > INTERVALO_ENVIO_THINGSPEAK))
    {
        sprintf(FieldUmidade,"field1=%d",contador);
        EnviaInformacoesThingspeak(FieldUmidade);
    }

     delay(1000);
}
