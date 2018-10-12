#ifndef ROOM_H
#define ROOM_H
#include "pch.h"

void roomLook(const struct Room* self);
void roomGo(const struct Room* self, const char* noun);

enum Directions
{
	north = 0,
	east,
	south,
	west,
	up,
	down
};

struct Room
{
	int id;
	char name[NAME_SIZE];
	char description[DESCRIPTION_SIZE];
	void(*look)(const struct Room*);
	struct Room* neighbors[6];
};
#endif