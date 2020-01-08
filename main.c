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

    // Get the players to enter their names
    for(int p = 0; p < sizeof(player_pointer_list)/sizeof(player_pointer_list[0]); p++){
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

    int input, nb_ex_left;

    // Loop through every players
    for(int p = 0; p < sizeof(player_pointer_list)/sizeof(player_pointer_list[0]); p++){
        p_current_player = player_pointer_list[p];

        // Boat placement loop
        for(int i = 0; i < sizeof(boat_list)/sizeof(boat_list[0]); i++){

            current_boat = boat_list[i];
            nb_ex_left = current_boat.initial_nb;
            if (i == 0){
                system("cls");
                printf("Au tour de %s de placer ses bateaux.\n", (*p_current_player).name);
                print_array_placement((*p_current_player).self_board, cursor_position, current_boat, direction);
            }
            input = -1;

            // Procedure for placing one type of boat
            while(nb_ex_left != 0){

                input = ask_for_input();
                system("cls");
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
                printf("Au tour de %s de placer ses bateaux.\n", (*p_current_player).name);
                print_array_placement(preview_array, cursor_position, current_boat, direction);
            }
        }
    }

    return 0;
}
