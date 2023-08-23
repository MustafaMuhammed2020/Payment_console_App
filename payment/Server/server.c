#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS


#include "server.h"
#define MAX_LINE_LENGTH 255

ST_transaction_t  transDB[255] = { 0 };
ST_accountsDB_t accountsDB[255] = { '\0' };
ST_accountsDB_t* p;


EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	ST_accountsDB_t accountRefrence;
	transData->transState = APPROVED; /*Default State is APPROVED*/
	if (isValidAccount(&transData->cardHolderData, &accountRefrence) == ACCOUNT_NOT_FOUND)
	{
		transData->transState = FRAUD_CARD;
		printf("\nFraud Card\n");
	}
	
	if (transData->transState == APPROVED && isBlockedAccount(&accountRefrence) == BLOCKED_ACCOUNT)
	{
		transData->transState = DECLINED_STOLEN_CARD;
		printf("\nAccount is blocked\n");
	}
	
	if (transData->transState == APPROVED && isAmountAvailable(&transData->terminalData, &accountRefrence) == LOW_BALANCE)
	{
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		printf("\nInsuffecient funds\n");
	}

	if(transData->transState == APPROVED)
	{
		accountRefrence.balance -= transData->terminalData.transAmount;
		p->balance = accountRefrence.balance;
		printf("\nSuccessful Transaction\n");
	}

	if (saveTransaction(&(*transData)) == SAVING_FAILED)
	{
		transData->transState = INTERNAL_SERVER_ERROR;
		printf("\nSaving failed\n");
	}

	return transData->transState;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	for (int i = 0;i < 255 && strlen(accountsDB[i].primaryAccountNumber) != 0;i++)
	{
		if (!strcmp(accountsDB[i].primaryAccountNumber,cardData->primaryAccountNumber)) /*strcmp(string1,string2) compares between 2 strings and return 0 if equal*/
		{
			*accountRefrence = accountsDB[i];
			p = &accountsDB[i];
			return SERVER_OK;
		}
	}
	accountRefrence = NULL;
	return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	return accountRefrence->state == BLOCKED ? BLOCKED_ACCOUNT : SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	if ((termData->transAmount) > (accountRefrence->balance))
	{
		return LOW_BALANCE;
	}
	return SERVER_OK;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	for (int i = 0;i < 255;i++)
	{
		if (transDB[i].transactionSequenceNumber == 0)
		{
			transDB[i] = *transData;
			transDB[i].transactionSequenceNumber = (i+1);
			break;
			//return SERVER_OK;
		}
	}
	listSavedTransactions();
	return SERVER_OK;
	//return SAVING_FAILED;
}

void listSavedTransactions(void)
{

	for (int i = 0;i < 255;i++) 
	{
		if (transDB[i].transactionSequenceNumber > 0)
		{
			printf("###########################################\n");
			printf("Transaction Sequence Number: %d \n",transDB[i].transactionSequenceNumber);
			printf("Transaction Date           : %s \n", transDB[i].terminalData.transactionDate);
			printf("Transaction Amount         : %f \n", transDB[i].terminalData.transAmount);
			if(transDB[i].transState==0)
				printf("Transaction State          : %s \n", "Approved");
			if (transDB[i].transState == 1)
				printf("Transaction State          : %s \n", "DECLINED_INSUFFECIENT_FUND");
			if (transDB[i].transState == 2)
				printf("Transaction State          : %s \n", "DECLINED_STOLEN_CARD");
			if (transDB[i].transState == 3)
				printf("Transaction State          : %s \n", "FRAUD_CARD");
			if (transDB[i].transState == 4)
				printf("Transaction State          : %s \n", "INTERNAL_SERVER_ERROR");
			printf("Terminal Max Amount        : %f \n", transDB[i].terminalData.maxTransAmount);
			printf("Cardholder Name            : %s \n", transDB[i].cardHolderData.cardHolderName);
			printf("PAN                        : %s \n", transDB[i].cardHolderData.primaryAccountNumber);
			printf("Card Expiration Date       : %s \n", transDB[i].cardHolderData.cardExpirationDate);
			printf("###########################################\n");

		}
		else 
		{
			break;
		}
	}
}

void getDataBase(ST_accountsDB_t* DB)
{
	char* tok = NULL;
	char* path = "file.txt";
	char line[MAX_LINE_LENGTH] = { 0 };
	int i = 0;

	FILE* file = fopen(path, "r");

	while (fgets(line, MAX_LINE_LENGTH, file)) //Reads each line from the file and assigns each elements to it's corresponding element in the database
	{ 
		
		tok = strtok(line, ","); /*Splits the string to tokens containing the string until the next "," */

		if (tok)
			DB[i].balance = atof(tok); /*Converts string to float*/

		tok = strtok(NULL, ",");

		if (tok)
			DB[i].state = atoi(tok); /*Converts string to integer*/

		tok = strtok(NULL, "\n"); /*Last token is followed by a newline so delimeter is changed to "\n"*/

		if (tok)
			strcpy(&DB[i].primaryAccountNumber, tok); /*Copy the token string to PAN*/
		i++;
	}
	
}

//EN_serverError_t updateDatabase(ST_accountsDB_t* DB)
//{
//
//}
//
//void writeTransaction(ST_transaction_t* transData)
//{
//	char* path = "transactionData.txt";
//	char line[MAX_LINE_LENGTH] = { 0 };
//	FILE* file = fopen(path, "a");
//	char sn[100];
//
//	itoa(transData->transactionSequenceNumber, sn, 10);
//	strcpy(line, sn); //copies the current string to the string that will be passed to the transactionData.txt
//	strcat(line, "a,"); //add new line at the end of the string
//
//	strcat(line, transData->terminalData.transactionDate);
//	strcat(line, "b,"); //add new line at the end of the string
//
//	ltoa(transData->terminalData.transAmount,sn,10);
//	strcpy(line, sn); //copies the current string to the string that will be passed to the transactionData.txt
//	strcat(line, "c,"); //add new line at the end of the string
//
//	itoa(transData->transState, sn, 10);
//	strcpy(line, sn); //copies the current string to the string that will be passed to the transactionData.txt
//	strcat(line, "d,"); //add new line at the end of the string
//	
//	ltoa(transData->terminalData.maxTransAmount, sn, 10);
//	strcpy(line, sn); //copies the current string to the string that will be passed to the transactionData.txt
//	strcat(line, "e,"); //add new line at the end of the string
//
//	strcat(line, transData->cardHolderData.cardHolderName);
//	strcat(line, "f,"); //add new line at the end of the string
//
//	strcat(line, transData->cardHolderData.primaryAccountNumber);
//	strcat(line, "g,"); //add new line at the end of the string
//
//	strcat(line,transData->cardHolderData.cardExpirationDate);
//	strcat(line, "h\n");
//	
//	
//	fputs(line, file);
//}
//
//
//void main()
//{
//	getDataBase(accountsDB);
//	if (!strcmp(accountsDB[0].primaryAccountNumber, "898937461543685221"))
//	{
//		printf("FOUND\n");
//	}
//	else {
//		printf("NOT FOUND\n");
//	}
//
//	for(int i=0;i<255 && strlen(accountsDB[i].primaryAccountNumber) != 0;i++)
//	{
//		printf("Balance : %f\nState   : %d\nPAN     : %s\n---------------\n", accountsDB[i].balance, accountsDB[i].state, accountsDB[i].primaryAccountNumber);
//	}
//
//	system("pause");
//	//writeTransaction(transDB);
//}