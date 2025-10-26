#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "display.c"


/*
    This function saves data to a file
*/
void savegame(int* day, int* daycount, int* outing, int* actionPoint, int* cameraRoll, int* mathLVL, int* mathEXP, int* peLVL, int* peEXP, int* damianBP, int* beckyBP, int* hendersonBP, int* bondBP)
{
    
}

/*
    This function is the main loop which loops through the 40 days
    Preconditions: All parameters are positive integer
    @param day - time of day [1]-Morning, [2]-Afternoon, [3]-Evening
    @param daycount - number of day
    @param outing - where the outing is gonna be [1]-Park, [2]-City Mall, [3]-Ostania Beach, [4]-West Berlint Aquarium, [5]-Ostania Art Museum, [6]-Berlint Mouseney Land, [7]-Park Avenue Dogland
    @param mathLVL - Math level [1],[2],[3],[4](MAX)
    @param mathEXP - Math exp
    @param peLVL - PE level [1],[2],[3],[4](MAX)
    @param peEXP - PE exp
    @param damianBP - Damian Desmond BP
    @param beckyBP - Becky Blackbell BP
    @param hendersonBP - Mr. Henderson BP
    @param bondBP - Bond Forger BP
*/
void gameloop(int* day, int* daycount, int* outing, int* actionPoint, int* cameraRoll, int* mathLVL, int* mathEXP, int* peLVL, int* peEXP, int* damianBP, int* beckyBP, int* hendersonBP, int* bondBP)
{
    int quit = 0; // [0]-Continue, [1]-QUIT
    int input;
    do {

        mainUI(day, daycount, outing, actionPoint, cameraRoll, mathLVL, mathEXP, peLVL, peEXP, damianBP, beckyBP, hendersonBP, bondBP);
        dialogue();


        if ((*daycount % 4 == 0) && *day == 1)
        {
            // ADD
        }

        switch(input = getch())
        {
            case 'Q':
            case 'q':
                quit = 1;
                savegame(day, daycount, outing, actionPoint, cameraRoll, mathLVL, mathEXP, peLVL, peEXP, damianBP, beckyBP, hendersonBP, bondBP);
                break;
            default:
                break;
        }

    } while (quit !=1 );
}

/*
    This function sets a fresh data / variables
*/
void startgame()
{
    int day = 3;
    int daycount = 7;
    int outing = 0;
    int activityPoint = 3;
    int cameraRoll = 5;
    int mathLVL = 1;
    int mathEXP = 0;
    int peLVL = 1;
    int peEXP = 0;
    int damianBP = 0;
    int beckyBP = 0;
    int hendersonBP = 0;
    int bondBP = 0;

    gameloop(&day, &daycount, &outing, &activityPoint, &cameraRoll, &mathLVL, &mathEXP, &peLVL, &peEXP, &damianBP, &beckyBP, &hendersonBP, &bondBP);
}

/*
    This function loads existing data to the variables
*/
void loadgame()
{
    
}


int main()
{
    /* Initialize */
    initscr();              // Start the screen
    start_color();          // Starts color
    noecho();               // Key pressed will not show
    keypad(stdscr, TRUE);   // enables keypad

    int quit = 0;
    int index = 1;
    int input;

    init_pair(1, COLOR_WHITE, COLOR_BLACK); // NORMAL COLOR
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // SELECTED COLOR
    
    /* LOOPS until quit */
    do {
        mainmenu(&index);

        move(0,0);

        switch (input = getch())
        {
            case KEY_UP:
                index--;
                // Checks if index is 0 to set to the highest option
                if (index <= 0)
                {
                    index = 3;
                }
                break;
            case KEY_DOWN:
                index++;
                // Checks if index is over the options to set to 1
                if (index > 3) 
                {
                    index = 1;
                }
                break;
            case '\n':
                if (index == 1)
                {
                    startgame();
                } else if (index == 2)
                {
                    loadgame();
                } else if (index == 3)
                {
                    quit = 1;
                }
                break;
            default:
                break;
        }
        refresh();
    } while (quit != 1);

    endwin();
    return 0;
}






// int asdmain()
// {
//     int day = 5;
    




//     init_pair(2,COLOR_BLACK, COLOR_WHITE);


    
//     int daycount = 5;
//     int timeday = 1;

//     /* Main Menu */
    


//     /* Display the Day, Daycount, Time of Day, Type of Day, Next Outing, AP, Camera Roll */
//     switch (timeday) // Sets Time of Day: 1-Morning, 2-Afternoon, 3-Evening
//     {
//         case 1:
//             mvprintw(2,2,"Day:   %02d - Morning",daycount);
//             break;
//         case 2:
//             mvprintw(2,2,"Day:   %02d - Afternoon",daycount);
//             break;
//         case 3:
//             mvprintw(2,2,"Day:   %02d - Evening",daycount);
//             break;
//         default:
//             mvprintw(2,2,"Day:   %02d - ERROR",daycount);
//             break;
//     }
//     if (daycount % 4 == 0 || daycount == 0)
//     {
//         mvprintw(3,9,"OUTING DAY");
//     } else
//     {
//         mvprintw(3,9,"SCHOOL DAY");
//     }

//     /* Display Controls */
//     // mvprintw(33, 18, " [^][v][<][>] - USE ARROW KEYS TO MOVE     |     [ENTER] - TO SELECT AN OPTION     |     [q/Q] - BACK TO MAIN MENU");
    
//     refresh();

//     // Checks whether you are using linux
//     #ifdef linux
//     /* NOTE: MUST USE KITTY TERMINAL TO WORK */
//     system("kitten icat -z -1 --place 150x150@1x1 anya.jpg"); // Display image using kitty kitten icat
//     #endif

//     int isUpDown = 0;       // Movement: 0 - Left and Right, 1 - Up and Down
//     int index = 0;          // index for options
//     int options = 0;        // Number of Options
//     int part = 0;
    
//     int input;

//     // LOOP UNTIL QUIT
//     while ((input = getch()) != 'q')
//     {
//         switch (input)
//         {
//             case KEY_UP:
//                 if (isUpDown == 1)
//                 {
//                     index--;
//                     // Checks if index is 0 to set to the highest option
//                     if (index <= 0)
//                     {
//                         index = options;
//                     }
//                 }
//                 break;
//             case KEY_DOWN:
//                 if (isUpDown == 1)
//                 {
//                     index++;
//                     // Checks if index is over the options to set to 1
//                     if (index > options) 
//                     {
//                         index = 1;
//                     }
//                 }
//                 break;
//             case KEY_LEFT:
//                 if (isUpDown == 0)
//                 {
//                     index--;
//                     // Checks if index is 0 to set to the highest option
//                     if (index <= 0)
//                     {
//                         index = options;
//                     }
//                 }
//                 break;
//             case KEY_RIGHT:
//                 if (isUpDown == 0)
//                 {
//                     index++;
//                     // Checks if index is over the options to set to 1
//                     if (index > options) 
//                     {
//                         index = 1;
//                     }
//                 }
//                 break;
//             case 10:
//                 enterkey(index, part);
//                 break;
//             default:
//                 break;
//         }
//     }
    
    

//     endwin();
//     return 0;
// }