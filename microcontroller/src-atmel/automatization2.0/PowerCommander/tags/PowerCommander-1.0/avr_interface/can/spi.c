#include <avr/io.h>

#include "spi.h"
#include "../config.h"

extern void spi_init()
{

	/* configure MOSI, SCK, lines as outputs */
	DDRB |= _BV(MC_MOSI) | _BV(MC_CLK); // mosi, sck output

	SPCR = _BV(MSTR) | _BV(SPE); // Master Mode,  Enable SPI
	SPSR = _BV(SPI2X); // Double speed on
}



extern uint8_t spi_send(uint8_t data)
{
	SPDR = data;
	while (!(SPSR & _BV(SPIF)));
	return SPDR;
}
