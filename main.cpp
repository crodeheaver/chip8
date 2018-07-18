/*#include <iostream>
#include <ncurses.h>
#include "include/chip8.h"

int main() {

    initscr();			*//* Start curses mode 		  *//*
    if(has_colors() == FALSE)
    {	endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();			*//* Start color 			*//*
    attron(COLOR_PAIR(1));

    chip8 chip;
    chip.load("IBM.ch8");
    for(;;)
    {
        chip.tick();
        if(chip.drawFlag){

            for(int y = 0; y < 32; ++y){
                for(int x = 0; x < 64; ++x){
                    move(y, x);
                    if(chip.display[(y * 64) + x])
                        addch(ACS_CKBOARD);	// Disabled

                }
            }
            chip.drawFlag = false;
        }

        refresh();			*//* Print it on to the real screen *//*
    }
    endwin();			*//* End curses mode		  *//*
    return 0;
}*/

#include <iostream>
#include <ncurses.h>
#include "include/chip8.h"

int main() {

    //initscr();			/* Start curses mode 		  */

    chip8 chip;
    chip.load("IBM.ch8");
    for(;;)
    {
        chip.tick();
        if(chip.drawFlag){

            for(int y = 0; y < 32; ++y){
                for(int x = 0; x < 64; ++x){
                    move(y, x);
                    if(chip.display[(y * 64) + x])
                        printf("0");	// Disabled
                    else
                        printf(" ");

                }
                printf("\n");
            }
            printf("\n");
            chip.drawFlag = false;
        }

        //refresh();			/* Print it on to the real screen */
        //getch();			/* Wait for user input */
    }
    //endwin();			/* End curses mode		  */
    return 0;
}