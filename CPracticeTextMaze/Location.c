#include <stdio.h>
#include <string.h>

struct Location {
	const char *description;
	const char *tag;
}
locations[] = {
   {"An open field", "field"},
   {"A little cave", "cave"}
};

#define numberOfLocations (sizeof(locations) / sizeof(*locations))

static unsigned locationOfPlayer = 0;

void actionLook(const char *noun) {
	printf("You are in %s.\n", locations[locationOfPlayer].description);
}

void actionGo(const char *noun) {
	unsigned i;

	for(i = 0; i < numberOfLocations; i++) {
		if (noun != NULL && strcmp(noun, locations[i].tag) == 0) {
			if (i == locationOfPlayer) {
				printf("You are already there.\n");
			}
			else {
				printf("OK.\n");
				locationOfPlayer = i;
				actionLook(NULL);
			}

			return;
		}
	}
	printf("I don't understand where you want to go.\n");
}