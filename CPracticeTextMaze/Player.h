#ifndef PLAYER_H
#define PLAYER_H
#include "pch.h"

void playerLook(const struct Player* self);
void playerGo(struct Player* self, char* direction);

struct Player
{
	char name[NAME_SIZE];
	int gender;
	int level;
	struct Room* room;
	void (*look)(const struct Player*);
	void (*go)(const struct Player*);
};
#endif