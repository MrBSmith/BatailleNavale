#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "types.h"
#include "prototype.h"

// Menu navigation
int navigate_menu(int index, int menu_size, INPUTS input){
    if(input == UP){
        index--;
        if(index < 0){
            index = menu_size - 1;
        }
    } else if(input == DOWN){
        index++;
        if(index > menu_size - 1){
            index = 0;
        }
    }
    return index;
}

// Toggle player index
int toggle_player_index(int p){
    if(p == 0){
        p = 1;
    } else {
        p = 0;
    }
    return p;
}

// Write into the file
void write_score(player* p_player, int score){
    FILE* p_score_file = fopen("score.bin", "w");

    if(p_score_file == NULL){
        printf("L'ouverture du fichier n'a pas fonctionnee\n");
    } else {
        printf("L'ouverture du fichier a bien fonctionnee\n");
    }
}

// Return VRAI is the boat location is valid, FAUX if not
BOULEIN is_boat_location_valid(player* p_current_player, vector2 cursor_pos, boat current_boat, int direction){
    for(int i = 0; i < current_boat.lenght; i++){
        if(direction == HORIZONTAL){
            if(p_current_player -> self_board[cursor_pos.y][cursor_pos.x + i].y == UNDAMAGED_BOAT_CELL.y){
                return FAUX;
            }
        } else {
            if(p_current_player -> self_board[cursor_pos.y + i][cursor_pos.x].y == UNDAMAGED_BOAT_CELL.y){
                return FAUX;
            }
        }
    }
    return VRAI;
}

// Print the menu
void print_menu(char* menu_option_list[3], int menu_option_list_size, int cursor){

    system("cls");

    vector2 RED_TEXT = {RED, BLACK};
    vector2 NORMAL_TEXT = {WHITE, BLACK};
    char str[20];

    for(int i = 0; i < menu_option_list_size; i++){

        // Turn the text red, if it is the currently selected text
        if(i == cursor){
            change_text_color_vector2(RED_TEXT);
        } else {
            change_text_color_vector2(NORMAL_TEXT);
        }

        strcpy(str, menu_option_list[i]);
        printf("%s", str);

        change_text_color_vector2(NORMAL_TEXT);
        printf("\n");
    }
}

// Display gameplay procedure
void display_gameplay(player* p_current_player, player* p_opponent_player, vector2 cursor_position){
    system("cls");

    // Print witch player's turn it is
    printf("C'est le tour de %s: \n", p_current_player -> name);

    // Print the current_player self board
    printf("Voici l'etat de votre grille:\n");
    print_board_state(p_current_player -> self_board, p_opponent_player -> enemy_board, cursor_position, FAUX);

   // Print what the current player knows about the opponent board
    printf("Voici l'etat de la grille de votre adversaire:\n");
    print_board_state(p_opponent_player -> self_board, p_current_player -> enemy_board, cursor_position, VRAI);
}

// Victory condition: return VRAI if the current player wins, FAUX if not
BOULEIN is_winning(player *p_opponent, boat boat_list[], int boat_list_lenght){
    int cells_to_hit = 0;
    int boat_touched = 0;

    // Determine the number of cells you have to successfully hit to win
    for(int i = 0; i < boat_list_lenght; i++){
        cells_to_hit += boat_list[i].initial_nb * boat_list[i].lenght;
    }

    // Determine the number of cells you did hit
    for(int i = 0; i < ARRAY_SIZE; i++){
        for(int j = 0; j < ARRAY_SIZE; j++){
            if(p_opponent -> self_board[i][j].y == DAMAGED_BOAT_CELL.y){
                 boat_touched++;
            }
        }
    }

    // Check if the player has touched all the cells he needs to win
    if(boat_touched >= cells_to_hit){
        return VRAI;
    }

    // Return false, in any other case
    return FAUX;
}


// Print the board of a player
void print_board_state(vector2 self_board[][ARRAY_SIZE], char enemy_board[][ARRAY_SIZE], vector2 cursor_pos, BOULEIN shooting){
    for(int i = 0; i < ARRAY_SIZE; i++){
        for(int j = 0; j < ARRAY_SIZE; j++){
            if(shooting == FAUX){
                change_text_color_vector2(self_board[i][j]);
            } else {
                if(cursor_pos.x == j && cursor_pos.y == i){
                    change_text_color_vector2(CURSOR_CELL);
                } else if(enemy_board[i][j] == 'X'){
                    change_text_color_vector2(self_board[i][j]);
                } else{
                    change_text_color_vector2(EMPTY_CELL);
                }
            }
            printf("%c ", enemy_board[i][j]);
        }
        printf("\n");
    }
    change_text_color_vector2(EMPTY_CELL);
    printf("\n");
}


// Return the current player's opponent
player* get_opponent(player* player_pointer_array[], player *p_current_player){
    player* p_opponent;
    if(p_current_player == player_pointer_array[0]){
        p_opponent = player_pointer_array[1];
    } else{
        p_opponent = player_pointer_array[0];
    }
    return p_opponent;
}


// Display the current player's boat placement
void display_boat_placement(vector2 g_array[ARRAY_SIZE][ARRAY_SIZE], vector2 cursor_pos, boat current_boat, int direction, player* p_current_player){
    system("cls");
    printf("Au tour de %s de placer ses bateaux.\n", (*p_current_player).name);
    print_array_placement((*p_current_player).self_board, cursor_pos, current_boat, direction);
}


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

        board[h][v] = UNDAMAGED_BOAT_CELL;
    }
}


// Get inputs from a player, and return the corresponding input type
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
        case UP: position -> y--; break;
        case DOWN: position -> y++; break;
        case LEFT: position -> x--; break;
        case RIGHT: position -> x++; break;
        case SPACE: toggle_direction(p_direction); break;
        case ENTER: break;
        case ERR: printf("Erreur\n"); break;
        default: break;
    }
}


// Ceil the given position to given min and max
void ceil_position(vector2 *position, int x_min, int x_max, int y_min, int y_max){
    if(position -> x < x_min){
        position -> x = x_min;
    } else if(position -> x > x_max){
        position -> x = x_max;
    }
    if(position -> y < y_min){
        position -> y = y_min;
    } else if(position -> y > y_max){
        position -> y = y_max;
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
            array[i][j] = WATER_CELL;
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
void print_array_placement(vector2 g_array[ARRAY_SIZE][ARRAY_SIZE], vector2 cursor_pos, boat curent_boat, int direction){
    for(int i = 0; i<ARRAY_SIZE; i++){
        for(int j = 0; j<ARRAY_SIZE; j++){
            if(is_cell_inside_boat(direction, cursor_pos, curent_boat.lenght, i, j) == VRAI){
                change_text_color_vector2(CURSOR_CELL);
            } else {
                change_text_color_vector2(g_array[i][j]);
            }
            printf("0 ");
        }
        printf("\n");
    }
    change_text_color_vector2(EMPTY_CELL);
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


// Change the colors of the text with a vector2, the x is the text color, the y the background color
void change_text_color_vector2(vector2 cell_color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, cell_color.y * 16 + cell_color.x);
}

#endif // FUNCTIONS_H_INCLUDED
