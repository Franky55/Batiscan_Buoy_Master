
#include "Arduino.h"
#include "Globals.h"
#include "main.h"
#include "Service_Protocole_BFIO.h"
#include "interface_NEOPIXEL.h"
#include "serviceBaseDeTemps.h"

#include <stdio.h>
#include "Processus_Communication.h"




Execution service_Protocole_BFIO_Get_Bytes_To_Send(unsigned short* plane, unsigned char* ucplane, int *size);
Execution service_Protocole_BFIO_Setup_Universal_Answer(unsigned short* plane, int *size);
Execution service_Protocole_BFIO_Setup_UPDATE_LIGHTS(unsigned short* plane, int *size);
Execution service_Protocole_BFIO_Setup_UPDATE_CAMERA(unsigned short* plane, int *size);
Execution service_Protocole_BFIO_Setup_GET_ALL_STATES(unsigned short* plane, int *size);
Execution service_Protocole_BFIO_Setup_GET_ALL_SENSORS(unsigned short* plane, int *size);
Execution service_Protocole_BFIO_Setup_UPDATE_NAVIGATION(unsigned short* plane, int *size);
Execution service_Protocole_BFIO_Setup_SET_BALLAST(unsigned short* plane, int *size);
Execution service_Protocole_BFIO_Setup_SURFACE(unsigned short* plane, int *size);


Execution service_Protocole_BFIO_Received_UPDATE_LIGHTS(unsigned short *plane, int resultedPlaneSize);
Execution service_Protocole_BFIO_Received_UPDATE_CAMERA(unsigned short *plane, int resultedPlaneSize);
Execution service_Protocole_BFIO_Received_UPDATE_NAVIGATION(unsigned short *plane, int resultedPlaneSize);
Execution service_Protocole_BFIO_Received_SET_BALLAST(unsigned short *plane, int resultedPlaneSize);
Execution service_Protocole_BFIO_Received_SURFACE(unsigned short *plane, int resultedPlaneSize);

int service_Protocole_BFIO_initialise(void);




int service_Protocole_BFIO_initialise(void)
{
    Device.SetStatus(Status::Handshake);
    return 0;
}

/**
 * @brief 
 * Unsigned long long ID = 4210
 * Unsigned long long BFIO Version = 1
 * 
 * unsigned char type = 2
 * unsigned char status = device.status (start handshack, after available)
 * 
 * string Git repo
 * string DeviceName = Batiscan
 * 
 * string DeviceVersion = Rev A
 * 
 */
Execution service_Protocole_BFIO_Setup_Universal_Answer(unsigned short* plane, int *size)
{   
    Execution execution;
    unsigned char buffer_Byte_ID[8];
    unsigned char buffer_Byte_BFIO_Version[8];
    unsigned char buffer_Byte_type[1];
    unsigned char buffer_Byte_ucStatus[1];
    unsigned char buffer_Byte_GitRepo[100];
    unsigned char buffer_Byte_DeviceName[50];
    unsigned char buffer_Byte_DeviceVersion[50];


    unsigned short buffer_Short_ID[9];
    unsigned short buffer_Short_BFIO_Version[9];
    unsigned short buffer_Short_type[2];
    unsigned short buffer_Short_ucStatus[2];
    unsigned short buffer_Short_GitRepo[100];
    unsigned short buffer_Short_DeviceName[50];
    unsigned short buffer_Short_DeviceVersion[50];

    unsigned short buffer_Short_To_Send[300];
    

    int resultedPlaneSize = 100;
    unsigned char functionID = 7;


    int status = 0;
    Device.GetStatus(&status);
    unsigned long long ID = 4210;
    unsigned long long BFIO_Version = 1;
    unsigned char type = 69;
    unsigned char ucStatus = status;/////////////////////////////////////////////////////
    std::string GitRepo = "https://github.com/Franky55/Batiscan_Buoy_Master";
    std::string DeviceName = "Batiscan";
    std::string DeviceVersion = "Rev A";
    
    #pragma region --- CONVERT TO BYTES
    execution = Data.ToBytes(ID, buffer_Byte_ID, 8);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(BFIO_Version, buffer_Byte_BFIO_Version, 8);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(type, buffer_Byte_type, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(ucStatus, buffer_Byte_ucStatus, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(GitRepo, buffer_Byte_GitRepo, GitRepo.size());
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    execution = Data.ToBytes(DeviceName, buffer_Byte_DeviceName, DeviceName.size());
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    execution = Data.ToBytes(DeviceVersion, buffer_Byte_DeviceVersion, DeviceVersion.size());
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    #pragma endregion
    
    #pragma region --- CONVERT TO SEGMENTS
    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_ID, buffer_Short_ID, 8, 9);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_BFIO_Version, buffer_Short_BFIO_Version, 8, 9);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_type, buffer_Short_type, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_ucStatus, buffer_Short_ucStatus, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_GitRepo, buffer_Short_GitRepo, GitRepo.size(), GitRepo.size()+1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_DeviceName, buffer_Short_DeviceName, DeviceName.size(), DeviceName.size()+1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_DeviceVersion, buffer_Short_DeviceVersion, DeviceVersion.size(), DeviceVersion.size()+1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    #pragma endregion

    #pragma region --- APPEND SEGMENTS
    execution = Packet.AppendSegments(buffer_Short_ID, 9, buffer_Short_BFIO_Version, 9, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    // execution = Packet.AppendSegments(buffer_Short_To_Send, resultedPlaneSize, buffer_Short_BFIO_Version, 9, buffer_Short_To_Send, &resultedPlaneSize);
    // if(execution != Execution::Passed)
    // {
    //     return Execution::Failed;
    // }

    execution = Packet.AppendSegments(buffer_Short_To_Send, resultedPlaneSize, buffer_Short_type, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.AppendSegments(buffer_Short_To_Send, resultedPlaneSize, buffer_Short_ucStatus, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.AppendSegments(buffer_Short_To_Send, resultedPlaneSize, buffer_Short_GitRepo, GitRepo.size()+1, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.AppendSegments(buffer_Short_To_Send, resultedPlaneSize, buffer_Short_DeviceName, DeviceName.size()+1, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.AppendSegments(buffer_Short_To_Send, resultedPlaneSize, buffer_Short_DeviceVersion, DeviceVersion.size()+1, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }


    #pragma endregion

    #pragma region --- CREATE PLANE
    execution = Packet.CreateFromSegments(functionID, buffer_Short_To_Send, resultedPlaneSize, plane, 300);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    #pragma endregion

    
    resultedPlaneSize = resultedPlaneSize +2;
    *size = resultedPlaneSize;
    Device.SetStatus(Status::Available);
    return Execution::Passed;
}


/**
 * @brief Fonction qui permet de faire un avion pour repondre a update lights
 * 
 * @param plane L'endroit ou je vais mettre l'avion construit
 * @param size La grosseur de l'avion construit
 * @return Execution 
 */
Execution service_Protocole_BFIO_Setup_UPDATE_LIGHTS(unsigned short* plane, int *size)
{   
    Execution execution;
    unsigned char buffer_Byte_Left_Light[1];
    unsigned char buffer_Byte_Right_Light[1];


    unsigned short buffer_Short_Left_Light[2];
    unsigned short buffer_Short_Right_Light[2];


    unsigned short buffer_Short_To_Send[50];
    

    int resultedPlaneSize = 100;
    unsigned char functionID = UPDATE_LIGHTS;

    
    #pragma region --- CONVERT TO BYTES
    execution = Data.ToBytes(processus_Communication_Struct_WANTED_Value.union_Bool.bits.Left_Light_State, buffer_Byte_Left_Light, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(processus_Communication_Struct_WANTED_Value.union_Bool.bits.Right_Light_State, buffer_Byte_Right_Light, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    
    #pragma endregion
    
    #pragma region --- CONVERT TO SEGMENTS
    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Left_Light, buffer_Short_Left_Light, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Right_Light, buffer_Short_Right_Light, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    
    #pragma endregion

    #pragma region --- APPEND SEGMENTS
    execution = Packet.AppendSegments(buffer_Short_Left_Light, 2, buffer_Short_Right_Light, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    #pragma endregion

    #pragma region --- CREATE PLANE
    execution = Packet.CreateFromSegments(functionID, buffer_Short_To_Send, resultedPlaneSize, plane, 300);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    #pragma endregion

    
    resultedPlaneSize = resultedPlaneSize +2;
    *size = resultedPlaneSize;
    Device.SetStatus(Status::Available);
    return Execution::Passed;
}

/**
 * @brief Fonction qui permet de faire un avion pour repondre a update camera
 * 
 * @param plane L'endroit ou je vais mettre l'avion construit
 * @param size La grosseur de l'avion construit
 * @return Execution 
 */
Execution service_Protocole_BFIO_Setup_UPDATE_CAMERA(unsigned short* plane, int *size)
{   
    Execution execution;
    unsigned char buffer_Byte_Camera_State[1];
    unsigned char buffer_Byte_Camera_Servo[1];


    unsigned short buffer_Short_Camera_State[2];
    unsigned short buffer_Short_Camera_Servo[2];


    unsigned short buffer_Short_To_Send[50];
    

    int resultedPlaneSize = 100;
    unsigned char functionID = UPDATE_CAMERA;

    
    #pragma region --- CONVERT TO BYTES
    execution = Data.ToBytes(processus_Communication_Struct_WANTED_Value.union_Bool.bits.Camera_State, buffer_Byte_Camera_State, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(processus_Communication_Struct_WANTED_Value.Camera_Servo_Angle, buffer_Byte_Camera_Servo, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    
    #pragma endregion
    
    #pragma region --- CONVERT TO SEGMENTS
    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Camera_State, buffer_Short_Camera_State, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Camera_Servo, buffer_Short_Camera_Servo, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    
    #pragma endregion

    #pragma region --- APPEND SEGMENTS
    execution = Packet.AppendSegments(buffer_Short_Camera_State, 2, buffer_Short_Camera_Servo, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    #pragma endregion

    #pragma region --- CREATE PLANE
    execution = Packet.CreateFromSegments(functionID, buffer_Short_To_Send, resultedPlaneSize, plane, 300);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    #pragma endregion

    
    resultedPlaneSize = resultedPlaneSize +2;
    *size = resultedPlaneSize;
    Device.SetStatus(Status::Available);
    return Execution::Passed;
}



/**
 * @brief Fonction qui permet de faire un avion pour repondre a Get All States
 * 
 * @param plane L'endroit ou je vais mettre l'avion construit
 * @param size La grosseur de l'avion construit
 * @return Execution 
 */
Execution service_Protocole_BFIO_Setup_GET_ALL_STATES(unsigned short* plane, int *size)
{   
    Execution execution;
    unsigned char buffer_Byte_Water_Detected[1];
    unsigned char buffer_Byte_Camera_State[1];
    unsigned char buffer_Byte_Low_Battery[1];
    unsigned char buffer_Byte_Left_Light_State[1];
    unsigned char buffer_Byte_Right_Light_State[1];
    unsigned char buffer_Byte_In_Emergency[1];
    unsigned char buffer_Byte_Ballast[1];
    unsigned char buffer_Byte_IsCommunicating[1];


    unsigned short buffer_Short_Water_Detected[2];
    unsigned short buffer_Short_Camera_State[2];
    unsigned short buffer_Short_Low_Battery[2];
    unsigned short buffer_Short_Left_Light_State[2];
    unsigned short buffer_Short_Right_Light_State[2];
    unsigned short buffer_Short_In_Emergency[2];
    unsigned short buffer_Short_Ballast[2];
    unsigned short buffer_Short_IsCommunicating[2];


    unsigned short buffer_Short_To_Send[100];
    

    int resultedPlaneSize = 100;
    unsigned char functionID = GET_ALL_STATES;

    
    #pragma region --- CONVERT TO BYTES
    execution = Data.ToBytes(processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.Water_Detection, buffer_Byte_Water_Detected, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.Camera_State, buffer_Byte_Camera_State, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.Low_Battery, buffer_Byte_Low_Battery, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.Left_Light_State, buffer_Byte_Left_Light_State, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.Right_Light_State, buffer_Byte_Right_Light_State, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.In_Emergency, buffer_Byte_In_Emergency, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.Ballast_State, buffer_Byte_Ballast, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(processus_Communication_Struct_ACTUAL_Value.Is_Communicating, buffer_Byte_IsCommunicating, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    
    #pragma endregion
    
    #pragma region --- CONVERT TO SEGMENTS
    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Water_Detected, buffer_Short_Water_Detected, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Camera_State, buffer_Short_Camera_State, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Low_Battery, buffer_Short_Low_Battery, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Left_Light_State, buffer_Short_Left_Light_State, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Right_Light_State, buffer_Short_Right_Light_State, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_In_Emergency, buffer_Short_In_Emergency, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Ballast, buffer_Short_Ballast, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    
    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_IsCommunicating, buffer_Short_IsCommunicating, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    
    #pragma endregion

    #pragma region --- APPEND SEGMENTS
    execution = Packet.AppendSegments(buffer_Short_Water_Detected, 2, buffer_Short_Camera_State, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.AppendSegments(buffer_Short_To_Send, resultedPlaneSize, buffer_Short_Low_Battery, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.AppendSegments(buffer_Short_To_Send, resultedPlaneSize, buffer_Short_Left_Light_State, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.AppendSegments(buffer_Short_To_Send, resultedPlaneSize, buffer_Short_Right_Light_State, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.AppendSegments(buffer_Short_To_Send, resultedPlaneSize, buffer_Short_In_Emergency, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.AppendSegments(buffer_Short_To_Send, resultedPlaneSize, buffer_Short_Ballast, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.AppendSegments(buffer_Short_To_Send, resultedPlaneSize, buffer_Short_IsCommunicating, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    #pragma endregion

    #pragma region --- CREATE PLANE
    execution = Packet.CreateFromSegments(functionID, buffer_Short_To_Send, resultedPlaneSize, plane, 300);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    #pragma endregion

    
    resultedPlaneSize = resultedPlaneSize +2;
    *size = resultedPlaneSize;
    Device.SetStatus(Status::Available);
    return Execution::Passed;
}


/**
 * @brief Fonction qui permet de faire un avion pour repondre a Get All Sensors
 * 
 * @param plane L'endroit ou je vais mettre l'avion construit
 * @param size La grosseur de l'avion construit
 * @return Execution 
 */
Execution service_Protocole_BFIO_Setup_GET_ALL_SENSORS(unsigned short* plane, int *size)
{   
    Execution execution;
    unsigned char buffer_Byte_Pressure[2];
    unsigned char buffer_Byte_Pitch[1];
    unsigned char buffer_Byte_Roll[1];
    unsigned char buffer_Byte_Yaw[1];
    unsigned char buffer_Byte_Speed[1];
    unsigned char buffer_Byte_Battery[1];


    unsigned short buffer_Short_Pressure[3];
    unsigned short buffer_Short_Pitch[2];
    unsigned short buffer_Short_Roll[2];
    unsigned short buffer_Short_Yaw[2];
    unsigned short buffer_Short_Speed[2];
    unsigned short buffer_Short_Battery[2];


    unsigned short buffer_Short_To_Send[150];
    

    int resultedPlaneSize = 100;
    unsigned char functionID = GET_ALL_SENSORS;

    
    #pragma region --- CONVERT TO BYTES
    execution = Data.ToBytes(processus_Communication_Struct_ACTUAL_Value.Pressure, buffer_Byte_Pressure, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(processus_Communication_Struct_ACTUAL_Value.Pitch, buffer_Byte_Pitch, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(processus_Communication_Struct_ACTUAL_Value.Roll, buffer_Byte_Roll, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(processus_Communication_Struct_ACTUAL_Value.Yaw, buffer_Byte_Yaw, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(processus_Communication_Struct_ACTUAL_Value.Speed, buffer_Byte_Speed, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(processus_Communication_Struct_ACTUAL_Value.Battery, buffer_Byte_Battery, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    
    #pragma endregion
    
    #pragma region --- CONVERT TO SEGMENTS
    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Pressure, buffer_Short_Pressure, 2, 3);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Pitch, buffer_Short_Pitch, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Roll, buffer_Short_Roll, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Yaw, buffer_Short_Yaw, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Speed, buffer_Short_Speed, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Battery, buffer_Short_Battery, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    
    #pragma endregion

    #pragma region --- APPEND SEGMENTS
    execution = Packet.AppendSegments(buffer_Short_Pressure, 3, buffer_Short_Pitch, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.AppendSegments(buffer_Short_To_Send, resultedPlaneSize, buffer_Short_Roll, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.AppendSegments(buffer_Short_To_Send, resultedPlaneSize, buffer_Short_Yaw, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.AppendSegments(buffer_Short_To_Send, resultedPlaneSize, buffer_Short_Speed, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.AppendSegments(buffer_Short_To_Send, resultedPlaneSize, buffer_Short_Battery, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }


    #pragma endregion

    #pragma region --- CREATE PLANE
    execution = Packet.CreateFromSegments(functionID, buffer_Short_To_Send, resultedPlaneSize, plane, 300);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    #pragma endregion

    
    resultedPlaneSize = resultedPlaneSize +2;
    *size = resultedPlaneSize;
    Device.SetStatus(Status::Available);
    return Execution::Passed;
}

/**
 * @brief Fonction qui permet de faire un avion pour repondre a Update Navigation
 * 
 * @param plane L'endroit ou je vais mettre l'avion construit
 * @param size La grosseur de l'avion construit
 * @return Execution 
 */
Execution service_Protocole_BFIO_Setup_UPDATE_NAVIGATION(unsigned short* plane, int *size)
{   
    Execution execution;
    unsigned char buffer_Byte_Pressure[1];
    unsigned char buffer_Byte_Pitch[1];
    unsigned char buffer_Byte_Roll[1];
    unsigned char buffer_Byte_Yaw[1];


    unsigned short buffer_Short_Pressure[2];
    unsigned short buffer_Short_Pitch[2];
    unsigned short buffer_Short_Roll[2];
    unsigned short buffer_Short_Yaw[2];


    unsigned short buffer_Short_To_Send[150];
    

    int resultedPlaneSize = 100;
    unsigned char functionID = UPDATE_NAVIGATION;

    
    #pragma region --- CONVERT TO BYTES
    execution = Data.ToBytes(processus_Communication_Struct_WANTED_Value.Speed, buffer_Byte_Pressure, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(processus_Communication_Struct_WANTED_Value.Pitch, buffer_Byte_Pitch, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(processus_Communication_Struct_WANTED_Value.Roll, buffer_Byte_Roll, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Data.ToBytes(processus_Communication_Struct_WANTED_Value.Yaw, buffer_Byte_Yaw, 1);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }


    
    #pragma endregion
    
    #pragma region --- CONVERT TO SEGMENTS
    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Pressure, buffer_Short_Pressure, 2, 3);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Pitch, buffer_Short_Pitch, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Roll, buffer_Short_Roll, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Yaw, buffer_Short_Yaw, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    
    #pragma endregion

    #pragma region --- APPEND SEGMENTS
    execution = Packet.AppendSegments(buffer_Short_Pressure, 3, buffer_Short_Pitch, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.AppendSegments(buffer_Short_To_Send, resultedPlaneSize, buffer_Short_Roll, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    execution = Packet.AppendSegments(buffer_Short_To_Send, resultedPlaneSize, buffer_Short_Yaw, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }



    #pragma endregion

    #pragma region --- CREATE PLANE
    execution = Packet.CreateFromSegments(functionID, buffer_Short_To_Send, resultedPlaneSize, plane, 300);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    #pragma endregion

    
    resultedPlaneSize = resultedPlaneSize +2;
    *size = resultedPlaneSize;
    Device.SetStatus(Status::Available);
    return Execution::Passed;
}


/**
 * @brief Fonction qui permet de faire un avion pour repondre a Set Ballast
 * 
 * @param plane L'endroit ou je vais mettre l'avion construit
 * @param size La grosseur de l'avion construit
 * @return Execution 
 */
Execution service_Protocole_BFIO_Setup_SET_BALLAST(unsigned short* plane, int *size)
{   
    Execution execution;
    unsigned char buffer_Byte_Pressure[1];

    unsigned short buffer_Short_Pressure[2];


    unsigned short buffer_Short_To_Send[150];
    

    int resultedPlaneSize = 100;
    unsigned char functionID = SET_BALLAST;

    
    #pragma region --- CONVERT TO BYTES
    execution = Data.ToBytes(processus_Communication_Struct_WANTED_Value.union_Bool.bits.Ballast_State, buffer_Byte_Pressure, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    #pragma endregion
    
    #pragma region --- CONVERT TO SEGMENTS
    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Pressure, buffer_Short_Pressure, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }


    
    #pragma endregion

    #pragma region --- APPEND SEGMENTS

    execution = Packet.AppendSegments(buffer_Short_To_Send, 0, buffer_Short_Pressure, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }



    #pragma endregion

    #pragma region --- CREATE PLANE
    execution = Packet.CreateFromSegments(functionID, buffer_Short_To_Send, resultedPlaneSize, plane, 300);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    #pragma endregion

    
    resultedPlaneSize = resultedPlaneSize +2;
    *size = resultedPlaneSize;
    Device.SetStatus(Status::Available);
    return Execution::Passed;
}


/**
 * @brief Fonction qui permet de faire un avion pour repondre a Surface
 * 
 * @param plane L'endroit ou je vais mettre l'avion construit
 * @param size La grosseur de l'avion construit
 * @return Execution 
 */
Execution service_Protocole_BFIO_Setup_SURFACE(unsigned short* plane, int *size)
{   
    Execution execution;
    unsigned char buffer_Byte_Pressure[1];

    unsigned short buffer_Short_Pressure[2];


    unsigned short buffer_Short_To_Send[150];
    

    int resultedPlaneSize = 100;
    unsigned char functionID = SURFACE;

    
    #pragma region --- CONVERT TO BYTES
    execution = Data.ToBytes(processus_Communication_Struct_WANTED_Value.union_Bool.bits.Surfacing, buffer_Byte_Pressure, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }

    #pragma endregion
    
    #pragma region --- CONVERT TO SEGMENTS
    execution = Packet.GetParameterSegmentFromBytes(buffer_Byte_Pressure, buffer_Short_Pressure, 1, 2);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }


    
    #pragma endregion

    #pragma region --- APPEND SEGMENTS

    execution = Packet.AppendSegments(buffer_Short_To_Send, 0, buffer_Short_Pressure, 2, buffer_Short_To_Send, &resultedPlaneSize);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }



    #pragma endregion

    #pragma region --- CREATE PLANE
    execution = Packet.CreateFromSegments(functionID, buffer_Short_To_Send, resultedPlaneSize, plane, 300);
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    #pragma endregion

    
    resultedPlaneSize = resultedPlaneSize +2;
    *size = resultedPlaneSize;
    Device.SetStatus(Status::Available);
    return Execution::Passed;
}



Execution service_Protocole_BFIO_Get_Bytes_To_Send(unsigned short* plane, unsigned char* ucplane, int *size)
{
    int compt_ucplane = 0;
    for(int i = 0; i < *size; i++)
    {
        unsigned char tabTemp[2];
        Chunk.ToUART(plane[i], tabTemp);
        
        ucplane[compt_ucplane] = tabTemp[1];
        compt_ucplane++;
        ucplane[compt_ucplane] = tabTemp[0];
        compt_ucplane++;
    }
    *size = compt_ucplane;
    return Execution::Passed;
}

void service_Protocole_BFIO_Setup_Answer(int fonctionID, unsigned char* plane, int* size)
{
    unsigned short usPlane[300];
    switch (fonctionID)
    {
    case 7://Universal Answer
        service_Protocole_BFIO_Setup_Universal_Answer(usPlane, size);
        break;

    case UPDATE_LIGHTS:
        service_Protocole_BFIO_Setup_UPDATE_LIGHTS(usPlane, size);
        break;

    case UPDATE_SERVOS:

        break;

    case UPDATE_MOTORS:

        break;

    case UPDATE_CAMERA:
        service_Protocole_BFIO_Setup_UPDATE_CAMERA(usPlane, size);
        break;

    case GET_ALL_STATES:
        service_Protocole_BFIO_Setup_GET_ALL_STATES(usPlane, size);
        break;

    case GET_ALL_SENSORS:
        service_Protocole_BFIO_Setup_GET_ALL_SENSORS(usPlane, size);
        break;

    case UPDATE_NAVIGATION:
        service_Protocole_BFIO_Setup_UPDATE_NAVIGATION(usPlane, size);
        break;

    case SET_BALLAST:
        service_Protocole_BFIO_Setup_SET_BALLAST(usPlane, size);
        break;

    case SURFACE:
        service_Protocole_BFIO_Setup_SURFACE(usPlane, size);
        break;

    
    default:
        break;
    }

    service_Protocole_BFIO_Get_Bytes_To_Send(usPlane, plane, size);
}



//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

//                      Receiver

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////




Execution service_Protocole_BFIO_Received_UPDATE_LIGHTS(unsigned short *plane, int resultedPlaneSize)
{   
    unsigned char receivedBytes[25];
    Execution execution = Packet.GetBytes(plane, resultedPlaneSize, 1, receivedBytes, 25);//Get Left Light
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    processus_Communication_Struct_WANTED_Value.union_Bool.bits.Left_Light_State = receivedBytes[0];
    memset(receivedBytes, 0, 25);


    execution = Packet.GetBytes(plane, resultedPlaneSize, 2, receivedBytes, 25);//Get Right Light
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    processus_Communication_Struct_WANTED_Value.union_Bool.bits.Right_Light_State = receivedBytes[0];
    memset(receivedBytes, 0, 25);
    return Execution::Passed;
}


Execution service_Protocole_BFIO_Received_UPDATE_CAMERA(unsigned short *plane, int resultedPlaneSize)
{   
    unsigned char receivedBytes[25];
    Execution execution = Packet.GetBytes(plane, resultedPlaneSize, 1, receivedBytes, 25);//Get Camera state
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    processus_Communication_Struct_WANTED_Value.union_Bool.bits.Camera_State = receivedBytes[0];
    memset(receivedBytes, 0, 25);


    execution = Packet.GetBytes(plane, resultedPlaneSize, 2, receivedBytes, 25);//Get Camera Angle
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    processus_Communication_Struct_WANTED_Value.Camera_Servo_Angle = receivedBytes[0];
    memset(receivedBytes, 0, 25);
    return Execution::Passed;
}


Execution service_Protocole_BFIO_Received_UPDATE_NAVIGATION(unsigned short *plane, int resultedPlaneSize)
{   
    unsigned char receivedBytes[25];
    Execution execution = Packet.GetBytes(plane, resultedPlaneSize, 1, receivedBytes, 25);//Get Speed
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    processus_Communication_Struct_WANTED_Value.Speed = receivedBytes[0];
    memset(receivedBytes, 0, 25);


    execution = Packet.GetBytes(plane, resultedPlaneSize, 2, receivedBytes, 25);//Get Pitch
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    processus_Communication_Struct_WANTED_Value.Pitch = receivedBytes[0];
    memset(receivedBytes, 0, 25);

    execution = Packet.GetBytes(plane, resultedPlaneSize, 3, receivedBytes, 25);//Get Roll
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    processus_Communication_Struct_WANTED_Value.Roll = receivedBytes[0];
    memset(receivedBytes, 0, 25);

    execution = Packet.GetBytes(plane, resultedPlaneSize, 4, receivedBytes, 25);//Get Yaw
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    processus_Communication_Struct_WANTED_Value.Yaw = receivedBytes[0];
    memset(receivedBytes, 0, 25);
    return Execution::Passed;
}


Execution service_Protocole_BFIO_Received_SET_BALLAST(unsigned short *plane, int resultedPlaneSize)
{   
    unsigned char receivedBytes[25];
    Execution execution = Packet.GetBytes(plane, resultedPlaneSize, 1, receivedBytes, 25);//Get Camera state
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    processus_Communication_Struct_WANTED_Value.union_Bool.bits.Ballast_State = receivedBytes[0];
    memset(receivedBytes, 0, 25);

    return Execution::Passed;
}

Execution service_Protocole_BFIO_Received_SURFACE(unsigned short *plane, int resultedPlaneSize)
{   
    unsigned char receivedBytes[25];
    Execution execution = Packet.GetBytes(plane, resultedPlaneSize, 1, receivedBytes, 25);//Get Camera state
    if(execution != Execution::Passed)
    {
        return Execution::Failed;
    }
    processus_Communication_Struct_WANTED_Value.union_Bool.bits.Surfacing = receivedBytes[0];
    memset(receivedBytes, 0, 25);

    return Execution::Passed;
}



void service_Protocole_BFIO_Read_Data(int *fonctionID, unsigned char* tabReceived, int* size)
{
    Execution execution;
    unsigned short plane[300];
    unsigned char ucFonctionID = 0;

    int resultedPlaneSize = 0;
    int extractedParameterCount;

    for(int i = 0; i < (*size); i+=2)
    {
        plane[i/2] = (unsigned short)(tabReceived[i] << 8) + tabReceived[i+1];
    }

    execution = Packet.GetID(plane, *size, &ucFonctionID);
    if(execution != Execution::Passed)
    {
        return;
    }

    execution = Packet.FullyAnalyze(plane, &resultedPlaneSize, &extractedParameterCount, &ucFonctionID);


    switch (ucFonctionID)
    {
    case 7://Universal Answer
        //Don't fucking care bitch
        //just need the ID
        break;

    case UPDATE_LIGHTS:
        service_Protocole_BFIO_Received_UPDATE_LIGHTS(plane, resultedPlaneSize);
        break;

    case UPDATE_SERVOS:

        break;

    case UPDATE_MOTORS:

        break;

    case UPDATE_CAMERA:
        service_Protocole_BFIO_Received_UPDATE_CAMERA(plane, resultedPlaneSize);
        break;

    case GET_ALL_STATES:
        //Just need the function ID
        break;

    case GET_ALL_SENSORS:
        //Just need the function ID
        break;

    case UPDATE_NAVIGATION:
        service_Protocole_BFIO_Received_UPDATE_NAVIGATION(plane, resultedPlaneSize);
        break;

    case SET_BALLAST:
        service_Protocole_BFIO_Received_SET_BALLAST(plane, resultedPlaneSize);
        break;

    case SURFACE:
        service_Protocole_BFIO_Received_SURFACE(plane, resultedPlaneSize);
        break;

    
    default:
    //wrong ID
        Serial.println("Wrong ID from plane");
        break;
    }

}