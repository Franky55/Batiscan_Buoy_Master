
#ifndef SERVICEPROTOCOLESPI_H
#define SERVICEPROTOCOLESPI_H




int service_Protocole_SPI_initialise(void);
int service_Protocole_SPI_Received(unsigned char* plane, int* size);
int service_Protocole_SPI_Pepare_Trame_Slave(unsigned char* plane, int* size);


#endif