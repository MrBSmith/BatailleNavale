#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define HORIZONTAL 0
#define VERTICAL 1
#define ARRAY_SIZE 10

// Custom types
typedef enum BOULEIN{
    VRAI = 0,
    FAUX = 1
}BOULEIN;

typedef enum COLOR{
    RED = 12,
    BLACK = 0,
    BLUE = 9,
    WHITE = 15
}COLOR;

typedef enum INPUTS{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER,
    SPACE,
    ERR
}INPUTS;

typedef struct vector2{
    int x;
    int y;
}vector2;

typedef struct boat{
    char name[12];
    vector2 position;
    int lenght;
    int initial_nb;
}boat;

typedef struct player{
    char name[10];
    char boats_position[ARRAY_SIZE][ARRAY_SIZE];
    char board_state[ARRAY_SIZE][ARRAY_SIZE];
}player;

// Prototypes
INPUTS ask_for_input();
void init_array(char array[ARRAY_SIZE][ARRAY_SIZE]);
void print_array(char array[ARRAY_SIZE][ARRAY_SIZE], vector2 cursor_pos, BOULEIN print_cursor);
void print_array_placement(char array[ARRAY_SIZE][ARRAY_SIZE], vector2 cursor_pos, BOULEIN print_cursor, boat curent_boat, int direction);
void toggle_bool(BOULEIN boolean);
void toggle_direction(int *p_direction);
void init_color(int t, int f);
void respond_to_input(INPUTS input, vector2 *position, int *p_direction);
void ceil_position(vector2 *position, int x_min, int x_max, int y_min, int y_max);


// Main procedure
int main()
{
    player player1;
    player player2;

    char preview_array[ARRAY_SIZE][ARRAY_SIZE];

    vector2 cursor_position = {0, 0};
    vector2* p_cursor_pos = &cursor_position;
    int direction = HORIZONTAL;
    int* p_direction = &direction;

    // Initialize arrays
    init_array(player1.boats_position);
    init_array(player1.board_state);
    init_array(player2.boats_position);
    init_array(player2.board_state);
    init_array(preview_array);

    // Declare the types of boats
    boat carrier = {"Porte-Avions", {0, 0}, 5 , 1};
    boat battleShip = {"Croiseur", {0, 0}, 4 , 1};
    boat destroyer = {"Tropilleur", {0, 0}, 3, 2};
    boat submarine = {"Sous-marin", {0, 0}, 2, 1};

    boat current_boat = carrier;
    int nb_ex_left = current_boat.initial_nb;

    // printf("%d, %d\n", cursor_position.x, cursor_position.y); // Print cursor position (debug purpose)

    // Boat placement loop
    while(2+2 != 5){
        int input = ask_for_input();
        respond_to_input(input, p_cursor_pos, p_direction);
        if(input != ENTER && input != ERR){

            if(direction == HORIZONTAL){
                ceil_position(p_cursor_pos, 0, ARRAY_SIZE - current_boat.lenght, 0, ARRAY_SIZE - 1);
            } else {
                ceil_position(p_cursor_pos, 0, ARRAY_SIZE - 1, 0, ARRAY_SIZE - current_boat.lenght);
            }

            system("cls");
            printf("%d, %d\n", cursor_position.x, cursor_position.y);
            memcpy(preview_array, player1.boats_position, sizeof(preview_array));
            print_array_placement(preview_array, cursor_position, VRAI, current_boat, direction);
        }
    }

    return 0;
}

// Get inputs from a player
INPUTS ask_for_input(){
    int input;
    INPUTS returned_input;
    input = getch();

    switch(input){
        case 8: returned_input = SPACE; break;
        case 32: returned_input = SPACE; break;
        case 13: returned_input = ENTER; break;
        case 90: returned_input = UP; break;
        case 122: returned_input = UP; break;
        case 83: returned_input = DOWN; break;
        case 115: returned_input = DOWN; break;
        case 81: returned_input = LEFT; break;
        case 113: returned_input = LEFT; break;
        case 68: returned_input = RIGHT; break;
        case 100: returned_input = RIGHT; break;
        default: returned_input = ERR; break;
    }
    return returned_input;
}

// Apply the right response to the given input
void respond_to_input(INPUTS input, vector2 *position, int *p_direction){
    switch(input){
        case UP: (*position).y--; break;
        case DOWN: (*position).y++; break;
        case LEFT: (*position).x--; break;
        case RIGHT: (*position).x++; break;
        case SPACE: toggle_direction(p_direction); break;
        case ENTER: printf("Pouet\n"); break;
        case ERR: printf("Erreur\n"); break;
    }
}

// Ceil the given position to given min and max
void ceil_position(vector2 *position, int x_min, int x_max, int y_min, int y_max){
    if((*position).x < x_min){
        (*position).x = x_min;
    } else if((*position).x > x_max){
        (*position).x = x_max;
    }
    if((*position).y < y_min){
        (*position).y = y_min;
    } else if((*position).y > y_max){
        (*position).y = y_max;
    }
}

// Toggle the given booleen
void toggle_bool(BOULEIN boolean){
    if(boolean != TRUE){
        boolean = TRUE;
    } else {
        boolean = FALSE;
    }
}

// Toggle the current boat direction
void toggle_direction(int *p_direction){
    if(*p_direction == HORIZONTAL){
        *p_direction = VERTICAL;
    } else {
        *p_direction = HORIZONTAL;
    }
}

// Initialize the given array with O char in every cells
void init_array(char array[][ARRAY_SIZE]){
    for(int i = 0; i<ARRAY_SIZE; i++){
        for(int j = 0; j<ARRAY_SIZE; j++){
            array[i][j] = 'O';
        }
    }
}

// Print every cells of the given array
void print_array_placement(char array[ARRAY_SIZE][ARRAY_SIZE], vector2 cursor_pos, BOULEIN print_cursor, boat curent_boat, int direction){
    for(int i = 0; i<ARRAY_SIZE; i++){
        for(int j = 0; j<ARRAY_SIZE; j++){
            if(direction == VERTICAL){
                if(print_cursor == VRAI && i >= cursor_pos.y && i < cursor_pos.y + curent_boat.lenght && j == cursor_pos.x){
                    init_color(WHITE, BLUE);
                    printf("%c ", array[i][j]);
                    init_color(WHITE, BLACK);
                } else {
                    printf("%c ", array[i][j]);
                }
            } else {
                if(print_cursor == VRAI && i == cursor_pos.y && j >= cursor_pos.x && j < cursor_pos.x + curent_boat.lenght){
                    init_color(WHITE, BLUE);
                    printf("%c ", array[i][j]);
                    init_color(WHITE, BLACK);
                } else {
                    printf("%c ", array[i][j]);
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Print every cells of the given array
void print_array(char array[ARRAY_SIZE][ARRAY_SIZE], vector2 cursor_pos, BOULEIN print_cursor){
    for(int i = 0; i<ARRAY_SIZE; i++){
        for(int j = 0; j<ARRAY_SIZE; j++){
            if(print_cursor == VRAI && i == cursor_pos.y && j == cursor_pos.x){
                init_color(WHITE, RED);
                printf("%c ", array[i][j]);
                init_color(WHITE, BLACK);
            } else {
                printf("%c ", array[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Define colors
void init_color(int text_col, int back_col){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, back_col * 16 + text_col);
}
