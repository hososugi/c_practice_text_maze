#include "pch.h"

void playerLook(const struct Player* self)
{
	printf("You are %s. %d and level %d.\n", self->name, self->gender, self->level);
}

void playerGo(struct Player* self, char* direction)
{
	if(direction == NULL)
	{
		// Get all available directions.
		char directionsString[37] = {'\0'};
		int directionCount = 0;
		char* exitText;

		// Loop through each possible direction to count and build direction list.
		for(int i = 0; i < 6; i++)
		{
			if(self->room->neighbors[i])
			{
				// No hashes, so we'll do this for now for each direction.
				if (i == 0)
					strcat(directionsString, "north, ");
				else if (i == 1)
					strcat(directionsString, "east, ");
				else if (i == 2)
					strcat(directionsString, "south, ");
				else if (i == 3)
					strcat(directionsString, "west, ");
				else if (i == 4)
					strcat(directionsString, "up, ");
				else if (i == 5)
					strcat(directionsString, "down, ");

				directionCount++;
			}
		}

		// Determine the correct plurality of exit based on how many exists.
		if (directionCount == 1)
			exitText = "exit";
		else
			exitText = "exists";

		// Check if there are 0 or more exits.
		if(directionCount == 0)
			printf("Go where? You look around don't see any exits.\n");
		else
		{
			// Remove the trailing ', ' at the end.
			directionsString[strlen(directionsString) - 2] = '\0';
			printf("Go where? You look around and only see %d %s: %s.\n", directionCount, exitText, directionsString);
		}
	}
	else
	{
		//printf("You are trying to go %s.\n", direction);
		struct Room* newRoom = { NULL };

		// Check if the room has an exit.
		if (strcmp(direction, "north") == 0)
		{
			if(self->room->neighbors[north] != NULL)
				newRoom = self->room->neighbors[north];
		}
		else if(strcmp(direction, "east") == 0)
		{
			if(self->room->neighbors[east] != NULL)
				newRoom = self->room->neighbors[east];
		}
		else if(strcmp(direction, "south") == 0)
		{
			if (self->room->neighbors[south] != NULL)
				newRoom = self->room->neighbors[south];
		}
		else if(strcmp(direction, "west") == 0)
		{
			if(self->room->neighbors[west] != NULL)
				newRoom = self->room->neighbors[west];
		}

		if(newRoom != NULL)
		{
			self->room = newRoom;
			printf("You went %s.\n", direction);
			self->room->look(self->room);
		}
		else
			printf("You can't go %s.\n", direction);
		
	}
}