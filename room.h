/**********************
	Room struct header
***********************/

#ifndef __ROOM_H
#define __ROOM_H

struct room
{
	int isTaken;
	int numOfRegistered;
	int numOfRegisteredToBreakfast;
};

/*The function gets a pointer to the hotel and returns the first not taken room in it.
If the hotel has no empty rooms, it returns -1*/
int searchRoom(const Hotel*);

/*The function gets the reservation database, its size and a room pointer.
It prints the data about the recieved room, including the customer that reserved the room*/
void showRoom(const Reservation **, int, Room *);

#endif
