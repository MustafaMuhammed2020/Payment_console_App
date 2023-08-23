#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include "app.h"

void appStart(void)
{
	ST_cardData_t card;
	ST_terminalData_t terminal;
	EN_terminalError_t Maxamountstate = TERMINAL_OK;
	EN_terminalError_t Amountstate = TERMINAL_OK;
	ST_transaction_t transaction;
	EN_transState_t error;
	EN_cardError_t nameState,dateState,panState = 0;
	char u8_amountcounter = 0;
	
	do
	{
		nameState = getCardHolderName(&card); /*get the card holder name */
		
	} while (nameState);
	

	do
	{
		dateState=getCardExpiryDate(&card);/*get the card expiray date*/

	} while (dateState );

	 panState = getCardPAN(&card); /*get the card PAN */
	
	if (panState)
	{
		printf("\nWrong PAN!\n");
		return;
	}
	


	strcpy(transaction.cardHolderData.cardExpirationDate, card.cardExpirationDate);
	strcpy(transaction.cardHolderData.primaryAccountNumber, card.primaryAccountNumber);

	if (getTransactionDate(&terminal) == WRONG_DATE)
	{
		printf("Declined\nTransaction date is not valid\n");	
		return;
	}

	strcpy(transaction.terminalData.transactionDate, terminal.transactionDate);


	if (isCardExpired(&card, &terminal) == EXPIRED_CARD)
	{
		printf("Declined\n");
		return;
	}

	
	
	if (setMaxAmount(&terminal, 5000.000) != INVALID_MAX_AMOUNT) /* Set the maximum transaction amount */
	{
		do
		{
			Amountstate = getTransactionAmount(&terminal);  // Ask the user for the transaction amount

			Maxamountstate = isBelowMaxAmount(&terminal);  // Ceck the amount valid or not

			u8_amountcounter++; /* increase the amount counter by 1 */

		} while ((u8_amountcounter < 2) && (Maxamountstate)); /* repeat for 2 times if the entered amount isn't valid */

	}
	
	
	transaction.terminalData.maxTransAmount = terminal.maxTransAmount;
	transaction.terminalData.transAmount = terminal.transAmount;
	strcpy(transaction.cardHolderData.cardHolderName, card.cardHolderName);
	getDataBase(accountsDB);
	error = recieveTransactionData(&transaction);
	


	while(1)
	{
		Amountstate = getTransactionAmount(&terminal);
		transaction.terminalData.transAmount = terminal.transAmount;
		error = recieveTransactionData(&transaction);
	}

}

void main()
{
	appStart();

	system("pause");
}