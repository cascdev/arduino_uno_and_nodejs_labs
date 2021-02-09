/*****************************************************************************************************
* Programa Acende Retorna JSON Ethernet Shield W5100
*
*Acesso a interface atraves do endereco de IP:porta de internet no nosso caso: 192.168.0.150:3000:
*Programa funcionando e OK! Charles Augusto.
*
*****************************************************************************************************/
#include <SPI.h>
#include <Ethernet.h>

byte mac[ ]     = { 0xDE,0xAD,0xBE,0xEF, 0xFE, 0xED };
byte ip[ ]      = { 192, 168, 0, 150 };       //Colocar o ip do arduino, e substituir os pontos por virgula
byte gateway[ ] = { 192, 168, 0, 50  };      //Entre com o IP do roteador onde a Ethernet Shield está instalada
byte subnet[ ]  = { 255, 255, 255, 0 };     //Entre com a Máskara de Subrede
EthernetServer server( 3000 );             //Selecionar porta de saída >> acesso em 192.168.0.150:3000

void setup() {
 Serial.begin( 9600 ); 
 while( !Serial ){ Serial.print("."); }
 //  Inicia o servidor
 Ethernet.begin( mac, ip, gateway, subnet );    
  // Check se o Ethernet hardware está presente
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield ausente. Seu hardware não pode ser encontrado.");
    while (true) { delay(1); }    
  }
  else if ( Ethernet.linkStatus() == LinkOFF ) {  Serial.println("Cabo ethernet não conectado."); }
  
  server.begin();
  Serial.println("");
  Serial.print("servidor ativo em: ");
  Serial.print( Ethernet.localIP() );   //Mostra na serial o endereço IP 
  Serial.println("\n");
 }

void loop()
{  
 EthernetClient client = server.available(); 
 
 if( client ){  
  Serial.println("Cliente on-line!");  
  boolean currentLineIsBlank = true;  // Um http request finaliza com uma linha em branco

    while( client.connected() ){ 
      if( client.available() ){
        char c = client.read();
        Serial.write(c);
        if ( c == '\n' && currentLineIsBlank ) { // Envia ao client
  
           // Cabeçalho HTTP padrão
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: application/json");  // Servidor Web Arduino nos retorna JSON
            client.println("connection:close");
            client.println();         
                  
            
            client.println( "[ { \"A0\": 741 ,\"A2\": 321,\"D1\": true }, { \"A1\": 745, \"A3\": 548, \"D2\": false } ]" ); // dado hard coded json correct
                    
            break;        
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }        
      }           
    }
    delay(1);
    client.stop();
    Serial.println("O cliente foi desconectado!");
    
  }
}
 
