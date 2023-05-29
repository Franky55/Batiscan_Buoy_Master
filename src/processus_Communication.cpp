#include "Arduino.h"
#include "main.h"
#include "interface_NEOPIXEL.h"
#include "serviceBaseDeTemps.h"
//#include "BFIO"
#include <stdio.h>
#include "interface_WIFI.h"
#include "interface_SPI_Master.h"
#include "Service_Protocole_BFIO.h"
#include "service_Protocole_SPI.h"
#include "Processus_Communication.h"

// if udp:         https://gist.github.com/santolucito/70ecb94ce297eb1b8b8034f78683447b


//ads
void Processus_Communication_ConnexionClient();
void Processus_Communication_Check_State_WIFI();
void Processus_Communication_Read_WIFI();
void Processus_Communication_Send_WIFI();
void Processus_Communication_SPI();
void Processus_Communication_SPI_GERE_INFORECEIVED();

/**
 * @brief Definition des structures
 * 
 */
PROCESSUS_WIFI processus_WIFI;
PROCESSUS_COMMUNICATION processus_Communication_Struct_WANTED_Value;
PROCESSUS_COMMUNICATION processus_Communication_Struct_ACTUAL_Value;


int compt = 0;
int compteur_Com_SPI = 0;


int Processus_Communication_initialise(void)
{
    processus_Communication_Struct_WANTED_Value.union_Bool.All = 0;
    processus_Communication_Struct_WANTED_Value.union_Bool.bits.Left_Light_State = 1;
    processus_Communication_Struct_WANTED_Value.Camera_Servo_Angle = 0;
    processus_Communication_Struct_WANTED_Value.Pressure = 0;
    processus_Communication_Struct_WANTED_Value.Temperature = 0;
    processus_Communication_Struct_WANTED_Value.Pitch = 0;
    processus_Communication_Struct_WANTED_Value.Roll = 0;
    processus_Communication_Struct_WANTED_Value.Yaw = 0;
    processus_Communication_Struct_WANTED_Value.Speed = 0;
    processus_Communication_Struct_WANTED_Value.Battery = 0;


    compteur_Com_SPI = 0;
    processus_WIFI.State = 0;
    processus_WIFI.DataToRead = 0;
    processus_WIFI.DataToSend = 0;
    interface_NEOPIXEL_allume(0, 0, 100);
    serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_Check_State_WIFI;
    serviceBaseDeTemps_execute[PROCESSUS_SPI_PHASE] = Processus_Communication_SPI;
    
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
    processus_WIFI.State = 1;
 
    //Send hand shake and all my data
    serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_Check_State_WIFI;

}


void Processus_Communication_Check_State_WIFI()
{
    if(!interface_WIFI_Check_Connexion())//rentre jamais ici
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
        serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_Read_WIFI;
        processus_WIFI.DataToSend = 1;
        return;
    }

    if(processus_WIFI.DataToSend == 1)
    {
        serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_Send_WIFI;
    }


}

void Processus_Communication_Read_WIFI()
{
    
    int length = interface_WIFI_Read(processus_WIFI.tabReceived, processus_WIFI.DataToRead);
    processus_WIFI.LengthDataReceived = length;

    service_Protocole_BFIO_Read_Data(&processus_WIFI.fonctionID, processus_WIFI.tabReceived, &processus_WIFI.LengthDataReceived);

    // Serial.print("Processus_Communication_Read: processus_WIFI.tabReceived: ");

    // for(int i = 0; i < length; i++)
    // {
    //     Serial.print((char)processus_WIFI.tabReceived[i]);
    // }
    // Serial.println("");

    // if(processus_WIFI.tabReceived[1] == 'R')
    // {
    //     interface_NEOPIXEL_allume(255, 0, 0);
    //     //interface_WIFI_eteint();
    // }
    // if(processus_WIFI.tabReceived[1] == 'G')
    // {
    //     interface_NEOPIXEL_allume(0, 255, 0);
    //     //interface_WIFI_eteint();
    // }
    // if(processus_WIFI.tabReceived[1] == 'B')
    // {
    //     interface_NEOPIXEL_allume(0, 0, 255);
    //     //interface_WIFI_eteint();
    // }
    processus_WIFI.DataToSend = 1;
    serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_Check_State_WIFI;

}


void Processus_Communication_Send_WIFI()
{
    int size = 0;
    unsigned char bufferTestSend[300];

    service_Protocole_BFIO_Setup_Answer(processus_WIFI.fonctionID, bufferTestSend, &size);

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

    serviceBaseDeTemps_execute[PROCESSUS_WIFI_PHASE] = Processus_Communication_Check_State_WIFI;

}


void Processus_Communication_SPI()
{
    compteur_Com_SPI++;

    if(compteur_Com_SPI < 10)
    {
        return;
    }
    
    unsigned char data[255] = "";
    unsigned char out[255] = "";
    unsigned char tab_Size = 0;
    // Serial.println("SPI data sending");
    // Serial.print("Processus_Communication_SPI: processus_WIFI.tabReceived: ");

    // for(int i = 0; i < processus_WIFI.DataToSendSPI; i++)
    // {
    //     Serial.print((char)processus_WIFI.tabReceived[i]);
    // }
    // Serial.println("");
    //interface_SPI_MASTER_Transaction((unsigned char*)"dat", (unsigned char*)processus_WIFI.tabReceived, 3);
    service_Protocole_SPI_Pepare_Trame_Slave(data, &tab_Size);
    interface_SPI_MASTER_Transaction(data, out, tab_Size);
    interface_SPI_Master_Struct.Size = tab_Size;

    compteur_Com_SPI = 0;
    serviceBaseDeTemps_execute[PROCESSUS_SPI_PHASE] = Processus_Communication_SPI_GERE_INFORECEIVED;
}

void Processus_Communication_SPI_GERE_INFORECEIVED()
{
    service_Protocole_SPI_Received(interface_SPI_Master_Struct.Received_SPI, &interface_SPI_Master_Struct.Size);
    serviceBaseDeTemps_execute[PROCESSUS_SPI_PHASE] = Processus_Communication_SPI;
}