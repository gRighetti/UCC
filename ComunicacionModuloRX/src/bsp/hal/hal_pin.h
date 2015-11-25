/**
 *  @file       hal_pins.h
 *  @brief      Constant, structs and definitions of Hal PIN
 *  @details
 *  @author     Laboratorio de Comunicaciones - Universidad Catolica de Cordoba
 *
 *  @author		Raúlito
 *  @author		Marcucci, Ricardo Martin - rmarku(at)gmail.com
 *  @version	1.0
 *  @date       Agosto 27, 2013
 *  @pre        First initialize the system.
 *  @warning    Improper use can crash your application
 */

#ifndef HAL_PINS_H
#define	HAL_PINS_H

#include "../system.h"

/**
 *  @brief   Opciones de las configuracion del tipo de pin.
 */
typedef enum {
	HAL_PIN_DIG_IN,
	HAL_PIN_DIG_IN_R,
	HAL_PIN_DIG_OUT,
	HAL_PIN_INT_HILO,
	HAL_PIN_INT_LOHI,
	HAL_PIN_ANA_IN,
	HAL_PIN_ANA_OUT,
	HAL_PIN_SEC_FUNC,
	HAL_PIN_SEC_FUNC_OUT
} type_pin;

/**
 *  @brief   Opciones de las configuracion del tipo de pin.
 */
typedef enum {
	HAL_PORT1, HAL_PORT2, HAL_PORT3, HAL_PORT4, HAL_PORT5, HAL_PORT6, HAL_PORT7, HAL_PORT8, HAL_PORT9, HAL_PORT10
} select_port;

/**
 *  @brief   Datos necesarios para configurar un pin
 */
struct _pinConfig {
		select_port port; /**< Referencia del puerto al que pertenece el pin */
		uint16_t pin; /**< Pin del puerto que se desea acceder */
		type_pin type; /**< Configura el tipo de pin */
		uint16_t initialValue; /**< Valor inicial */
		uint16_t mask; /**< Mascara */
};

/** @typedef        pinConfig
 *  @brief          Configura el pin
 *  @port           Referencia del puerto al que pertenece el pin
 *  @pin            Pin del puerto que se desea acceder
 *  @direction      Configura si es entrada o salida
 *  @initialValue   Valor inicial
 */
typedef struct _pinConfig pinConfig;

/**
 *  @brief       Inicializa el pin del MCU , configurando el tipo de pin que es y
 *               el estado logico que corresponda
 *  @param       [in]   p     Puntero del pin a configurar
 *  @return      El puntero de vinculacion para ultilizar desde la aplicacion
 */

const void * hal_pin_init(const pinConfig* p);

/**
 *  @brief       Configura el pin del MCU
 *  @param  [in]   p     Puntero del pin a configurar
 *  @see       pinConfig
 */

void hal_pin_config(const pinConfig* p, type_pin type);

/**
 *  @brief      Retorna el estado logico de un pin especifico
 *  @param  [in]   p     Puntero del pin al que se desea leer el estado logico.
 *  @return     Retorna "0" en caso de diferente de cero sera evaluado como un
 *              "1" logico.
 */

uint16_t hal_pin_in(const pinConfig* p);

/**
 *  @brief   Asigna un estado especifico a un pin especifico.
 *  @param  [in]   p     Puntero del recurso de hardware que se quiere asignar.
 *  @param  [in]  data   Valor al que quiere asignar al pin.
 *  @note    Utiliza la variable "data" como bool, es decir cualquier valor
 *           diferente de cero sera evaluado como un "1" logico.
 */
void hal_pin_out(const pinConfig* p, uint16_t data);

/**
 *  @brief   Permite invertir el estado de un pin especifico.
 *  @param  [in]   p     Puntero del recurso de hardware que se quiere invertir
 *                       el estado.
 */
void hal_pin_toggle(const pinConfig* p);

/**
 *  @brief  Devuelve el estado de la Flag de Interrupcion de un pin especiico
 *  @param  [in]   p     Puntero del recurso de hardware que se quiere invertir
 *                       el estado.
 */
uint8_t hal_pin_intGetFlag(const pinConfig* p);

/**
 *  @brief   Limpia la Flag de Interrupcion de un pin especiico
 *  @param  [in]   p     Puntero del recurso de hardware que se quiere invertir
 *                       el estado.
 */
void hal_pin_intClearFlag(const pinConfig* p);

/**
 *  @brief   Permite habilitar la Interrupcion de un pin especifico.
 *  @param  [in]   p     Puntero del recurso de hardware que se quiere invertir
 *                       el estado.
 */
void hal_pin_intEnable(const pinConfig* p);

/**
 *  @brief   Permite deshabilitar la Interrupcion de un pin especifico.
 *  @param  [in]   p     Puntero del recurso de hardware que se quiere invertir
 *                       el estado.
 */
void hal_pin_intDisable(const pinConfig* p);

#endif	/* HAL_PINS_H */
