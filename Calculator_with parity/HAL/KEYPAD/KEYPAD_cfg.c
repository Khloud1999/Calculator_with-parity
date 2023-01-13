/*
 * KEYPAD_cfg.c
 *
 *  Created on: Dec 29, 2022
 *      Author: kholoud
 */

#include "../../SERV/STD_TYPES.h"
#include "../../MCAL/DIO/dio_int.h"


typedef struct {
	uint8 port ;
	uint8 pin ;
}keypad_pin;


#define KEYPAD_NO_COL       4
#define KEYPAD_NO_ROW       4

//[ROW][COLUMN]
 uint8 KEYPAD_au8KeyVal [KEYPAD_NO_ROW][KEYPAD_NO_COL] = {
		{'1','2','3','+'},
		{'4','5','6','-'},
		{'7','8','9','*'},
		{'0', 'A','=','/'}
 };

//config port and pin to each row
 keypad_pin KEYPAD_au8RowPins[KEYPAD_NO_ROW ] =
{
		{ //R0
				PORT_C,
				PIN_0
		},
		{ //R1
				PORT_C	,
				PIN_1
		},
		{ //R2

				PORT_C	,
				PIN_2
		},

		{ //R3

				PORT_C	,
				PIN_3
		}

};

//config  port and pin to each column
 keypad_pin KEYPAD_au8ColPins[KEYPAD_NO_COL] =
{
		{ //C0
				PORT_C ,
				PIN_4
		},
		{ //C1
				PORT_C	,
				PIN_5
		},
		{ //C2

				PORT_C	,
				PIN_6
		},
		{ //C3

				PORT_C	,
				PIN_7
		}

};

