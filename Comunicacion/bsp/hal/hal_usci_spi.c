/**
 *  @file       hal_uci_spi.c
 *  @brief      Implementacion del Hal UCI en modo SPI
 *  @details
 *  @author     Laboratorio de Comunicaciones - Universidad Catolica de Cordoba
 *
 *  @author		Marcucci, Ricardo Martin - rmarku(at)gmail.com
 *  @version	1.0
 */
#include "hal_usci_spi.h"

#define UCxxCTL0   *(spiBaseAdd + 0)
#define UCxxCTL1   *(spiBaseAdd + 1)
#define UCxxBR0    *(spiBaseAdd + 2)
#define UCxxBR1    *(spiBaseAdd + 3)
#define UCxxMCTL   *(spiBaseAdd + 4)
#define UCxxSTAT   *(spiBaseAdd + 5)
#define UCxxRXBUF  *(spiBaseAdd + 6)
#define UCxxTXBUF  *(spiBaseAdd + 7)

/**
 * @brief Funcion para configurar el SPI
 * @param spiBaseAdd Direccion base de la UCI que se va a usar
 * @return
 */

uint8_t *spiBaseAdd;

//const volatile unsigned char* spiBaseAdd = &UCA0CTL0;

void spi1_setup(uint8_t *add) {
	spiBaseAdd = add;

//TODO: Ver como pasar configuracion.

	UCxxCTL0 |= UCMST + UCCKPL + UCMSB + UCSYNC;    // 3-pin, 8-bit SPI master
	UCxxCTL1 |= UCSSEL_1;                     		// ACLK
	UCxxBR0 |= 0x02;           						// UCLK/2
	UCxxBR1 = 0;
	UCxxCTL1 &= ~UCSWRST;                   	// Initialize USCI state machine

}

void spi1_start(void) {
	UCxxCTL1 &= ~UCSWRST;                   	// Initialize USCI state machine
//	UCxxCTL1 |= UCSWRST;                   	// Initialize USCI state machine
}
/**
 * @brief Funcion para mandar esperando que el buffer este libre
 * @param spiBaseAdd   Direccion base de la UCI que se va a usar
 * @param data  data to be transmited
 * @return data recibed from
 */
void spi1_write(uint8_t data) {

	while (spi1_txBufReady(spiBaseAdd));
	UCxxTXBUF = data;                        // Send data
}

/**
 * @brief Funcion para mandar esperando a que termine una transmicion anterior.
 * @param spiBaseAdd   Direccion base de la UCI que se va a usar
 * @param data  data to be transmited
 * @return data recibed from
 */
void spi1_write_wait(uint8_t data) {

	while (spi1_txBufReady(spiBaseAdd))
		;
	UCxxTXBUF = data;                        // Send data
}
/**
 * Espera a que el buffer de transmicion este vacio
 * @return 0 si esta listo, !=0 si no esta listo
 */

uint8_t spi1_txBufReady() {
	char UCxxTXIFG = UCA0TXIFG;

	if ((uint16_t) spiBaseAdd & 0x0008)
		UCxxTXIFG = UCB0TXIFG;

	return (!(IFG2 & UCxxTXIFG));
}

/**
 * Espera a que una recepcion termine
 * @return 0 si esta listo, !=0 si no esta listo
 */

uint8_t spi1_rxFinish() {
	uint8_t UCxxRXIFG = UCA0RXIFG;
	uint8_t estado;

	if ((uint16_t) spiBaseAdd & 0x0008)
		UCxxRXIFG = UCB0RXIFG;
	estado = !(IFG2 & UCxxRXIFG);
	IFG2 &= ~UCxxRXIFG;
	return (estado);
}

/**
 * Indica si hay transmiciones llevandoce a cabo.
 * @return 0 si esta listo, !=0 si no esta listo
 */

uint8_t spi1_busy() {
	return (UCxxSTAT & UCBUSY);
}

/**
 * @brief Funcion para mandar o recibir un dato
 * @param spiBaseAdd   Direccion base de la UCI que se va a usar
 * @param data  data to be transmited
 * @return data recibed from
 */

uint8_t spi1_wr(uint8_t data) {
	uint8_t t;

	while (spi1_txBufReady());
	UCxxTXBUF = data;                      // Send data
	do {
		t = spi1_busy();
	} while (t);; // Wait for TX to finish

	do {
		t = spi1_rxFinish();
	} while (t);

	; // Wait for TX to finish
	return UCxxRXBUF;
}
