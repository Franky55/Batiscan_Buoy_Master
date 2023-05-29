
#include "main.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WiFiUdp.h>
#include "interface_WIFI.h"


#define UDP_PORT_RECEIVE 4210

// UDP
WiFiUDP UDP;
char packet[255];
char reply[] = "Packet received!";

// WiFiServer server(80);
// WiFiClient client;
IPAddress local_ip(192, 168, 4, 2);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress myIP;


/**
 * @brief Initialisation du serveur
 * N'importe qui peut se connecter au serveur avec le bon mot de passe
 * 
 * @return int 
 */
int interface_WIFI_initialise()
{
    // You can remove the password parameter if you want the AP to be open.
  // a valid password must have more than 7 characters

  if (!WiFi.softAP(WIFI_SSID, WIFI_PASSWORD)) {
    log_e("Soft AP creation failed.");
    return -1;
  }
    WiFi.softAPConfig(local_ip, gateway, subnet);
    myIP = WiFi.softAPIP();
    
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Begin listening to UDP port
  UDP.begin(UDP_PORT_RECEIVE);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT_RECEIVE);


  return 0;
}


/**
 * @brief La fonction retourne 0 jusqu'à ce qu'un
 * client se connecte au serveur
 * 
 * @return int 
 */
int interface_WIFI_Connexion()
{
    
    return 1;
}

/**
 * @brief La fonction retourne le nombre de data à lire
 * 
 * @return true 
 * @return false 
 */
int interface_WIFI_Data_Available()
{
    return UDP.parsePacket();
}





  

/**
 * @brief 
 * La fonction retourne true si le client est encore connecté
 * La fonction retourne false si le client n'est pas connecté
 * @return true 
 * @return false 
 */
bool interface_WIFI_Check_Connexion()
{
    return true;
}


int interface_WIFI_Read(unsigned char * packet, int length)
{
    int len = UDP.read(packet, length);
    if (len > 0)
    {
      packet[len] = '\0';
    }




    Serial.print("Packet received: ");

    for(int i = 0; i < len; i++)
    {
        Serial.print(packet[i]);
        Serial.print(", ");
    }
    Serial.println("\n");

    return len;
}


int interface_WIFI_Send(unsigned char * packet, int length)
{
        // Send return packet
    //Serial.print("UDP.remoteIP(): ");
    //Serial.println(UDP.remoteIP());

    //Serial.print("UDP.remotePort(): ");
    //Serial.println(UDP.remotePort());


    //Serial.print("myIP: ");
    //Serial.println(myIP);

    UDP.beginPacket(UDP.remoteIP(), 4211);
    Serial.print("Sending packet to ");
    Serial.print(UDP.remoteIP());
    Serial.print(" on port ");
    Serial.print(4211);
    Serial.print(":  size: ");
    Serial.print(length);
    Serial.print("\n\n");

    for(int byte = 0; byte < length; byte++)
    {
        Serial.print(packet[byte]);
        Serial.print(", ");
    }
    Serial.println("");

    UDP.write(packet, length);
    UDP.endPacket();
    Serial.println("Sent :)");
    return 0;
}

