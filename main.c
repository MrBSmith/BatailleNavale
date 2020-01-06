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
} BOULEIN;

typedef enum COLOR{
    ROUGE = 12,
    NOIR = 0,
    BLEU = 9
} COLOR;

typedef enum INPUTS{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER,
    SPACE,
    ERR
} INPUTS;

typedef struct vector2{
    int x;
    int y;
} vector2;

typedef struct boat{
    char type;
    int lenght;
    vector2 position;
} boat;

typedef struct player{
    char name;
    char boats_position[ARRAY_SIZE][ARRAY_SIZE];
    char board_state[ARRAY_SIZE][ARRAY_SIZE];
}player;

// Prototypes
INPUTS ask_for_input();
void init_array(char array[ARRAY_SIZE][ARRAY_SIZE]);
void print_array(char array[ARRAY_SIZE][ARRAY_SIZE]);
void toggle_bool(BOULEIN boolean);
void toggle_direction(int direction);
void init_color(int t, int f);
void respond_to_input(INPUTS input, vector2 *position, int direction);
void ceil_position(vector2 *position, int min, int max);


// Main procedure
int main()
{
    player player1;
    player player2;

    char preview_array[ARRAY_SIZE][ARRAY_SIZE];

    vector2 cursor_position = {0, 0};
    vector2* p_cursor_pos = &cursor_position;
    int direction = HORIZONTAL;

    init_array(player1.boats_position);
    init_array(player1.board_state);
    init_array(player2.boats_position);
    init_array(player2.board_state);

    print_array(player1.boats_position);
    print_array(player1.board_state);
    print_array(player2.boats_position);
    print_array(player2.board_state);

    printf("%d, %d\n", cursor_position.x, cursor_position.y);

    while(2+2 != 5){
        int input = ask_for_input();
        respond_to_input(input, p_cursor_pos, direction);
        if(input != SPACE && input != ENTER && input != ERR){
            ceil_position(p_cursor_pos, 0, ARRAY_SIZE);
            printf("%d, %d\n", cursor_position.x, cursor_position.y);
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
void respond_to_input(INPUTS input, vector2 *position, int direction){

    switch(input){
        case UP: (*position).y--; break;
        case DOWN: (*position).y++; break;
        case LEFT: (*position).x--; break;
        case RIGHT: (*position).x++; break;
        case SPACE: toggle_direction(direction); break;
        case ENTER: printf("Pouet\n"); break;
        case ERR: printf("Erreur\n"); break;
    }
}

// Ceil the given position to given min and max
void ceil_position(vector2 *position, int min, int max){
    if((*position).x < min){
        (*position).x = min;
    } else if((*position).x > max){
        (*position).x = max;
    }
    if((*position).y < min){
        (*position).y = min;
    } else if((*position).y > max){
        (*position).y = max;
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
void toggle_direction(int direction){
    if(direction != VERTICAL){
        direction = VERTICAL;
    } else {
        direction = HORIZONTAL;
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
void print_array(char array[ARRAY_SIZE][ARRAY_SIZE]){
    for(int i = 0; i<ARRAY_SIZE; i++){
        for(int j = 0; j<ARRAY_SIZE; j++){
                printf("%c ", array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Define colors
void init_color(int t, int f){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,f*16+t);
}
