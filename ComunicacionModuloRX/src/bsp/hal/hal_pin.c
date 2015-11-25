/**
 *  @file       hal_pins.c
 *  @brief      Implementation of Hal PIN MSP430
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

#include "hal_pin.h"

#define PxIN	0
#define PxOUT	1
#define PxDIR	2
#define PxIFG	3
#define PxIES	4
#define PxIE	5
#define PxSEL	6
#define PxREN	7

/**
 * @brief Array en rom de todos los punteros a los puertos de cada pin segun el puerto.
 */
volatile unsigned char* const pinPort[][10] = {

#if defined(__MSP430_HAS_PORT1__) || defined(__MSP430_HAS_PORT1_R__)
	{	&P1IN, &P1OUT, &P1DIR, &P1IFG, &P1IES, &P1IE, &P1SEL
#ifdef __MSP430_HAS_PORT1_R__
		, &P1REN
#endif
	}
#endif

#if defined(__MSP430_HAS_PORT2__) || defined(__MSP430_HAS_PORT2_R__)
	, {	&P2IN, &P2OUT, &P2DIR, &P2IFG, &P2IES, &P2IE, &P2SEL
#ifdef __MSP430_HAS_PORT2_R__
		, &P2REN
#endif
	}
#endif

#if defined(__MSP430_HAS_PORT3__) || defined(__MSP430_HAS_PORT3_R__)
	, {	&P3IN, &P3OUT, &P3DIR, 0, 0, 0, &P3SEL
#ifdef __MSP430_HAS_PORT3_R__
		, &P3REN
#endif
	}
#endif

#if defined(__MSP430_HAS_PORT4__) || defined(__MSP430_HAS_PORT4_R__)
	, {	&P4IN, &P4OUT, &P4DIR, 0, 0, 0, &P4SEL
#ifdef __MSP430_HAS_PORT4_R__
		, &P4REN
#endif
	}
#endif

#if defined(__MSP430_HAS_PORT5__) || defined(__MSP430_HAS_PORT5_R__)
	, {	&P5IN, &P5OUT, &P5DIR, 0, 0, 0, &P5SEL
#ifdef __MSP430_HAS_PORT5_R__
		, &P5REN
#endif
	}
#endif

#if defined(__MSP430_HAS_PORT6__) || defined(__MSP430_HAS_PORT6_R__)
	, {	&P6IN, &P6OUT, &P6DIR, 0, 0, 0, &P6SEL
#ifdef __MSP430_HAS_PORT6_R__
		, &P6REN
#endif
	}
#endif

#if defined(__MSP430_HAS_PORT7__) || defined(__MSP430_HAS_PORT7_R__)
	, {	&P7IN, &P7OUT, &P7DIR, 0, 0, 0, &P7SEL
#ifdef __MSP430_HAS_PORT7_R__
		, &P7REN
#endif
	}
#endif

#if defined(__MSP430_HAS_PORT8__) || defined(__MSP430_HAS_PORT8_R__)
	, {	&P8IN, &P8OUT, &P8DIR, 0, 0, 0, &P8SEL
#ifdef __MSP430_HAS_PORT8_R__
		, &P8REN
#endif
	}
#endif

#if defined(__MSP430_HAS_PORT9__) || defined(__MSP430_HAS_PORT9_R__)
	, {	&P9IN, &P9OUT, &P9DIR, 0, 0, 0, &P9SEL
#ifdef __MSP430_HAS_PORT9_R__
		, &P9REN
#endif
	}
#endif

#if defined(__MSP430_HAS_PORT10__) || defined(__MSP430_HAS_PORT10_R__)
	, {	&P10IN, &P10OUT, &P10DIR, 0, 0, 0, &P10SEL
#ifdef __MSP430_HAS_PORT10_R__
		, &P10REN
#endif
	}
#endif
};

const void* hal_pin_init(const pinConfig* p) {
	switch (p->type) {
	case HAL_PIN_DIG_OUT:
		hal_pin_out(p, p->initialValue);
		break;
	default:
		break;
	}
	hal_pin_config(p, p->type);
	return (p);
}

void hal_pin_config(const pinConfig* p, type_pin type) {
	switch (type) {
	case HAL_PIN_DIG_IN:
		*(pinPort[p->port][PxDIR]) &= ~(p->mask);
		*(pinPort[p->port][PxSEL]) &= ~(p->mask);
		break;

	case HAL_PIN_DIG_IN_R:
		*(pinPort[p->port][PxDIR]) &= ~(p->mask);
		*(pinPort[p->port][PxSEL]) &= ~(p->mask);
		*(pinPort[p->port][PxREN]) |= (p->mask);
		if (p->initialValue)
			*(pinPort[p->port][PxOUT]) |= (p->mask);
		else
			*(pinPort[p->port][PxOUT]) &= ~(p->mask);
		break;

	case HAL_PIN_DIG_OUT:
		*(pinPort[p->port][PxDIR]) |= (p->mask);
		*(pinPort[p->port][PxSEL]) &= ~(p->mask);
		break;

	case HAL_PIN_INT_LOHI:
		*(pinPort[p->port][PxDIR]) &= ~(p->mask);
		*(pinPort[p->port][PxSEL]) &= ~(p->mask);
		*(pinPort[p->port][PxIES]) &= ~(p->mask);
		*(pinPort[p->port][PxIFG]) &= ~(p->mask);
		*(pinPort[p->port][PxIE]) |= (p->mask);
		break;

	case HAL_PIN_INT_HILO:
		*(pinPort[p->port][PxDIR]) &= ~(p->mask);
		*(pinPort[p->port][PxSEL]) &= ~(p->mask);
		*(pinPort[p->port][PxIES]) |= (p->mask);
		*(pinPort[p->port][PxIFG]) &= ~(p->mask);
		*(pinPort[p->port][PxIE]) |= (p->mask);
		break;

	case HAL_PIN_ANA_IN:
		*(pinPort[p->port][PxDIR]) &= ~(p->mask);
		break;

	case HAL_PIN_ANA_OUT:
		break;

	case HAL_PIN_SEC_FUNC:
		*(pinPort[p->port][PxSEL]) |= (p->mask);
		*(pinPort[p->port][PxDIR]) &= ~(p->mask);
		break;
	case HAL_PIN_SEC_FUNC_OUT:
		*(pinPort[p->port][PxSEL]) |= (p->mask);
		*(pinPort[p->port][PxDIR]) |= (p->mask);
		break;
	default:
		break;
	}
}

uint16_t hal_pin_in(const pinConfig* p) {

	if ((*(pinPort[p->port][PxIN]) & (p->mask)) != 0)
		return (1);
	else
		return (0);
}

void hal_pin_out(const pinConfig* p, uint16_t data) {

	switch (p->type) {
	case HAL_PIN_DIG_OUT:

		if (data) {
			*(pinPort[p->port][PxOUT]) |= (p->mask);
		} else {
			*(pinPort[p->port][PxOUT]) &= ~(p->mask);
		}
		break;

	default:
		break;
	}
}

void hal_pin_toggle(const pinConfig* p) {
	switch (p->type) {
	case HAL_PIN_DIG_OUT:
		*(pinPort[p->port][PxOUT]) ^= p->mask;
		break;
	default:
		break;
	}
}

uint8_t hal_pin_intGetFlag(const pinConfig* p) {

	if ((*(pinPort[p->port][PxIFG]) & p->mask) != 0)
		return 1;
	else
		return 0;
}

void hal_pin_intClearFlag(const pinConfig* p) {
	P2IFG&= ~0x01;
	*(pinPort[p->port][PxIFG]) &= ~(p->mask);
}

void hal_pin_intEnable(const pinConfig* p) {
	*(pinPort[p->port][PxIE]) |= p->mask;
}

void hal_pin_intDisable(const pinConfig* p) {
	*(pinPort[p->port][PxIE]) &= ~(p->mask);
}
