#include "pch.h"

// Definte the global variables.
static char input[100];
char *next_token;

_Bool playing      = 1;
rsize_t strmax     = sizeof input;
const char *delims = " \t\n";
struct Player player;
struct Room rooms[2];

// Declare the functions.
int mainMenu();
int startNewGame();
int playGame();
char* getInput(char* outputString);

int main(int argc, char *argv[])
{
	int status = 1;

	// Show the main menu and decide what to do based on the input.
	switch(mainMenu())
	{
		case START_NEW_GAME:
			status = startNewGame();
			break;
		case LOAD_GAME:
			status = playGame();
			break;
		case QUIT_GAME:
			printf("Thank you for playing. Bye.");
			break;
		default:
			printf("Couldn't understand your selection. Exiting.");
			break;
	}

	return status;
}

char* readTitle()
{
	char* filename = "./Config/ascii_title2.txt";
	FILE* filePointer;
	char* buffer = 0;
	long length;
	int i = 0;

	filePointer = fopen(filename, "rb");

	if (filePointer == NULL)
	{
		printf("ERROR: cannot open title file %s.\n", filename);
		exit(0);
	}
	else
	{
		fseek(filePointer, 0, SEEK_END);
		length = ftell(filePointer);

		fseek(filePointer, 0, SEEK_SET);
		buffer = malloc(length + 1);

		if (buffer)
		{
			fread(buffer, 1, length, filePointer);
		}

		buffer[length] = '\0';

		fclose(filePointer);
	}

	return buffer;
}

int mainMenu()
{
	// Print out the menu.
	char* title = readTitle();
	printf("%s\n", title);
	printf("Welcome!\n");
	printf("%d) Play new game\n", START_NEW_GAME);
	printf("%d) Quit\n", QUIT_GAME);

	// Get the player input.
	char menuInputString[NAME_SIZE] = {'\0'};
	char* endPointer;

	printf(">");
	getInput(menuInputString);

	return strtol(menuInputString, &endPointer, 10);
}

int startNewGame()
{
	// Set up the rooms.
	rooms[0] = (struct Room) { 0, "Your Bedroom", "A description of your bedroom", roomLook, {NULL} };
	rooms[1] = (struct Room) { 1, "The Living room", "a description of the living room", roomLook, {NULL} };

	rooms[0].look = roomLook;
	rooms[1].look = roomLook;

	// Set up the room neighbors.
	rooms[0].neighbors[east] = &rooms[1];
	rooms[1].neighbors[west] = &rooms[0];

	struct Room* startRoom = &rooms[0];
	//startRoom.neighbors = (struct Room*) malloc(sizeof(struct Room) * 6);

	// Create the player.
	char playerName[NAME_SIZE] = {'\0'};
	printf("What is your name?\n>");

	getInput(playerName);

	player = (struct Player) { playerName, 1, 1, startRoom, playerLook, playerGo };
	player.room = startRoom;
	player.look = playerLook;
	player.go   = playerGo;

	return playGame();
}

int playGame()
{
	int quitCondition = 0;
	int status = 1;
	char input[INPUT_SIZE];
	char* token;
	char* tokens[10];
	int tokenIndex = 0;
	char* action = malloc(INPUT_SIZE);

	// Show the starting room.
	player.room->look(player.room);

	// Game loop
	while(!quitCondition)
	{
		//printf("Game Loop.\n");

		// Reset the input string and get it again.
		memset(input, '\0', sizeof(input));
		memset(action, '\0', sizeof(action));
		memset(tokens, '\0', sizeof tokens);
		tokenIndex = 0;

		printf(">");

		getInput(input);

		if(input != "")
		{
			// Parse the input here.
			tokens[tokenIndex] = strtok(input, " ");

			while(tokens[tokenIndex] != NULL)
			{
				tokens[++tokenIndex] = strtok(NULL, " ");
			}

			// Attempt the actions.
			action = tokens[0];

			if (strcmp(action, "look") == 0)
			{
				player.room->look(player.room);
			}
			else if (strcmp(action, "go") == 0)
			{
				if(tokenIndex > 1)
					player.go(&player, tokens[1]);
				else
					player.go(&player, NULL);
			}
			else if(strcmp(action, "quit") == 0
				 || strcmp(action, "exit") == 0)
			{
				printf("Thank you for playing. Bye.\n");
				quitCondition = 1;
			}
			else
			{
				printf("Couldn't understand what you want to do.\n");
			}
		}

	}	

	return status;
}

char* getInput(char* outputString)
{
	char* input = malloc(INPUT_SIZE + 1);

	fgets(input, INPUT_SIZE, stdin);
	if((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
		input[strlen(input) - 1] = '\0';

	strcpy(outputString, input);

	free(input);

	return outputString;
}