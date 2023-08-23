/****************************************************************************************/
/* Author   : Omar Ashraf Taha                                                          */
/* Date     : 29 Mar , 2023                                                             */
/* Version  : V01                                                                       */
/* Hint     : Header file of Server module                                              */
/****************************************************************************************/

/* HEADER FILE GUARD */
#ifndef SERVER_H
#define SERVER_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../Terminal/terminal.h"
#include "../Application/app.h"
#include "../Card/card.h"






/*********************************************************/
/* enum for tranaction state return errors               */
/* returns 0 ==> approved transaction                    */
/*         1 ==> insuffecient fund                       */
/*         2 ==> declined card                           */
/*         3 ==> fraud card                              */
/*         4 ==> internal server error, can't save data  */
/*********************************************************/
typedef enum EN_transState_t
{
    APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

/**************************************************************/
/* typedef for transaction data, includes:                    */
/* 1 - Card Holder Data Struct passed from Card Module        */
/* 2 - Terminal Data Struct passed from Terminal Module       */
/* 3 - Transaction Sequence Number                            */
/**************************************************************/
typedef struct ST_transaction_t
{

    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;

/*********************************************************/
/* enum for server return errors                         */
/* returns 0 ==> Server is ok                            */
/*         1 ==> Saving failed                           */
/*         2 ==> Transaction not found                   */
/*         3 ==> Account not found                       */
/*         4 ==> Low balance                             */   
/*         5 ==> Account is blocked                      */
/*********************************************************/
typedef enum EN_serverError_t
{
    SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t;

/*********************************************************/
/* enum for account state return state                   */
/* returns 0 ==> Account is running                      */
/*         1 ==> Account is blocked                      */
/*********************************************************/
typedef enum EN_accountState_t
{
    RUNNING,BLOCKED
}EN_accountState_t;

/**************************************************************/
/* typedef for database, includes:                            */
/* 1 - Balance                                                */
/* 2 - Account state                                          */
/* 3 - PAN                                                    */
/**************************************************************/
typedef struct ST_accountsDB_t
{
    float balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

/*==========================================================================================================================================================*/
/* Description : Receives the transaction data and checks the account state, if the tansaction amount is available or not and saves the transaction data    */
/* Inputs      : Refrence to store the transaction data with the type of ST_transaction_t                                                                   */
/* Return      : Transaction State                                                                                                                          */
/*==========================================================================================================================================================*/
EN_transState_t recieveTransactionData(ST_transaction_t* transData);

/*======================================*/
/*= Description : Tester Function      =*/
/*======================================*/
void recieveTransactionDataTest(void);

/*=======================================================================================================================================================================================================*/
/* Description : Receives the cardholder data, start searching for it in the database and updates the accountRefrence variable with the current accoount data                                            */
/* Inputs      : Refrence to the cardholder data with the type of ST_cardData_t and refrence to a current account data with the type of ST_accountsDB_t                                                  */                                                                
/* Return      : Account State                                                                                                                                                                           */
/*=======================================================================================================================================================================================================*/
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence);

/*=================================================================*/
/*= Description : Checks if the account is blocked                =*/
/*= Inputs      : Refrence to the current account data            =*/
/*= Return      : Account State                                   =*/
/*=================================================================*/
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence);

/*===================================================================================================================*/
/* Description : Checks if amount to be deducted is available                                                        */
/* Inputs      : Refrence to the terminal data of type ST_terminalData_t and a refrence to the current account data  */
/* Return      : Account State                                                                                       */
/*===================================================================================================================*/
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence);

/*===================================================================================================================*/
/* Description : Saves the transaction and assigns a transaction sequence number for it                              */
/* Inputs      : Refrence to transaction data array which stores all the transaction                                 */
/* Return      : Server State                                                                                        */
/*===================================================================================================================*/
EN_serverError_t saveTransaction(ST_transaction_t* transData);

/*======================================================================================*/
/* Description : Lists all the saved transactions in the transactions database          */
/* Inputs      : void                                                                   */
/* Return      : void                                                                   */
/*======================================================================================*/
void listSavedTransactions(void);

/*================================================================================================================================================================================================================================*/
/* Description    : Reads Data from the database file and copies it to an array                                                                                                                                                   */
/* Inputs         : Refrence to an array of type ST_accountsDB_t                                                                                                                                                                  */
/* Return         : Void                                                                                                                                                                                                          */
/* Important Note : The file name is: file.txt and should be placed in the main folder of the project and Data format inside the file should be balance,state in decimal value,PAN and followed by a newline right after.         */
/*================================================================================================================================================================================================================================*/
void getDataBase(ST_accountsDB_t* DB);

/*================================================================================================================================================================================================================================*/
/* Description    : Updates Data from the database array and copies it to the file                                                                                                                                                */
/* Inputs         : Refrence to a variable of type ST_accountsDB_t                                                                                                                                                                */
/* Return         : Server_ok or Internal_server_error                                                                                                                                                                            */
/* Important Note : The file name is: file.txt and should be placed in the main folder of the project and Data format inside the file should be balance,state in decimal value,PAN and followed by a newline right after.         */
/*================================================================================================================================================================================================================================*/
//EN_serverError_t updateDatabase(ST_accountsDB_t* DB);
//
//void writeTransaction(ST_transaction_t* transData);

extern ST_transaction_t  transDB[255];
extern ST_accountsDB_t accountsDB[255];

#endif