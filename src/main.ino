//#############################################################################
/**
 * @file main.c
 * @author Francis Gratton
 * @brief
 * Program file containing the code defined in xmain.h
 * Please refer to this other file for information necessary in order to make this work.
 * @version 0.1
 * @date 2023-05-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
//#############################################################################


//INCLUSIONS
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>
#include "main.h"
#include "Globals.h"


// inlcude des pilotes


#include "pilote_NEOPIXEL.h"
#include "pilote_GPIO.h"
//#include "pilote_SPI.h"


// Include des Services
#include "serviceTaskServer.h"
#include "serviceBaseDeTemps.h"
#include "Service_Protocole_BFIO.h"
#include "service_Protocole_SPI.h"

// Inlude des interfaces
#include "interface_NEOPIXEL.h"
#include "interface_WIFI.h"
#include "interface_SPI_Master.h"
#include "interface_GPIO.h"

// Include des processus
#include "processusClignotant.h"
#include "Processus_Communication.h"

//Definitions privees
//pas de definitions privees
//#include <Adafruit_NeoPixel.h>
cDevice Device;
cChunk Chunk;
cData Data;
cPacket Packet;


unsigned char supportedBFIOIDs[_AMOUNT_OF_SUPPORTED_ID] = {
    0, // [MANDATORY]  - Ping(None)
    1, // [MANDATORY]  - Status (Get)
    2, // [MANDATORY]  - Handshake
    3, // [MANDATORY]  - ErrorMessage
    4, // [MANDATORY]  - Device Type
    5, // [MANDATORY]  - ID
    6, // [MANDATORY]  - RESTART PROTOCOL
    7, // [MANDATORY]  - GetUniversalInfos
    8, // [MANDATORY]  - HandlingError
    9, // [MANDATORY]  - RESERVED
    10, // [MANDATORY] - RESERVED

    20, // [SPECIFIC] -TX: 0 -RX: 0 - ResetInputs(None)                                                     -> None
    21, // [SPECIFIC] -TX: 1 -RX: 1 - Joystick(unsigned char JoystickID)                                    -> char X, char Y, bool button
    22, // [SPECIFIC] -TX: 2 -RX: 1 - JoystickAxis(unsigned char Joystick_ID, unsigned char AxisID)         -> char AxisValue
    23, // [SPECIFIC] -TX: 6 -RX: 6 - Joysticks(char X, char Y, char X, char Y, bool left, bool right)      -> char X, char Y, char X, char Y, bool left, bool right
    24, // [SPECIFIC] -TX: 2 -RX: 1 - Trim(unsigned char JoystickID, unsigned char AxisID)                  -> char Trim
    25, // [SPECIFIC] -TX: 2 -RX: 1 - Deadzone(unsigned char JoystickID, unsigned char AxisID)              -> char Deadzone
    26, // [SPECIFIC] -TX: 1 -RX: 1 - Button(unsigned char ButtonID)                                        -> unsigned char buttonState
    27, // [SPECIFIC] -TX: 5 -RX: 5 - Buttons(uc ButtonA, uc ButtonB, uc ButtonC, uc ButtonD, uc ButtonE)   -> uc ButtonA, uc ButtonB, uc ButtonC, uc ButtonD, uc ButtonE
    28 // [SPECIFIC] -TX: 3 -RX: 3 - RGB(uc Red, uc Green, uc Blue)                                        -> uc Red, uc Green, uc Blue
};

/// @brief Fonction qui fait l'initialisation de tout les modules permettant
//   au fonctionnement global du véhicule.
/// @param void
void main_initialise(void);
// Execution InitializeProject();
// Execution TestInitialization();

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
Execution InitializeProject()
{
    Device = cDevice();
    Chunk = cChunk();
    Data = cData();
    Packet = cPacket();

    return Execution::Passed;
}

Execution TestInitialization()
{
    Serial.println("Project test: -> START");

  

    if(!Device.built){
        Serial.println("Project test: -> DEVICE OBJECT FAIL");
        return Execution::Failed;
    }

    if(!Chunk.built){
        Serial.println("Project test: -> CHUNK OBJECT FAIL");
        return Execution::Failed;
    }

    if(!Data.built){
        Serial.println("Project test: -> DATA OBJECT FAIL");
        return Execution::Failed;
    }

    if(!Packet.built){
      Serial.println("Project test: -> PACKET OBJECT FAIL");
      return Execution::Failed;
    }


    Serial.println("Project test: -> SUCCESS");
    return Execution::Passed;
}


void main_initialise(void)
{
  serviceTaskServer_initialise();
  serviceBaseDeTemps_initialise();

  InitializeProject();

  pilote_NEOPIXEL_initialise(); 
  pilote_GPIO_Initialise();

  //interfaceEntree1_initialise();
  interface_NEOPIXEL_initialise();
  interface_WIFI_initialise();
  interface_SPI_MASTER_initialise();
  interface_GPIO_Initialise();

  //Service
  service_Protocole_BFIO_initialise();
  service_Protocole_SPI_initialise();

  //processusClignotant_initialise();
  Processus_Communication_initialise();
}

void setup(void) 
{
  Serial.begin(115200);
  main_initialise();
  

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  // END of Trinket-specific code.

  

  serviceTaskServer_DemarreLesTachesALaTouteFinDeSetup();
}

void loop(void) 
{
  serviceTaskServer_gestion.execute();
  serviceBaseDeTemps_gereDansLoop();   
}

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
//pas de fonctions publiques
