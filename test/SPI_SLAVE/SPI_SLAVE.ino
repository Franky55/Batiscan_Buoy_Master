#include <ESP32SPISlave.h>


#define SPI_MISO 13
#define SPI_MOSI 11
#define SPI_CLK 12
#define SPI_CS1 10


ESP32SPISlave slave;

static const uint32_t BUFFER_SIZE {1};
uint8_t spi_slave_tx_buf[BUFFER_SIZE] {8};
uint8_t spi_slave_rx_buf[BUFFER_SIZE] {0};

void setup() {
    Serial.begin(115200);
    delay(10000);


    // SPI Slave
    // HSPI = CS: 15, CLK: 14, MOSI: 13, MISO: 12 -> default
    // VSPI = CS:  5, CLK: 18, MOSI: 23, MISO: 19
    slave.setDataMode(SPI_MODE0);
    slave.begin(SPI3_HOST, SPI_CLK, SPI_MISO, SPI_MOSI, SPI_CS1);

    // connect same name pins each other
    // CS - CS, CLK - CLK, MOSI - MOSI, MISO - MISO

    printf("Master Slave Polling Test Start\n");
}

void loop() {
    // just queue transaction
    // if transaction has completed from master, buffer is automatically updated
    slave.queue(spi_slave_rx_buf, spi_slave_tx_buf, BUFFER_SIZE);


    // if slave has received transaction data, available() returns size of received transactions
    while (slave.available()) {
        printf("master -> slave : ");
        for (size_t i = 0; i < slave.size(); ++i) {
            printf("%d ", spi_slave_rx_buf[i]);
        }
        printf("\n");


        // clear received data
        memset(spi_slave_rx_buf, 0, BUFFER_SIZE);

        // you should pop the received packet
        slave.pop();
    }

    delay(2000);
}