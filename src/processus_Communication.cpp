#include "Arduino.h"
#include "main.h"
#include "interface_NEOPIXEL.h"
#include "serviceBaseDeTemps.h"
//#include "BFIO"
#include <stdio.h>
#include "interface_WIFI.h"
#include "interface_SPI_Master.h"
#include "Service_Protocole_BFIO.h"
#include "Processus_Communication.h"

// if udp:         https://gist.github.com/santolucito/70ecb94ce297eb1b8b8034f78683447b


//ads
void Processus_Communication_ConnexionClient();
void Processus_Communication_Check_State();
void Processus_Communication_Read();
void Processus_Communication_Send();
void Processus_Communication_SPI();

/**
 * @brief Definition des structures
 * 
 */
PROCESSUS_WIFI processus_WIFI;
PROCESSUS_COMMUNICATION processus_Communication_Struct_WANTED_Value;
PROCESSUS_COMMUNICATION processus_Communication_Struct_ACTUAL_Value;


int compt = 0;



int Processus_Communication_initialise(void)
{
    processus_WIFI.State = 0;
    processus_WIFI.DataToRead = 0;
    processus_WIFI.DataToSend = 0;
    interface_NEOPIXEL_allume(0, 0, 100);
    serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_Check_State;
    return 0;
}


void Processus_Communication_ConnexionClient()
{
    
    if(interface_WIFI_Connexion() == 0)
    {
        //Serial.println("NOPE");
        processus_WIFI.State = 0;
        return;
    }
    Serial.println("YES");
    //interface_NEOPIXEL_allume(0, 100, 0);
    //interface_WIFI_Show_Page();
    processus_WIFI.State = 1;
 
    //Send hand shake and all my data
    serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_Check_State;

}


void Processus_Communication_Check_State()
{
    if(!interface_WIFI_Check_Connexion())
    {
 
        //interface_NEOPIXEL_allume(100, 0, 0);
        processus_WIFI.State = 0;
        processus_WIFI.DataToRead = 0;
        processus_WIFI.DataToSend = 0;
        serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_ConnexionClient;
        return;
    }

    processus_WIFI.State = 1;

    processus_WIFI.DataToRead = interface_WIFI_Data_Available();
    if(processus_WIFI.DataToRead > 0)
    {
        serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_Read;
        processus_WIFI.DataToSend = 1;
        return;
    }

    if(processus_WIFI.DataToSend == 1)
    {
        serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_Send;
    }


}

void Processus_Communication_Read()
{
    
    int length = interface_WIFI_Read(processus_WIFI.tabReceived, processus_WIFI.DataToRead);
    processus_WIFI.DataToSendSPI = length;
    // Serial.print("Processus_Communication_Read: processus_WIFI.tabReceived: ");

    // for(int i = 0; i < length; i++)
    // {
    //     Serial.print((char)processus_WIFI.tabReceived[i]);
    // }
    // Serial.println("");

    if(processus_WIFI.tabReceived[1] == 'R')
    {
        interface_NEOPIXEL_allume(255, 0, 0);
        //interface_WIFI_eteint();
    }
    if(processus_WIFI.tabReceived[1] == 'G')
    {
        interface_NEOPIXEL_allume(0, 255, 0);
        //interface_WIFI_eteint();
    }
    if(processus_WIFI.tabReceived[1] == 'B')
    {
        interface_NEOPIXEL_allume(0, 0, 255);
        //interface_WIFI_eteint();
    }
    
    serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_SPI;

}


void Processus_Communication_Send()
{
    int size = 0;
    unsigned char bufferTestSend[300];

    service_Protocole_BFIO_Setup_Answer(7, bufferTestSend, &size);

    interface_WIFI_Send(bufferTestSend, size);
    processus_WIFI.DataToSend = 0;//data has been sent
    // unsigned char bufferTest[255];

    // bufferTest[0] = 2;
    // bufferTest[1] = 0;
    // bufferTest[2] = 1;
    // bufferTest[3] = 0;
    // bufferTest[4] = 0;
    // bufferTest[5] = 255;
    // bufferTest[6] = 3;
    // bufferTest[7] = 255;



    // interface_WIFI_Send(bufferTest, 8);
    //interface_WIFI_Send(interface_SPI_Master_Struct.Received_SPI, interface_SPI_Master_Struct.Size);

    serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_Check_State;

}


void Processus_Communication_SPI()
{
    
    const unsigned char data[255] = "";
    // Serial.println("SPI data sending");
    // Serial.print("Processus_Communication_SPI: processus_WIFI.tabReceived: ");

    // for(int i = 0; i < processus_WIFI.DataToSendSPI; i++)
    // {
    //     Serial.print((char)processus_WIFI.tabReceived[i]);
    // }
    // Serial.println("");
    //interface_SPI_MASTER_Transaction((unsigned char*)"dat", (unsigned char*)processus_WIFI.tabReceived, 3);
    interface_SPI_MASTER_Transaction((unsigned char*)processus_WIFI.tabReceived, (unsigned char*)data, 4);

    // compt++;
    // if(compt < 10)
    // {
    //     return;
    // }
    // compt = 0;
    processus_WIFI.DataToRead = 0;//data has been read
    serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_Check_State;
}