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
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "main.h"


#include "Enums.h"

#include "Device.h"
#include "BFIO.h"
#include "Chunk.h"
#include "Data.h"
#include "Packet.h"


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
/** 
 * @brief Hardware handling class that
 * directly handles the WS2812 RGB
 * LEDs. This is used by the RGB class. 
 */

/**
 * @brief Interface allowing easy
 * handling of colors and modes of the
 * WS2812 addressable RGB LEDs without
 * having to manually deal with the
 * Adafruit hardware handling class.
 */

#pragma endregion
#pragma region --- Controls ---
/**
 * @brief Class allowing easy readings
 * and interfacing of Gamepad's
 * left joystick.
 * This is a timebase class and must have
 * its update called periodically.
 */



#pragma endregion
#pragma region --- Data Parsing --- 
/**
 * @brief The class that represents the device
 * that executes this program. This class
 * is global and accessed by multiple other
 * classes and functions. It is used to set
 * modes and take global actions.
 */
extern cDevice Device;

/**
 * @brief Global object which can be accessed
 * by all programs which include the Globals.h
 * file. This object is used to handle low level
 * BFIO chunk conversions. See Chunk.h for the
 * class's details such as its members and
 * methods.
 */
extern cChunk Chunk;

/**
 * @brief Global object which can be accessed
 * by all program swhich includes Globals.h.
 * This object is used to handle type convertions
 * to arrays of bytes and vise versa to be used
 * through the BFIO protocol.
 */
extern cData Data;

/**
 * @brief Global object which can be accessed
 * by all programs which includes Globals.h.
 * This object is used to handle packet
 * creation and convertions. In other words,
 * it creates and gets informations from planes.
 * 
 */
extern cPacket Packet;
#pragma endregion
#pragma region --- Terminals ---
/**
 * @brief The master terminal of the device.
 * Handles taxiways and runways required to
 * ask the other device functions and read
 * its answers.
*/

/**
 * @brief The slave terminal of the device.
 * Handles taxiways and provides answers
 * to the other device's function requests.
 */

#pragma endregion
#pragma region --- Runways ---
/**
 * @brief The runway used for the
 * master terminal's departure
 */

/**
 * @brief The runway used for the
 * slave terminal's departure.
 */

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

#pragma endregion

#pragma region Functions
/**
 * @brief Function that initializes and
 * builds the classes defined in the
 * section above. Call this as the
 * very first thing in your program.
 * @return Execution:
 * See definition for potential values.
 */


Execution InitializeProject();

/**
 * @brief Function that tests if the
 * initialization done when calling
 * @ref InitializeProject 
 * was successful.
 * 
 * @return Execution
 */
Execution TestInitialization();

#pragma endregion

#endif
