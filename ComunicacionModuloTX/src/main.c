#include "bsp/bsp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bsp/system.h"
#include <time.h>

#define MY_ADDRESS 2
#define TEMPO_TX	131500
#define TEMPO_RX	520
/*
 #define TIEMPO_CODIGO_RX			0
 #define TIEMPO_CODIGO_TX			0
 #define TIEMPO_TRANSMICION			637
 #define TIEMPO_ACTUALIZACION_TAR	0
 */

#define RETRANSMISION				5

const void* LedVerde;
const void* LedRojo;
const void* Switch1;
/*
 struct S_Calibration {
 uint32_t timestamp;
 uint8_t comand;

 };
 union U_Calibration {

 struct S_Calibration campos;
 char buffer[5];
 };
 union U_Calibration rf_rxCalibration, rf_txCalibration;

 union trama_rf{
 uint8_t counter;
 char buffer[15];
 uint16_t check;
 }trama;
 */

//Timer
/*
 uint16_t tar_inicial, tar_final, tar_envio;
 uint16_t tar_segundo = 0x8000;
 uint8_t flagdespertar = 0;

 uint8_t cont_rebase_timer;
 */
uint8_t i;
char estado = 0;
int rx_new_data;

//Constantes RF
uint8_t net_myAddr = MY_ADDRESS;
/*
 char uartRxBuf[5];
 uint8_t flagCalibration = 0;
 uint8_t EstadoCalibration = 0;
 uint8_t tiem_envio = 0;
 */
//variables calibracion y sincronismo
/*uint32_t timestamp;
 uint32_t timestamp_inicial;
 uint32_t timestamp_final;
 uint32_t timestamprx;*/
/*
 uint16_t rebasesRX;
 int32_t diferencia[3];
 int16_t correccion = 0;
 int32_t ciclo_correccion;
 int32_t proxima_correccion;
 uint8_t flag_calibracion_automatica = 0;
 uint16_t timestamp_TAR;
 */
char txBuffer[20] = "Holaaaaa";
int flagRecibido = 0;
char length = 20;
char txBufferOk[20] = "ok";
//char rxBuffer[20] = "nada";
uint8_t rxBuffer;
char rssi;
char lqi;
int flagEnviado = 1;
uint16_t checkSum = 0;
char bufferSerie[20] = "HOLAAAaaaaAFD";
char rxPacket[18] = "sdfhsdfhhsdfhh";
char rxBufferRecibi[15];
char rxBufferTiempo[4];
char rx_UartBuf[5] = "holaa";
uint8_t contador = 0, size, procesar=0, procesarTiempo=0;
char datoRx;
char bufferPrueba[14] = { 0x14, 0x40, 0x5F, 0xDC, 0x06, 0x5A, 0x05, 0x0E, 0x01,
		0x14, 0x6F, 0x12, 0x18, 0x00 };
//unsigned char buf_uart[LONG_DATA_FIELD + 5];
/*
 * main.c
 */
#define RSSI_OFFSET 69
//void Calibration(uint8_t estado);
uint8_t procesar_uart(void);
uint8_t procesar_tiempo(void);

int main(void) {
	//char str_tx[40];

	bsp_Init();
	RF_PwrUpRx();                           // Enciendo Radio

	while (1) {

		//.................................................... Para mandar la trama del puerto serie
		if (bspFlags.enviarDato == 1) {
			led_Toggle(LedRojo);
			bspFlags.enviarDato = 0;
			/*rxBuffer = 1;
			 for (i = 0; i < 13; i++) {
			 checkSum += (uint8_t) bufferSerie[i];
			 }
			 rxPacket[0] = rxBuffer;
			 for (i = 0; i < 13; i++) {
			 rxPacket[i + 1] = bufferSerie[i];
			 }
			 rxPacket[15] = checkSum;
			 */

			for (i = 0; i <= RETRANSMISION; i++) {
				//RF_SendPacket(1, bufferSerie, 20);
				RF_SendPacket(1, &rxPacket[0], size);
				//RF_SendPacket(1, &trama, 18);
			}
			bsp_msDelay(50);
			led_Toggle(LedRojo);
		}
		if (procesar == 1 && bspFlags.enviarDato == 0) {
			procesar = 0;
			size = procesar_uart();
		}

		if (procesarTiempo == 1 && bspFlags.enviarDato == 0) {
			procesarTiempo = 0;
			size = procesar_tiempo();
		}

		if (uart_rxData() == 1) {
			for(i=0; i<15; i++){
				rxBufferRecibi[i]=getDato(i);
			}
			procesar=1;
		}
		if (uart_rxData() == 2) {
			for(i=0; i<4; i++)
				rxBufferTiempo[i] = getDatoTiempo(i);
			procesarTiempo=1;
		}
		//....................................................
		/*
		 if (RF_rxDataReady()) {
		 RF_getRxPacket(&rf_rxCalibration.buffer[0], 10);

		 }

		 if (uart_rxData()) {
		 uart_rxGetPack();
		 }
		 */
		/*
		 //----------------Puerto Serie-------------------
		 if (bspFlags.enviarSerie) {
		 //Led_On(LedVerde);
		 bspFlags.enviarSerie = 0;

		 serie_SendString(&rxBufferRecibi);
		 led_On(LedRojo);

		 bsp_msDelay(1000);
		 led_Off(LedRojo);
		 //led_Off(LedVerde);
		 }
		 */
		/*	if (RF_rxDataReady()) {
		 //led_On(LedRojo);

		 led_On(LedVerde);
		 RF_getRxPacket(&rxBufferRecibi[0], 20);
		 bsp_msDelay(1000);
		 led_Off(LedVerde);
		 }*/

		/*	if(bspFlags.enviarDato){
		 bspFlags.enviarDato=0;
		 bsp_msDelay(1000);
		 led_Toggle(LedVerde);
		 }*/
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

uint8_t procesar_uart() {
//Guarda los datos en el Buffer
	uint8_t i, cantidad=18, cantidadBytes=14;
	checkSum = 0;
	rxBuffer = 0;
	for (i = 0; i < 15; i++) {
		//checkSum += (uint8_t) bufferSerie[i];
		checkSum += rxBufferRecibi[i];
		//checkSum += bufferPrueba[i];
	}
	rxPacket[0] = rxBuffer;
	rxPacket[1] = cantidadBytes;
	for (i = 0; i < 15; i++) {
		rxPacket[i + 2] = rxBufferRecibi[i];
		//rxPacket[i + 1] = bufferPrueba[i];
	}
	rxPacket[17] = checkSum;
	bspFlags.enviarDato = 1;
	return cantidad;
	/*
	 for (i = 0; i < 15; i++)
	 uartRxBuf[i] = uartRxBuf[i + 1];
	 uartRxBuf[4] = dato;*/
}

uint8_t procesar_tiempo() {
	uint8_t i, cantidadBytes, cantidad = 7;
	 checkSum = 0;
	 rxBuffer = 1;
	 for (i = 0; i < 15; i++) {
	 //checkSum += (uint8_t) bufferSerie[i];
	 //checkSum += rxBufferRecibi[i];
	 checkSum += bufferPrueba[i];
	 }
	 rxPacket[0] = rxBuffer;
	 rxPacket[1] = cantidadBytes;
	 for (i = 0; i < 4; i++) {
		 rxPacket[i + 2] = rxBufferTiempo[i];
	 //rxPacket[i + 1] = bufferPrueba[i];
	 }
	 rxPacket[6] = checkSum;
	 bspFlags.enviarDato = 1;
	 /*
	 for (i = 0; i < 15; i++)
	 uartRxBuf[i] = uartRxBuf[i + 1];
	 uartRxBuf[4] = dato;*/
	return cantidad;
}
