/**********************
	Customer struct header
***********************/

#ifndef __CUSTOMER_H
#define __CUSTOMER_H

struct customer
{
	int ID;
	char * name;
	long long creditCardNumber;
	int creditCardValidity[2];
};

/*The function gets a pointer to the Customer database and a pointer to its' size,
the function adds a new customer to the database and increases the size of the array by 1*/
void addCustomer(Customer ***, int*);

/*The function gets the pointers to a new customer components, reads the values from the user and puts them in the corresponding pointers*/
void getCustomerInfo(Customer **, int, char*, long long *, int[2]);

/*The fucntion gets a customer database and its' size and prints the customers in the database*/
void showCustomerDatabase(const Customer**, int);

/*The function gets a string, the customer database, its size and a pointer to a new customer array.
The function returnes all the customers that has the received string in the customers' names*/
int getAllCustomersWithSubString(char *, const Customer**, int, int, Customer**);

/*Capitalizes the customers names*/
void upperCaseCustomers(Customer **, int);

/*Uppercases an entire string*/
char * upperCaseString(char *);

/*Frees the customer database*/
void freeCustomerDatabase(Customer ***, int);

#endif

