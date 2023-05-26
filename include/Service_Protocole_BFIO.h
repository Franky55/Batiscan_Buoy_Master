#ifndef SERVICEPROTOCOLEBFIO_H
#define SERVICEPROTOCOLEBFIO_H



typedef struct
{
    bool Left_Light_State;
    bool Right_Light_State;

    bool Camera_State;
    unsigned char Camera_Servo_Angle;

    bool Water_Detection;
    bool Low_Battery;
    bool In_Emergency;
    bool Ballast_State;
    bool Is_Communicating;

    int Pressure;
    signed char Temperature;
    signed char Pitch;
    signed char Roll;
    signed char Yaw;

    signed char Speed;
    unsigned char Battery;

    bool Surfacing;

}SERVICE_PROTOCOLE_BFIO;




int service_Protocole_BFIO_initialise(void);
void service_Protocole_BFIO_Setup_Answer(int fonctionID, unsigned char* plane, int* size);

extern SERVICE_PROTOCOLE_BFIO Service_Protocole_BFIO_struct;
#endif