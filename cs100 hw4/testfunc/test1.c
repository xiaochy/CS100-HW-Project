#include<stdio.h>
#include<stdlib.h>
typedef enum gameState { losing, onGoing, winning } GameState;
typedef struct game {
	char** grid;     // a 2-dimensional array of characters to display the game;
	int rows;        // number of rows of the grid;
	int columns;     // number of columns of the grid;
	int foodCount;   // number of remaining food in the game;
	int score;       // current score;
	GameState state; // the state of the game, one of losing, onGoing, or winning.
} Game;
int main(void)
{
	//int m, n;
	//int i,j;
	//int** arr;
	//scanf_s("%d %d", &m, &n);
	//arr = (int**)malloc(m * sizeof(int*));
	//for (i = 0; i < m; i++) {
	//	arr[i] = (int*)malloc(n * sizeof(int));
	//}
	//for (i = 0; i < m; i++) {
	//	for (j = 0; j < n; j++) {
	//		arr[i][j] = j;
	//		printf("%d\n", arr[i][j]);
	//	}
	//}
	//for (i = 0; i < m; i++) {
	//	free(arr[i]);
	//}
	//free(arr);

	//Game game_1;
	//game_1.rows = 3;
	//game_1.columns = 5;
	//game_1.foodCount = 0;
	//game_1.score = 0;
	//game_1.state = 1;
	//printf("%d %d %d %d %d\n", game_1.rows, game_1.columns, game_1.foodCount, game_1.score, game_1.state,game_1.state);
	//char** arr;
	//int i, j;
	//arr = (char**)malloc(game_1.rows * sizeof(char*));
	//for (i = 0; i < game_1.rows; i++) {
	//	arr[i] = (char*)malloc(game_1.columns * sizeof(char));
	//}
	//for (i = 0; i < game_1.rows; i++) {
	//	for (j = 0; j < game_1.columns; j++) {
	//		arr[i][j] = '1';
	//	}
	//}
	//game_1.grid = arr;
	//for (i = 0; i < game_1.rows; i++) {
	//	for (j = 0; j < game_1.columns; j++) {
	//		putchar(game_1.grid[i][j]);
	//		putchar('\n');
	//	}
	//}
	//for (i = 0; i < game_1.rows; i++) {
	//	free(arr[i]);
	//}
	//free(arr);


	//Game game_1;
	//Game* ptr = &game_1;
	//(*ptr).rows = 3;
	//(*ptr).columns = 5;
	////game_1.foodCount = 0;
	////game_1.score = 0;
	////game_1.state = 1;
	//printf("%d %d\n", (*ptr).rows, (*ptr).columns);
	//char** arr;
	//int i, j;
	//arr = (char**)malloc((*ptr).rows * sizeof(char*));
	//for (i = 0; i < (*ptr).rows; i++) {
	//	arr[i] = (char*)malloc((*ptr).columns * sizeof(char));
	//}
	//for (i = 0; i < (*ptr).rows; i++) {
	//	for (j = 0; j < (*ptr).columns; j++) {
	//		arr[i][j] = '1';
	//	}
	//}
	//(*ptr).grid = arr;
	//for (i = 0; i < (*ptr).rows; i++) {
	//	for (j = 0; j < (*ptr).columns; j++) {
	//		putchar((*ptr).grid[i][j]);
	//		putchar('\n');
	//	}
	//}
	//for (i = 0; i < (*ptr).rows; i++) {
	//	free(arr[i]);
	//}
	//free(arr);

	Game game_1;
	Game* ptr = &game_1;
	game_1.state = 1;
	game_1.score = 100;
	game_1.foodCount = 20;

	
	switch (ptr->state) {
	case losing:
		printf("Pacman died! Your score: %d\n", ptr->score);
		break;
	case onGoing:
		printf("Score: %d\n",ptr->score);
		printf("There are %d foods remaining!\n", ptr->foodCount);
		printf("Pacman wants food! (control by w/a/s/d/i, confirm by Enter)\n\n");
		break;
	case winning:
		printf("Victory! Your score: %d\n", ptr->score);
		break;
	default:
		printf("ERROR: invalid game state!\n");
	}

}