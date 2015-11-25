/**
 *  @file       hal_cc2500.c
 *  @brief      Use of CC2500 transeiver
 *  @details
 *  @author     Laboratorio de Comunicaciones - Universidad Catolica de Cordoba
 *
 *  @author		Marcucci, Ricardo Martin - rmarku(at)gmail.com
 *  @version	1.0
 *  @date       Agosto 27, 2013
 *  @pre        First initialize the system.
 *  @warning    Improper use can crash your application
 */

#include "hal_cc2500.h"
#include <msp430.h>

extern const pinConfig cc_gdo0, cc_gdo2, cc_spiSOMI, cc_spiSIMO, cc_spiCLK, cc_spinCS;

#ifdef CC_2500_PAEN
extern const pinConfig cc_PAEN, cc_LNAEN;
#endif

// 2.4GHz
// Product = CC2500
// Crystal accuracy = 40 ppm
// X-tal frequency = 26 MHz
// RF output power = 0 dBm
// RX filterbandwidth = 540.000000 kHz
// Deviation = 0.000000
// Return state:  Return to RX state upon leaving either TX or RX
// Modulation = (7) MSK
// Manchester enable = (0) Manchester disabled
// RF Frequency = 2433.000000 MHz
// Channel spacing = 199.950000 kHz
// Channel number = 0
// Optimization = Sensitivity
// Sync mode = (3) 30/32 sync word bits detected
// Format of RX/TX data = (0) Normal mode, use FIFOs for RX and TX
// CRC operation = (1) CRC calculation in TX and CRC check in RX enabled
// Forward Error Correction = (0) FEC disabled
// Length configuration = (1) Variable length packets, packet length configured by the first received byte after sync word.
// Packetlength = 255
// Preamble count = (2)  4 bytes
// Append status = 1
// Address check = (1) Address check, No Broadcast
// FIFO autoflush = 0
// Device address = 0
// GDO0 signal selection = ( 6) Asserts when sync word has been sent / received, and de-asserts at the end of the packet
// GDO2 signal selection = ( 9) CCA

#define spi_write spi1_write
#define spi_txBufReady spi1_txBufReady
#define spi_wr spi1_wr
#define spi_setup spi1_setup
#define spi_busy spi1_busy

void hal_cc2500_wakeup();
void hal_cc2500_writeReg(char addr, char value);
void hal_cc2500_writeBurstReg(char addr, char *buffer, char count);
char hal_cc2500_readReg(char addr);
void hal_cc2500_readBurstReg(char addr, char *buffer, char count);
char hal_cc2500_readStatus(char addr);
void hal_cc2500_strobe(char strobe);
void hal_cc2500_powerupReset(void);
char hal_cc2500_status(void);

void hal_cc2500_WriteRFSettings(void) {

	// Write register settings


	hal_cc2500_writeReg(TI_CCxxx0_IOCFG2, 0x09); // GDO2 output pin config. Como CCA
	hal_cc2500_writeReg(TI_CCxxx0_IOCFG0, 0x06); // GDO0 output pin config.
	hal_cc2500_writeReg(TI_CCxxx0_PKTLEN, 0xFF); // Packet length.
	hal_cc2500_writeReg(TI_CCxxx0_PKTCTRL1, 0x04); // Packet automation control. No Addr.check & RSSI & LQI & CRCflag
	hal_cc2500_writeReg(TI_CCxxx0_PKTCTRL0, 0x05); // Packet automation control. variable packet length & CRCcalc
	hal_cc2500_writeReg(TI_CCxxx0_ADDR, 0x01); // Device address.
	hal_cc2500_writeReg(TI_CCxxx0_CHANNR, 0x00); // Channel number.
	//---------------------------------------------
	hal_cc2500_writeReg(TI_CCxxx0_PATABLE, 0xFF);


#if TI_CC_BAUD_RATE_KBPS == TI_CC_BR_10_KBPS   
	hal_cc2500_writeReg(TI_CCxxx0_FSCTRL1, 0x06); // Freq synthesizer control.
	hal_cc2500_writeReg(TI_CCxxx0_FSCTRL0, 0x00); // Freq synthesizer control.
	hal_cc2500_writeReg(TI_CCxxx0_FREQ2, 0x5D); // Freq control word, high byte
	hal_cc2500_writeReg(TI_CCxxx0_FREQ1, 0x93); // Freq control word, mid byte.
	hal_cc2500_writeReg(TI_CCxxx0_FREQ0, 0xB1); // Freq control word, low byte.
	hal_cc2500_writeReg(TI_CCxxx0_MDMCFG4, 0x78); // Modem configuration.
	hal_cc2500_writeReg(TI_CCxxx0_MDMCFG3, 0x93); // Modem configuration.
	hal_cc2500_writeReg(TI_CCxxx0_MDMCFG2, 0x03); // Modem configuration.
	hal_cc2500_writeReg(TI_CCxxx0_MDMCFG1, 0x22); // Modem configuration.
	hal_cc2500_writeReg(TI_CCxxx0_MDMCFG0, 0xF8); // Modem configuration.
	hal_cc2500_writeReg(TI_CCxxx0_DEVIATN, 0x44); // Modem dev (when FSK mod en)
	hal_cc2500_writeReg(TI_CCxxx0_MCSM1, 0x3F); //  MainRadio Cntrl State Machine CCA_MODE 3.
	hal_cc2500_writeReg(TI_CCxxx0_MCSM0, 0x18); // MainRadio Cntrl State Machine
	hal_cc2500_writeReg(TI_CCxxx0_FOCCFG, 0x16); // Freq Offset Compens. Config
	hal_cc2500_writeReg(TI_CCxxx0_BSCFG, 0x6C); // Bit synchronization config.
	hal_cc2500_writeReg(TI_CCxxx0_AGCCTRL2, 0x43); // AGC control.
	hal_cc2500_writeReg(TI_CCxxx0_AGCCTRL1, 0x40); // AGC control.
	hal_cc2500_writeReg(TI_CCxxx0_AGCCTRL0, 0x91); // AGC control.
	hal_cc2500_writeReg(TI_CCxxx0_FREND1, 0x56); // Front end RX configuration.
	hal_cc2500_writeReg(TI_CCxxx0_FREND0, 0x10); // Front end RX configuration.
	hal_cc2500_writeReg(TI_CCxxx0_FSCAL3, 0xA9); // Frequency synthesizer cal.
#endif

#if TI_CC_BAUD_RATE_KBPS == TI_CC_BR_250_KBPS
	hal_cc2500_writeReg(TI_CCxxx0_FSCTRL1, 0x07); // Freq synthesizer control.
	hal_cc2500_writeReg(TI_CCxxx0_FSCTRL0, 0x00);// Freq synthesizer control.
	hal_cc2500_writeReg(TI_CCxxx0_FREQ2, 0x5D);// Freq control word, high byte
	hal_cc2500_writeReg(TI_CCxxx0_FREQ1, 0x93);// Freq control word, mid byte.
	hal_cc2500_writeReg(TI_CCxxx0_FREQ0, 0xB1);// Freq control word, low byte.
	hal_cc2500_writeReg(TI_CCxxx0_MDMCFG4, 0x2D);// Modem configuration.
	hal_cc2500_writeReg(TI_CCxxx0_MDMCFG3, 0x3B);// Modem configuration.
	hal_cc2500_writeReg(TI_CCxxx0_MDMCFG2, 0x73);// Modem configuration.
	hal_cc2500_writeReg(TI_CCxxx0_MDMCFG1, 0x22);// Modem configuration.
	hal_cc2500_writeReg(TI_CCxxx0_MDMCFG0, 0xF8);// Modem configuration.
	hal_cc2500_writeReg(TI_CCxxx0_DEVIATN, 0x00);// Modem dev (when FSK mod en)
	hal_cc2500_writeReg(TI_CCxxx0_MCSM1 , 0x3F);// MainRadio Cntrl State Machine CCA_MODE 3.
	hal_cc2500_writeReg(TI_CCxxx0_MCSM0 , 0x18);// MainRadio Cntrl State Machine
	hal_cc2500_writeReg(TI_CCxxx0_FOCCFG, 0x1D);// Freq Offset Compens. Config
	hal_cc2500_writeReg(TI_CCxxx0_BSCFG, 0x1C);// Bit synchronization config.
	hal_cc2500_writeReg(TI_CCxxx0_AGCCTRL2, 0x03);// AGC control.
	hal_cc2500_writeReg(TI_CCxxx0_AGCCTRL1, 0x40);// AGC control.
	hal_cc2500_writeReg(TI_CCxxx0_AGCCTRL0, 0xB2);// AGC control.
	hal_cc2500_writeReg(TI_CCxxx0_FREND1, 0xB6);// Front end RX configuration.
	hal_cc2500_writeReg(TI_CCxxx0_FREND0, 0x10);// Front end RX configuration.
	hal_cc2500_writeReg(TI_CCxxx0_FSCAL3, 0xEA);// Frequency synthesizer cal.
#endif

	hal_cc2500_writeReg(TI_CCxxx0_FSCAL2, 0x0A); // Frequency synthesizer cal.
	hal_cc2500_writeReg(TI_CCxxx0_FSCAL1, 0x00); // Frequency synthesizer cal.
	hal_cc2500_writeReg(TI_CCxxx0_FSCAL0, 0x11); // Frequency synthesizer cal.
	hal_cc2500_writeReg(TI_CCxxx0_FSTEST, 0x59); // Frequency synthesizer cal.
	hal_cc2500_writeReg(TI_CCxxx0_TEST2, 0x88); // Various test settings.
	hal_cc2500_writeReg(TI_CCxxx0_TEST1, 0x31); // Various test settings.
	hal_cc2500_writeReg(TI_CCxxx0_TEST0, 0x0B); // Various test settings.

	hal_cc2500_strobe(TI_CCxxx0_SRX);                                 // RX Mode
}
/**
 * This function transmits a packet with length up to 63 bytes.  To use this
 *  function, GD00 must be configured to be asserted when sync word is sent and
 *  de-asserted at the end of the packet, which is accomplished by setting the
 *  IOC FG0 register to 0x06,per the CCxxxx datasheet.  GDO0 goes high at
 *  packet start and returns low when complete.  The function polls GDO0 to
 *  ensure packet completion before returning.
 *
 * @param addr Variable containing the destination address to the ransmitted packet
 * @param txBuffer Pointer to a buffer containing the data to be transmitted
 * @param size The size of the txBuffer
 * @return 1 Packet Sended
 *           0 Not Sended (channel busy)
 */

char hal_cc2500_sendPacket(char addr, char *txBuffer, char size) {
	char status;

	hal_cc2500_writeReg(TI_CCxxx0_TXFIFO, (size + 1)); // Write the length of the packet in TX FIFO
	hal_cc2500_writeReg(TI_CCxxx0_TXFIFO, addr); // Write the address in TX FIFO
	hal_cc2500_writeBurstReg(TI_CCxxx0_TXFIFO, txBuffer, size); // Write TX data

	if (hal_pin_in(&cc_gdo2)) {             //Si esta libre el canal

#ifdef CC_2500_PAEN
		hal_pin_out(&cc_LNAEN, 0);
		hal_pin_out(&cc_PAEN, 1);
#endif
		hal_pin_intDisable(&cc_gdo0);            // Disable GDO0 Interrupt
		hal_cc2500_strobe(TI_CCxxx0_STX); // Change state to TX, initiating data transfer

		status = hal_cc2500_status();                       // Get CC2500 Status
		if (((status & TI_CCxxx0_STATUS_STATE) == TI_CCxxx0_STATUS_TX)
				|| ((status & TI_CCxxx0_STATUS_STATE) == TI_CCxxx0_STATUS_FSTXON)) {

			while (!hal_pin_in(&cc_gdo0))
				;                            // Wait GDO0 to go hi -> sync TX'ed

			while (hal_pin_in(&cc_gdo0))
				;                            // Wait GDO0 to clear -> end of pkt

			hal_pin_intClearFlag(&cc_gdo0);  // Clear GDO0 Interrupt Flag
			hal_pin_intEnable(&cc_gdo0);            // Enable GDO0 Interrupt
#ifdef CC_2500_PAEN
			hal_pin_out(&cc_PAEN, 0);
			hal_pin_out(&cc_LNAEN, 1);
#endif
			return 1;
		}
	}
#ifdef CC_2500_PAEN
	hal_pin_out(&cc_PAEN, 0);
	hal_pin_out(&cc_LNAEN, 1);
#endif

	hal_cc2500_strobe(TI_CCxxx0_SIDLE);
	hal_cc2500_strobe(TI_CCxxx0_SFTX);                           // Flush TXFIFO
	hal_cc2500_strobe(TI_CCxxx0_SRX);                                 // RX Mode
	hal_pin_intClearFlag(&cc_gdo0);  // Clear GDO0 Interrupt Flag
	hal_pin_intEnable(&cc_gdo0);            // Enable GDO0 Interrupt
	return 0;                                                    // Return Error
}

/**
 *   Receives a packet of variable length.
 * The packet length should not exceed the RXFIFO size.  To use this function,
 * APPEND_STATUS in the PKTCTRL1 register must be enabled.
 * It is assumed that the function is called after it is known that a packet has
 * been received; for example, in response to GDO0 going low when it is
 * configured to output packet reception status.
 *
 * The RXBYTES register is first read to ensure there are bytes in the FIFO.
 * This is done because the GDO signal will go high even if the FIFO is flushed
 * due to address filtering, CRC filtering, or packet length filtering.
 *
 * @param addr Pointer to a variable containing the address of the packet that is recived.
 * @param rxBuffer Pointer to the buffer where the incoming data should be stored
 * @param length Pointer to a variable containing the size of the rxBuffer where the
 *         incoming data should be stored. After this function returns, that
 *          variable holds the packet length.
 * @param rssi Pointer to a variable containing the RSSI.
 * @param lqi Pointer to a variable containing the LQI (Link Quality Indicator)
 * @return  0x80:  CRC OK
 *          0x00:  CRC NOT OK or receive ERROR
 */

char hal_cc2500_receivePacket(char *addr, char *rxBuffer, char *length, char *rssi, char *lqi) {
	char status[2];
	char pktLen;
	char rxFifo;

	rxFifo = (hal_cc2500_readStatus(TI_CCxxx0_RXBYTES) & TI_CCxxx0_NUM_RXBYTES); // Read the size of RX FIFO
	if (rxFifo) {                                           // If it�s not empty
		pktLen = hal_cc2500_readReg(TI_CCxxx0_RXFIFO); // Read length byte of the packet
		if (((pktLen + 2) < rxFifo) && (pktLen <= (*length + 1))) { // If size of (pktLen + RSSI + LQI) < RX FIFO and
																	//    size of pktLen <= size of (my packet + address)
			*addr = hal_cc2500_readReg(TI_CCxxx0_RXFIFO);        // Pull address
			hal_cc2500_readBurstReg(TI_CCxxx0_RXFIFO, rxBuffer, (pktLen - 1)); // Pull data in rxBuffer
			*length = pktLen - 1;                      // Return the actual size
			hal_cc2500_readBurstReg(TI_CCxxx0_RXFIFO, status, 2); // Read appended status bytes

			*rssi = status[TI_CCxxx0_RSSI_RX];                    // Return RSSI
			*lqi = (status[TI_CCxxx0_LQI_RX] & 0x7F);              // Return LQI

			rxFifo = (hal_cc2500_readStatus(TI_CCxxx0_RXBYTES) & TI_CCxxx0_NUM_RXBYTES);     // Read the size of RX FIFO
			if (rxFifo) {                                   // Is RX FIFO Empty?
				hal_cc2500_strobe(TI_CCxxx0_SIDLE); // If is not -> Flush the RX FIFO
				hal_cc2500_strobe(TI_CCxxx0_SFRX);
				hal_cc2500_strobe(TI_CCxxx0_SRX);                     // RX Mode
			}

			return (char) (status[TI_CCxxx0_LQI_RX] & TI_CCxxx0_CRC_OK); // Return CRC_OK bit
		} else {    // If i'm try to get less data than the actual size of pkLen
			*length = pktLen - 1;                       // Return the large size
			hal_cc2500_strobe(TI_CCxxx0_SIDLE);
			hal_cc2500_strobe(TI_CCxxx0_SFRX);                   // Flush RXFIFO
			hal_cc2500_strobe(TI_CCxxx0_SRX);                         // RX Mode
			return 0;                                            // Return Error
		}
	} else {                                              // If RX FIFO is empty
		hal_cc2500_strobe(TI_CCxxx0_SIDLE);
		hal_cc2500_strobe(TI_CCxxx0_SFRX);                       // Flush RXFIFO
		hal_cc2500_strobe(TI_CCxxx0_SRX);                             // RX Mode
		return 0;                                                // Return Error
	}
}

// Parte SPI, comandos

/**
 * Delay function. # of CPU cycles delayed is similar to "cycles". Specifically,
 * it's ((cycles-15) % 6) + 15.  Not exact, but gives a sense of the real-time
 * delay.  Also, if MCLK ~1MHz, "cycles" is similar to # of useconds delayed.
 *
 * @param cycles
 */

//TODO: ver que hacer para un delay de 1us de base.
inline void hal_cc2500_wait(uint16_t cycles) {

	//while (cycles > 15)                        // 15 cycles consumed by overhead
	//	cycles = cycles - 6;                 // 6 cycles consumed each iteration
}

/**
 *  Writes "value" to a single configuration register at address "addr".
 *
 * @param addr   address of configuration register
 * @param value  value to write
 */
void hal_cc2500_writeReg(char addr, char value) {
	hal_pin_out(&cc_spinCS, 0);

	hal_cc2500_wakeup();				// Wait for CCxxxx ready

	spi_write(addr);        			// Send address
	while (spi_busy())
		;

	spi_write(value);        			// Send data
	while (spi_busy())
		;

	hal_pin_out(&cc_spinCS, 1);
}

void hal_cc2500_wakeup() {
	while (hal_pin_in(&cc_spiSOMI)) {	// Wait for CCxxxx ready

		hal_pin_out(&cc_spinCS, 1);		// /CS disable
		__delay_cycles(100*FRQ_FACTOR);
		hal_pin_out(&cc_spinCS, 0);		// /CS enable

	}

}

/**
 * Writes values to multiple configuration registers, the first register being
 *  at address "addr".  First data byte is at "buffer", and both addr and
 *  buffer are incremented sequentially (within the CCxxxx and MSP430,
 *  respectively) until "count" writes have been performed.
 *
 * @param addr
 * @param buffer
 * @param count
 */
void hal_cc2500_writeBurstReg(char addr, char *buffer, char count) {
	unsigned int i;

	hal_pin_out(&cc_spinCS, 0);
	hal_cc2500_wakeup();						// Wait for CCxxxx ready

	spi_write(addr | TI_CCxxx0_WRITE_BURST);
	for (i = 0; i < count; i++) {
		spi_write(buffer[i]);                	// Send data
	}
	while (spi_busy())
		; // Wait for TX to finish
	hal_pin_out(&cc_spinCS, 1);
}

/**
 *  Reads a single configuration register at address "addr" and returns the
 *  value read.
 *
 * @param addr
 * @return
 */
char hal_cc2500_readReg(char addr) {

	char x;
	hal_pin_out(&cc_spinCS, 0);					// CS enabled
	hal_cc2500_wakeup();						// Wait for CCxxxx ready

	spi_write(addr | TI_CCxxx0_READ_SINGLE);  	// Send address
	x = spi_wr(0);                           	// Read data

	hal_pin_out(&cc_spinCS, 1);					// CS disabled
	return x;
}

/**
 *  Reads multiple configuration registers, the first register being at address
 *  "addr".  Values read are deposited sequentially starting at address
 *  "buffer", until "count" registers have been read.
 *
 * @param addr
 * @param buffer
 * @param count
 */
void hal_cc2500_readBurstReg(char addr, char *buffer, char count) {
	char i;

	hal_pin_out(&cc_spinCS, 0);					// CS enabled
	hal_cc2500_wakeup();

	spi_write(addr | TI_CCxxx0_READ_BURST); 	// Send add

	for (i = 0; i < count; i++) {
		buffer[i] = spi_wr(0);        			// Store data from last data RX
	}
	hal_pin_out(&cc_spinCS, 1);					// CS disabled

}

/**
 *  Special read function for reading status registers.  Reads status register
 *  at register "addr" and returns the value read.
 *
 * @param addr
 * @return
 */
char hal_cc2500_readStatus(char addr) {
	char x;

	hal_pin_out(&cc_spinCS, 0);					// CS enabled
	hal_cc2500_wakeup();

	spi_write(addr | TI_CCxxx0_READ_BURST);  	// Send address

	x = spi_wr(0);                           	// Read data
	hal_pin_out(&cc_spinCS, 1);					// CS disabled

	return x;
}

/**
 *   Special write function for writing to command strobe registers.  Writes
 *  to the strobe at address "addr".
 *
 * @param strobe
 */
void hal_cc2500_strobe(char strobe) {

	hal_pin_out(&cc_spinCS, 0);
	hal_cc2500_wakeup();				// Wait for CCxxxx ready

	spi_write(strobe);         			// Send strobe
	while (spi_busy())
		; // Wait for TX to finish
	hal_pin_out(&cc_spinCS, 1);

}

/**
 * 		Special function that restart the CC2500 and left it operative.
 *
 */
void hal_cc2500_powerupReset(void) {

	hal_pin_out(&cc_spinCS, 1);
	__delay_cycles(30*FRQ_FACTOR);
	hal_pin_out(&cc_spinCS, 0);
	__delay_cycles(30*FRQ_FACTOR);
	hal_pin_out(&cc_spinCS, 1);
	__delay_cycles(45*FRQ_FACTOR);

	hal_cc2500_strobe(TI_CCxxx0_SRES);
}

/**
 * 	Return the status byte of CC2500
 * @return  cc2500 status
 */
char hal_cc2500_status(void) {
	char x;

	hal_pin_out(&cc_spinCS, 0);					// CS enabled
	hal_cc2500_wakeup();

	spi_write(TI_CCxxx0_SNOP);  				// Send address
	x = spi_wr(0);                           	// Read data
	hal_pin_out(&cc_spinCS, 1);					// CS disabled

	return x;
}

