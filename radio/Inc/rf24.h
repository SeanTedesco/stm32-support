/** @file rf24.h
 *
 * @author	sean-tedesco
 * @date	2022-12-15
 */

#ifndef RF24_H_
#define RF24_H_

#include "cppmain.h"
#include "rf24_registers.h"

#define rf24_max(a, b) (a > b ? a : b)
#define rf24_min(a, b) (a < b ? a : b)

class RF24
{
    private:
        uint16_t ce_pin;                    /* chip enable pin, activates the RX or TX role */
        uint16_t csn_pin;                   /* spi chip select */
        uint32_t spi_speed;                 /* spi bus speed */
        uint8_t status;                     /* the status byte returned from every SPI transaction */
        uint8_t payload_size;               /* fixed size of payloads */
        uint8_t pipe0_reading_address[5];   /* last address set on pipe 0 for reading. */
        uint8_t config_reg;                 /* for storing the value of the NRF_CONFIG register */
        bool _is_p_variant;                 /* for storing the result of testing the toggleFeatures() affect */
        bool _is_p0_rx;                     /* for keeping track of pipe 0's usage in user-triggered RX mode. */

    protected:
        bool ack_payloads_enabled;          /* whether ack payloads are enabled. */
        uint8_t addr_width;                 /* the address width to use (3, 4 or 5 bytes). */
        bool dynamic_payloads_enabled;      /* whether dynamic payloads are enabled. */

        void read_register(uint8_t reg, uint8_t* buf, uint8_t len);
        uint8_t read_register(uint8_t reg);

    public:
        RF24(uint16_t _cepin, uint16_t _cspin, uint32_t _spi_speed = RF24_SPI_SPEED);
        RF24(uint32_t _spi_speed = RF24_SPI_SPEED);
        bool begin(void);
        bool begin(uint16_t _cepin, uint16_t _cspin);
        bool isChipConnected();
        void startListening(void);
        void stopListening(void);
        bool available(void);
        bool available(uint8_t* pipe_num);
        void read(void* buf, uint8_t len);
        bool write(const void* buf, uint8_t len);
        void openWritingPipe(const uint8_t* address);
        void openReadingPipe(uint8_t number, const uint8_t* address);

        void printDetails(void);
        void printPrettyDetails(void);
        bool rxFifoFull();
        uint8_t isFifo(bool about_tx);
        bool isFifo(bool about_tx, bool check_empty);
        void powerDown(void);
        void powerUp(void);
        bool write(const void* buf, uint8_t len, const bool multicast);
        bool writeFast(const void* buf, uint8_t len);
        bool writeFast(const void* buf, uint8_t len, const bool multicast);

};

void nRF24_init(void);
void nRF24_tx_mode(uint8_t *address, uint8_t channel);
void nRF24_rx_mode(uint8_t *address, uint8_t channel);
uint8_t nRF24_transmit (uint8_t *data);
void nRF24_receive (uint8_t *data);
uint8_t nRF24_is_data_available(int pipenum);
void nRF24_read_all (uint8_t *data);


#endif /* RF24_H_ */
