#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define FOOD_SCORE 10
#define MAX_GHOSTS 30
#define CAPSULE_DURATION 10
#define CAPSULE_SCORE 50
#define GHOST_SCORE 200

typedef enum gameState { losing, onGoing, winning } GameState;
typedef enum direction { up, down, left, right, idle } Direction;
typedef struct ghost {
    int ghost_num;
    int** g_direction;
    int** is_food;//第一个位置表示有没有.有的话为1，第二个位置表示有没有o，有的话为1
    int** axis;
    int** is_alive;
}Ghost;

typedef struct capsule {
    int capsule_dure;
    int dure_round;
    int state;  //state为1时表示有suoerpower,state为0时，表示没有superpower
}Capsule;


typedef struct game {
    char** grid;     // a 2-dimensional array of characters to display the game;
    int rows;        // number of rows of the grid;
    int columns;     // number of columns of the grid;
    int foodCount;   // number of remaining food in the game;
    int score;       // current score;
    GameState state; // the state of the game, one of losing, onGoing, or winning.
    Ghost ghost;
    Capsule capsule;
} Game;

/* Creates a new game, with given rows and columns.
 * The top-left corner is at row 0 and column 0.
 * Boundary is not included in either rows or columns.
 * You should dynamically allocate space for a Game pointer,
 * dynamically allocate a 2-dimensional char grid,
 * and initialize any other value in your Game structure.
 * Return that pointer to the game you created.
 */
Game* NewGame(int rows, int columns) { //这里return的是一个指向struct game数据类型的指针 因为用了typedef 所以Game=struct game
    Game* ptr = malloc(sizeof(Game));
    assert(ptr != NULL);
    (*ptr).rows = rows;
    (*ptr).columns = columns;
    (*ptr).foodCount = 0;
    (*ptr).score = 0;
    (*ptr).state = 1;
    (*ptr).capsule.capsule_dure = 0;
    (*ptr).capsule.dure_round = 0;
    (*ptr).capsule.state = 0;
    (*ptr).ghost.ghost_num = 0;
    char** arr;
    int i, j;
    arr = (char**)malloc((*ptr).rows * sizeof(char*));
    assert(arr != NULL);
    for (i = 0; i < (*ptr).rows; i++) {
        arr[i] = (char*)malloc((*ptr).columns * sizeof(char));
    }
    for (i = 0; i < (*ptr).rows; i++) {
        for (j = 0; j < (*ptr).columns; j++) {
            arr[i][j] = ' ';
        }
    }
    (*ptr).grid = arr;

    int** arr_2;
    arr_2 = (int**)malloc(30 * sizeof(int*));
    //assert(arr_2 != NULL);
    for (i = 0; i < 30; i++) {
        arr_2[i] = (int*)malloc(2 * sizeof(int));
    }
    for (i = 0; i < 30; i++) {
        for (j = 0; j < 2; j++) {
            arr_2[i][j] =0;
        }
    }
    (*ptr).ghost.axis = arr_2;

    int** arr_3;
    arr_3 = (int**)malloc(30 * sizeof(int*));
    //assert(arr_3 != NULL);
    for (i = 0; i < 30; i++) {
        arr_3[i] = (int*)malloc(sizeof(int));
    }
    for (i = 0; i < 30; i++) {      
        arr_3[i][0] = 0;       
    }
    (*ptr).ghost.g_direction = arr_3;

    int** arr_4;
    arr_4 = (int**)malloc(30 * sizeof(int*));
    //assert(arr_4 != NULL);
    for (i = 0; i < 30; i++) {
        arr_4[i] = (int*)malloc(2*sizeof(int));
    }
    for (i = 0; i < 30; i++) {
        arr_4[i][0] = 0;
        arr_4[i][1] = 0;
    }
    (*ptr).ghost.is_food = arr_4;
    //printf("%d\n", ptr->state);
    int** arr_5;
    arr_5 = (int**)malloc(30 * sizeof(int*));
    //assert(arr_4 != NULL);
    for (i = 0; i < 30; i++) {
        arr_5[i] = (int*)malloc(sizeof(int));
    }
    for (i = 0; i < 30; i++) {
        arr_5[i][0] = 0;
    }
    (*ptr).ghost.is_alive = arr_5;
    return ptr; // This is incorrect.
}

/* Ends your game by freeing any memory
 * you dynamically allocated.
 * After that, free the "game" pointer,    //指的就是free掉Game 这个指针
 * since it is also dynamically created.
 */
void EndGame(Game* game) {
    int i;

    //这里不止要free Game这个指针，还需要free任何的动态数组
   for (i = 0; i < (*game).rows; i++) {
        free((*game).grid[i]);
   }
   for (i = 0; i < 30; i++) {
       free((*game).ghost.axis[i]);
   }
   for (i = 0; i < 30; i++) {
       free((*game).ghost.g_direction[i]);
   }
   for (i = 0; i < 30; i++) {
       free((*game).ghost.is_food[i]);
   }
   for (i = 0; i < 30; i++) {
       free((*game).ghost.is_alive[i]);
   }
    free((*game).grid);
    free((*game).ghost.axis);
    free((*game).ghost.g_direction);
    free((*game).ghost.is_food);
    free((*game).ghost.is_alive);
    free(game);
    //return;// This is incorrect.
}

/* Adds a wall to the game, at row = r, column = c.
 * Walls should be added only to an empty place.
 * After you successfully add a wall,
 * you should modify the "grid" to represent
 * the wall by '#'. Then, return true.
 * Return false on failures.
 */
bool AddWall(Game* game, int r, int c) {
    //printf("%d\n", game->rows);
    //printf("%d\n", game->columns);
    if (r < 0 || r >= (*game).rows || c < 0 || c >= (*game).columns) {
        return false;
    }
    if((*game).grid[r][c]==' ') {
        (*game).grid[r][c] = '#';
        return true;
    }
    else {
        return false;
    }
 
    // This is not always correct.
}

/* Adds a food to the game, at row = r, column = c.
 * Foods should be added only to an empty place.
 * After you successfully add a food,
 * you should modify the "grid" to represent
 * the food by '.', also update the "foodCount"
 * correctly. Then, return true.
 * Return false on failures.
 */
bool AddFood(Game* game, int r, int c) {
    
    if (r < 0 || r >= (*game).rows || c < 0 || c >= (*game).columns) {
        return false;
    }
    if((*game).grid[r][c]==' ') {
        (*game).grid[r][c] = '.';
        (*game).foodCount += 1;
        return true;
    }
    else {
        return false;
    }
    
    }
    // This is not always correct.


/* Adds a Pacman to the game! At row = r, column = c.
 * If there is already a Pacman, return false.
 * Pacman should be added only to an empty place.
 * After you successfully add a Pacman,
 * you should modify the "grid" to represent
 * the Pacman by 'C'. Then, return true.
 * Return false on failures.
 */
bool AddPacman(Game* game, int r, int c) {

    int i, j;
    int is_pacman = 0;
    for (i = 0; i < (*game).rows; i++) {
        for (j = 0; j < (*game).columns; j++) {
            if ((*game).grid[i][j] == 'C') {
                is_pacman = 1;
            }
        }
    }
    if (r < 0 || r >= (*game).rows || c < 0 || c >= (*game).columns) {
        return false;
    }
    if (is_pacman == 0&&(*game).grid[r][c]==' ') {
        (*game).grid[r][c] = 'C';
        return true;
    }
    else {
        return false;
    }
    
    // This is not always correct.
}

/* Moves Pacman in the given direction.
 * The direction will always be valid.
 * Pacman should stay still if this move
 * will let it hit a wall or boundaries.
 * No matter what move is performed, the
 * game's score should decrease by 1.
 *
 * If Pacman eats a food, the game's score
 * should increase by FOOD_SCORE. If that
 * food is the last one in the game, you
 * should mark the game's state as "winning".
 *
 *
 * FOR PART B:
 *
 * Pacman is allowed to move onto a grid
 * with a ghost. In that case, Pacman loses,
 * and will not be able to eat the food or capsule
 * under that ghost, if any. Score should
 * still decrease by 1, and you should mark the
 * game's state as "losing".
 *
 * If Pacman eats a capsule, the game's score
 * should increase by CAPSULE_SCORE, and Pacman
 * will gain CAPSULE_DURATION = 10 turns of
 * superpower. If that capsule is the last food
 * in the game, mark the game's state as "winning".
 *
 */
void MovePacman(Game* game, Direction direction) {
    int direct_list[2] = { 0 };
    int i, j,k;
    int pac_x=0, pac_y=0;
    int count_bean = 0;
    for (i = 0; i < (*game).rows; i++) {
        for (j = 0; j < (*game).columns; j++) {
            if ((*game).grid[i][j] == 'C') {
                pac_x = i;
                pac_y = j;
            }
        }
    }

    if (direction == 0) {
        direct_list[0] = -1;
    }
    else if (direction == 1) {
        direct_list[0] = 1;
    }
    else if (direction == 2) {
        direct_list[1] = -1;
    }
    else if (direction == 3) {
        direct_list[1] = 1;
    }
    else if (direction == 4) {
        direct_list[0] = 0;
        direct_list[1] = 0;
    }

    
        if ((pac_x + direct_list[0]) >= (*game).rows || (pac_x + direct_list[0]) < 0 || (pac_y + direct_list[1]) >= (*game).columns || (pac_y + direct_list[1]) < 0) {
            (*game).grid[pac_x][pac_y] = 'C';
            (*game).score -= 1;
            (*game).state = 1;
        }
        else if ((*game).grid[pac_x + direct_list[0]][pac_y + direct_list[1]] == '#') {
            (*game).grid[pac_x][pac_y] = 'C';
            (*game).score -= 1;
            (*game).state = 1;
        }
        else {
            if ((*game).grid[pac_x + direct_list[0]][pac_y + direct_list[1]] == '.') {
                (*game).score += FOOD_SCORE;
                (*game).foodCount -= 1;
                (*game).score -= 1;
                (*game).state = 1;
                (*game).grid[pac_x][pac_y] = ' ';
                (*game).grid[pac_x + direct_list[0]][pac_y + direct_list[1]] = 'C';
            }
            else if ((*game).grid[pac_x + direct_list[0]][pac_y + direct_list[1]] == 'o') {
                (*game).capsule.state = 1;
                (*game).score += CAPSULE_SCORE;
                (*game).capsule.capsule_dure = (*game).capsule.dure_round+CAPSULE_DURATION;
                //(*game).capsule.dure_round += 1;
                (*game).foodCount -= 1;
                (*game).score -= 1;
                (*game).state = 1;
                (*game).grid[pac_x][pac_y] = ' ';
                (*game).grid[pac_x + direct_list[0]][pac_y + direct_list[1]] = 'C';
            }
            else if ((*game).grid[pac_x + direct_list[0]][pac_y + direct_list[1]] == 'X') {
                int rank_ghost = 0;
                for (i = 0; i < (*game).ghost.ghost_num; i++) {
                    for (j = 0; j < 2; j++) {
                        if ((*game).ghost.axis[i][0] == pac_x + direct_list[0] && (*game).ghost.axis[i][1] == pac_y + direct_list[1]) {
                            rank_ghost = i;
                        }
                    }
                }
                if ((*game).ghost.is_food[rank_ghost][1] == 1) { //这里还需要补东西,即表面上是X,但其实下面还有capsule o
                    (*game).capsule.state = 1;
                    (*game).score += (CAPSULE_SCORE + GHOST_SCORE);
                    (*game).capsule.capsule_dure = (*game).capsule.dure_round + CAPSULE_DURATION;
                    //(*game).capsule.dure_round += 1;
                    (*game).foodCount -= 1;
                }
                else if ((*game).ghost.is_food[rank_ghost][0] == 1) {    //表面上是X，但其实下面还有. food
                    (*game).score += (FOOD_SCORE + GHOST_SCORE);
                    (*game).foodCount -= 1;
                }
                else {
                    (*game).score += GHOST_SCORE;
                }
                (*game).state = 1;
                (*game).score -= 1;
                (*game).ghost.is_alive[rank_ghost][0] = 0;
                (*game).grid[pac_x][pac_y] = ' ';
                (*game).grid[pac_x + direct_list[0]][pac_y + direct_list[1]] = 'C';
            }
            else if ((*game).grid[pac_x + direct_list[0]][pac_y + direct_list[1]] == ' ') {
                (*game).state = 1;
                (*game).score -= 1;
                (*game).grid[pac_x][pac_y] = ' ';
                (*game).grid[pac_x + direct_list[0]][pac_y + direct_list[1]] = 'C';
            }
            else if ((*game).grid[pac_x + direct_list[0]][pac_y + direct_list[1]] == '@') {//如果是@，则直接被吃掉，losing,无法吃到ghost下面的food
                (*game).grid[pac_x][pac_y] = ' ';
                (*game).state = 0;
                (*game).score -= 1;
            }
            else if ((*game).grid[pac_x + direct_list[0]][pac_y + direct_list[1]] == 'C') {
                (*game).grid[pac_x][pac_y] = 'C';
                (*game).state = 1;
                (*game).score -= 1;
            }

        }
    
        for (i = 0; i < (*game).rows; i++) {
            for (j = 0; j < (*game).columns; j++) {
                if ((*game).grid[i][j] == '.' || (*game).grid[i][j] == 'o') {
                    count_bean += 1;
                }
            }
        }
        for (i = 0; i < (*game).ghost.ghost_num; i++) {
            if ((*game).ghost.is_alive[i][0] == 1) {
                if ((*game).ghost.is_food[i][0] == 1 || (*game).ghost.is_food[i][1] == 1) {
                    count_bean += 1;
                }
            }
        }
        if (count_bean == 0 && (*game).state != 0) {
            (*game).state = 2;
        }
        else if(count_bean != 0 && (*game).state != 0) {
            (*game).state = 1;
        }
      /*  int count_ghost=0;
        if (count_bean == 0 && (*game).state != 0) {
            for (i = 0; i < (*game).ghost.ghost_num; i++) {
                if ((*game).ghost.is_food[i][0] == 0 && (*game).ghost.is_food[i][1] == 0) {
                    count_ghost += 1;
                }
            }
            if (count_ghost == (*game).ghost.ghost_num) {
                (*game).state = 2;
            }
            else {
                (*game).state = 1;
            }
        }
        else if (count_bean!=0 && (*game).state != 0){
            (*game).state = 1;
        }*/
 }       
    
           

                  //return;// This is incorrect.


//////////////////////// PART B ////////////////////////


/* Adds a ghost to the game,
 * at row = r, column = c, with given initial direction.
 * you should modify the "grid" to represent the ghost by '@'.
 * Ghosts can be added to an empty place or on a food.
 * For the latter case, the ghost will cover that food on display,
 * represented also by an '@'.
 * That food must still exist, and that grid should
 * display '.' when the ghost leaves.
 */

bool AddGhost(Game* game, int r, int c, Direction direction) {
    int ghost_number = 0;
    int i, j,k;
   /* for (k = 0; k < 30; k++) {
        (*game).ghost.is_food[k][0] = 0;
        (*game).ghost.is_food[k][1] = 0;
    }*/
    for (i = 0; i < (*game).rows; i++) {
        for (j = 0; j < (*game).columns; j++) {
            if ((*game).grid[i][j] == '@') {
                ghost_number += 1;
            }
        }
    }
    //(*game).ghost.ghost_num = ghost_number;
    if (r < 0 || r >= (*game).rows || c < 0 || c >= (*game).columns) {
        return false;
    }
    if (ghost_number >= MAX_GHOSTS) {
        return false;
    }
  
    if ((*game).grid[r][c] == ' ') {       
        (*game).grid[r][c] = '@';
        (*game).ghost.g_direction[ghost_number][0] = direction;
        (*game).ghost.axis[ghost_number][0] = r;
        (*game).ghost.axis[ghost_number][1] = c;
        (*game).ghost.ghost_num = ghost_number+1;
        for (k = 0; k < (*game).ghost.ghost_num; k++) {
            (*game).ghost.is_alive[k][0] = 1;
        }
        return true;
    }
    else if ((*game).grid[r][c] == 'o') {
        (*game).grid[r][c] = '@';
        (*game).ghost.g_direction[ghost_number][0] = direction;//direction 也需要建立一个数组来存放,ghost structute里是存放了所有ghost的相关信息，而不是单一的
        (*game).ghost.is_food[ghost_number][1] = 1;//在moveghost的函数里需要使用这个来判断 ghost走了以后之气那的位置上是否有需要恢复的内容
        (*game).ghost.axis[ghost_number][0] = r;
        (*game).ghost.axis[ghost_number][1] = c;
        (*game).ghost.ghost_num = ghost_number + 1;
        for (k = 0; k < (*game).ghost.ghost_num; k++) {
            (*game).ghost.is_alive[k][0] = 1;
        }
        return true;
    }
    else if ((*game).grid[r][c] == '.') {
        (*game).grid[r][c] = '@';
        (*game).ghost.g_direction[ghost_number][0] = direction;
        (*game).ghost.is_food[ghost_number][0] = 1;
        (*game).ghost.axis[ghost_number][0] = r;
        (*game).ghost.axis[ghost_number][1] = c;
        (*game).ghost.ghost_num = ghost_number + 1;
        for (k = 0; k < (*game).ghost.ghost_num; k++) {
            (*game).ghost.is_alive[k][0] = 1;
        }
        return true;
    }
    else {
        return false;
    }// This is not always correct.
}

/* Moves all ghosts in their own directions.
 * Ghosts should be moved in the order they were added.//这个还得考虑一下
 * If a ghost will bump into a wall, another ghost, or a boundary,
 * Its direction will reverse, and it will try to move
 * in the new direction immediately this turn.
 * If it bumps into another wall/ghost/boundary,
 * it won't move for this turn.
 */
int reverse(int a) {
    if (a == 0) {
        a = 1;
    }
    else if (a == 1) {
        a = 0;
    }
    else if (a == 2) {
        a = 3;
    }
    else if (a == 3) {
        a = 2;
    }
    return a;
}
int direct_g(int a) {
    
    if (a == 0) {
       a= -1;
    }
    else if (a == 1) {
        a = 1;
    }
    else if (a == 2) {
        a = -1;
    }
    else if (a == 3) {
        a = 1;
    }
    return a;
}
void MoveGhosts(Game* game) {
    //int axis_x, axis_y;
    //axis_x = game->ghost.axis[];
    int i, j,k;
    int axis_x, axis_y;
    int direct;
    
    for (i = 0; i < (*game).ghost.ghost_num; i++) {
        if ((*game).ghost.is_alive[i][0] == 0) {    //'X'被吃掉以后这边有异常
            continue;
        }

        int direct_list[2] = { 0 };
        
        axis_x = (*game).ghost.axis[i][0];
        axis_y = (*game).ghost.axis[i][1];
        direct = (*game).ghost.g_direction[i][0];    //在这里用这个数组就没问题
        if (direct==2||direct==3) {
            direct_list[1] = direct_g(direct);
        }
        else if (direct==0||direct==1) {
            direct_list[0] = direct_g(direct);
        }
       
        if ((*game).capsule.state == 0) {         //pacman没有superpower时   //这里判断的时候数组可能会越界
            if ((axis_x + direct_list[0]) >= (*game).rows || (axis_x + direct_list[0]) < 0 || (axis_y + direct_list[1]) >= (*game).columns || (axis_y + direct_list[1]) < 0) {
                direct_list[0] = 0;   //这里指的是走了就撞到东西反弹或不动的情况
                direct_list[1] = 0;
                //(*game).grid[axis_x][axis_y] = '@';
                (*game).ghost.g_direction[i][0] = reverse((*game).ghost.g_direction[i][0]);  //把reverse的方向存入数组里
                if ((*game).ghost.g_direction[i][0] == 2 || (*game).ghost.g_direction[i][0] == 3) {
                    direct_list[1] = direct_g((*game).ghost.g_direction[i][0]);
                }
                else if ((*game).ghost.g_direction[i][0] == 0 || (*game).ghost.g_direction[i][0] == 1) {
                    direct_list[0] = direct_g((*game).ghost.g_direction[i][0]);
                }
             
            
               
                if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '#' || (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '@') {
                    (*game).grid[axis_x][axis_y] = '@';
                    (*game).ghost.axis[i][0] = axis_x;
                    (*game).ghost.axis[i][1] = axis_y;

                    /*  for (k = 0; k < 2; k++) {
                          (*game).ghost.is_food[i][k] = 0;
                      }*/

                }
            
            
                else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '.') {
                    (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@'; //注意后面还需要还原这个食物
                    (*game).grid[axis_x][axis_y] = ' ';
                    (*game).ghost.axis[i][0] = axis_x + direct_list[0];   //这里是记录每一次鬼的位置
                    (*game).ghost.axis[i][1] = axis_y + direct_list[1];

                    if ((*game).ghost.is_food[i][0] == 1) {
                        (*game).grid[axis_x][axis_y] = '.';
                    }
                    if ((*game).ghost.is_food[i][1] == 1) {
                        (*game).grid[axis_x][axis_y] = 'o';
                    }
                   
                    for (k = 0; k < 2; k++) {
                        (*game).ghost.is_food[i][k] = 0;
                    }
                    (*game).ghost.is_food[i][0] = 1;
                }

                else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'o') {
                    (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@'; //注意后面还需要还原这个食物
                    (*game).grid[axis_x][axis_y] = ' ';
                    (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                    (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                   
                    if ((*game).ghost.is_food[i][0] == 1) {
                        (*game).grid[axis_x][axis_y] = '.';
                    }
                    if ((*game).ghost.is_food[i][1] == 1) {
                        (*game).grid[axis_x][axis_y] = 'o';
                    }
                    
                    for (k = 0; k < 2; k++) {
                        (*game).ghost.is_food[i][k] = 0;
                    }
                    (*game).ghost.is_food[i][1] = 1;
                }

                else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == ' ') {
                    (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@';
                    if ((*game).ghost.is_food[i][0]==1) {
                        (*game).grid[axis_x][axis_y] = '.';
                    }
                    else if ((*game).ghost.is_food[i][1] == 1) {
                        (*game).grid[axis_x][axis_y] = 'o';
                    }
                    else {
                        (*game).grid[axis_x][axis_y] = ' ';
                    }
                    (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                    (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                    for (k = 0; k < 2; k++) {
                        (*game).ghost.is_food[i][k] = 0;
                    }
                }
                else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'C') {
                    (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@';//这样游戏就结束了losing
                    (*game).grid[axis_x][axis_y] = ' ';
                    (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                    (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                    (*game).state = 0;
                    for (k = 0; k < 2; k++) {
                        (*game).ghost.is_food[i][k] = 0;
                    }

                }   
            }
            else if((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '#' || (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '@'){
                
                    direct_list[0] = 0;   //这里指的是走了就撞到东西反弹或不动的情况
                    direct_list[1] = 0;
                    //(*game).grid[axis_x][axis_y] = '@';
                    (*game).ghost.g_direction[i][0] = reverse((*game).ghost.g_direction[i][0]);  //把reverse的方向存入数组里
                    if ((*game).ghost.g_direction[i][0] == 2 || (*game).ghost.g_direction[i][0] == 3) {
                        direct_list[1] = direct_g((*game).ghost.g_direction[i][0]);
                    }
                    else if ((*game).ghost.g_direction[i][0] == 0 || (*game).ghost.g_direction[i][0] == 1) {
                        direct_list[0] = direct_g((*game).ghost.g_direction[i][0]);
                    }

                    if ((axis_x + direct_list[0]) >= (*game).rows || (axis_x + direct_list[0]) < 0 || (axis_y + direct_list[1]) >= (*game).columns || (axis_y + direct_list[1]) < 0) {
                        (*game).grid[axis_x][axis_y] = '@';
                    }
                    else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '#' || (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '@') {
                        (*game).grid[axis_x][axis_y] = '@';
                        (*game).ghost.axis[i][0] = axis_x;
                        (*game).ghost.axis[i][1] = axis_y;

                        /*  for (k = 0; k < 2; k++) {
                              (*game).ghost.is_food[i][k] = 0;
                          }*/

                    }
                   
                    else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '.') {
                        (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@';
                        if ((*game).ghost.is_food[i][0] == 1) {
                            (*game).grid[axis_x][axis_y] = '.';
                        }
                        else if ((*game).ghost.is_food[i][1] == 1) {
                            (*game).grid[axis_x][axis_y] = 'o';
                        }
                        else {
                            (*game).grid[axis_x][axis_y] = ' ';
                        }
                        (*game).ghost.is_food[i][0] = 1;
                        (*game).ghost.is_food[i][1] = 0;
                        (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                        (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                    }
                    else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'o') {
                        (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@';
                        if ((*game).ghost.is_food[i][0] == 1) {
                            (*game).grid[axis_x][axis_y] = '.';
                        }
                        else if ((*game).ghost.is_food[i][1] == 1) {
                            (*game).grid[axis_x][axis_y] = 'o';
                        }
                        else {
                            (*game).grid[axis_x][axis_y] = ' ';
                        }
                        (*game).ghost.is_food[i][1] = 1;
                        (*game).ghost.is_food[i][0] = 0;
                        (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                        (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                    }
                    else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == ' ') {
                        (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@';

                        if ((*game).ghost.is_food[i][0] == 1) {
                            (*game).grid[axis_x][axis_y] = '.';
                        }
                        else if ((*game).ghost.is_food[i][1] == 1) {
                            (*game).grid[axis_x][axis_y] = 'o';
                        }
                        else {
                            (*game).grid[axis_x][axis_y] = ' ';
                        }
                        (*game).ghost.is_food[i][0] = 0;         //这个要不要加？？？
                        (*game).ghost.is_food[i][1] = 0;
                        (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                        (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                    }
                    else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'C') {
                        (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@';//游戏此时结束了
                        if ((*game).ghost.is_food[i][0] == 1) {
                            (*game).grid[axis_x][axis_y] = '.';
                        }
                        else if ((*game).ghost.is_food[i][1] == 1) {
                            (*game).grid[axis_x][axis_y] = 'o';
                        }
                        else {
                            (*game).grid[axis_x][axis_y] = ' ';
                        }
                        (*game).ghost.is_alive[i][0] = 1;
                        (*game).state = 0;
                        (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                        (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                        /* if ((*game).ghost.is_food[i][0] == 1) {
                             (*game).score += FOOD_SCORE;
                         }
                         else if ((*game).ghost.is_food[i][1] == 1) {
                             (*game).score += CAPSULE_SCORE;
                         }*/
                        for (k = 0; k < 2; k++) {
                            (*game).ghost.is_food[i][k] = 0;
                        }
                        /* for (k = 0; k < 2; k++) {
                             (*game).ghost.is_food[i][k] = 0;
                         }*/
                    }
                }
            else {
                if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '.') {
                    (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@';
                    if ((*game).ghost.is_food[i][0] == 1) {
                        (*game).grid[axis_x][axis_y] = '.';
                    }
                    else if ((*game).ghost.is_food[i][1] == 1) {
                        (*game).grid[axis_x][axis_y] = 'o';
                    }
                    else {
                        (*game).grid[axis_x][axis_y] = ' ';
                    }
                    (*game).ghost.is_food[i][0] = 1;
                    (*game).ghost.is_food[i][1] = 0;
                    (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                    (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                }
                else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'o') {
                    (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@';
                    if ((*game).ghost.is_food[i][0] == 1) {
                        (*game).grid[axis_x][axis_y] = '.';
                    }
                    else if ((*game).ghost.is_food[i][1] == 1) {
                        (*game).grid[axis_x][axis_y] = 'o';
                    }
                    else {
                        (*game).grid[axis_x][axis_y] = ' ';
                    }
                    (*game).ghost.is_food[i][1] = 1;
                    (*game).ghost.is_food[i][0] = 0;
                    (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                    (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                }
                else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == ' ') {
                    (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@';
                    
                    if ((*game).ghost.is_food[i][0] == 1) {
                        (*game).grid[axis_x][axis_y] = '.';
                    }
                    else if ((*game).ghost.is_food[i][1] == 1) {
                        (*game).grid[axis_x][axis_y] = 'o';
                    }
                    else {
                        (*game).grid[axis_x][axis_y] = ' ';
                    }
                    (*game).ghost.is_food[i][0] = 0;         //这个要不要加？？？
                    (*game).ghost.is_food[i][1] = 0;
                    (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                    (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                }
                else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'C') {
                    (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@';//这样游戏就结束了losing
                    if ((*game).ghost.is_food[i][0] == 1) {
                        (*game).grid[axis_x][axis_y] = '.';
                    }
                    else if ((*game).ghost.is_food[i][1] == 1) {
                        (*game).grid[axis_x][axis_y] = 'o';
                    }
                    else {
                        (*game).grid[axis_x][axis_y] = ' ';
                    }
                    (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                    (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                    (*game).state = 0;
                 /*   for (k = 0; k < 2; k++) {
                        (*game).ghost.is_food[i][k] = 0;
                    }*/
                }
            }
        }
        else if ((*game).capsule.state == 1) {   //pacman有superpower时
            int p;
            if ((*game).capsule.dure_round >= 0 && (*game).capsule.dure_round < (*game).capsule.capsule_dure) {
                for (k = 0; k < (*game).rows; k++) {
                    for (p = 0; p < (*game).columns; p++) {
                        if ((*game).grid[k][p] == '@') {
                            (*game).grid[k][p] = 'X';
                        }
                    }
                }
                if (((*game).capsule.dure_round)%2==1) {
                    (*game).ghost.axis[i][0] = axis_x;
                    (*game).ghost.axis[i][1] = axis_y;
                }
                else if(((*game).capsule.dure_round)%2==0) {
                    if ((axis_x + direct_list[0]) >= (*game).rows || (axis_x + direct_list[0]) < 0 || (axis_y + direct_list[1]) >= (*game).columns || (axis_y + direct_list[1]) < 0 ) {
                        direct_list[0] = 0;   //这里指的是走了就撞到东西反弹或不动的情况
                        direct_list[1] = 0;
                        //(*game).grid[axis_x][axis_y] = '@';
                        (*game).ghost.g_direction[i][0] = reverse((*game).ghost.g_direction[i][0]);  //把reverse的方向存入数组里

                        if ((*game).ghost.g_direction[i][0] == 2 || (*game).ghost.g_direction[i][0] == 3) {
                            direct_list[1] = direct_g((*game).ghost.g_direction[i][0]);
                        }
                        else if ((*game).ghost.g_direction[i][0] == 0 || (*game).ghost.g_direction[i][0] == 1) {
                            direct_list[0] = direct_g((*game).ghost.g_direction[i][0]);
                        }

                        if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '#' || (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'X') {
                            (*game).grid[axis_x][axis_y] = 'X';
                            (*game).ghost.axis[i][0] = axis_x;
                            (*game).ghost.axis[i][1] = axis_y;
                          /*  for (k = 0; k < 2; k++) {
                                (*game).ghost.is_food[i][k] = 0;
                            }*/

                        }
                        else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '.') {
                            (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = 'X'; //注意后面还需要还原这个食物
                            (*game).grid[axis_x][axis_y] = ' ';
                            (*game).ghost.axis[i][0] = axis_x + direct_list[0];   //这里是记录每一次鬼的位置
                            (*game).ghost.axis[i][1] = axis_y + direct_list[1];

                            if ((*game).ghost.is_food[i][0] == 1) {
                                (*game).grid[axis_x][axis_y] = '.';
                            }
                            if ((*game).ghost.is_food[i][1] == 1) {
                                (*game).grid[axis_x][axis_y] = 'o';
                            }

                            for (k = 0; k < 2; k++) {
                                (*game).ghost.is_food[i][k] = 0;
                            }
                            (*game).ghost.is_food[i][0] = 1;
                        }

                        else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'o') {
                            (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = 'X'; //注意后面还需要还原这个食物
                            (*game).grid[axis_x][axis_y] = ' ';
                            (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                            (*game).ghost.axis[i][1] = axis_y + direct_list[1];

                            if ((*game).ghost.is_food[i][0] == 1) {
                                (*game).grid[axis_x][axis_y] = '.';
                            }
                            if ((*game).ghost.is_food[i][1] == 1) {
                                (*game).grid[axis_x][axis_y] = 'o';
                            }

                            for (k = 0; k < 2; k++) {
                                (*game).ghost.is_food[i][k] = 0;
                            }
                            (*game).ghost.is_food[i][1] = 1;
                        }

                        else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == ' ') {
                            (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = 'X';
                            if ((*game).ghost.is_food[i][0] == 1) {
                                (*game).grid[axis_x][axis_y] = '.';
                            }
                            else if ((*game).ghost.is_food[i][1] == 1) {
                                (*game).grid[axis_x][axis_y] = 'o';
                            }
                            else {
                                (*game).grid[axis_x][axis_y] = ' ';
                            }
                            (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                            (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                            for (k = 0; k < 2; k++) {
                                (*game).ghost.is_food[i][k] = 0;
                            }
                        }
                        else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'C') {
                            //(*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = 'X';//这样游戏继续，鬼被吃了
                            (*game).grid[axis_x][axis_y] = ' ';
                            (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                            (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                            (*game).state = 1;
                            (*game).ghost.is_alive[i][0] = 0;
                            (*game).score += GHOST_SCORE;
                          /*  if ((*game).ghost.is_food[i][0] == 1) {
                                (*game).score += FOOD_SCORE;
                            }
                            else if ((*game).ghost.is_food[i][1] == 1) {
                                (*game).score += CAPSULE_SCORE;
                            }*/
                            for (k = 0; k < 2; k++) {
                                (*game).ghost.is_food[i][k] = 0;
                            }

                        }
                    }
                    else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '#' || (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'X') {
                        direct_list[0] = 0;   //这里指的是走了就撞到东西反弹或不动的情况
                        direct_list[1] = 0;
                        //(*game).grid[axis_x][axis_y] = '@';
                        (*game).ghost.g_direction[i][0] = reverse((*game).ghost.g_direction[i][0]);  //把reverse的方向存入数组里
                        
                        if ((*game).ghost.g_direction[i][0] == 2 || (*game).ghost.g_direction[i][0] == 3) {
                            direct_list[1] = direct_g((*game).ghost.g_direction[i][0]);
                        }
                        else if ((*game).ghost.g_direction[i][0] == 0 || (*game).ghost.g_direction[i][0] == 1) {
                            direct_list[0] = direct_g((*game).ghost.g_direction[i][0]);
                        }

                        if ((axis_x + direct_list[0]) >= (*game).rows || (axis_x + direct_list[0]) < 0 || (axis_y + direct_list[1]) >= (*game).columns || (axis_y + direct_list[1]) < 0) {
                            (*game).grid[axis_x][axis_y] = 'X';
                        }
                        else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '#' || (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'X') {
                            (*game).grid[axis_x][axis_y] = 'X';
                            (*game).ghost.axis[i][0] = axis_x;
                            (*game).ghost.axis[i][1] = axis_y;
                            /*  for (k = 0; k < 2; k++) {
                                  (*game).ghost.is_food[i][k] = 0;
                              }*/

                        }
                        
                      
                        else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '.') {
                            (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = 'X';
                            if ((*game).ghost.is_food[i][0] == 1) {
                                (*game).grid[axis_x][axis_y] = '.';
                            }
                            else if ((*game).ghost.is_food[i][1] == 1) {
                                (*game).grid[axis_x][axis_y] = 'o';
                            }
                            else {
                                (*game).grid[axis_x][axis_y] = ' ';
                            }
                            (*game).ghost.is_food[i][0] = 1;
                            (*game).ghost.is_food[i][1] = 0;
                            (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                            (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                        }
                        else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'o') {
                            (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = 'X';
                            if ((*game).ghost.is_food[i][0] == 1) {
                                (*game).grid[axis_x][axis_y] = '.';
                            }
                            else if ((*game).ghost.is_food[i][1] == 1) {
                                (*game).grid[axis_x][axis_y] = 'o';
                            }
                            else {
                                (*game).grid[axis_x][axis_y] = ' ';
                            }
                            (*game).ghost.is_food[i][1] = 1;
                            (*game).ghost.is_food[i][0] = 0;
                            (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                            (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                        }
                        else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == ' ') {
                            (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = 'X';

                            if ((*game).ghost.is_food[i][0] == 1) {
                                (*game).grid[axis_x][axis_y] = '.';
                            }
                            else if ((*game).ghost.is_food[i][1] == 1) {
                                (*game).grid[axis_x][axis_y] = 'o';
                            }
                            else {
                                (*game).grid[axis_x][axis_y] = ' ';
                            }
                            (*game).ghost.is_food[i][0] = 0;         //这个要不要加？？？
                            (*game).ghost.is_food[i][1] = 0;
                            (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                            (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                        }
                        else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'C') {
                            (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = 'C';//游戏这时还是继续，ghost会被吃掉   这里是鬼往pacman上撞
                            if ((*game).ghost.is_food[i][0] == 1) {
                                (*game).grid[axis_x][axis_y] = '.';
                            }
                            else if ((*game).ghost.is_food[i][1] == 1) {
                                (*game).grid[axis_x][axis_y] = 'o';
                            }
                            else {
                                (*game).grid[axis_x][axis_y] = ' ';
                            }
                            (*game).ghost.is_alive[i][0] = 0;
                            (*game).state = 1;
                            (*game).score += GHOST_SCORE;
                            /* if ((*game).ghost.is_food[i][0] == 1) {
                                 (*game).score += FOOD_SCORE;
                             }
                             else if ((*game).ghost.is_food[i][1] == 1) {
                                 (*game).score += CAPSULE_SCORE;
                             }*/
                            for (k = 0; k < 2; k++) {
                                (*game).ghost.is_food[i][k] = 0;
                            }
                            /* for (k = 0; k < 2; k++) {
                                 (*game).ghost.is_food[i][k] = 0;
                             }*/
                        }
                    }
                    else {
                        if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '.') {
                            (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = 'X';
                            if ((*game).ghost.is_food[i][0] == 1) {
                                (*game).grid[axis_x][axis_y] = '.';
                            }
                            else if ((*game).ghost.is_food[i][1] == 1) {
                                (*game).grid[axis_x][axis_y] = 'o';
                            }
                            else {
                                (*game).grid[axis_x][axis_y] = ' ';
                            }
                            (*game).ghost.is_food[i][0] = 1;
                            (*game).ghost.is_food[i][1] = 0;
                            (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                            (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                        }
                        else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'o') {
                            (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = 'X';
                            if ((*game).ghost.is_food[i][0] == 1) {
                                (*game).grid[axis_x][axis_y] = '.';
                            }
                            else if ((*game).ghost.is_food[i][1] == 1) {
                                (*game).grid[axis_x][axis_y] = 'o';
                            }
                            else {
                                (*game).grid[axis_x][axis_y] = ' ';
                            }
                            (*game).ghost.is_food[i][1] = 1;
                            (*game).ghost.is_food[i][0] = 0;
                            (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                            (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                        }
                        else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == ' ') {
                            (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = 'X';
                            
                            if ((*game).ghost.is_food[i][0] == 1) {
                                (*game).grid[axis_x][axis_y] = '.';
                            }
                            else if ((*game).ghost.is_food[i][1] == 1) {
                                (*game).grid[axis_x][axis_y] = 'o';
                            }
                            else {
                                (*game).grid[axis_x][axis_y] = ' ';
                            }
                            (*game).ghost.is_food[i][0] = 0;         //这个要不要加？？？
                            (*game).ghost.is_food[i][1] = 0;
                            (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                            (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                        }
                        else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'C') {
                            (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = 'C';//游戏这时还是继续，ghost会被吃掉   这里是鬼往pacman上撞
                            if ((*game).ghost.is_food[i][0] == 1) {
                                (*game).grid[axis_x][axis_y] = '.';
                            }
                            else if ((*game).ghost.is_food[i][1] == 1) {
                                (*game).grid[axis_x][axis_y] = 'o';
                            }
                            else {
                                (*game).grid[axis_x][axis_y] = ' ';
                            }
                            (*game).ghost.is_alive[i][0] = 0;
                            (*game).state = 1;
                            (*game).score += GHOST_SCORE;
                           /* if ((*game).ghost.is_food[i][0] == 1) {
                                (*game).score += FOOD_SCORE;
                            }
                            else if ((*game).ghost.is_food[i][1] == 1) {
                                (*game).score += CAPSULE_SCORE;
                            }*/
                            for (k = 0; k < 2; k++) {
                                (*game).ghost.is_food[i][k] = 0;
                            }
                           /* for (k = 0; k < 2; k++) {
                                (*game).ghost.is_food[i][k] = 0;
                            }*/
                        }
                    }
                }

            }
            else {
                (*game).capsule.state = 0;
                (*game).capsule.dure_round = 0;
                (*game).capsule.capsule_dure = 0;
                for (k = 0; k < (*game).rows; k++) {
                    for (p = 0; p < (*game).columns; p++) {
                        if ((*game).grid[k][p] == 'X') {
                            (*game).grid[k][p] = '@';
                        }
                    }
                }
                if ((axis_x + direct_list[0]) >= (*game).rows || (axis_x + direct_list[0]) < 0 || (axis_y + direct_list[1]) >= (*game).columns || (axis_y + direct_list[1]) < 0) {
                    direct_list[0] = 0;   //这里指的是走了就撞到东西反弹或不动的情况
                    direct_list[1] = 0;
                    //(*game).grid[axis_x][axis_y] = '@';
                    (*game).ghost.g_direction[i][0] = reverse((*game).ghost.g_direction[i][0]);  //把reverse的方向存入数组里
                    if ((*game).ghost.g_direction[i][0] == 2 || (*game).ghost.g_direction[i][0] == 3) {
                        direct_list[1] = direct_g((*game).ghost.g_direction[i][0]);
                    }
                    else if ((*game).ghost.g_direction[i][0] == 0 || (*game).ghost.g_direction[i][0] == 1) {
                        direct_list[0] = direct_g((*game).ghost.g_direction[i][0]);
                    }



                    if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '#' || (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '@') {
                        (*game).grid[axis_x][axis_y] = '@';
                        (*game).ghost.axis[i][0] = axis_x;
                        (*game).ghost.axis[i][1] = axis_y;

                        /*  for (k = 0; k < 2; k++) {
                              (*game).ghost.is_food[i][k] = 0;
                          }*/

                    }


                    else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '.') {
                        (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@'; //注意后面还需要还原这个食物

                        if ((*game).ghost.is_food[i][0] == 1) {
                            (*game).grid[axis_x][axis_y] = '.';
                        }
                        else if ((*game).ghost.is_food[i][1] == 1) {
                            (*game).grid[axis_x][axis_y] = 'o';
                        }
                        else {
                            (*game).grid[axis_x][axis_y] = ' ';
                        }

                        (*game).ghost.axis[i][0] = axis_x + direct_list[0];   //这里是记录每一次鬼的位置
                        (*game).ghost.axis[i][1] = axis_y + direct_list[1];

                       

                        for (k = 0; k < 2; k++) {
                            (*game).ghost.is_food[i][k] = 0;
                        }
                        (*game).ghost.is_food[i][0] = 1;
                    }

                    else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'o') {
                        (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@'; //注意后面还需要还原这个食物

                        if ((*game).ghost.is_food[i][0] == 1) {
                            (*game).grid[axis_x][axis_y] = '.';
                        }
                        else if ((*game).ghost.is_food[i][1] == 1) {
                            (*game).grid[axis_x][axis_y] = 'o';
                        }
                        else {
                            (*game).grid[axis_x][axis_y] = ' ';
                        }

                        (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                        (*game).ghost.axis[i][1] = axis_y + direct_list[1];



                        for (k = 0; k < 2; k++) {
                            (*game).ghost.is_food[i][k] = 0;
                        }
                        (*game).ghost.is_food[i][1] = 1;
                    }

                    else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == ' ') {
                        (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@';
                        if ((*game).ghost.is_food[i][0] == 1) {
                            (*game).grid[axis_x][axis_y] = '.';
                        }
                        else if ((*game).ghost.is_food[i][1] == 1) {
                            (*game).grid[axis_x][axis_y] = 'o';
                        }
                        else {
                            (*game).grid[axis_x][axis_y] = ' ';
                        }
                        (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                        (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                        for (k = 0; k < 2; k++) {
                            (*game).ghost.is_food[i][k] = 0;
                        }
                    }
                    else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'C') {
                        (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@';//这样游戏就结束了losing

                        if ((*game).ghost.is_food[i][0] == 1) {
                            (*game).grid[axis_x][axis_y] = '.';
                        }
                        else if ((*game).ghost.is_food[i][1] == 1) {
                            (*game).grid[axis_x][axis_y] = 'o';
                        }
                        else {
                            (*game).grid[axis_x][axis_y] = ' ';
                        }

                        (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                        (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                        (*game).state = 0;
                        for (k = 0; k < 2; k++) {
                            (*game).ghost.is_food[i][k] = 0;
                        }

                    }
                }
                else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '#' || (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '@') {

                    direct_list[0] = 0;   //这里指的是走了就撞到东西反弹或不动的情况
                    direct_list[1] = 0;
                    //(*game).grid[axis_x][axis_y] = '@';
                    (*game).ghost.g_direction[i][0] = reverse((*game).ghost.g_direction[i][0]);  //把reverse的方向存入数组里
                    if ((*game).ghost.g_direction[i][0] == 2 || (*game).ghost.g_direction[i][0] == 3) {
                        direct_list[1] = direct_g((*game).ghost.g_direction[i][0]);
                    }
                    else if ((*game).ghost.g_direction[i][0] == 0 || (*game).ghost.g_direction[i][0] == 1) {
                        direct_list[0] = direct_g((*game).ghost.g_direction[i][0]);
                    }

                    if ((axis_x + direct_list[0]) >= (*game).rows || (axis_x + direct_list[0]) < 0 || (axis_y + direct_list[1]) >= (*game).columns || (axis_y + direct_list[1]) < 0) {
                        (*game).grid[axis_x][axis_y] = '@';
                    }
                    else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '#' || (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '@') {
                        (*game).grid[axis_x][axis_y] = '@';
                        (*game).ghost.axis[i][0] = axis_x;
                        (*game).ghost.axis[i][1] = axis_y;

                        /*  for (k = 0; k < 2; k++) {
                              (*game).ghost.is_food[i][k] = 0;
                          }*/

                    }
                    else {
                       
                        if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '.') {
                            (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@';

                            if ((*game).ghost.is_food[i][0] == 1) {
                                (*game).grid[axis_x][axis_y] = '.';
                            }
                            else if ((*game).ghost.is_food[i][1] == 1) {
                                (*game).grid[axis_x][axis_y] = 'o';
                            }
                            else {
                                (*game).grid[axis_x][axis_y] = ' ';
                            }

                            (*game).ghost.is_food[i][0] = 1;
                            (*game).ghost.is_food[i][1] = 0;
                            (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                            (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                        }
                        else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'o') {
                            (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@';

                            if ((*game).ghost.is_food[i][0] == 1) {
                                (*game).grid[axis_x][axis_y] = '.';
                            }
                            else if ((*game).ghost.is_food[i][1] == 1) {
                                (*game).grid[axis_x][axis_y] = 'o';
                            }
                            else {
                                (*game).grid[axis_x][axis_y] = ' ';
                            }

                            (*game).ghost.is_food[i][1] = 1;
                            (*game).ghost.is_food[i][0] = 0;
                            (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                            (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                        }
                        else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == ' ') {
                            (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@';

                            if ((*game).ghost.is_food[i][0] == 1) {
                                (*game).grid[axis_x][axis_y] = '.';
                            }
                            else if ((*game).ghost.is_food[i][1] == 1) {
                                (*game).grid[axis_x][axis_y] = 'o';
                            }
                            else {
                                (*game).grid[axis_x][axis_y] = ' ';
                            }


                            (*game).ghost.is_food[i][0] = 0;         //这个要不要加？？？
                            (*game).ghost.is_food[i][1] = 0;
                            (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                            (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                        }
                        else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'C') {
                            (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@';//这样游戏就结束了losing

                            if ((*game).ghost.is_food[i][0] == 1) {
                                (*game).grid[axis_x][axis_y] = '.';
                            }
                            else if ((*game).ghost.is_food[i][1] == 1) {
                                (*game).grid[axis_x][axis_y] = 'o';
                            }
                            else {
                                (*game).grid[axis_x][axis_y] = ' ';
                            }

                            (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                            (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                            (*game).state = 0;
                            /*   for (k = 0; k < 2; k++) {
                                   (*game).ghost.is_food[i][k] = 0;
                               }*/
                        }

                    }


                }
                else {
                    if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == '.') {
                        (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@';

                        if ((*game).ghost.is_food[i][0] == 1) {
                            (*game).grid[axis_x][axis_y] = '.';
                        }
                        else if ((*game).ghost.is_food[i][1] == 1) {
                            (*game).grid[axis_x][axis_y] = 'o';
                        }
                        else {
                            (*game).grid[axis_x][axis_y] = ' ';
                        }

                        (*game).ghost.is_food[i][0] = 1;
                        (*game).ghost.is_food[i][1] = 0;
                        (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                        (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                    }
                    else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'o') {
                        (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@';

                        if ((*game).ghost.is_food[i][0] == 1) {
                            (*game).grid[axis_x][axis_y] = '.';
                        }
                        else if ((*game).ghost.is_food[i][1] == 1) {
                            (*game).grid[axis_x][axis_y] = 'o';
                        }
                        else {
                            (*game).grid[axis_x][axis_y] = ' ';
                        }

                        (*game).ghost.is_food[i][1] = 1;
                        (*game).ghost.is_food[i][0] = 0;
                        (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                        (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                    }
                    else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == ' ') {
                        (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@';

                        if ((*game).ghost.is_food[i][0] == 1) {
                            (*game).grid[axis_x][axis_y] = '.';
                        }
                        else if ((*game).ghost.is_food[i][1] == 1) {
                            (*game).grid[axis_x][axis_y] = 'o';
                        }
                        else {
                            (*game).grid[axis_x][axis_y] = ' ';
                        }

                        
                        (*game).ghost.is_food[i][0] = 0;         //这个要不要加？？？
                        (*game).ghost.is_food[i][1] = 0;
                        (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                        (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                    }
                    else if ((*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] == 'C') {
                        (*game).grid[axis_x + direct_list[0]][axis_y + direct_list[1]] = '@';//这样游戏就结束了losing

                        if ((*game).ghost.is_food[i][0] == 1) {
                            (*game).grid[axis_x][axis_y] = '.';
                        }
                        else if ((*game).ghost.is_food[i][1] == 1) {
                            (*game).grid[axis_x][axis_y] = 'o';
                        }
                        else {
                            (*game).grid[axis_x][axis_y] = ' ';
                        }

                        (*game).ghost.axis[i][0] = axis_x + direct_list[0];
                        (*game).ghost.axis[i][1] = axis_y + direct_list[1];
                        (*game).state = 0;
                        /*   for (k = 0; k < 2; k++) {
                               (*game).ghost.is_food[i][k] = 0;
                           }*/
                    }
                }
            }
            

        }
        
        
    }
    if ((*game).capsule.state == 1) {
        (*game).capsule.dure_round += 1;//这里应该是重复加了
    }
     // This is incorrect.
}

/* Adds a capsule to the game, at row = r, column = c.
 * Capsules should be added only to an empty place,
 * or added to a cell with food to upgrade that food.
 * After you successfully add a capsule, return true.
 * Return false on failures.
 *
 * Capsules will grant Pacman CAPSULE_SCORE = 50 and
 * CAPSULE_DURATION = 10 turns of superpower when eaten.
 *
 * When with superpower, scared ghosts will be displayed in 'X',
 * and will be unable to move every other turn.
 * (they can move on the turn when Pacman eats a capsule.)
 * When Pacman eats a scared ghost, it earns GHOST_SCORE = 200.
 *
 * Pacman's superpower activates immediately when it eats a
 * capsule, and counts down immediately after Pacman's turn,
 * starting from its next turn. In other words, Pacman's superpower
 * ends after 10 turns at the same moment of eating a capsule.
 */
bool AddCapsule(Game* game, int r, int c) {
    if (r < 0 || r >= (*game).rows || c < 0 || c >= (*game).columns) {
        return false;
    }
    if ((*game).grid[r][c] == ' ') {
        (*game).grid[r][c] = 'o';
        (*game).foodCount += 1;
        return true;
    }
    else if ((*game).grid[r][c]=='.') {
        (*game).grid[r][c] = 'o';
        return true;
    }
    else {
        return false;
    }

}
 // This is not always correct.



///////////////////////////////////////////////////////////////////////////////
/////////////////// Please submit all code above to OJ ////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Declarations of provided functions
void PlayGame(Game* game);

int main() {
    Game* game = NewGame(8, 8);
    
    //AddWall(game, 0, 1);// Add walls, foods, and pacman here.
    //AddFood(game, 4,2);
    //AddFood(game, 1,2);
    //AddPacman(game, 2, 3);
    
    AddCapsule(game, 3,4);
    //AddFood(game, 3,2);
    //AddCapsule(game, 0,2);
    //AddFood(game, 3,3);
    //AddFood(game, 3, 0);
    //AddWall(game, 2,2);
    //AddFood(game, 4,4);
    //AddWall(game,1,0);
    //AddFood(game, 2, 3);
    //AddFood(game, 1, 3);
    AddCapsule(game, 3, 3);
    //AddCapsule(game, 3, 2);
    //AddCapsule(game, 4, 2);
    //AddWall(game, 1, 1);
    //AddWall(game, 1, 2);
    AddWall(game, 2,4);
   /* AddWall(game, 0, 3);
    AddWall(game, 0, 2);
    AddWall(game, 1, 1);
    AddWall(game, 2, 2);
    AddWall(game, 2,3);*/
  
    
    //AddWall(game, 2, 3);
    //AddWall(game, 2,2);
    AddPacman(game,3 ,2);
    //AddWall(game, 4, 4);
    //AddPacman(game, 1, 2);
    //printf("%d\n", game->state);
    //AddFood(game, 4, 4);
    //AddGhost(game,3,1,1);
    //AddGhost(game, 1, 1, 3);
    //AddGhost(game, 2, 3, 2);
    AddGhost(game, 1,1,3);
    AddGhost(game, 2, 3, 2);
    AddGhost(game, 2, 2, 0);
    //AddGhost(game, 0, 4, 1);
    // AddGhost(game, 2, 3, 3);
    
    PlayGame(game);
    
}

///////////////////////////////////////////////////////////////////////////////
//////////////////////// DO NOT MODIFY ANY CODE BELOW! ////////////////////////
///////////////////////////////////////////////////////////////////////////////

/* This function prints the game grid with boundary,
 * and any message depending on game state.
 * Please make sure that, after any action is done,
 * game->state, game->score, and game->foodCount
 * are correctly updated.
 */
#ifdef _WIN32

#include <windows.h>

#endif // _WIN32

void PrintGame(Game* game) {
    if (!game || !game->grid) return;

    // If Windows, clear console.
#ifdef _WIN32 
    system("cls");
#else
// Clears terminal screen
    fflush(stdout);
    system("clear");
#endif

    // The game grid
    //printf("%d\n", game->state);
    printf(" ");
    for (int i = 0; i < game->columns; i++)
        printf("_");
    printf(" \n");

    for (int i = 0; i < game->rows; i++) {
        printf("|");
        for (int j = 0; j < game->columns; j++)
            printf("%c", game->grid[i][j]);
        printf("|\n");
    }
    printf("\\");
    for (int i = 0; i < game->columns; i++)
        printf("-");
    printf("/\n\n");
    

    //printf("%d\n", game->state);
    // Messages on different states
    switch (game->state) {
    case losing:
        printf("Pacman died! Your score: %d\n", game->score);
        break;
    case onGoing:
        printf("Score: %d\n", game->score);
        printf("There are %d foods remaining!\n", game->foodCount);
        printf("Pacman wants food! (control by w/a/s/d/i, confirm by Enter)\n\n");
        break;
    case winning:
        printf("Victory! Your score: %d\n", game->score);
        break;
    default:
        printf("ERROR: invalid game state!\n");
    }
}

/* Plays the game, and calls EndGame on winning or losing.
 */
void PlayGame(Game* game) {

    // Prints the initial grid
    PrintGame(game);
 

    // Main loop of game. Terminates when the game ends.
    while (true) {
        // We only care about one charater, but should eat the whole line of input.
        char input[127];
        input[0] = '\0';
        scanf_s("%[^\n]", input,sizeof(input));
        // Handles the '\n'.
        getchar();
        Direction direction;
        switch (input[0]) {
        case 'w':
        case 'W':
            direction = up; break;
        case 'a':
        case 'A':
            direction = left; break;
        case 's':
        case 'S':
            direction = down; break;
        case 'd':
        case 'D':
            direction = right; break;
        case 'i':
        case 'I':
            direction = idle; break;
        default:
            PrintGame(game);
            continue;
        }

        // Pacman moves first.
        MovePacman(game, direction);

        // Wins if Pacman eats all the food, loses if Pacman bumps into a ghost.
        if (game->state != onGoing) {
            break;
        }

        // If you haven't implemented ghosts, this does nothing.
        MoveGhosts(game);
        //printf("%d\n", (*game).capsule.dure_round);

        // Loses if a ghost kills Pacman.
        if (game->state != onGoing) {
            break;
        }
        PrintGame(game);
    }

    // End game message
    PrintGame(game);
    printf("Press Enter to exit.\n");
    EndGame(game);
    getchar();
}
