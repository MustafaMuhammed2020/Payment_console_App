/****************************************************************************************/
/* Author   : Mustafa Mohammed Abdou                                                    */
/* Date     : 29 Mar , 2023                                                             */
/* Version  : V01                                                                       */
/* Hint     : Header file of terminal module                                            */
/****************************************************************************************/

/* HEADER FILE GUARD */
#ifndef TERMINAL_H_
#define TERMINAL_H_

#include<stdio.h>
#include"card.h"
#include"standard_types.h"


/****************************************/
/* typedef for terminal data includes   */
/* 1 - trans amount                     */
/* 2 - max trans amount                 */
/* 3 - date of transaction              */
/****************************************/
typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;


/**********************************************/
/* enum for various return errors             */
/* returns 0 ==> ok                           */
/*         1 ==> wrong date                   */
/*         2 ==> expired date                 */
/*         3 ==> invalid card                 */
/*         4 ==> invalid amount               */
/*         5 ==> exceed max amount            */
/*         6 ==> invalid max amount           */
/**********************************************/
typedef enum EN_terminalError_t
{
    TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;



/*=================================================================================================*/
/*= Describtion   : Ask the user for transaction date and store it in terminal data               =*/
/*= Date describtion  : 10 characters DD/MM/YYYY                                                  =*/
/*= Inputs     : struct from ST_terminalData_t                                                    =*/
/*= Return     : if the date isn't valid returns WRONG_DATE else returns TERMINAL_OK              =*/
/*=================================================================================================*/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);


/*=====================================================================================================================================================*/
/*= Describtion  : This function compares the card expiry date with the transaction date.                                                             =*/
/*= Input : struct from ST_terminalData_t and another struct from  ST_cardData_t                                                                      =*/
/*= Return  : If the card expiration date is before the transaction date will return EXPIRED_CARD, else return TERMINAL_OK                            =*/
/*=====================================================================================================================================================*/
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);

/*=====================================================================================================*/
/*= Describtion  : Ask the user for the transaction amount to validate it eith the amount in the card =*/
/*= Input : struct from ST_terminalData_t to save amount in it                                        =*/
/*= Return  : if amount >= 0 return INVALID_AMOUNT else return TERMINAL_OK                            =*/
/*=====================================================================================================*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);


/*===========================================================================================================================================*/
/*= Describtion  :  This function compares the transaction amount with the terminal max allowed amount                                      =*/
/*= Input : struct from ST_terminalData_t to comare its max amount with transaction amount                                                  =*/
/*= Return  :  amount is larger than the terminal max allowed amount will return EXCEED_MAX_AMOUNT, else return TERMINAL_OK                 =*/
/*===========================================================================================================================================*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);


/*===========================================================================================================================================*/
/*= Describtion  :  This function takes the maximum allowed amount and stores it into terminal data                                         =*/
/*= Input : struct from ST_terminalData_t and Transaction max amount is a float number                                                      =*/
/*= Return  :  If transaction max amount less than or equal to 0 will return the INVALID_MAX_AMOUNT error, else return TERMINAL_OK          =*/
/*===========================================================================================================================================*/
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount);

/* EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData);  Optional */





#endif 
