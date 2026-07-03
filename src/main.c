#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAP_SIZE 15

char map[MAP_SIZE][MAP_SIZE]; 



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



void placeRandomWalls()
{ // Places random walls excluding the border walls and the starting position of players.

	int count = 0;

	while (count < 30)
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


int main ()
{ // Main function that initializes and prints the map.

	printf("Quest for the Lost Treasure\n");
	initializeMap();
	placeRandomWalls();
	printMap();

	return 0;

}    