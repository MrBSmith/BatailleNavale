#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#define HORIZONTAL 0
#define VERTICAL 1
#define ARRAY_SIZE 10

////    CUSTOM TYPES    ////

// Booleen
typedef enum BOULEIN{
    VRAI = 0,
    FAUX = 1
} BOULEIN;


// Color list definition
typedef enum COLOR{
    GREEN = 2,
    RED = 12,
    BLACK = 0,
    BLUE = 9,
    KAKI = 6,
    WHITE = 15
} COLOR;


// Input list definition
typedef enum INPUTS{
    EMPTY_INPUT,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ENTER,
    SPACE,
    ERR
} INPUTS;


// Vector2 definition
typedef struct vector2{
    int x;
    int y;
} vector2;


// Boat type definition
typedef struct boat{
    char name[12];
    vector2 position;
    int lenght;
    int initial_nb;
} boat;


// Define the cell of a board
typedef struct cell{
    char state;
    vector2 content;
} cell;


// Player type definition
typedef struct player{
    char name[10];
    cell board[ARRAY_SIZE][ARRAY_SIZE];
    int score;
} player;


// Cells color definition
vector2 EMPTY_CELL = {WHITE, BLACK};
vector2 CURSOR_CELL = {BLACK, WHITE};
vector2 WATER_CELL = {WHITE, BLUE};
vector2 DAMAGED_BOAT_CELL = {WHITE, RED};
vector2 UNDAMAGED_BOAT_CELL = {WHITE, KAKI};

#endif // TYPES_H_INCLUDED
