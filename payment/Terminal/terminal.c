/****************************************************************************************/
/* Author   : Mustafa Mohammed Abdou                                                    */
/* Date     : 29 Mar , 2023                                                             */
/* Version  : V01                                                                       */
/* Hint     : Header file of terminal module                                            */
/****************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS


#include"Terminal.h"


uint8_t transactionmonth = 0;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	/* Define variable from EN_terminalError_t to hold the return status */
	EN_terminalError_t Localreturnstatus = TERMINAL_OK;

	uint8_t day1 = 0 , day2 = 0 , day = 0 , month1 = 0 , month2 = 0 , month = 0 ; /* Variables for day and month */
	 
	uint16_t year1 = 0 , year2 = 0 , year3 = 0 , year4 = 0 , year ; /* Variable for year */

	uint8_t validDate = 1 ; /* check */

	printf("Enter the transaction date as DD/MM/YYYY\n"); /* Ask the user to enter the date of transaction */

	scanf("%s", termData->transactionDate); /* Scan the date from user the */

    /*=======================================================================*/
	/*=                    day representation                               =*/
	/*=======================================================================*/
	day1 = termData->transactionDate[0] - 48; /* Convert character to number */
	day2 = termData->transactionDate[1] - 48; /* Convert character to number */


	day = ((day1 * 10) + day2);        /* represent the day as number */


	/*=======================================================================*/
	/*=                 month representation                                =*/
	/*=======================================================================*/
	month1 = termData->transactionDate[3] - 48; /* Convert character to number */
	month2 = termData->transactionDate[4] - 48; /* Convert character to number */

	month = ((month1 * 10) + month2); /* represent the day as number */

	transactionmonth = month; /* globally assign the transaction month */


	/*=======================================================================*/
	/*=                   year representation                               =*/
	/*=======================================================================*/
	year1 = termData->transactionDate[6] - 48;  /* Convert character to number */
	year2 = termData->transactionDate[7] - 48;  /* Convert character to number */
	year3 = termData->transactionDate[8] - 48;  /* Convert character to number */
	year4 = termData->transactionDate[9] - 48;  /* Convert character to number */
	
	year = ((year1 * 1000) + (year2 * 100) + (year3 * 10) + (year4) );
	
	/*========================================================================*/
        /*=       validate the date in terms day, month and year                = */
	/*========================================================================*/
	
	if ((day >= 1) && (day <= 31))
	{
		/* Do nothing */
	}
	else
	{
		validDate = 0;
	}

	if ((month >= 1) && (month <= 12))
	{
		/* Do nothing */
	}
	else
	{
		validDate = 0;
	}

	if (year == 2024)
	{
		/* Do nothing */
	}
	else
	{
		validDate = 0;
	}

	if (validDate == 0)
	{
		Localreturnstatus = WRONG_DATE;  /* Date is not valid */
	}
	else
	{
		Localreturnstatus = TERMINAL_OK; /* Date is valid */
	}

	return Localreturnstatus; /* Return the final status */
}


EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	EN_terminalError_t Localexpiredstatus = TERMINAL_OK; 

	uint8_t year1 = 0, year2 = 0, year = 0 , month = 0 , month1 = 0, month2 = 0;

	/*=======================================================================*/
	/*=                 month representation                                =*/
	/*=======================================================================*/
	month1 = cardData->cardExpirationDate[0] - 48; /* Convert character to number */
	month2 = cardData->cardExpirationDate[1] - 48; /* Convert character to number */

	month = ((month1 * 10) + month2); /* represent the day as number */


	/*=======================================================================*/
	/*=                   year representation                               =*/
	/*=======================================================================*/
	year1 = cardData->cardExpirationDate[3] - 48;  /* Convert character to number */
	year2 = cardData->cardExpirationDate[4] - 48;  /* Convert character to number */

	year = ((year1 * 10) + year2);
	


	if (year < 24)
	{
		printf("your card is expired\n");
		Localexpiredstatus = EXPIRED_CARD;  /* card is expired */
	}
	else if (month > 12)
	{
		printf("Card expiry date isn't valid\n");
		Localexpiredstatus = EXPIRED_CARD;  /* card is expired */
	}
	else if (year == 24 )
	{
		if (transactionmonth > month)
		{
			printf("Your card is expired\n");
			Localexpiredstatus = EXPIRED_CARD;  /* card is expired */
		}
	}
	else
	{
		Localexpiredstatus = TERMINAL_OK; /* card not valid */
	}

	return Localexpiredstatus;
}



EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t Localamountstatus = TERMINAL_OK; /* Variable to holds the function status */
	float amount = 0;

	printf("Enter the transaction amount\n"); /* Ask user to enter the amount */

	scanf("%f", &amount); /* Scan amount from the user */
	
	if (amount <= 0) /* Invalid amount */
	{
		printf("Transaction amout isn't valid\n"); /* Ask user to enter the amount */
		Localamountstatus = INVALID_AMOUNT ;
	}
	else
	{
		termData->transAmount = amount; /* Save the amount */

		Localamountstatus = TERMINAL_OK ;
	}

	return Localamountstatus; /* Return the final status */
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t Localmaxamountstatus = TERMINAL_OK ; /* Variable to hold the function status  */

	/* Check the status of the amount inserted by the user */
	if (termData->transAmount > termData->maxTransAmount )
	{
		printf("\nYou exceeded the available max transaction amount\n"); /* Ask user to enter the amount */
		printf("Enter value less than %.2f\n", termData->maxTransAmount ); /* Ask user to enter the amount */

		Localmaxamountstatus = EXCEED_MAX_AMOUNT ; /* Amount isn't valid */
	}

	else
	{
		Localmaxamountstatus = TERMINAL_OK ; /* Amount is valid */
	}

	return Localmaxamountstatus ; /* Return the final state */
}


EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	EN_terminalError_t LocalMaxamoutsetstatus = TERMINAL_OK ; /* Variable to hold the return type of the function */

	if (maxAmount <= 0)
	{
		printf("The max transaction amount isn't valid\n");
		LocalMaxamoutsetstatus = INVALID_MAX_AMOUNT ; 
	}
	else
	{
		termData->maxTransAmount = maxAmount; /* Set the max transaction amount */
	}
	
	return LocalMaxamoutsetstatus ; /* Return the final status */
}