#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

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
    vector2 self_board[ARRAY_SIZE][ARRAY_SIZE];
    char enemy_board[ARRAY_SIZE][ARRAY_SIZE];
}player;


#endif // TYPES_H_INCLUDED
