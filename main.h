/******************************************************************************
 *
 * File Name: main.h
 *
 * Description: header file for main
 *
 * Author: Yahia Hamimi
 ******************************************************************************/

#ifndef MAIN_H_
#define MAIN_H_
#include "std_types.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function to display the symbol recieved from keypad into the LCD
 * it checks if the recieved symbol is a number or an operator
 * and call the proper function to display it
 * this is done by seperate the operands and the operators into different arrays.
 * Also, calculating the results into different stages according to the mathematical operations order
 */
void Symbol_display(uint8 symbol);
/*
 * Description :
 * Function to process the pressed keypad switch
 * it checks if the pressed switch is a number or an operator
 * and call the proper function to process it
 * The function uses a while loop to keep asking for the pressed switch
 * until the user presses the '=' button
 * if the pressed switch is a number, it is stored in the operand array
 * if the pressed switch is an operator, it is stored in the op array
 * and the proper calculation is done then the result is stored in the result array
 */
void processKey(void);
/*
 * Description :
 * Function for calculating the result of single operation containing just two operands
 */
sint16 calculateResult(uint8 op, sint16 num1, sint16 num2);
/*
 * Description :
 * Function for summing the array
 */
uint16 finalResult(sint16 a[], uint8 arr_size);

#endif /* MAIN_H_ */
