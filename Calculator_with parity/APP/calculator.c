/*
 * calculator.c
 *
 *  Created on: Jan 6, 2023
 *      Author: kholoud
 */

#include <stdint.h>
#include <string.h>
#include "../SERV/STD_TYPES.h"
#include "../SERV/BIT_MATH.h"
#include "calculator.h"
#define F_CPU 8000000UL
#include "util/delay.h"
#include "../HAL/LCD/LCD_int.h"
#include"../HAL/KEYPAD/KEYPAD_int.h"


sint64 Result=0;
sint64 Operands[MaxNumberOfOperands];
uint8 Operations[MaxNumberOfOperations];
uint8 Digit[MaxNumberOfDigit];

uint8 OperandsCounter=0;
uint8 OperationsCounter=0;
uint8 DigitCounter=0;

sint8 Sign =1;
uint8 OtherNumberSign=false;

uint8 ScanData ()
{
	uint8 temp=0;
	temp = keypad_u8CheckPress();
	while(temp!= '=')
	{

		if (temp == 'A')
		{
			Resetall();
			LCD_voidWriteCmd(0x01);
		}

		//storing any thing the user input
		if((temp!=0) && (temp != 'A'))
		{

			Digit[DigitCounter]=temp;
			LCD_voidWriteChar(Digit[DigitCounter]);
			DigitCounter++;
			_delay_ms(50);

		}
		temp=keypad_u8CheckPress();

	}
	Digit[DigitCounter]='=';
	LCD_voidWriteChar(Digit[DigitCounter]);
	DigitCounter++;
	Digit[DigitCounter]='\0'; // to close array

	return AnalyzePoint;

}

sint32 ConvertToInt(uint8 array[]){
	sint32 num=0, sign=1, i=-1;

	if(array[0] == '-')    //check if the string is -ve
	{
		sign = -1;
		i = 0;           //skip the -ve sign to the number
	}

	while(array[++i] != 0)
	{
		num = (num * 10) + (array[i] - '0');
	}

	num *= sign;
	return num;
}

void InitArray(uint8 array[]){
	uint8 i =0;
	while(array[i] != '\0'){
		array[i]='\0';
		i++;
	}
}


uint8 AnalyzeData()
{
	sint8 TempArr[MaxNumberOfDigit]={0};
	uint8 TempIndex=0;
	uint8 index=0;

	Sign =1;
	OtherNumberSign =1;

	if (IsOperation(Digit[0]) && Digit[0]!= '-'&& Digit[0]!= '+') //input ex (*5)
	{
		LCD_voidWriteString("Syntax error");
		_delay_ms(100);
		return Reset;
	}

	while(DigitCounter != 0)
	{
		if(((Digit[index]>='0') && (Digit[index]<='9')) || ((Digit[index]=='-') && (IsOperation(Digit[index-1])))/*||OtherNumberSign*/)
		{
			TempArr[TempIndex]=Digit[index];
			TempIndex++;

		}
		else if (((IsOperation(Digit[index]))||(Digit[index]== '=')))
		{
			Operations[OperationsCounter]=Digit[index];
			OperationsCounter++;
			Operands[OperandsCounter]= ConvertToInt(TempArr)/* Sign*/;
			OperandsCounter++;
			InitArray(TempArr);
			TempIndex=0;
		}
		index++;
		DigitCounter--;
	}
	return CalculatePoint;
}


void shift_s64array_left(uint64* array ,uint8 start_index){


	for(uint8 i = start_index;1; i++) {

		array[i]=array[i+1];
		if(array[i] == '\0'){
			break;
		}
	}
}

void shift_uint8array_left(uint8 array[] ,uint8 start_index){


	for(uint8 i = start_index;1; i++) {

		array[i]=array[i+1];
		if(array[i] == '\0'){
			break;
		}
	}
}

sint64 SubCalculate(sint64 operand1,sint64 operand2,uint8 operation)
{
	sint64 return_value = 0;
	if (operation != '=')
	{
		switch(operation)
		{
			case '+' :
			return_value = operand1+operand2;
			break;
			case '-' :
			return_value = operand1-operand2;
			break;
			case '*' :
			return_value = operand1*operand2;
			break;
			case '/' :
			return_value = operand1/operand2;
			break;
		}

		return return_value;
	}

	return 0;
}

uint8 calculate(){
	uint8 Operations_index=0 , Operands_index;

	while((Operations[Operations_index] != '=') && (Operations[Operations_index] != '\0') )
	{
		if (Operations[Operations_index] == '*')
		{
			Operands[Operations_index] = Operands[Operations_index] * Operands[Operations_index+1];
			shift_s64array_left((uint64*)Operands,Operations_index+1);
			shift_uint8array_left(Operations,Operations_index);

		}
		else if (Operations[Operations_index] == '/')
		{
			Operands[Operations_index] = Operands[Operations_index] / Operands[Operations_index+1];
			shift_s64array_left((uint64*)Operands,Operations_index+1);
			shift_uint8array_left(Operations,Operations_index);

		}
		else
		{
			Operations_index++;
		}
	}

	Operations_index=0; Operands_index =1;
	Result = Operands[0];
	while((Operations[Operations_index] != '=') && (Operands[Operands_index] != '\0') )
	{
		Result =SubCalculate(Result,Operands[Operands_index],Operations[Operations_index]);
		Operations_index++;
		Operands_index++;
	}

	return DisplayPoint;
}

uint8  display()
{

	LCD_voidMoveCursor(2,1);
	LCD_voidWriteNumber(Result);

	return Reset;
}

uint8  Resetall()
{
	uint8 index=0;
	for(index=0;index<MaxNumberOfDigit;index++)
	Digit[index]=0;
	for(index=0;index<MaxNumberOfOperands;index++)
	Operands[index]=0;
	for(index=0;index<MaxNumberOfOperations;index++)
	Operations[index]=0;
	OperandsCounter=0;
	OperationsCounter=0;
	DigitCounter=0;
	Result=0;

	return StartPoint;
}
