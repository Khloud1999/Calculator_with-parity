/*
 * KEYPAD_int.h
 *
 *  Created on: Dec 23, 2022
 *      Author: kholoud
 */

#ifndef HAL_KEYPAD_KEYPAD_INT_H_
#define HAL_KEYPAD_KEYPAD_INT_H_

#define NOTPRESSED         0xff

void Keypad_voidInit (void);

uint8 keypad_u8CheckPress(void);


#endif /* HAL_KEYPAD_KEYPAD_INT_H_ */
