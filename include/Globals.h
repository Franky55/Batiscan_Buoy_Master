/**
 * @file Globals.h
 * @author Lyam (LyamBRS@gmail.com.com)
 * @brief This file contains the various class
 * definitions used throughout this project.
 * This allows classes and object to be accessed
 * globally by all entities at any point.
 * 
 * @attention
 * You must initialize each class in this file
 * in void setup prior to actually using them.
 * @version 0.1
 * @date 2023-04-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
/*  ############    ############     ##########
    ############    ############     ##########
              ##              ##   ## 
    ####    ##      ####    ##     ############
    ####    ##      ####    ##     ############
              ##              ##             ##
    ############    ####      ##   ##########
    ############    ####      ##   ##########   */

#ifndef BRS_GLOBALS_H
    #define BRS_GLOBALS_H

#include <iostream>
#include <cstring>
#include <Arduino.h>

#include "Enums.h"
#include "Device.h"
#include "BFIO.h"
#include "Chunk.h"
#include "Data.h"
#include "Packet.h"
#include "Terminal.h"
#include "Gates.h"
#include "Runway.h"

#include "main.h"

///@brief RGB LED uses GPIO 48
#define RGB_PIN 38
///@brief The button of the left joystick is GPIO45
#define LEFT_JOYSTICK_SWITCH_PIN 45
///@brief The button of the right joystick is GPIO16
#define RIGHT_JOYSTICK_SWITCH_PIN 16
///@brief The X axis ADC of the left joystick is GPIO 
#define LEFT_JOYSTICK_X_PIN 3
///@brief The X axis ADC of the right joystick is GPIO 
#define RIGHT_JOYSTICK_X_PIN 2
///@brief The Y axis ADC of the left joystick is GPIO 
#define LEFT_JOYSTICK_Y_PIN 4
///@brief The Y axis ADC of the right joystick is GPIO 
#define RIGHT_JOYSTICK_Y_PIN 1

#define BUTTON_1_PIN 48
#define BUTTON_2_PIN 47
#define BUTTON_3_PIN 21
#define BUTTON_4_PIN 9
#define BUTTON_5_PIN 10

#define RGB_COUNT 1
#define DEBUG_BAUD_RATE 9600
#define CLOCK_PERIOD_MS 1

#pragma region --- Indicators


#pragma endregion
#pragma region --- Data Parsing --- 
/**
 * @brief The class that represents the device
 * that executes this program. This class
 * is global and accessed by multiple other
 * classes and functions. It is used to set
 * modes and take global actions.
 */
cDevice Device;

/**
 * @brief Global object which can be accessed
 * by all programs which include the Globals.h
 * file. This object is used to handle low level
 * BFIO chunk conversions. See Chunk.h for the
 * class's details such as its members and
 * methods.
 */
cChunk Chunk;

/**
 * @brief Global object which can be accessed
 * by all program swhich includes Globals.h.
 * This object is used to handle type convertions
 * to arrays of bytes and vise versa to be used
 * through the BFIO protocol.
 */
cData Data;

/**
 * @brief Global object which can be accessed
 * by all programs which includes Globals.h.
 * This object is used to handle packet
 * creation and convertions. In other words,
 * it creates and gets informations from planes.
 * 
 */
cPacket Packet;
#pragma endregion
#pragma region --- Terminals ---
/**
 * @brief The master terminal of the device.
 * Handles taxiways and runways required to
 * ask the other device functions and read
 * its answers.
 */
cTerminal MasterTerminal;

/**
 * @brief The slave terminal of the device.
 * Handles taxiways and provides answers
 * to the other device's function requests.
 */
cTerminal SlaveTerminal;
#pragma endregion
#pragma region --- Runways ---
/**
 * @brief The runway used for the
 * master terminal's departure
 */
cDepartureRunway MasterDepartureRunway;
/**
 * @brief The runway used for the
 * slave terminal's departure.
 */
cDepartureRunway SlaveDepartureRunway;
#pragma endregion
#pragma region --- Gates ---
/**
 * @brief This object handles the 
 * ping gate both for request
 * arrivals and request
 * departues aswell as answer parsing.
 * 
 * This mandatory BFIO gate is used to
 * handle the ping functions both ways.
 */
cGate_Ping Gate_Ping;
#pragma endregion

#pragma region Functions




#pragma endregion

#endif
