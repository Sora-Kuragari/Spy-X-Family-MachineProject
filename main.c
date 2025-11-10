#include <stdio.h>
#include <stdlib.h>
#include "display.c"
#include "minigame.c"

// Checks if you are using linux because ncurses have different path on linux than windows
#ifdef linux
#include <ncurses.h>
#else
#include <ncurses\ncurses.h>
#endif


/*
    This function saves data to a file
*/
void savegame(int* day, int* daycount, int* outing, int* actionPoint, int* cameraRoll, int* mathLVL, int* mathEXP, int* peLVL, int* peEXP, int* damianBP, int* beckyBP, int* hendersonBP, int* bondBP)
{
    
}

/*
    This function is the main game loop which loops through the 40 days
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
    // Starts the color
    start_color();
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // SELECTED COLOR

    int quit = 0; // [0]-Continue, [1]-QUIT
    int input, dcounting;
    int options;    // Number of options
    int index = 1;
    int dialogue = 0;

    // Loops for 41 days (day 0 to day 40), ends when its above 40 or the player press the quit key
    for (int i = 0; i <= 40 && quit != 1; i++)
    {
        *daycount = i; // Synconizes daycount with i (Important specially when game is continued from a saved file)

        // Checks if its school day then set it to 2 times else (outing day) set it to 3 times
        if (*daycount % 4 != 0)
        {
            dcounting = 2;
        } else
        {
            dcounting = 3;
        }

        // Loops through the day: Morning -> Afternoon -> Evening (Only on Outing day)
        for (int j = 1; j <= dcounting && quit != 1; j=j)    // Day won't move unless pressed enter (or does an action)
        {
            // Checks if day count is 0, since day 0 should start at Evening
            if (*daycount == 0)
            {
                j = 3;
            } 
            *day = j; // Syncronizes day with j (Important specially when game is continued from a saved file)

            mainUI(day, daycount, outing, actionPoint, cameraRoll, mathLVL, mathEXP, peLVL, peEXP, damianBP, beckyBP, hendersonBP, bondBP);
            dialoguefunc();
            // *actionPoint += mathGame(mathLVL, mathEXP);
            // *actionPoint += peGame(peLVL, peEXP);

            /* Display the options */
            if ((*daycount % 4 != 0) && *day == 1) // If its school day and morning
            {
                options = 4;

                // Display choices
                mvprintw(20,50,"%-35s","  Bond with Damian");
                mvprintw(21,50,"%-35s","  Bond with Becky");
                mvprintw(22,50,"%-35s","  Bond with Mr. Henderson");
                mvprintw(23,50,"%-35s","  Proceed Home");

                // Adds color when its selected based on the index
                attron(COLOR_PAIR(2));
                switch (index)
                {
                case 1:
                    mvprintw(20,50,"%-35s","> Bond with Damian");
                    break;
                case 2:
                    mvprintw(21,50,"%-35s","> Bond with Becky");
                    break;
                case 3:
                    mvprintw(22,50,"%-35s","> Bond with Mr. Henderson");
                    break;
                case 4:
                    mvprintw(23,50,"%-35s","> Proceed Home");
                    break;
                default:
                    break;
                }
                attroff(COLOR_PAIR(2));
                
            } else if ((*daycount % 4 != 0) && *day == 2) // If its school day and afternoon
            {
                options = 4;

                // Display choices
                mvprintw(20,50,"%-35s","  Study Math with Loid");
                mvprintw(21,50,"%-35s","  Train Physical Education with Yor");
                mvprintw(22,50,"%-35s","  Play with Bond");
                mvprintw(23,50,"%-35s","  Slack Off");

                // Adds color when its selected based on the index
                attron(COLOR_PAIR(2));
                switch (index)
                {
                case 1:
                    mvprintw(20,50,"%-35s","> Study Math with Loid");
                    break;
                case 2:
                    mvprintw(21,50,"%-35s","> Train Physical Education with Yor");
                    break;
                case 3:
                    mvprintw(22,50,"%-35s","> Play with Bond");
                    break;
                case 4:
                    mvprintw(23,50,"%-35s","> Slack Off");
                    break;
                default:
                    break;
                }
                attroff(COLOR_PAIR(2));
            } else if ((*daycount % 4 == 0) && *day == 1) // If its outing day and morning
            {
                options = 4;
            } else if ((*daycount % 4 == 0) && *day == 2) // If its outing day and afternoon
            {
                options = 4;
            } else // If its outing day and evening (aka Family Meeting)
            {
                options = 7;
            }


            /* Gets the input and does the corresponding actions */
            switch(input = getch())
            {
                case KEY_UP:    // Arrow Up
                    index--;
                    if (index == 0) // If its go past the first option, make it select the last option
                    {
                        index = options;
                    }
                    break;
                case KEY_DOWN:  // Arrow Down
                    index++;
                    if (index > options) // If its go past the last option, make it select the first option
                    {
                        index = 1;
                    }
                    break;
                case '\n':      // Enter Key
                    
                    // CHECK WHAT TIME AND DAY
                    if (*daycount % 4 != 0) // School Day
                    {
                        if (dialogue != 1) // Check if there is a dialoge
                        {
                            if (*day == 1) // Check whether its Morning or Afternoon
                            {
                                switch (index)
                                {
                                case 1:
                                    if (*actionPoint > 0)
                                    {
                                        *actionPoint -= 1;
                                        bondGame(damianBP, 1, mathLVL, peLVL);
                                    } else
                                    {
                                        j--; // RESET since there is no action point
                                    }
                                    break;                                
                                case 2:
                                    if (*actionPoint > 0)
                                    {
                                        *actionPoint -= 1;
                                        bondGame(beckyBP, 2, mathLVL, peLVL);
                                    } else
                                    {
                                        j--; // RESET since there is no action point
                                    }
                                    break;
                                case 3:
                                    if (*actionPoint > 0)
                                    {
                                        *actionPoint -= 1;
                                        bondGame(hendersonBP, 3, mathLVL, peLVL);
                                    } else
                                    {
                                        j--; // RESET since there is no action point
                                    }
                                    break;
                                default:
                                    break;
                                }
                            } else
                            {
                                switch (index)
                                {
                                case 1:
                                    if (*actionPoint > 0)
                                    {
                                        *actionPoint -= 1;
                                        mathGame(mathLVL, mathEXP);
                                    } else
                                    {
                                        j--; // RESET since there is no action point
                                    }                        
                                    break;
                                case 2:
                                    if (*actionPoint > 0)
                                    {
                                        *actionPoint -= 1;
                                        peGame(peLVL, peEXP);
                                    } else
                                    {
                                        j--; // RESET since there is no action point
                                    }
                                    break;
                                case 3:
                                    if (*actionPoint > 0)
                                    {
                                        *actionPoint -= 1;
                                        bondGame(bondBP, 4, mathLVL, peLVL);
                                    } else
                                    {
                                        j--; // RESET since there is no action point
                                    }
                                    break;
                                default:
                                    break;
                                }
                            }
                        }
                    } else
                    {
                        if (dialogue != 1) // Check if there is a dialoge
                        {
                            if (*day == 1) // Check whether its Morning or Afternoon
                            {

                            } else if (*day == 2)
                            {

                            } else
                            {

                            }
                        }
                    }

                    j++; // Only proceed to next when entered
                    break;

                case 'Q':       // Capital Q
                case 'q':       // Q
                    quit = 1;
                    savegame(day, daycount, outing, actionPoint, cameraRoll, mathLVL, mathEXP, peLVL, peEXP, damianBP, beckyBP, hendersonBP, bondBP);
                    break;
                default:
                    break;

            }

            /* FUNCTIONS FOR THE OPTIONS */
        }

        // Checks if its fourth day to replenish the action point if its below 3 and everyday except 3rd day plus one action point
        if (*daycount % 3 == 0)
        {
            // DO NOTHING
        } else if (*daycount % 4 == 0)
        {
            if (*actionPoint < 3)
            {
                *actionPoint = 3;
            }
        } else
        {
            *actionPoint += 1;
        }

    }

    // Checks if the player did not quit and played through 41 days ( 0 - 40 day )
    if (quit != 1)
    {
        // CONGRATS
    }

    clear();    // Clear everything
}

/*
    This function sets a fresh data / variables and starts the main game loop
*/
void startgame()
{
    int day = 3;
    int daycount = 38;
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

    clear();    // Cleans the screen (removes the main menu)
    gameloop(&day, &daycount, &outing, &activityPoint, &cameraRoll, &mathLVL, &mathEXP, &peLVL, &peEXP, &damianBP, &beckyBP, &hendersonBP, &bondBP);
}

/*
    This function loads existing data to the variables and starts the main game loop
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
    curs_set(0);            // Hides the cursor

    int quit = 0;
    int index = 1;
    int input;

    init_pair(1, COLOR_WHITE, COLOR_BLACK); // NORMAL COLOR
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // SELECTED COLOR
    
    /* LOOPS until quit */
    do {
        mainmenu(&index);
        refresh();
        /* Gets the input and does the corresponding actions */
        switch (input = getch())
        {
            case KEY_UP:    // Arrow Up
                index--;
                // Checks if index is 0 to set to the highest option
                if (index <= 0)
                {
                    index = 3;
                }
                break;
            case KEY_DOWN:  // Arrow Down
                index++;
                // Checks if index is over the options to set to 1
                if (index > 3) 
                {
                    index = 1;
                }
                break;
            case '\n':      // Enter Key
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