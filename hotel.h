/**********************
	Hotel struct header
***********************/

#ifndef __HOTEL_H
#define __HOTEL_H
struct room;

struct hotel
{
	int numOfFloors;
	int numOfRooms;
	Room * rooms;
};

/*The function gets a Hotel pointer, Customer database pointer and Reservation database pointer and initialize them*/
void Init(Hotel *, Customer***, Reservation***);

/*The functions gets a reservation database, its' size and a pointer to a Hotel and prints the status of the hotel*/
void showHotelStatus(const Reservation **, int, const Hotel *);

/*The function gets the customer array database pointer, the reservation database pointer,
their sizes and the hotel pointer and checks in a new customer to the hotel.
If the customer does not exist in the database, it lets the user the option to add a new customer to the database*/
void checkIn(Customer***, int *, Reservation***, int *, const Hotel *);

/*The function gets the reservation database, its size, a number of a room and a pointer to the hotel and chceks out the reservation of the recieved room*/
void checkOut(Reservation**, int, const Hotel*, int room);

/*Frees the hotel rooms*/
void freeHotelRooms(Hotel *);

/*The function shows the menu of the hotel*/
void showMenu();

#endif
