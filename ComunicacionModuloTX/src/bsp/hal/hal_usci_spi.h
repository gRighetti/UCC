/**
 *  @file       hal_uci_spi.h
 *  @brief      Constant, structs and definitions of Hal UCI en modo SPI
 *  @details
 *  @author     Laboratorio de Comunicaciones - Universidad Catolica de Cordoba
 *
 *  @author		Marcucci, Ricardo Martin - rmarku(at)gmail.com
 *  @version	1.0
 */
#ifndef HAL_UCI_SPI_H_
#define HAL_UCI_SPI_H_

#include "../system.h"

// Definir solo la base del Puerto SPI.

#define SPI_PORT		1




/**
 * @brief Funcion para configurar el SPI
 * @param spiBaseAdd Direccion base de la UCI que se va a usar
 * @return
 */
void spi1_setup(uint8_t *add) ;


void spi1_start(void);

/**
 * @brief Funcion para mandar esperando a que termine una transmicion anterior.
 * @param spiBaseAdd   Direccion base de la UCI que se va a usar
 * @param data  data to be transmited
 * @return data recibed from
 */
void spi1_write(uint8_t data);
/**
 * @brief Funcion para mandar o recibir un dato
 * @param spiBaseAdd   Direccion base de la UCI que se va a usar
 * @param data  data to be transmited
 * @return data recibed from
 */

uint8_t spi1_wr( uint8_t data);
/**
 * Indica si hay transmiciones llevandoce a cabo.
 * @return 0 si esta listo, !=0 si no esta listo
 */

uint8_t spi1_busy();

/**
 * Espera a que una recepcion termine
 * @return 0 si esta listo, !=0 si no esta listo
 */

uint8_t spi1_rxFinish();

/**
 * Espera a que el buffer de transmicion este vacio
 * @return 0 si esta listo, !=0 si no esta listo
 */

uint8_t spi1_txBufReady();

/**
 * Selecciona el modulo SPI a usar
 * @param spiAdd Direccion del puerto a usar
 */

void spi1_setAdd(uint8_t* spiAdd);

#endif /* HAL_UCI_SPI_H_ */
