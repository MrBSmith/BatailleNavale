#ifndef PROTOTYPE_H_INCLUDED
#define PROTOTYPE_H_INCLUDED
#include "types.h"

// Prototypes
INPUTS ask_for_input();
void place_boat(vector2 board[ARRAY_SIZE][ARRAY_SIZE], boat current_boat, vector2 cursor_position, int direction);
void init_char_array(char array[ARRAY_SIZE][ARRAY_SIZE]);
void init_color_array(vector2 array[ARRAY_SIZE][ARRAY_SIZE]);
void print_self_board(vector2 array[ARRAY_SIZE][ARRAY_SIZE], vector2 cursor_pos, BOULEIN print_cursor);
void print_array_placement(vector2 array[ARRAY_SIZE][ARRAY_SIZE], vector2 cursor_pos, boat curent_boat, int direction);
void toggle_bool(BOULEIN boolean);
void toggle_direction(int *p_direction);
void init_color(int text_col, int back_col);
void respond_to_input(INPUTS input, vector2 *position, int *p_direction);
void ceil_position(vector2 *position, int x_min, int x_max, int y_min, int y_max);
void copy_board(vector2 board_to_copy[ARRAY_SIZE][ARRAY_SIZE], vector2 destination_board[ARRAY_SIZE][ARRAY_SIZE]);
BOULEIN is_cell_inside_boat(int direction, vector2 cursor_pos, int boat_len, int i, int j);

#endif // PROTOTYPE_H_INCLUDED
