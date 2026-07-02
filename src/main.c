#include <stdio.h>

#define MAP_SIZE 15

char map[MAP_SIZE][MAP_SIZE]; 


void initializeMap(){  // Initializes the 15x15 map and places border walls.

	int i, j;

	for (i = 0; i < MAP_SIZE; i++){
		for (j = 0; j < MAP_SIZE; j++){
			if (i == 0 || i == MAP_SIZE - 1 || j == 0 || j == MAP_SIZE - 1){ // Places border walls represented by '#' character.
				map[i][j] = '#';
			}
			else {
				map[i][j] = ' ';
			}
		}
	}
}


void printMap(){  // Prints the 15X15 map to the console as output.
	
	int i, j;

	for (i = 0; i < MAP_SIZE; i++){
		for (j = 0; j < MAP_SIZE; j++){
			printf("%c ", map[i][j]);
		}
	printf("\n");
	}
}	


int main (){ // Main function that initializes and prints the map.

	printf("Quest for the Lost Treasure\n");
	initializeMap();
	printMap();

	return 0;
}    