
#include "Arduino.h"
#include "Globals.h"
#include "main.h"
#include "Service_Protocole_BFIO.h"
#include "interface_NEOPIXEL.h"
#include "serviceBaseDeTemps.h"

#include <stdio.h>
#include "interface_WIFI.h"
#include "interface_SPI_Master.h"




Execution service_Protocole_BFIO_Get_Bytes_To_Send(unsigned short* plane, unsigned char* ucplane, int *size);
Execution service_Protocole_BFIO_Setup_Universal_Answer(unsigned short* plane, int *size);
int service_Protocole_BFIO_initialise(void);

SERVICE_PROTOCOLE_BFIO Service_Protocole_BFIO_struct;



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
    interface_NEOPIXEL_allume(50,0,55);
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
    case 7:
        service_Protocole_BFIO_Setup_Universal_Answer(usPlane, size);
        interface_NEOPIXEL_allume(255,255,255);
        service_Protocole_BFIO_Get_Bytes_To_Send(usPlane, plane, size);
        break;
    
    default:
        break;
    }
}