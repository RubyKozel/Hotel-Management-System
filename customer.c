#include "defnmac.h"

void addCustomer(Customer *** customerDatabase, int * currentSize)
{
	static int ID = 0;
	printf("\n\nWelcome to the customer addition interface.\n");
	//Credit Card array
	int validity[2] = { 0 };
	char name[MAX_WORD_LENGTH];
	long long creditCardNumber;

	//getting the info of the customer
	getCustomerInfo(*customerDatabase, *currentSize, name, &creditCardNumber, validity);

	//Allocating memory for a new customer pointer
	Customer * newCustomer = NULL;
	if (!(newCustomer = MALLOC(Customer, 1)))
	{
		NOT_ENOUGH_MEMORY;
		exit(0);
	}

	//Allocating memory for the new customer name
	if (!(newCustomer->name = MALLOC(char, strlen(name))))
	{
		NOT_ENOUGH_MEMORY;
		exit(0);
	}

	//Filling the new customer with the info
	newCustomer->ID = ++ID;
	strcpy(newCustomer->name, name);
	newCustomer->creditCardNumber = creditCardNumber;
	newCustomer->creditCardValidity[0] = validity[0];
	newCustomer->creditCardValidity[1] = validity[1];

	//Adding the customer to the database
	(*customerDatabase)[(*currentSize)++] = newCustomer;

	//Reallocating the customer database, increasing the size of the array by 1 pointer
	Customer ** tmp = REALLOC(Customer*, *customerDatabase, *currentSize + 1);
	if (!(tmp))
	{
		NOT_ENOUGH_MEMORY;
		exit(0);
	}
	*customerDatabase = tmp;
	printf("\nThe customer has been added to the customer database!\n");
}//end of function

void showCustomerDatabase(const Customer ** customerDatabase, int size)
{
	if (!size)
	{
		printf("\nNo customers!\n");
		return;
	}
	for (int i = 0; i < size; i++)
		PRINT_POINTED_CUSTOMER(i + 1, customerDatabase[i]);
}//end of function

int getAllCustomersWithSubString(char * string, const  Customer** customerDatabase, int size, int sizeOfArray, Customer** customers)
{
	//There shouldn't be a difference in the name if the user wrote it with uppercaed letters or not,
	//so we uppercase both strings and than serach if there's any customers with that letter sequence
	for (int i = 0; i < size; i++)
	{
		//Allocating memory to the uppercase name to avoid changing the real customer name in the customer database
		char * upperName = NULL;
		if (!(upperName = MALLOC(char, strlen(customerDatabase[i]->name))))
		{
			NOT_ENOUGH_MEMORY;
			exit(0);
		}

		strcpy(upperName, customerDatabase[i]->name);
		if (strstr(upperCaseString(upperName), upperCaseString(string)) != NULL)
			(*customers)[sizeOfArray++] = *customerDatabase[i];
	}
	return sizeOfArray;
}//end of function

void getCustomerInfo(Customer ** database, int databasesize, char* name, long long * creditCardNumber, int validity[2])
{
	//buffer cleaning in case we chose to add customer from menu
	CLEAR;
	printf("Please enter the name of the customer [Max length - 50 letters]: \n");
	//we are reading the name from the user until we get '\n'
	scanf("%[^\n]s", name);
	int isNew;
	printf("Please enter the credit card number (press -1 to exit): \n");
	do
	{
		
		//reading the credit card number and checking its validity, if its invalid, we let the user enter it again
		scanf("%lld", creditCardNumber);
		if (*creditCardNumber == -1)
			exit(0);

		if (CHECK_CREDIT_CARD_NUMBER(*creditCardNumber))
		{
			printf("\nInvalid Credit Card Number, try again!\n");
			//buffer cleaner
			CLEAR;
		}

		//assuming credit card is new 
		isNew = TRUE;
		//checking if there's a customer with this credit card already in the database...
		for (int i = 0; i < databasesize; i++)
		{
			if (database[i]->creditCardNumber == *creditCardNumber)
			{
				printf("this credit card is already in the database, please choose a different number\n");
				isNew = FALSE;
				break;
			}
		}
	} while (!isNew || CHECK_CREDIT_CARD_NUMBER(*creditCardNumber));


	//reading the credit card validity and checking if its valid, if its invalid, we let the user enter it again
	printf("Please enter the validity month of the credit card (press -2 to exit): \n");
	do
	{
		scanf("%d", &validity[0]);
		if (CHECK_CREDIT_CARD_MONTH(validity[0]))
		{
			if (validity[0] == -2)
				exit(0);
			printf("\nInvalid month, try again\n");
			//buffer cleaner
			CLEAR;
		}
	} while (CHECK_CREDIT_CARD_MONTH(validity[0]));

	printf("Please enter the validity year of the credit card (press -2 to exit): \n");
	do
	{
		scanf("%d", &validity[1]);
		if (CHECK_CREDIT_CARD_YEAR(validity[1]))
		{
			if (validity[1] == -2)
				exit(0);
			printf("\nInvalid year, try again\n");
			//buffer cleaner
			CLEAR;
		}
	} while (CHECK_CREDIT_CARD_YEAR(validity[1]));
}//end of function

void upperCaseCustomers(Customer ** customerDatabase, int size)
{
	for (int i = 0; i < size; i++)
		customerDatabase[i]->name[0] = toupper(customerDatabase[i]->name[0]);
}//end of function

char * upperCaseString(char * upperString)
{
	char * ptr = upperString;
	while (*ptr)
	{
		*ptr = toupper((unsigned char)(*ptr));
		ptr++;
	}
	return upperString;
}

void freeCustomerDatabase(Customer *** database, int size)
{
	for (int i = 0; i < size; i++)
	{
		free((*database)[i]->name);
		free((*database)[i]);
	}
	free(*database);
}
