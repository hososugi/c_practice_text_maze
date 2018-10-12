#include "pch.h"

void roomLook(const struct Room* self)
{
	printf("You are in %s.\n%s\n", self->name, self->description);
}

void roomGo(const struct Room* self, const char *direction)
{
	printf("Do the roomGo function.\n");
}