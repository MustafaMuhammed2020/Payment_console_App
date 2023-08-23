#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData){

	EN_cardError_t returnstate = CARD_OK;

	printf("\nPlease, Enter your card name: ");
	//fflsh(stdout);
	gets(cardData->cardHolderName);
	//scanf("%[^\n]",cardDatas->cardHolderName);
	//getch();


	uint32_t len_name = strlen(cardData->cardHolderName);

	if (len_name > 24 || len_name < 20 || len_name == NULL)
	{
		returnstate = WRONG_NAME;
	}
	else 
	{
		return CARD_OK;
	}
		

	return returnstate ;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){

	EN_cardError_t expireddatestate = CARD_OK; 

	printf("\nPlease, Enter the Expiry date (MM/YY): ");
	//fflsh(stdout);
	gets(cardData->cardExpirationDate);
	//scanf("%s", cardData->cardExpirationDate);

	uint32_t len_date = strlen(cardData->cardExpirationDate);

	if (len_date != 5 || cardData->cardExpirationDate[2] != '/' || len_date == 0)
	{
		expireddatestate = WRONG_EXP_DATE;
	}
		

	return expireddatestate ;
}


EN_cardError_t getCardPAN(ST_cardData_t *cardData){

	printf("\nPlease, Enter your primaryAccountNumber: ");
	//fflsh(stdout);
	scanf("%s",&cardData->primaryAccountNumber);

	uint32_t len_PAN = strlen(cardData->primaryAccountNumber);

	if(len_PAN >19 || len_PAN <16 || len_PAN == 0)
		return WRONG_PAN ;

	return CARD_OK;
}
