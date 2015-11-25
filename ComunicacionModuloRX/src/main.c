#include "bsp/bsp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bsp/system.h"

#define MY_ADDRESS 2
#define TEMPO_TX	131500
#define TEMPO_RX	520

#define TIEMPO_CODIGO_RX			0
#define TIEMPO_CODIGO_TX			0
#define TIEMPO_TRANSMICION			637
#define TIEMPO_ACTUALIZACION_TAR	0
#define RETRANSMISION				5

const void* LedVerde;
const void* LedRojo;
const void* Switch1;

struct S_Calibration {
	uint32_t timestamp;
	uint8_t comand;

};
union U_Calibration {

	struct S_Calibration campos;
	char buffer[5];
};
union U_Calibration rf_rxCalibration, rf_txCalibration;

//Timer

uint16_t tar_inicial, tar_final, tar_envio;
uint16_t tar_segundo = 0x8000;
uint8_t flagdespertar = 0;

uint8_t cont_rebase_timer;

uint8_t i;
char estado = 0;
int rx_new_data;

//Constantes RF
uint8_t net_myAddr = MY_ADDRESS;
char uartRxBuf[5];
uint8_t flagCalibration = 0;
uint8_t EstadoCalibration = 0;
uint8_t tiem_envio = 0;

//variables calibracion y sincronismo
uint32_t timestamp;
uint32_t timestamp_inicial;
uint32_t timestamp_final;
uint32_t timestamprx;
uint16_t rebasesRX;
int32_t diferencia[3];
int16_t correccion = 0;
int32_t ciclo_correccion;
int32_t proxima_correccion;
uint8_t flag_calibracion_automatica = 0;
uint16_t timestamp_TAR;
char txBuffer[20] = "Holaaaaa";
int flagRecibido = 0;
char length = 20;
char txBufferOk[20] = "ok";
//char rxBuffer[20] = "nada";
uint8_t rxBuffer;
char rssi;
char lqi;
int flagEnviado = 1;
uint16_t checkSum;
char bufferSerie[18];
char rxPacket[17];
char rxBufferRecibi[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
char rx_UartBuf[5] = "holaa";
uint8_t malEnviado = 0;

//unsigned char buf_uart[LONG_DATA_FIELD + 5];
/*
 * main.c
 */
#define RSSI_OFFSET 69
void Calibration(uint8_t estado);
void procesar_datos(void);

int main(void) {
	//char str_tx[40];

	bsp_Init();
	RF_PwrUpRx();                           // Enciendo Radio

	while (1) {
		/*
		 //.................................................... Para mandar la trama del puerto serie
		 if (bspFlags.enviarDato == 1) {
		 bspFlags.enviarDato = 0;
		 *//*
		 rxBuffer = 1;
		 for (i = 0; i < 13; i++) {
		 checkSum += (uint8_t) bufferSerie[i];
		 }
		 rxPacket[0] = rxBuffer;
		 for (i = 0; i < 13; i++) {
		 rxPacket[i + 1] = bufferSerie[i];
		 }
		 rxPacket[15] = checkSum;
		 */
		/*
		 for (i = 0; i <= RETRANSMISION; i++) {
		 RF_SendPacket(1, bufferSerie, 20);
		 }
		 bsp_msDelay(100);
		 led_Toggle(LedVerde);
		 }*/

		//....................................................
		if (RF_rxDataReady()) {
			RF_getRxPacket(&rxBufferRecibi[0], 16);
			procesar_datos();
		}
		/*
		 if (uart_rxData()) {
		 uart_rxGetPack();
		 }
		 */
		//----------------Puerto Serie-------------------
		if (bspFlags.enviarSerie) {
			//Led_On(LedVerde);
			bspFlags.enviarSerie = 0;

			//serie_SendString(rx_UartBuf);
			serie_SendString(bufferSerie);
			//serie_SendString(rxBufferRecibi);

			led_On(LedRojo);
			bsp_msDelay(100);
			led_Off(LedRojo);
			//led_Off(LedVerde);
		}

		if (RF_rxDataReady()) {
			//led_On(LedRojo);

			led_On(LedVerde);
			RF_getRxPacket(&rxBufferRecibi[0], 18);
			bsp_msDelay(100);
			led_Off(LedVerde);
		}

		if (bspFlags.enviarDato) {
			bspFlags.enviarDato = 0;
			RF_getRxPacket(&rxBufferRecibi[0], 18);
			led_On(LedRojo);
			bsp_msDelay(100);
			led_Off(LedRojo);
		}
	}
}

void app_TimerISR_1ms(void) {
	static uint16_t contador = 0;

	if (contador == 500) {
		//tiem_envio = 1;
		contador = 0;
	} else {
		contador++;
	}
}

void app_TimerISR_1s(void) {
	static uint16_t cont = 0;

//.................................................... Tiempos de calibracion
	cont++;

//flag_calibracion_automatica++;

//....................................................

//	led_Toggle(LedVerde);

}

/*
 for (i = 0; i <= RETRANSMISION; i++) {
 rf_txCalibration.campos.timestamp = TimeStamp();

 RF_SendPacket(1, &rf_txCalibration.buffer[0], 5);
 */

void app_RxPacketISR(void) {

}

void procesar_uart(char dato) {
//Guarda los datos en el Buffer
	unsigned int i;
	for (i = 0; i < 4; i++)
		uartRxBuf[i] = uartRxBuf[i + 1];
	uartRxBuf[4] = dato;
}

void procesar_datos(void) {

	if (rxBufferRecibi[0] != 1) {
		malEnviado = 1;
	}
	for (i = 1; i < 15; i++) {
		checkSum += rxBufferRecibi[i];
		bufferSerie[i - 1] = rxBufferRecibi[i];
	}
	if (checkSum == rxBufferRecibi[15]) {
		bspFlags.enviarSerie = 1;
	} else
		malEnviado = 1;

}
