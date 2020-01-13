#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "types.h"
#include "prototype.h"

//////// CURSOR RELATED FUNCTIONS ////////

// Reset cursor position
void reset_cursor_pos(vector2* p_cursor){
    p_cursor -> x = 0;
    p_cursor -> y = 0;
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

//////// MENU NAVIGATION FUNCTIONS ////////

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

//////// BINARY FILE RELATED FUNCTIONS ////////

// Write the score and the player's name into the file
void write_score(char name[20], int score){

    FILE* p_score_file = fopen("score.bin", "ab");
    int str_size_oct = sizeof(name[0]) * 20;

    if(p_score_file == NULL){
        printf("L'ouverture du fichier n'a pas fonctionnee\n");
    } else {
        fwrite(name, str_size_oct, 1, p_score_file);
        fwrite(&score, 4, 1, p_score_file);
        fclose(p_score_file);
    }
}


//////// CHECKING FUCNTIONS ////////

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

// Check if the current boat location is valid. Return VRAI is the boat location is valid, FAUX if not
BOULEIN is_boat_location_valid(player* p_current_player, vector2 cursor_pos, boat* p_current_boat, int direction){
    for(int i = 0; i < p_current_boat -> lenght; i++){
        if(direction == HORIZONTAL){
            if(p_current_player -> board[cursor_pos.y][cursor_pos.x + i].content.y == UNDAMAGED_BOAT_CELL.y){
                return FAUX;
            }
        } else {
            if(p_current_player -> board[cursor_pos.y + i][cursor_pos.x].content.y == UNDAMAGED_BOAT_CELL.y){
                return FAUX;
            }
        }
    }
    return VRAI;
}

// Check for victory condition. Return VRAI if the current player wins, FAUX if not
BOULEIN is_winning(player *p_opponent, boat* boat_pointer_list[], int boat_list_lenght){
    int cells_to_hit = 0;
    int boat_touched = 0;

    // Determine the number of cells you have to successfully hit to win
    for(int i = 0; i < boat_list_lenght; i++){
        cells_to_hit += boat_pointer_list[i] -> initial_nb * boat_pointer_list[i] -> lenght;
    }

    // Determine the number of cells you did hit
    for(int i = 0; i < ARRAY_SIZE; i++){
        for(int j = 0; j < ARRAY_SIZE; j++){
            if(p_opponent -> board[i][j].content.y == DAMAGED_BOAT_CELL.y){
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

//////// PLAYERS MANAGMENT FUNCTIONS ////////

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

////////   DISPLAY PROCEDURES  ////////

// Display the current player's boat placement
void display_boat_placement(vector2 cursor_pos, boat* p_current_boat, int direction, player* p_current_player){
    system("cls");
    printf("Au tour de %s de placer ses bateaux.\n", p_current_player -> name);
    printf("Utilisez Z Q S et D pour vous deplacer dans la grille, ESPACE pour tourner le bateau, ENTRER pour le placer.\n\n");
    print_array_placement(p_current_player -> board, cursor_pos, p_current_boat, direction);
}


// Display gameplay procedure
void display_gameplay(player* p_current_player, player* p_opponent_player, vector2 cursor_position){
    system("cls");

    // Print witch player's turn it is
    printf("C'est le tour de %s: \n", p_current_player -> name);

    // Print the current_player board
    printf("Voici l'etat de votre grille:\n");
    print_board_state(p_current_player -> board, p_opponent_player -> board, cursor_position, FAUX);

   // Print what the current player knows about the opponent board
    printf("Voici l'etat de la grille de votre adversaire:\n");
    printf("Utilisez Z Q S et D pour vous deplacer dans la grille, ENTRER pour tirer.\n\n");
    print_board_state(p_current_player -> board, p_opponent_player -> board, cursor_position, VRAI);
}


//////// PRINT FUNCTIONS ////////

// Print the board of a player
void print_board_state(cell player_board[][ARRAY_SIZE], cell enemy_board[][ARRAY_SIZE], vector2 cursor_pos, BOULEIN shooting){
    for(int i = 0; i < ARRAY_SIZE; i++){
        for(int j = 0; j < ARRAY_SIZE; j++){

            // If we want to print the board of the current player
            if(shooting == FAUX){

                change_text_color_vector2(player_board[i][j].content);

                // In any case, print the state of the cell
                printf("%c ", player_board[i][j].state);

            // If we want to print what the current player knows about the opponent board
            } else {
                // Change the color of the current cell if it's where the cursor is
                if(cursor_pos.x == j && cursor_pos.y == i){
                    change_text_color_vector2(CURSOR_CELL);

                // If the current cell as already been fired, show it content
                } else if(enemy_board[i][j].state == 'X'){
                    change_text_color_vector2(enemy_board[i][j].content);

                // If the current cell has not been fired, hide it content
                } else{
                    change_text_color_vector2(EMPTY_CELL);
                }

                // In any case, print the state of the cell
                printf("%c ", enemy_board[i][j].state);
            }
        }
        printf("\n");
    }
    // Reset the color for further printing
    change_text_color_vector2(EMPTY_CELL);
    printf("\n");
}


// Print every cells of the given array
void print_array_placement(cell board[ARRAY_SIZE][ARRAY_SIZE], vector2 cursor_pos, boat* p_curent_boat, int direction){
    for(int i = 0; i < ARRAY_SIZE; i++){
        for(int j = 0; j < ARRAY_SIZE; j++){
            if(is_cell_inside_boat(direction, cursor_pos, p_curent_boat -> lenght, i, j) == VRAI){
                change_text_color_vector2(CURSOR_CELL);
            } else {
                change_text_color_vector2(board[i][j].content);
            }
            printf("0 ");
        }
        printf("\n");
    }
    change_text_color_vector2(EMPTY_CELL);
    printf("\n");
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

//////// COLOR RELATED FUNCTIONS ////////

// Change the colors of the text with a vector2, the x is the text color, the y the background color
void change_text_color_vector2(vector2 cell_color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, cell_color.y * 16 + cell_color.x);
}


//////// BOAT PLACEMENT PROCEDURE ////////

// Place the given boat at the given position, with the given direction in the given array
void place_boat(cell board[ARRAY_SIZE][ARRAY_SIZE], boat* p_current_boat, vector2 cursor_pos, int direction){
    int h = 0, v = 0, i = 0, j = 0;

    while(i < p_current_boat -> lenght && j < p_current_boat -> lenght){
        h = cursor_pos.y + i;
        v = cursor_pos.x + j;

        if (direction == VERTICAL){
            i++;
        } else {
            j++;
        }

        board[h][v].content = UNDAMAGED_BOAT_CELL;
    }
}


//////// INPUT RELATED FUNCTIONS ////////

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


//////// TOGGLE FUNCTIONS ////////

// Toggle player index
int toggle_player_index(int p){
    if(p == 0){
        p = 1;
    } else {
        p = 0;
    }
    return p;
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


//////// INITIALIZATION FUNCTIONS ////////

// Initialize the given board with 0 char for the state (meaning its untouched) and WATER_CELL for the content in every cells
void init_board(cell board[ARRAY_SIZE][ARRAY_SIZE]){
    for(int i = 0; i < ARRAY_SIZE; i++){
        for(int j = 0; j < ARRAY_SIZE; j++){
            board[i][j].state = '0';
            board[i][j].content = WATER_CELL;
        }
    }
}

//////// ARRAY DUPLACTION ////////

// Copy the given array into the second given array
void copy_board(vector2 board_to_copy[ARRAY_SIZE][ARRAY_SIZE], vector2 destination_board[ARRAY_SIZE][ARRAY_SIZE]){
    for(int i = 0; i < ARRAY_SIZE; i++){
        for(int j = 0; j < ARRAY_SIZE; j++){
            destination_board[i][j] = board_to_copy[i][j];
        }
    }
}

#endif // FUNCTIONS_H_INCLUDED
