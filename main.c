/******************************************************************************
 *
 * File Name: main.c
 *
 * Description: source file for main
 *
 * Author: Yahia Hamimi
 ******************************************************************************/

#include "keypad.h"
#include "lcd.h"
#include "std_types.h"
#include "main.h"
#include <util/delay.h>

uint8 g_recievedButtonFromKeypad;
uint8 g_calcResetFlag = 0;
/*array that hold all operands values*/
sint16 operand[20] = {0};
/*array that hold all the mathimatical operators */
uint8 op[20];
/*array that hold all numbers that need to be summed
to get the mathimatical operation final result*/
sint16 result[20] = {0};
uint8 counter = 0;

/**
 * @name main
 *
 * @details The main function implements a simple calculator using Keypad and LCD
 * The program will display a welcome message, then it will start to accept input
 * from the keypad and calculate the result of the entered mathematical operation
 *
 * @param None
 *
 * @return None
 */
int main(void)
{
	LCD_init(); /*get the LCD ready for displaying fo the first time*/
	while (1)
	{
		LCD_moveCursor(0, 5);
		LCD_displayString("welcome");
		LCD_moveCursor(1, 0); /* Move the cursor to the second row */
		LCD_displayString("calculator proj");
		_delay_ms(1000); /* Press time */
		LCD_clearScreen();
		while (1)
		{
			processKey();
			if (g_calcResetFlag == 1) /*if On Button is pressed clear LCD and return to the initial state*/
			{
				LCD_clearScreen();
				break;
			}
			LCD_intgerToString(finalResult(result, 20));
		}
	}
}

/**
 * @name Symbol_display
 *
 * @details Function to display the symbol recieved from keypad into the LCD
 * it checks if the recieved symbol is a number or an operator and call the proper function to display it
 * this is done by seperate the operands and the operators into different arrays.
 * Also, calculating the results into different stages according to the mathematical operations order
 *
 * @param symbol the recieved symbol from the keypad
 *
 * @return None
 */
void Symbol_display(uint8 symbol)
{

	if ((symbol <= 9) && (symbol >= 0))
	{
		LCD_intgerToString(symbol); /* display the pressed keypad switch */
	}
	else
	{
		LCD_displayCharacter(symbol); /* display the pressed keypad switch */
	}

	_delay_ms(500); /* Press time */
}

/**
 * @name processKey
 *
 * @details Function to process the pressed keypad switch
 * it checks if the pressed switch is a number or an operator
 * and call the proper function to process it
 * The function uses a while loop to keep asking for the pressed switch
 * until the user presses the '=' button
 * if the pressed switch is a number, it is stored in the operand array
 * if the pressed switch is an operator, it is stored in the op array
 * and the proper calculation is done
 * the result is stored in the result array
 *
 * @return None
 */

void processKey(void)
{
	while (1)
	{
		g_recievedButtonFromKeypad = KEYPAD_getPressedKey();
		if (g_recievedButtonFromKeypad == 13)
		{
			g_calcResetFlag = 1;
			return;
		}

		Symbol_display(g_recievedButtonFromKeypad);

		if (g_recievedButtonFromKeypad != '+' && g_recievedButtonFromKeypad != '-' && g_recievedButtonFromKeypad != '*' && g_recievedButtonFromKeypad != '%' && g_recievedButtonFromKeypad != '=')
		{
			operand[counter] = g_recievedButtonFromKeypad + operand[counter] * (10);
		}

		else
		{
			op[counter] = g_recievedButtonFromKeypad;
			if (op[counter - 1] == '-')
			{
				operand[counter] = operand[counter] * (-1);
			}
			if (op[counter - 1] == '*' || op[counter - 1] == '%')
			{
				result[counter] = calculateResult(op[counter - 1], operand[counter - 1], operand[counter]);
				if (op[counter] != '=')
					break;
			}
		}
		if ((op[counter] == '-' || op[counter] == '+'))
		{
			result[counter] = operand[counter];
			break;
		}
		if ((op[counter] == '*' || op[counter] == '%'))
		{

			break;
		}
		if (op[counter] == '=' && (op[counter - 1] == '+' || op[counter - 1] == '-'))
		{
			result[counter] = operand[counter];
			return;
		}
		if (op[counter] == '=' && (op[counter - 1] == '*' || op[counter - 1] == '%'))
		{
			return;
		}
	}

	counter++;
	processKey();
}

/**
 * @name calculateResult
 *
 *
 * @details Function for calculating the result of single operation containing just two operands
 *
 * @param[in] op operator
 * @param[in] num1 first operand
 * @param[in] num2 second operand
 *
 * @return result of the operation
 */
sint16 calculateResult(uint8 op, sint16 num1, sint16 num2)
{
	sint16 result;
	switch (op)
	{
	case '+':
		result = (num1 + num2);
		break;
	case '-':
		result = (num1 - num2);
		break;
	case '*':
		result = (num1 * num2);
		break;
	case '/':
		result = (num1 / num2);
		break;
	}
	return result;
}

/**
 * @name finalResult
 *
 *
 * @details Function for summing the array
 *
 * @param[in] a the array
 * @param[in] arr_size the size of the array
 *
 * @return the sum of all elements in the array
 */
uint16 finalResult(sint16 a[], uint8 arr_size)
{
	uint8 i = 0;
	uint16 sum = 0;
	for (i = 0; i < arr_size; i++)
		sum += a[i];
	return sum;
}
