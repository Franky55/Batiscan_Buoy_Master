#ifndef SERVICEPROTOCOLEBFIO_H
#define SERVICEPROTOCOLEBFIO_H





int service_Protocole_BFIO_initialise(void);
void service_Protocole_BFIO_Setup_Answer(int fonctionID, unsigned char* plane, int* size);
void service_Protocole_BFIO_Read_Data(int *fonctionID, unsigned char* tabReceived, int* size);


#endif