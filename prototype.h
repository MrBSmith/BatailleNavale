#ifndef PROTOTYPE_H_INCLUDED
#define PROTOTYPE_H_INCLUDED
#include "types.h"

////   PROTOTYPES   ////

// Score file
void init_score_file();
void write_score(char name[20], int score);

// Main procedures of the program
void gameplay();
void score();

// Procedure of the menu, returns the selected menu option index
int menu();

// Navigate through a menu
int navigate_menu(int index, int menu_size, INPUTS input);

// Inputs management
INPUTS ask_for_input();
void respond_to_input(INPUTS input, vector2 *position, int *p_direction);

// Boat placement
void place_boat(cell board[ARRAY_SIZE][ARRAY_SIZE], boat current_boat, vector2 cursor_position, int direction);

// Initialize arrays
void init_board(cell board[ARRAY_SIZE][ARRAY_SIZE]);

// Prints
void print_self_board(cell board[ARRAY_SIZE][ARRAY_SIZE], vector2 cursor_pos, BOULEIN print_cursor);
void print_array_placement(cell board[ARRAY_SIZE][ARRAY_SIZE], vector2 cursor_pos, boat curent_boat, int direction);
void print_board_state(cell board[][ARRAY_SIZE], cell enemy_board[][ARRAY_SIZE], vector2 cursor_pos, BOULEIN shooting);

void print_menu(char* menu_option_list[3], int menu_option_list_size, int cursor);

// Display procedures
void display_boat_placement(vector2 cursor_pos, boat current_boat, int direction, player* p_current_player);
void display_gameplay(player* p_current_player, player* p_opponent_player, vector2 cursor_position);

// Toggle values
void toggle_bool(BOULEIN boolean);
void toggle_direction(int *p_direction);

// Text color
void change_text_color_vector2(vector2 cell_color);

// Limit cursor position
void ceil_position(vector2 *position, int x_min, int x_max, int y_min, int y_max);

// Copy a board in another board
void copy_board(vector2 board_to_copy[ARRAY_SIZE][ARRAY_SIZE], vector2 destination_board[ARRAY_SIZE][ARRAY_SIZE]);
BOULEIN is_cell_inside_boat(int direction, vector2 cursor_pos, int boat_len, int i, int j);

// Return VRAI is the boat location is valid, FAUX if not
BOULEIN is_boat_location_valid(player* p_current_player, vector2 cursor_pos, boat current_boat, int direction);

// Player turn management
player* get_opponent(player* player_pointer_array[], player *p_current_player);

// Winning condition
BOULEIN is_winning(player *p_opponent, boat boat_list[], int boat_list_lenght);

#endif // PROTOTYPE_H_INCLUDED
