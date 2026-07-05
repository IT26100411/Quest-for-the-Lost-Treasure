#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAP_SIZE 15
#define HIDDEN_TRAPS 10
#define TREASURE_COUNT 12
#define WALL_COUNT 30
#define HEALTH_COUNT 5
#define KEY_COUNT 3
#define DOOR_COUNT 3
#define HIDDEN_TRAP_COUNT 10
#define EMPTY ' '

char map[MAP_SIZE][MAP_SIZE]; 
int hiddenTraps[HIDDEN_TRAPS][HIDDEN_TRAPS]; // 2D array to store the positions of hidden traps on the map.


typedef struct 

{
	char playerName[50];
	int row;
	int col;	
	int playerHealth;
	int playerScore;
	int keysCollected;
	char playerSymbol;

} player_t;


player_t players[2]; // Array to hold two players.


void placePlayers()

{
    
    // PLAYER 1
    players[0].playerSymbol = '1';
    players[0].playerHealth = 100;
    players[0].playerScore = 0;
    players[0].keysCollected = 0;

    
    int placed = 0;
    int attempts = 0;


while (attempts < 1000)

{
    players[0].row = rand() % MAP_SIZE;
    players[0].col = rand() % MAP_SIZE;

    if (map[players[0].row][players[0].col] == EMPTY)

    {
        placed = 1;
        break;
    }

    attempts++;
}


if (!placed)

{
    players[0].row = 1;
    players[0].col = 1;
}



    // PLAYER 2
players[1].playerSymbol = '2';
players[1].playerHealth = 100;
players[1].playerScore = 0;
players[1].keysCollected = 0;

int placed2 = 0;
int attempts2 = 0;

while (attempts2 < 1000)
{
    players[1].row = rand() % MAP_SIZE;
    players[1].col = rand() % MAP_SIZE;

    if (map[players[1].row][players[1].col] == EMPTY &&
        !(players[1].row == players[0].row && players[1].col == players[0].col))
    {
        placed2 = 1;
        break;
    }

    attempts2++;
}

if (!placed2)
{
    players[1].row = 1;
    players[1].col = 2;
}

map[players[0].row][players[0].col] = players[0].playerSymbol;
map[players[1].row][players[1].col] = players[1].playerSymbol;

}



int isValidMove(int x, int y)

{
    if (x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE)
        return 0;

    if (map[x][y] == '#')
        return 0;

	if (map[x][y] == '1' || map[x][y] == '2')
        return 0;

	return 1;

}



void movePlayer(int p)


{
	char move;
	

	printf("Player %c move (w/a/s/d)", players[p].playerSymbol);
	scanf(" %c", &move);

	int newRow = players[p].row;
	int newCol = players[p].col;

	char tile;

	if (move == 'w') newRow--;
	if (move == 'a') newCol--;
	if (move == 's') newRow++;
	if (move == 'd') newCol++;

	if (isValidMove(newRow, newCol))

{
	 tile = map[newRow][newCol];

     map[players[p].row][players[p].col] = EMPTY;
 
     players[p].row = newRow;
     players[p].col = newCol;

     map[newRow][newCol] = players[p].playerSymbol;

	 printf("Tile entered: %c\n", tile);

}

     else

{

     printf("Invalid move!\n");

}


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

				map[i][j] = EMPTY;

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
	
		if (map[x][y] == EMPTY) 
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

		if (map[x][y] == EMPTY)
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

		if (map[x][y] == EMPTY)

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

		if (map[x][y] == EMPTY )

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

		if (map[x][y] == EMPTY )

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

		if (map[x][y] == EMPTY && hiddenTraps[x][y] == 0)

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

srand(time(NULL));

initializeMap();
initializeHiddenTraps();

placeRandomWalls();

placeTreasures();
placeHealthPacks();
placeKeys();
placeDoors();

placeHiddenTraps();
placePlayers();

int currentPlayer = 0;

while (1)
{
    printMap();
    movePlayer(currentPlayer);

    currentPlayer = 1 - currentPlayer;
}

}