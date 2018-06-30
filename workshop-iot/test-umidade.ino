/*
 * WORKSHOP INTRODUCAO A IOT @SENAI -- 19/07/2018
 * Código para testar o sensor de umidade do solo
*/


float getsensor(void)
{
    int ValorADC;
    float UmidadePercentual;
 
     ValorADC = analogRead(0);      //978 -> 3,3V
     Serial.print("[Leitura ADC] ");
     Serial.println(ValorADC);
     
     //Escala do sensor de umidade
     //Quanto maior o numero lido do ADC, menor a umidade.
     //Sendo assim, calcula-se a porcentagem de umidade por:
     //      
     //   Valor lido                 Umidade percentual
     //      _    0                           _ 100
     //      |                                |   
     //      |                                |   
     //      -   ValorADC                     - UmidadePercentual 
     //      |                                |   
     //      |                                |   
     //     _|_  978                         _|_ 0
     //
     //   (UmidadePercentual-0) / (100-0)  =  (ValorADC - 978) / (-978)
     //      Logo:
     //      UmidadePercentual = 100 * ((978-ValorADC) / 978)  
     
     UmidadePercentual = 100 * ((978-(float)ValorADC) / 978);
     Serial.print("[Umidade Percentual] ");
     Serial.print(UmidadePercentual);
     Serial.println("%");
     return UmidadePercentual;
}

void setup()
{  
    Serial.begin(9600);
    Serial.println("Teste umidade do solo com ESP8266 NodeMCU");
    delay(2500);
}

//loop principal
void loop()
{
    float UmidadePercentualLida;    // variavel com a umidade do solo em %
    int UmidadePercentualTruncada;
    char FieldUmidade[11];
    UmidadePercentualLida = getsensor();
    UmidadePercentualTruncada = (int)UmidadePercentualLida; //trunca umidade como número inteiro
    // realiza operacao de mostrar no serial
    delay(1000);
}
