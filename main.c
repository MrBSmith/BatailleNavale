#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#include "prototype.h"
#include "functions.h"

// Main procedure
int main()
{
    player player1;
    player player2;

    player* player_pointer_list[2] = {&player1, &player2};
    player* p_current_player = player_pointer_list[0];
    player* p_opponent_player = player_pointer_list[1];

    int player_nb = sizeof(player_pointer_list) / sizeof(player_pointer_list[0]);

    // Get the players to enter their names
    for(int p = 0; p < player_nb; p++){
        printf("Entrez le nom du %de joueur\n", p + 1);
        gets((*player_pointer_list[p]).name);
    }

    // Initialize arrays
    init_color_array(player1.self_board);
    init_char_array(player1.enemy_board);
    init_color_array(player2.self_board);
    init_char_array(player2.enemy_board);

    vector2 preview_array[ARRAY_SIZE][ARRAY_SIZE];

    init_color_array(preview_array);


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
                display_boat_placement((*p_current_player).self_board, cursor_position, current_boat, direction, p_current_player);
            }
            input = -1;

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

                // Else if the player's input is enter, place the current boat in the cursor position
                }else if(input == ENTER){
                    place_boat((*p_current_player).self_board, current_boat, cursor_position, direction);
                    nb_ex_left--;
                }

                // Display
                copy_board((*p_current_player).self_board, preview_array);
                display_boat_placement((*p_current_player).self_board, cursor_position, current_boat, direction, p_current_player);
            }
        }
    }

    cursor_position.x = 0;
    cursor_position.y = 0;

    // Gameplay Procedure
    for(int p = 0; p < player_nb; p++){

        p_current_player = player_pointer_list[p];
        p_opponent_player = get_opponent(player_pointer_list, p_current_player);

        // Display self board
        display_player_board_state(p_current_player -> self_board, p_opponent_player -> enemy_board);

        input = ask_for_input();
        respond_to_input(input, p_cursor_pos, p_direction);

        // If the player's input is a direction, ceil the position of the cursor
        if(input != ENTER && input != ERR){
            ceil_position(p_cursor_pos, 0, ARRAY_SIZE - 1, 0, ARRAY_SIZE - 1);

        // Else if the player's input is enter, place the current boat in the cursor position
        }else if(input == ENTER){
            // Shoot procedure (yet to be added)
        }

        // Display opponent's board state (Yet to be added)

        if(p == player_nb - 1){
            p = 0;
        }
    }

    return 0;
}
