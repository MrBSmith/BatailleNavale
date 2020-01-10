#ifndef PROCEDURES_H_INCLUDED
#define PROCEDURES_H_INCLUDED

#include "types.h"
#include "prototype.h"
#include "functions.h"

// Menu procedure
int menu(){

    char option1[20] = "Nouvelle partie";
    char option2[20] = "Score";
    char option3[20] = "Quitter";

    char* menu_option_list[3] = {option1, option2, option3};
    int menu_option_list_size = sizeof(menu_option_list) / sizeof(menu_option_list[0]);

    INPUTS input = EMPTY_INPUT;

    int i = 0;

    while(input != ENTER){
        // Print the menu
        print_menu(menu_option_list, menu_option_list_size, i);

        // Wait for player's input
        input = ask_for_input();

        // Navigate through the menu
        i = navigate_menu(i, menu_option_list_size, input);
    }
    return i;
}


// Procedure of a game
void gameplay()
{
    system("cls");

    // Players definition
    player player1, player2;

    player* player_pointer_list[2] = {&player1, &player2};
    player* p_current_player = player_pointer_list[0];
    player* p_opponent_player = player_pointer_list[1];

    int player_nb = sizeof(player_pointer_list) / sizeof(player_pointer_list[0]);

    // Get the players to enter their names
    for(int p = 0; p < player_nb; p++){
        printf("Entrez le nom du %de joueur\n", p + 1);
        gets(player_pointer_list[p] -> name);
    }

    // Initialize arrays
    init_color_array(player1.self_board);
    init_char_array(player1.enemy_board);
    init_color_array(player2.self_board);
    init_char_array(player2.enemy_board);

    // Cursor declaration
    vector2 cursor_position = {0, 0};
    vector2* p_cursor_pos = &cursor_position;

    int direction = HORIZONTAL;
    int* p_direction = &direction;

    // Declare the types of boats
    boat carrier = {"Porte-Avions", {0, 0}, 5 , 1};
    boat battleShip = {"Croiseur", {0, 0}, 4 , 1};
    boat destroyer = {"Torpilleur", {0, 0}, 3, 2};
    boat submarine = {"Sous-marin", {0, 0}, 2, 1};

    boat boat_list[4] = {carrier, battleShip, destroyer, submarine};
    boat current_boat;

    int boat_type_nb = sizeof(boat_list) / sizeof(boat_list[0]);

    int input, nb_ex_left;

    // Boat placement loop
    // Loop through every players
    for(int p = 0; p < player_nb; p++){

        cursor_position.x = 0;
        cursor_position.y = 0;
        p_current_player = player_pointer_list[p];

        // Loop through the list of boat types
        for(int i = 0; i < boat_type_nb; i++){

            current_boat = boat_list[i];
            nb_ex_left = current_boat.initial_nb;
            if (i == 0){
                display_boat_placement(p_current_player -> self_board, cursor_position, current_boat, direction, p_current_player);
            }

            // Empty the input variable
            input = EMPTY_INPUT;

            // Procedure for placing one type of boat
            while(nb_ex_left != 0){

                input = ask_for_input();
                respond_to_input(input, p_cursor_pos, p_direction);

                // If the player's input is a direction, ceil the position of the cursor
                if(input != ENTER && input != ERR){
                    if(direction == HORIZONTAL){
                        ceil_position(p_cursor_pos, 0, ARRAY_SIZE - current_boat.lenght, 0, ARRAY_SIZE - 1);
                    } else {
                        ceil_position(p_cursor_pos, 0, ARRAY_SIZE - 1, 0, ARRAY_SIZE - current_boat.lenght);
                    }

                    // Refresh display
                    display_boat_placement(p_current_player -> self_board, cursor_position, current_boat, direction, p_current_player);

                // Else if the player's input is enter, place the current boat in the cursor position
                } else if(input == ENTER) {

                    write_score(p_current_player, 10);

                    if(is_boat_location_valid(p_current_player, cursor_position, current_boat, direction) == VRAI){
                        // Place the boat
                        place_boat(p_current_player -> self_board, current_boat, cursor_position, direction);
                        nb_ex_left--;

                        // Refresh display
                        display_boat_placement(p_current_player -> self_board, cursor_position, current_boat, direction, p_current_player);
                    } else {
                        printf("La position de votre bateau n'est pas valide.\n");
                    }
                }
            }
        }
    }

    // Reset the cursor position
    cursor_position.x = 0;
    cursor_position.y = 0;

    // Reset the input

    input = EMPTY_INPUT;
    INPUTS next_phase;

    BOULEIN fire;
    BOULEIN somebody_win = FAUX;

    int p = 0;

    // Gameplay Procedure
    while(somebody_win == FAUX){

        fire = FAUX;

        p_current_player = player_pointer_list[p];
        p_opponent_player = get_opponent(player_pointer_list, p_current_player);

        // Refresh the display at every input
        while(fire == FAUX){

            next_phase = ERR;

            // Display both players boards
            display_gameplay(p_current_player, p_opponent_player, cursor_position);

            // Wait for the player to enter an input
            input = ask_for_input();
            respond_to_input(input, p_cursor_pos, p_direction);

            // If the player's input is a direction, ceil the position of the cursor
            if(input != ENTER && input != ERR){
                ceil_position(p_cursor_pos, 0, ARRAY_SIZE - 1, 0, ARRAY_SIZE - 1);

            // Else if the player's input is ENTER, try to fire in the current cursor's position
            } else if(input == ENTER){

                // Check if the current position has already been fired of not
                if(p_current_player -> enemy_board[cursor_position.y][cursor_position.x] != 'X'){
                    p_current_player -> enemy_board[cursor_position.y][cursor_position.x] = 'X';
                    fire = VRAI;

                    // Refresh the display
                    display_gameplay(p_current_player, p_opponent_player, cursor_position);

                    // Damage the boat if there is one in the current position
                    if(p_opponent_player -> self_board[cursor_position.y][cursor_position.x].y == UNDAMAGED_BOAT_CELL.y){
                        p_opponent_player -> self_board[cursor_position.y][cursor_position.x] = DAMAGED_BOAT_CELL;
                        printf("Touche!\n");
                    } else {
                        printf("Dans l'eau!\n");
                    }
                } else {
                    printf("Vous avez deja tire ici. Essayez de viser ailleurs!\n");
                }

                printf("Appuyez sur entrer pour continuer.\n");

                // Wait for the player to hit enter
                while(next_phase != ENTER){
                    next_phase = ask_for_input();
                }
            }

            // Check for current player's victory
            if(is_winning(p_opponent_player, boat_list, boat_type_nb) == VRAI){
                printf("%s a gagne la partie!\n", p_current_player -> name);
                somebody_win = VRAI;
                write_score(p_current_player, 10);
            }
        }

        // Change player each end of turn
        p = toggle_player_index(p);
    }
}

#endif // PROCEDURES_H_INCLUDED
