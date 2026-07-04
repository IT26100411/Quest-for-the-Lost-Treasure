#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAP_SIZE 15
#define TREASURE_COUNT 12
#define WALL_COUNT 30
#define HEALTH_COUNT 5
#define KEY_COUNT 3
#define DOOR_COUNT 3
#define HIDDEN_TRAP_COUNT 10

char map[MAP_SIZE][MAP_SIZE]; 
int hiddenTraps[MAP_SIZE][MAP_SIZE]; // 2D array to store the positions of hidden traps on the map.


typedef struct 
{
	char playerName[50];
	int row;
	int col;	
	int playerHealth;
	int playerScore;
	int keysCollected;
	int attempts;
	char playerSymbol;

} player_t;


player_t players[2]; // Array to hold two players.


void placePlayers()
{
    int attempts;

    // PLAYER 1
    players[0].playerSymbol = '1';
    players[0].playerHealth = 100;
    players[0].playerScore = 0;
    players[0].keysCollected = 0;

    attempts = 0;
    do {
        players[0].row = rand() % MAP_SIZE;
        players[0].col = rand() % MAP_SIZE;
        attempts++;
    }
    while(map[players[0].row][players[0].col] != ' ' && attempts < 1000);

    map[players[0].row][players[0].col] = '1';

    // PLAYER 2
    players[1].playerSymbol = '2';
    players[1].playerHealth = 100;
    players[1].playerScore = 0;
    players[1].keysCollected = 0;

    attempts = 0;
    do {
        players[1].row = rand() % MAP_SIZE;
        players[1].col = rand() % MAP_SIZE;
        attempts++;
    }
    while(
        map[players[1].row][players[1].col] != ' ' ||
        (players[1].row == players[0].row && players[1].col == players[0].col)
        && attempts < 1000
    );

    map[players[1].row][players[1].col] = '2';

}



int isValidMove(int x, int y)
{
    if (x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE)
        return 0;

    if (map[x][y] == '#')
        return 0;

    return 1;
}



void initializeMap()

{  // Initializes the 15x15 map and places border walls.

	int i, j;

	for (i = 0; i < MAP_SIZE; i++)
	{
		for (j = 0; j < MAP_SIZE; j++){
			if (i == 0 || i == MAP_SIZE - 1 || j == 0 || j == MAP_SIZE - 1)
			{ // Places border walls represented by '#' character.

				map[i][j] = '#';

			}

			else {

				map[i][j] = ' ';

			}

		}

	}

}



void initializeHiddenTraps()

{ // Initializes the hidden traps on the map.

	int i, j;

	for (i = 0; i < MAP_SIZE; i++)
	{
		for (j = 0; j < MAP_SIZE; j++)
		{
			hiddenTraps[i][j] = 0; // Sets all positions to 0, indicating no traps.

		}
	}

}



void placeRandomWalls()

{ // Places random walls excluding the border walls .

	int count = 0;

	while (count < WALL_COUNT)
	{
		
		int x = rand() % MAP_SIZE;
		int y = rand() % MAP_SIZE;

		if (x == 0 || x == MAP_SIZE - 1 || y == 0 || y == MAP_SIZE - 1) 
		{

			continue;

		}
	
		if (map[x][y] == ' ') 
		{ // Places a wall represented by '#' character if the position is empty.

			map[x][y] = '#';
			count++;

		}

	}

}



void placeTreasures()

{ // Places treasures represented by 'T' character in random empty positions.

	int attempts = 0;
	int count = 0;
	

	while (count < TREASURE_COUNT && attempts < TREASURE_COUNT * MAP_SIZE * MAP_SIZE) 

	{
		int x = rand() % MAP_SIZE;
		int y = rand() % MAP_SIZE;

		if (map[x][y] == ' ')
		{ // Places the treasure if the space is empty.

			map[x][y] = 'T';
			count++; 
			
		}
		attempts++; // Prevents infinite loops in case of a full map.
	}
	
}


void placeHealthPacks()

{ // Places health packs represented by 'H' character in random empty positions.

	int attempts = 0;
	int count = 0;

	while (count < HEALTH_COUNT && attempts < HEALTH_COUNT * MAP_SIZE * MAP_SIZE)

	{

		int x = rand() % MAP_SIZE;
		int y = rand() % MAP_SIZE;

		if (map[x][y] == ' ')

		{ // Places the health pack if the space is empty.

			map[x][y] = 'H';
			count++;

		}
		attempts++; // Prevents infinite loops in case of a full map.
	}

}




void placeKeys()

{ // Places keys represented by 'K' character in random empty positions.

	int attempts = 0;
	int count = 0;

	while (count < KEY_COUNT && attempts < KEY_COUNT * MAP_SIZE * MAP_SIZE)

	{

		int x = rand() % MAP_SIZE;
		int y = rand() % MAP_SIZE;

		if (map[x][y] == ' ')

		{ // Places Keys if the space is empty.
			
			map[x][y] = 'K';
			count++;


		}
		attempts++;
	}
}



void placeDoors()

{ // Places doors represented by 'D' character in random empty positions.

	int attempts = 0;
	int count = 0;

	while (count < DOOR_COUNT && attempts < DOOR_COUNT * MAP_SIZE * MAP_SIZE)

	{

		int x = rand() % MAP_SIZE;
		int y = rand() % MAP_SIZE;

		if (map[x][y] == ' ')

		{ // Places Doors if the space is empty.

			map[x][y] = 'D';
			count++;

		}
		attempts++;
	}
}


void placeHiddenTraps()

{ // Places hidden traps that are not visible on the map but can affect the player if they step on them.

	int attempts = 0;
	int count = 0;

	while (count < HIDDEN_TRAP_COUNT && attempts < HIDDEN_TRAP_COUNT * MAP_SIZE * MAP_SIZE)

	{

		int x = rand() % MAP_SIZE;
		int y = rand() % MAP_SIZE;

		if (map[x][y] == ' ' && hiddenTraps[x][y] == 0)

		{ // Places Hidden Traps if the space is empty and no trap is already placed.

			hiddenTraps[x][y] = 1; // Marks the position as having a hidden trap.
			count++;

		}
		attempts++;
	}
}



void printMap()

{  // Prints the 15X15 map to the console as output.
	
	int i, j;

	for (i = 0; i < MAP_SIZE; i++)
	{
		for (j = 0; j < MAP_SIZE; j++)
		{
			printf("%c ", map[i][j]);
		}
	printf("\n");
	}

}

int main()

{
	srand(time(NULL)); // Seeds the random number generator with the current time.

	initializeMap(); // Initializes the map with border walls.
	placeRandomWalls(); // Places random walls on the map.
	placeTreasures(); // Places treasures on the map.
	placeHealthPacks(); // Places health packs on the map.
	placeKeys(); // Places keys on the map.
	placeDoors(); // Places doors on the map.
	placeHiddenTraps(); // Places hidden traps on the map.
	placePlayers(); // Places the player on the map.

	printMap(); // Prints the final map to the console.

	return 0;
}