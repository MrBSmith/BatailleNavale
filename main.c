#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#include "prototype.h"
#include "functions.h"
#include "procedures.h"

// Main procedure
int main(){

    int menu_index;
    menu_index = menu();

    switch(menu_index){
        case 0 : gameplay(); break;
        case 1 : /*score();*/ break;
        case 2 : exit(0); break;
    }

    return 0;
}
