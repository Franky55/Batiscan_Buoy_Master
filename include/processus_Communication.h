#ifndef PROCESSUSCOMMUNICATION_H
#define PROCESSUSCOMMUNICATION_H

typedef struct
{
    unsigned char State;
    unsigned char tabReceived[255];
    int DataToRead;
    int DataToSend;
    int DataToSendSPI;
}PROCESSUS_WIFI;

struct BITS
{
    unsigned char Left_Light_State:1;
    unsigned char Right_Light_State:1;
    unsigned char Camera_State:1;
    unsigned char Water_Detection:1;
    unsigned char Low_Battery:1;
    unsigned char In_Emergency:1;
    unsigned char Ballast_State:1;
    unsigned char Surfacing:1;

};

union Union_BOOL
{
    unsigned char All;
    struct BITS bits;
};


typedef struct
{
    union Union_BOOL union_Bool;

    unsigned char Camera_Servo_Angle;

    int Pressure;
    signed char Temperature;
    signed char Pitch;
    signed char Roll;
    signed char Yaw;

    signed char Speed;
    unsigned char Battery;

    bool Is_Communicating;

}PROCESSUS_COMMUNICATION;


int Processus_Communication_initialise(void);

extern PROCESSUS_WIFI processus_WIFI;
extern PROCESSUS_COMMUNICATION processus_Communication_Struct_WANTED_Value;
extern PROCESSUS_COMMUNICATION processus_Communication_Struct_ACTUAL_Value;
#endif