#ifndef _CONFIG_H
#define _CONFIG_H


// SPI
#define MC_MOSI    PB3
#define MC_CLK     PB5

#define MCP_CS        PB0
#define MCP_CMD_PORT  PORTB

#define SPI_REG_PIN_MCP_INT  PIND
#define SPI_PIN_MCP_INT      PD2
//#define CAN_INTERRUPT


//#define F_CPU 16000000UL
#define F_MCP F_CPU


#define MEGA8

#ifdef MEGA8
#	define SPI_PORT PORTB
#	define SPI_HARDWARE
#	define SPI_DDR DDRB
#	define SPI_PIN_SCK PB5
#	define SPI_PIN_MOSI PB3
#else
#	define SPI_PORT PORTB
#	define SPI_HARDWARE
#	define SPI_DDR DDRB
#	define SPI_PIN_SCK PB7
#	define SPI_PIN_MOSI PB5
#endif

//Number of Messages in Can TX Buffer
#define TX_SIZE 10



#endif // ifndef CONFIG_H
