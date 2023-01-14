/*
 * calculator.h
 *
 *  Created on: Jan 6, 2023
 *      Author: kholoud
 */

#ifndef APP_CALCULATOR_H_
#define APP_CALCULATOR_H_



#define MaxNumberOfDigit 16
#define MaxNumberOfOperands 12	//including =
#define MaxNumberOfOperations MaxNumberOfOperands-1 //excluding =



//enum Flags{Reset=0,StartPoint,AnalyzePoint,CalculatePoint,DisplayPoint,ErrorPoint};
#define Reset			0
#define StartPoint		1
#define AnalyzePoint	2
#define CalculatePoint	3
#define DisplayPoint	4


#define IsOperation(n) ((n=='*')||(n=='+')||(n=='-')||(n=='/'))

#define true   1
#define false  0


//store any key pressed from user
uint8  ScanData ();
//Convert ASCII to integer
sint32 ConvertToInt(uint8 array[]);
void InitArray(uint8 array[]);
//differentiates between operands & operations, signed & unsigned
uint8  AnalyzeData();
void shift_s64array_left(uint64* array ,uint8 start_index);
void shift_u8array_left(uint8 array[] ,uint8 start_index);
sint64 SubCalculate(sint64 operand1,sint64 operand2,uint8 operation);
uint8  calculate();
uint8  display();
uint8  Resetall();

#endif /* APP_CALCULATOR_H_ */
