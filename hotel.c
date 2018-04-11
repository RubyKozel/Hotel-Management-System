#include "defnmac.h"

void Init(Hotel * hotel, Customer*** customerDatabase, Reservation*** reservationDatabase)
{
	int result = 0;
	printf("Enter num of floors: \n");
	do
	{
		result = scanf("%d", &hotel->numOfFloors);
		if (result < 1 || hotel->numOfFloors == EOF)
			printf("\nplease enter a valid number!\n");
		CLEAR;
	} while (result < 1 || hotel->numOfFloors == EOF);
	printf("Enter num of rooms in each floor (0 < room <= %d): \n", ROOM_BASE);
	do
	{
		result = scanf("%d", &hotel->numOfRooms);
		if (result < 1 || hotel->numOfRooms > 100 || hotel->numOfRooms == EOF)
			printf("\nplease enter a valid number!\n");
		CLEAR;
	} while (result < 1 || hotel->numOfRooms > 100 || hotel->numOfRooms == EOF);

	//Allocating mamory to the room matrix
	if (!(hotel->rooms = MALLOC(Room, hotel->numOfRooms * hotel->numOfFloors)))
	{
		NOT_ENOUGH_MEMORY;
		exit(0);
	}

	//Allocating memory to the customers' pointer array
	if (!(*customerDatabase = MALLOC(Customer*, 1)))
	{
		NOT_ENOUGH_MEMORY;
		exit(0);
	}

	//Allocating memory for the first customer pointer
	if (!(*customerDatabase[0] = MALLOC(Customer, 1)))
	{
		NOT_ENOUGH_MEMORY;
		exit(0);
	}

	//Allocating memory to the Reservations' pointer array
	if (!(*reservationDatabase = MALLOC(Reservation*, 1)))
	{
		NOT_ENOUGH_MEMORY;
		exit(0);
	}

	//Allocating memory for the first reservation
	if (!(*reservationDatabase[0] = MALLOC(Reservation, 1)))
	{
		NOT_ENOUGH_MEMORY;
		exit(0);
	}

	//Initialization for the room matrix
	for (int i = 0; i < hotel->numOfFloors; i++)
	{
		for (int j = 0; j < hotel->numOfRooms; j++)
		{
			hotel->rooms[i*hotel->numOfRooms + j].isTaken = FALSE;
			hotel->rooms[i*hotel->numOfRooms + j].numOfRegistered = 0;
			hotel->rooms[i*hotel->numOfRooms + j].numOfRegisteredToBreakfast = 0;
		}
	}
}//end of function

void showHotelStatus(const Reservation ** database, int size, const Hotel * hotel)
{
	printf("\nHotel Status:\n");
	for (int i = 0; i < hotel->numOfFloors; i++)
	{
		for (int j = 0; j < hotel->numOfRooms; j++)
		{
			printf("\nRoom number %d:\n\t", CALCULATE_ROOM_NUMBER(i + 1, j));
			showRoom(database, size, &(hotel->rooms[i*hotel->numOfRooms + j]));
		}
	}
}//end of function

void checkIn(Customer*** customerDatabase, int  * sizeOfCustomerDatabase, Reservation*** reservationDatabase,
	int * sizeOfReservationDatabase, const Hotel * hotel)
{
	int numOfCustomers, numOfCustomersForBreakfast, index;
	char choice = 0;

	int floor = 0, room = 0;
	//searching the first available room, the function returns -1 if no room is available
	room = searchRoom(hotel); //returns the potentially room to be occupide
	if (room == -1)
	{
		printf("\nNo room available, come next time!\n");
		return; //if no room is available, there's no point to check in
	}

	printf("\nShowing the customers of the hotel: \n");
	showCustomerDatabase(*customerDatabase, *sizeOfCustomerDatabase);

	//If we have at least 1 customer in the database, we want to give the user the option to choose a customer
	if (*sizeOfCustomerDatabase)
	{
		//I chose to search the customer by the ID, because it is unique, while the name is not.
		printf("\nPlease choose a number of a Customer: \n");
		scanf("%d", &index);
		//Indexes of the customers starting at 0
		index--;
	}
	//If we don't have any customers, than the index of the customer to check in should be 0
	else
		index = 0;

	//Negative indexes are invalid, we terminate the function in that case.
	if (index < 0)
	{
		printf("\nindex of customer must be above 0\n");
		return;
	}
	//cleans the buffer 
	CLEAR;

	//If the index the user entered is not an index of a customer, we let the user the option to add a new customer to the database
	if (index >= *sizeOfCustomerDatabase)
	{
		if (index > 0)
			printf("\nThe customer you chose is not in the database, would you like to add him? Y/N\n");
		//We reach here only if there's no customers and we initiated the index to 0
		else if (index == 0)
			printf("\nDo you want to add a new customer to the database? Y/N\n");
		do
		{
			//getting the choice from the user and checking if its valid
			choice = getchar();
			if (CHECK_CHAR(choice))
			{
				printf("\nI didn't understand you, would you like to add him? Y/N\n");
				CLEAR;
			}
		} while (CHECK_CHAR(choice));

		//Adding a customer if the user wants to
		if (choice == 'Y' || choice == 'y')
		{
			addCustomer(customerDatabase, sizeOfCustomerDatabase);
			//the index of the new added customer is the size of the customer database before we increased it in the addCustomer function
			index = *sizeOfCustomerDatabase - 1;
		}
		else
		{
			printf("\nGood day!\n");
			return;
		}
	}

	printf("\nYou chose the customer %d, %s\n", (*customerDatabase)[index]->ID, (*customerDatabase)[index]->name);

	//Number of customers in 1 room can be up to 4 people
	printf("\nPlease enter the number of customers (0 < customers <= %d)\n", MAX_IN_ROOM);
	int result = 0;
	do
	{
		//Getting the number of customers and checking if its valid, we let the user enter it again if its invalid,
		//or exiting the program by pressing -2
		result = scanf("%d", &numOfCustomers);
		if (numOfCustomers == -2)
			exit(0);
		if (result < 1 || numOfCustomers == EOF)
		{
			printf("\nInvalid number, please try again.\n");
			CLEAR;
		}
		else if (CHECK_CUSTOMERS(numOfCustomers))
			printf("\nThere are no rooms with %d beds, please try again (press -2 to exit)\n", numOfCustomers);
	} while (result < 1 || numOfCustomers == EOF || CHECK_CUSTOMERS(numOfCustomers));

	//Number of customers for breakfast can be up to the number of customers in the room
	printf("\nPlease enter the numer of customers for breakfast (0<=customers<=%d)\n", MAX_IN_ROOM);
	do
	{
		//validating the number of customers and letting the user enter it again if its invalid
		result = scanf("%d", &numOfCustomersForBreakfast);
		if (numOfCustomersForBreakfast == -2)
			exit(0);
		if (result < 1 || numOfCustomersForBreakfast == EOF)
		{
			printf("\nInvalid number, please try again.\n");
			CLEAR;
		}
		else if (CHECK_CUSTOMERS_FOR_BREAKFAST(numOfCustomersForBreakfast, numOfCustomers))
			printf("Either the number of customers you enterd is invalid or you enterd more customers than the registerd customers, please try again (perss -2 to exit):\n");
	} while (result < 1 || numOfCustomersForBreakfast == EOF || CHECK_CUSTOMERS_FOR_BREAKFAST(numOfCustomersForBreakfast, numOfCustomers));

	//if we found a room, we add a reservation to the reservation database and changing the occupation of the room
	printf("\nroom number %d is available, Enjoy!\n", room);
	addReservationAndRoom(index, room, numOfCustomers, numOfCustomersForBreakfast,
		hotel, *customerDatabase, reservationDatabase, sizeOfReservationDatabase);
}//end of function


void checkOut(Reservation** reservationDatabase, int sizeOfReservationDatabase, const Hotel* hotel, int room)
{
	//We are getting a 3 digit room, so we turn it into 1 digit to search in the hotel->room matrix
	int roomNumber = GET_ONE_DIGIT_ROOM(room, hotel->numOfRooms);

	//if its not even taken, we have nothing to check out
	if (!hotel->rooms[roomNumber].isTaken)
	{
		printf("This room is not taken!\n");
		return;
	}
	//changing the occupation of the room, making it available with no customers
	else
	{
		hotel->rooms[roomNumber].isTaken = FALSE;
		hotel->rooms[roomNumber].numOfRegistered = 0;
		hotel->rooms[roomNumber].numOfRegisteredToBreakfast = 0;
	}

	//Last thing - we want to mark the reservation of this room as checked out
	for (int i = 0; i < sizeOfReservationDatabase; i++)
	{
		if (reservationDatabase[i]->room == &hotel->rooms[roomNumber])
		{
			//1 room can be reserved to many customers, so if there's a reservation with this room that has been checked out already,
			//we skip it to find the right reservation
			if (reservationDatabase[i]->isCheckedOut)
				continue;
			reservationDatabase[i]->isCheckedOut = TRUE;
			break;
		}
	}
	printf("\nThank you for staying in Hotel Califronia!\n");
}//end of function

void freeHotelRooms(Hotel * hotel)
{
	for (int i = 0; i < hotel->numOfFloors; i++)
		for (int j = 0; j < hotel->numOfRooms; j++)
			free(&hotel->rooms[i*hotel->numOfRooms + j]);
}

void showMenu()
{
	int sizeOfCustomers = 0, sizeOfReservations = 0;
	Hotel hotel;
	//Array of POINTERS to CUSTOMERS
	Customer ** customerDatabase = NULL;
	//Array of POINTERS to RESERVATIONS
	Reservation ** reservationDatabase = NULL;
	Init(&hotel, &customerDatabase, &reservationDatabase);
	int choice;
	do
	{
		printf("\n*********************************\n");
		printf(" WELCOME TO THE HOTEL CALIFORNIA!");
		printf("\n*********************************\n");
		printf("What would you like to do? \n");

		printf("\n"
			"1 - show hotel status\n"
			"2 - add a customer\n"
			"3 - check In\n"
			"4 - check out\n"
			"5 - see info about a room\n"
			"6 - make all names with capital letters\n"
			"7 - get all customers with a specific string\n"
			"-1 - Exit\n");

		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			showHotelStatus(reservationDatabase, sizeOfReservations, &hotel);
			break;
		case 2:
			addCustomer(&customerDatabase, &sizeOfCustomers);
			break;
		case 3:
			checkIn(&customerDatabase, &sizeOfCustomers, &reservationDatabase, &sizeOfReservations, &hotel);
			break;
		case 4:
		{
			int room = 0;
			printf("choose a room to check out: \n");
			int result = 0;
			do
			{
				result = scanf("%d", &room);
				if (result < 1 || room == EOF)
				{
					printf("\nInvalid number, please try again.\n");
					CLEAR;
				}
			} while (result < 1 || room == EOF);

			if (CHECK_IF_ROOM_EXIST(room, hotel.numOfFloors, hotel.numOfRooms))
			{
				printf("there's no such room");
				break;
			}
			checkOut(reservationDatabase, sizeOfReservations, &hotel, room);
			break;
		}
		case 5:
		{
			int room = 0;
			printf("\nwhat room you want to see? \n");
			int result = 0;
			do
			{
				result = scanf("%d", &room);
				if (result < 1 || room == EOF)
				{
					printf("\nInvalid number, please try again.\n");
					CLEAR;
				}
			} while (result < 1 || room == EOF);

			int roomNumber = GET_ONE_DIGIT_ROOM(room, hotel.numOfRooms);
			if (CHECK_IF_ROOM_EXIST(room, hotel.numOfFloors, hotel.numOfRooms))
			{
				printf("there's no such room");
				break;
			}
			showRoom(reservationDatabase, sizeOfReservations, &hotel.rooms[roomNumber]);
			break;
		}
		case 6:
			upperCaseCustomers(customerDatabase, sizeOfCustomers);
			printf("\nDone!\n");
			break;
		case 7:
		{
			int sizeOfArray = 0;
			Customer * customersWithSubString = NULL;

			//Allocating new array for the customers
			if (!(customersWithSubString = MALLOC(Customer, sizeOfCustomers)))
			{
				NOT_ENOUGH_MEMORY;
				exit(0);
			}

			char subString[MAX_WORD_LENGTH];
			printf("Enter a substring: \n");
			//cleaning the buffer
			CLEAR;
			//reading string up until '\n'
			scanf("%[^\n]s", subString);

			//the function returns the actual size of the array
			sizeOfArray = getAllCustomersWithSubString(subString, customerDatabase, sizeOfCustomers, sizeOfArray, &customersWithSubString);
			if (!sizeOfArray)
				printf("No customers with the substring %s", subString);
			else
			{
				printf("The customers are: \n");
				for (int i = 0; i < sizeOfArray; i++)
					PRINT_CUSTOMER(i + 1, customersWithSubString[i]);
			}

			//freeing the array
			free(customersWithSubString);
			break;
		}
		default:
			printf("Good bye!\n");
			return;
		}
	} while (choice != -1);

	//freeing the allocated memory
	freeReservationDatabase(&reservationDatabase, sizeOfReservations);
	freeCustomerDatabase(&customerDatabase, sizeOfCustomers);
	freeHotelRooms(&hotel);
}//end of function
