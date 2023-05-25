#ifndef SERVICEPROTOCOLEBFIO_H
#define SERVICEPROTOCOLEBFIO_H



typedef struct
{
    unsigned char State;
    unsigned char tabReceived[255];
    int DataToRead;
    int DataToSend;
    int DataToSendSPI;
}SERVICE_PROTOCOLE_BFIO;




int service_Protocole_BFIO_initialise(void);
void service_Protocole_BFIO_Setup_Answer(int fonctionID, unsigned char* plane, int* size);

extern SERVICE_PROTOCOLE_BFIO Service_Protocole_BFIO_struct;
#endif