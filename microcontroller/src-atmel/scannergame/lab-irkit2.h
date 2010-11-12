//      lab-irkit.h
//      
//      Authors: Hans-Gert Dahmen  <sexyludernatascha@gmail.com>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


/*
 * IR codes are stored in an array of on/off pulse lengths.
 * As transmissions must always start with a one and consist
 * of alternating ones and zeroes, every even index in the
 * array will be a one-pulse and every odd array index
 * will be a zero-pulse.
 */

#ifndef _H_LAB_IRKIT
#define _H_LAB_IRKIT

#include <avr/io.h>

//one tick is 16 µS long
//#define IR_TICK_US 16

#ifndef F_CPU
 #error F_CPU not defined
#else
 //standart IR frequencies, define your own here
 #define IR_FREQ30K (uint16_t)(F_CPU/30000UL)
 #define IR_FREQ33K (uint16_t)(F_CPU/33000UL)
 #define IR_FREQ36K (uint16_t)(F_CPU/36000UL)
 #define IR_FREQ38K (uint16_t)(F_CPU/38000UL)
 #define IR_FREQ40K (uint16_t)(F_CPU/40000UL)
 #define IR_FREQ56K (uint16_t)(F_CPU/56000UL)
 #define IR_FREQ455K (uint16_t)(F_CPU/455000UL)
#endif

//define output PORT
#define IRPORT PORTD
#define IRDDR DDRD
#define IRUSEDPORTS 0x2 

//define how long a carrier pulse last 0..1
//select 0.5 for normal LED mode or
//less values if you overcurrent the IR LEDs 
#define IR_pulse_width 0.1f

#define IR_PhilipsRC5_Carrier IR_FREQ36K
#define IR_PhilipsRC5_pulselength 889
#define IR_PhilipsRC5_oneCode 0b10
#define IR_PhilipsRC5_oneCodelength 2
#define IR_PhilipsRC5_zeroCode 0b01
#define IR_PhilipsRC5_zeroCodelength 2
#define IR_PhilipsRC5_header 0
#define IR_PhilipsRC5_headerlength 0

#define IR_PhilipsRC6_Carrier IR_FREQ36K
#define IR_PhilipsRC6_pulselength 444
#define IR_PhilipsRC6_oneCode 0b10
#define IR_PhilipsRC6_oneCodelength 2
#define IR_PhilipsRC6_zeroCode 0b01
#define IR_PhilipsRC6_zeroCodelength 2
#define IR_PhilipsRC6_header 0
#define IR_PhilipsRC6_headerlength 0

#define IR_SIRC_Carrier IR_FREQ40K
#define IR_SIRC_pulselength 600
#define IR_SIRC_oneCode 0b100
#define IR_SIRC_oneCodelength 3
#define IR_SIRC_zeroCode 0b10
#define IR_SIRC_zeroCodelength 2
#define IR_SIRC_header 0b11110
#define IR_SIRC_headerlength 5

#define IR_Sharp_Carrier IR_FREQ38K
#define IR_Sharp_pulselength 320
#define IR_Sharp_oneCode 0b100000
#define IR_Sharp_oneCodelength 6
#define IR_Sharp_zeroCode 0b100
#define IR_Sharp_zeroCodelength 3
#define IR_Sharp_header 0
#define IR_Sharp_headerlength 0

#define IR_NokiaNRC17_Carrier IR_FREQ38K
#define IR_NokiaNRC17_pulselength 500
#define IR_NokiaNRC17_oneCode 0b10
#define IR_NokiaNRC17_oneCodelength 2
#define IR_NokiaNRC17_zeroCode 0b01
#define IR_NokiaNRC17_zeroCodelength 2
#define IR_NokiaNRC17_header 0b100000
#define IR_NokiaNRC17_headerlength 6

#define IR_NEC_Carrier IR_FREQ38K
#define IR_NEC_pulselength 560
#define IR_NEC_oneCode 0b1000
#define IR_NEC_oneCodelength 4
#define IR_NEC_zeroCode 0b10
#define IR_NEC_zeroCodelength 2
#define IR_NEC_header 0b111111111111111100000000
#define IR_NEC_headerlength 24

#define IR_JVC_Carrier IR_FREQ38K
#define IR_JVC_pulselength 526
#define IR_JVC_oneCode 0b1000
#define IR_JVC_oneCodelength 4
#define IR_JVC_zeroCode 0b10
#define IR_JVC_zeroCodelength 2
#define IR_JVC_header 0b111111111111111100000000
#define IR_JVC_headerlength 24


//teufel signal definitions
//see datasheet of PT2248 chip
//all calculations are done in µS
// a is the base time unit
// a = (1/fOSC) * 192 -> fOSC typically is 455KHz
//#define PT2248_A 431 //431 fits best, empirically
// bit 0 = a on, 3*a off
//#define PT_OFF (PT2248_A / IR_TICK_US), ((3*PT2248_A) / IR_TICK_US)
// bit 1 = 3*a on, a off
//#define PT_ON ((3*PT2248_A) / IR_TICK_US), (PT2248_A / IR_TICK_US)


// Extended NEC Protocol
// Pulse distance encoding
// one additional bit for distance

// AGC Burst 9ms + 4,5ms pause
//#define PNEC_AGC_ON  (9000 / IR_TICK_US)
//#define PNEC_AGC_OFF (4500 / IR_TICK_US)
//#define PNEC_AGC_BURST (PNEC_AGC_ON), (PNEC_AGC_OFF)

// bit 0 560µs on + 560µs off
//#define PNEC_OFF (560 / IR_TICK_US), (560 / IR_TICK_US)

// bit 1 560µs on + 1,69ms off
//#define PNEC_ON (560 / IR_TICK_US), (1690 / IR_TICK_US)

//macro for generating  extended nec encodings
//x is the destination array, y is the input code, z is the bit count
//#define IR_GEN_NECEXT(x, y, z) (ir_genCode((uint16_t *)(x+4), PNEC_ON, PNEC_OFF, y, z) + 4); x[0] = PNEC_AGC_ON; x[1] = PNEC_AGC_OFF


// stop TIMER1, disable IRPORT
#define FREQGEN_OFF() TCCR1B = 0; IRPORT&=IRDDR

// start TIMER1, reset timer count
#define FREQGEN_ON() TCNT1 = 0; TCCR1B = _BV(WGM12)|_BV(CS10) //counter is running now

//function prototypes
uint8_t ir_init(uint16_t freq, uint16_t pulselength);
void ir_disable(void);
uint8_t ir_genCode(uint8_t headerlength, uint8_t channel, uint8_t oneCode, uint8_t oneCode_length, uint8_t zeroCode,uint8_t zeroCode_length, uint32_t bitCode, uint8_t codeLen);
uint8_t ir_genHeader(uint8_t channel, uint32_t headerCode, uint8_t headerLen);
uint8_t ir_freqInit(uint16_t freq, uint16_t pulselength);
void ir_sendCode(uint8_t codeLen);

//work in progress
/*typedef struct {
uint16_t oneOntime;
uint16_t oneOfftime;
uint16_t zeroOntime;
uint16_t zeroOfftime;

} ir_proto;*/


//function to generate extended nec encodings
//destCode is the destination array
//bitCode is the input code
//codeLen is the bit count
/*
static inline uint8_t ir_genENEC(uint16_t *destCode, uint32_t bitCode, uint8_t codeLen)
{
	//create nec preamble
	destCode[0] = PNEC_AGC_ON;
	destCode[1] = PNEC_AGC_OFF;

	//add a short trailing on pulse
	destCode[codeLen * 2 + 2] = (560 / IR_TICK_US);

	//generate the code, add 4 to the length (for preamble and footer) and return
	return ir_genCode(&destCode[2], PNEC_ON, PNEC_OFF, bitCode, codeLen) + 4;
}
*/
#endif //_H_LAB_IRKIT
