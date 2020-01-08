#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "types.h"
#include "prototype.h"

// Place the given boat at the given position, with the given direction in the given array
void place_boat(vector2 board[ARRAY_SIZE][ARRAY_SIZE], boat current_boat, vector2 cursor_pos, int direction){
    int h = 0, v = 0, i = 0, j = 0;

    while(i < current_boat.lenght && j < current_boat.lenght){
        h = cursor_pos.y + i;
        v = cursor_pos.x + j;

        if (direction == VERTICAL){
            i++;
        } else {
            j++;
        }

        board[h][v].x = WHITE;
        board[h][v].y = BLUE;
    }
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
        case ENTER: break;
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
void init_char_array(char array[ARRAY_SIZE][ARRAY_SIZE]){
    for(int i = 0; i < ARRAY_SIZE; i++){
        for(int j = 0; j < ARRAY_SIZE; j++){
            array[i][j] = 'O';
        }
    }
}

// Initialize the given array with white for text and black for background in every cells
void init_color_array(vector2 array[ARRAY_SIZE][ARRAY_SIZE]){
    for(int i = 0; i < ARRAY_SIZE; i++){
        for(int j = 0; j < ARRAY_SIZE; j++){
            array[i][j].x = WHITE;
            array[i][j].y = BLACK;
        }
    }
}

// Copy the given array into the second given array
void copy_board(vector2 board_to_copy[ARRAY_SIZE][ARRAY_SIZE], vector2 destination_board[ARRAY_SIZE][ARRAY_SIZE]){
    for(int i = 0; i < ARRAY_SIZE; i++){
        for(int j = 0; j < ARRAY_SIZE; j++){
            destination_board[i][j] = board_to_copy[i][j];
        }
    }
}

// Print every cells of the given array
void print_array_test(vector2 g_array[ARRAY_SIZE][ARRAY_SIZE], vector2 cursor_pos, boat curent_boat, int direction){
    for(int i = 0; i<ARRAY_SIZE; i++){
        for(int j = 0; j<ARRAY_SIZE; j++){
            printf("%d ", g_array[i][j].x);
        }
        printf("\n");
    }
    printf("\n");
}

// Print every cells of the given array
void print_array_placement(vector2 g_array[ARRAY_SIZE][ARRAY_SIZE], vector2 cursor_pos, boat curent_boat, int direction){
    for(int i = 0; i<ARRAY_SIZE; i++){
        for(int j = 0; j<ARRAY_SIZE; j++){
            if(is_cell_inside_boat(direction, cursor_pos, curent_boat.lenght, i, j) == VRAI){
                init_color(WHITE, RED);
            } else {
                init_color(g_array[i][j].x, g_array[i][j].y);
            }
            printf("0 ");
        }
        printf("\n");
    }
    init_color(WHITE, BLACK);
    printf("\n");
}

// Check if the given cell is inside a boat or not
BOULEIN is_cell_inside_boat(int direction, vector2 cursor_pos, int boat_len, int i, int j){
    if (direction == VERTICAL){
         if(i >= cursor_pos.y && i < cursor_pos.y + boat_len && j == cursor_pos.x){
            return VRAI;
        }
    } else {
        if(i == cursor_pos.y && j >= cursor_pos.x && j < cursor_pos.x + boat_len){
            return VRAI;
        }
    }
    return FAUX;
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


#endif // FUNCTIONS_H_INCLUDED
