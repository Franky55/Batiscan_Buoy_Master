/*
    ############    ############     ##########
    ############    ############     ##########
              ##              ##   ## 
    ####    ##      ####    ##     ############
    ####    ##      ####    ##     ############
              ##              ##             ##
    ############    ####      ##   ##########
    ############    ####      ##   ##########

    Title: BFIO.h
    Author: Lyam
*/

#ifndef BFIO_H
  #define BFIO_H
//=============================================//
//	Includes
//=============================================//

//=============================================//
//	Global Variables
//=============================================//
#define BFIO_TIMEOUT_MS 1000
#define BFIO_VERSION_ID 202305091044
#define BFIO_GIT_REPOSITORY "https://github.com/LyamBRS/BrSpand_GamePad.git"
#define _AMOUNT_OF_SUPPORTED_ID 20
#define MAX_PLANE_PASSENGER_CAPACITY 255

extern unsigned char supportedBFIOIDs[_AMOUNT_OF_SUPPORTED_ID];
//=============================================//
//	Classes
//=============================================//

/**
 * @brief Class that handles the high level
 * methods of the BFIO protocol. This also
 * contains the mandatory functions so you
 * can observe how they are defined and
 * handled.
 * 
 */
class cBFIO
 {       
    private:
           
    public:
        //////////////////////////////////// - CONSTRUCTOR -
        cBFIO();
        //////////////////////////////////// - Mandatory Functions -

        /**
         * @brief Mandatory BFIO function. This function
         * handles what to do when a ping function packet 
         * arrives at the master -> slave terminal. 
         * 
         * It automatically generates and queues the answer
         * it needs to send in the master -> slave terminal.
         * 
         * @param receivedPacket 
         * @param receivedPacketSize 
         * @return Execution 
         */
        // Execution Arrival_Ping(unsigned short* receivedPacket, int receivedPacketSize);

        // Execution Depart_Ping(unsigned );
 };

#endif