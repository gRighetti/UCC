#ifndef BSP_H_
#define BSP_H_

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>


extern const void* LedVerde;
extern const void* LedRojo;
extern const void* Switch1;

///////Estructuras Comunicación
#define struct_size 5
/*
 * los componentes non_used no se utilizan y estan para
 * igualar los tamaños de las diferentes estructuras en la union
 */
typedef struct {
	uint16_t address;
	uint8_t command;
	unsigned char nodotype :2;
	unsigned char checksum :6;
	uint8_t non_used;
} config;

typedef struct {
	uint16_t address;
	uint8_t command;
	uint8_t chesum;
	uint8_t non_used;
} command;

typedef struct {
	uint16_t address;
	uint8_t battery_level;
	unsigned char nodotype :2;
	uint8_t config_type;
	unsigned char checksum :6;
} state;

union {
	command command_struct;
	state state_struct;
	config config_struct;
	uint8_t buffer[struct_size];
} u_communications;

// variables y banderas del timer



struct str_bspFlags{
		 uint8_t   rf_rxDataReady			:1;
volatile uint8_t	timer_Rebase			:1;
		 uint8_t 	calibracion				:1;
		 uint8_t 	correccion				:1;
		 uint8_t	contro_serie			:1;
		 uint8_t	recibiUart				:1;
		 uint8_t    enviarDato				:1;
		 uint8_t    enviarSerie				:1;
}bspFlags;




extern void procesar_uart(char i );

// ----------------------- BSP Services ---------------------------
void bsp_Init(void);
//TODO: borrar si no se usan.
//void bsp_msDelay(uint16_t ms);
//int bsp_GetSemilla();

// ----------------------- Led Services ---------------------------
void led_On(const void* l);
void led_Off(const void* l);
void led_Toggle(const void* l);

uint8_t sw_state(const void* s);
uint16_t get_tar(void);
void escribir_TimeStamp(uint16_t tar,uint16_t contador_rebases);
uint32_t TimeStamp(void);

char RF_ReceivePacket(char *addr, char *rxBuffer, char *length, char *rssi, char *lqi);
char RF_SendPacket(char addr, char *txBuffer, char size);
void RF_PwrUpRx(void);
void RF_sleep(void);
uint8_t RF_rxDataReady(void);
void RF_getRxPacket(char *buffer, uint8_t size);

uint8_t uart_rxData(void);

unsigned int TensionBateria(void);



//void sleep();
//void wakeup();
void Timer_Habilitar(void);
void Timer_Desabilitar(void);

// UART
void serie_writeString(unsigned char * buf, int len);
void serial_writeNumber(uint32_t Num);
int serie_cantRX();
int serie_read(unsigned char * data, int numBytesToRead);
void serie_SendString( char * buf);

int bsp_GetSemilla();
void bsp_msDelay(uint16_t ms) ;

#endif
