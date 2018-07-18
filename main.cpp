#include <iostream>
#include <ncurses.h>
#include "include/chip8.h"

int main() {

//    initscr();			/* Start curses mode 		  */
//    printw("Hello World !!!");	/* Print Hello World		  */
//    refresh();			/* Print it on to the real screen */
//    getch();			/* Wait for user input */
//    endwin();			/* End curses mode		  */
    chip8 chip;
    chip.load("IBM.ch8");
    for(;;)
    {
        chip.tick();
    }

    return 0;
}