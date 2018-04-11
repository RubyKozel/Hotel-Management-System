#include "defnmac.h"

//Searching a room until one of them is not taken, if all are taken - the function returns -1
int searchRoom(const Hotel * hotel)
{
	for (int i = 0; i <  hotel->numOfFloors; i++)
	{
		for (int j = 0; j < hotel->numOfRooms; j++)
		{
			int currentRoom = i*hotel->numOfRooms + j;
			if (!hotel->rooms[currentRoom].isTaken)
				return CALCULATE_ROOM_NUMBER(i + 1, j);
		}
	}
	return -1;
}//end of function

void showRoom(const Reservation ** database, int size, Room * room)
{
	if (room->isTaken)
	{
		printf("Room's taken\n\t");
		printf("The room is registered under: \n\t");
		int i;
		for (i = 0; i < size; i++)
			if ((database[i]->room == room) && !database[i]->isCheckedOut)
				break;
		PRINT_POINTED_CUSTOMER(1, (database[i]->customer));
		printf("There are %d people registered and %d of them are registerd to breakfast\n", room->numOfRegistered, room->numOfRegisteredToBreakfast);
	}
	else
		printf("Room's not taken\n");
}//end of function
