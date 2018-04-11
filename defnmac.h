/*************************************************************************
			DEFINES N MACROS HEADER.
			defines all constants, includes, typedefs, structs and macros in this program
****************************************************************************/

#ifndef __DEFNMAC_H
#define __DEFNMAC_H


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

/*consts*/
#define TRUE 1
#define FALSE 0
#define ROOM_BASE 100
#define MAX_IN_ROOM 4
#define LOW_RANGE 99999999999
#define HIGH_RANGE 1000000000000
#define JANUARY 1
#define DECEMBER 12
#define LOW_YEAR_RANGE 2010
#define HIGH_YEAR_RANGE 2020
#define MAX_WORD_LENGTH 50

/*macros*/
#define CHECK_CREDIT_CARD_NUMBER(x) ((x) < LOW_RANGE || (x) > HIGH_RANGE) ? TRUE : FALSE
#define CHECK_CREDIT_CARD_MONTH(x) ((x) < JANUARY || (x) > DECEMBER) ? TRUE : FALSE
#define CHECK_CREDIT_CARD_YEAR(x) ((x) < LOW_YEAR_RANGE || (x) > HIGH_YEAR_RANGE) ? TRUE : FALSE
#define PRINT_POINTED_CUSTOMER(x,y) printf("Customer %d:\n\t ID: %d\n\t name: %s\n\t credit card number: %lld\n\t credit card validity %d / %d\n", (x), (y)->ID, (y)->name, (y)->creditCardNumber, (y)->creditCardValidity[0], (y)->creditCardValidity[1])
#define PRINT_CUSTOMER(x,y) printf("Customer %d:\n\t ID: %d\n\t name: %s\n\t credit card number: %lld\n\t credit card validity %d / %d\n", (x), (y).ID, (y).name, (y).creditCardNumber, (y).creditCardValidity[0], (y).creditCardValidity[1])
#define CHECK_CHAR(x) ((x) != 'N' && (x) != 'n' && (x) != 'y' && (x) != 'Y') ? TRUE: FALSE
#define CHECK_CUSTOMERS(x) ((x) < 0 || (x) > MAX_IN_ROOM) ? TRUE : FALSE
#define CHECK_CUSTOMERS_FOR_BREAKFAST(x,y) ((x) < -1 || (x) > MAX_IN_ROOM || (x) > (y)) ? TRUE : FALSE
#define CALCULATE_ROOM_NUMBER(x,y) (((x) * ROOM_BASE)  +(y))
#define GET_ONE_DIGIT_ROOM(x,y) ((((x) / ROOM_BASE) - 1)*(y)) + ((x) % ROOM_BASE)
#define CHECK_IF_ROOM_EXIST(x,y,z) ((x)/ROOM_BASE < 1 || (x)/ROOM_BASE > (y) || (x) % ROOM_BASE + 1 > (z))
#define NOT_ENOUGH_MEMORY printf("Not enough memory to allocate\n")
#define MALLOC(x,y) (x*) malloc((y)*sizeof(x))
#define REALLOC(x,y,z) (x*)realloc((y),(z)*sizeof(x))
#define CLEAR while (getchar() != '\n') //we use this because flushall() is deprecated

/*structs decleration and type definition*/
typedef struct reservation Reservation;
typedef struct room Room;
typedef struct customer Customer;
typedef struct hotel Hotel;

/*includes to other structs*/
#include "customer.h"
#include "hotel.h"
#include "room.h"
#include "reservation.h"




#endif
