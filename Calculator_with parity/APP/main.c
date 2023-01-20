/*
 * main.c
 *
 *  Created on: Jan 6, 2023
 *      Author: kholoud
 */
#include "../SERV/STD_TYPES.h"
#include "../MCAL/DIO/Dio_int.h"
#include "../HAL/KEYPAD/KEYPAD_int.h"
#include "../HAL/LCD/LCD_int.h"
#include "calculator.h"
#include <util/delay.h>

int main (void){
	LCD_voidInit();
	Keypad_voidInit();
	uint8 Flag;

		while(1)
		{

					Flag=StartPoint;
					while(Flag==StartPoint)		{   Flag=ScanData();	  }
					while(Flag==AnalyzePoint)	{   Flag=AnalyzeData();	  }
					while(Flag==CalculatePoint)	{   Flag=calculate();     }
					while(Flag==DisplayPoint)	{   Flag=display();	      }
					while(Flag==Reset)			{   Flag=Resetall();      }

					while(keypad_u8CheckPress()!='A'){}
					LCD_voidWriteCmd(0X01);
		}
}
