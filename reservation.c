#include "defnmac.h"

void addReservationAndRoom(int index, int room, int numOfCustomers, int numOfCustomersForBreakfast,
	const Hotel* hotel, Customer ** customerDatabase, Reservation *** reservationDatabase, int * sizeOfReservationDatabase)
{
	//Changing the occupation of the selected room
	int roomNumber = GET_ONE_DIGIT_ROOM(room, hotel->numOfRooms);
	hotel->rooms[roomNumber].isTaken = TRUE;
	hotel->rooms[roomNumber].numOfRegistered = numOfCustomers;
	hotel->rooms[roomNumber].numOfRegisteredToBreakfast = numOfCustomersForBreakfast;

	//Allocating memory for a new reservation
	Reservation * newReservation = NULL;
	if (!(newReservation = MALLOC(Reservation, 1)))
	{
		NOT_ENOUGH_MEMORY;
		exit(0);
	}

	//Filling the reservation with the info
	newReservation->customer = customerDatabase[index];
	newReservation->numOfCustomers = numOfCustomers;
	newReservation->numOfCustomersForBreakfast = numOfCustomersForBreakfast;
	newReservation->room = &hotel->rooms[roomNumber];
	newReservation->isCheckedOut = FALSE;

	//Adding the reservation to the reservation database
	(*reservationDatabase)[(*sizeOfReservationDatabase)++] = newReservation;

	//Reallocating the reservation database, increasing the size of the array by 1 pointer
	Reservation ** tmp = REALLOC(Reservation*, *reservationDatabase, *sizeOfReservationDatabase + 1);
	if (!tmp)
	{
		NOT_ENOUGH_MEMORY;
		exit(0);
	}
	*reservationDatabase = tmp;
}//end of function

void freeReservationDatabase(Reservation *** database, int size)
{
	for (int i = 0; i < size; i++)
		free((*database)[i]);
	free(*database);
}
