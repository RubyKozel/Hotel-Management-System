/*************************
	Reservation struct header
**************************/

#ifndef __RESERVATION_H
#define __RESERVATION_H

struct reservation
{
	Customer * customer;
	int numOfCustomers;
	int numOfCustomersForBreakfast;
	Room * room;
	int isCheckedOut;
};

/*The function gets a reservation components, the reservation array points,
the arrays' size pointer and the customer database and adds a new reservation to the database, it than increases the size of the reservation array by 1*/
void addReservationAndRoom(int, int, int, int, const Hotel*, Customer **, Reservation ***, int *);

/*frees the reservation database*/
void freeReservationDatabase(Reservation ***, int);

#endif
