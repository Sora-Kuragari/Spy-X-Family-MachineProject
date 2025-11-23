#include <stdio.h>
#include <stdlib.h>
#include "display.c"
#include "dialogue.c"
#include "minigame.c"
#include <ncurses\ncurses.h>

/*********************************************
Functions used in ncurses:
    mvprintw(y,x,"%d",1)                    - Moves to (x,y) position and prints 1
    init_pair(1,COLOR_BLACK,COLOR_WHITE)    - Initialize a pair with a keyword 1 that have Black as Foreground and White as Background
    scanw()                                 - Same scanf() but for ncurses
    attron(COLOR_PAIR(1))                   - Gives the attribute pair, that have keyword 1, to the proceeding print
    attroff(COLOR_PAIR(1))                  - Turns off giving attribute pair
    addch('a')                              - Same as printf but with only one character
    move(y,x)                               - Moves the cursor to (x,y) position
*********************************************/


/*
    This function saves data to a file with the following data line by line
    Preconditions: All parameter is a positive integer except for *name
    @param *name - name of the save file
    @param *day - time of day [1]-Morning, [2]-Afternoon, [3]-Evening
    @param *daycount - number of day
    @param *outing - where the outing is gonna be [1]-Park, [2]-City Mall, [3]-Ostania Beach, [4]-West Berlint Aquarium, [5]-Ostania Art Museum, [6]-Berlint Mouseney Land, [7]-Park Avenue Dogland
    @param *mathLVL - Math level [1],[2],[3],[4](MAX)
    @param *mathEXP - Math exp
    @param *peLVL - PE level [1],[2],[3],[4](MAX)
    @param *peEXP - PE exp
    @param *damianBP - Damian Desmond BP
    @param *beckyBP - Becky Blackbell BP
    @param *hendersonBP - Mr. Henderson BP
    @param *bondBP - Bond Forger BP
    @param *code - Outing Code Seed
*/
void savegame(char* name, int* day, int* daycount, int* outing, int* actionPoint, int* cameraRoll, int* mathLVL, int* mathEXP, int* peLVL, int* peEXP, int* damianBP, int* beckyBP, int* hendersonBP, int* bondBP, int* code, int* Cout1, int* Cout2, int* Cout3, int* Cout4, int* Cout5, int* Cout6, int* Cout7)
{
    FILE *fptr; // Initiate file

    // Opens the file
    fptr = fopen(name, "w");

    // Saves all the data in different line
    fprintf(fptr, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d", *day, *daycount, *outing, *actionPoint, *cameraRoll, *mathLVL, *mathEXP, *peLVL, *peEXP, *damianBP, *beckyBP, *hendersonBP, *bondBP, *code, *Cout1, *Cout2, *Cout3, *Cout4, *Cout5, *Cout6, *Cout7);

    fclose(fptr); // Closes the file
}

/*
    This function is the main game loop which loops through the 40 days
    Preconditions: All parameters are positive integer except for *name
    @param *name - name of the save file
    @param *day - time of day [1]-Morning, [2]-Afternoon, [3]-Evening
    @param *daycount - number of day
    @param *outing - where the outing is gonna be [1]-Park, [2]-City Mall, [3]-Ostania Beach, [4]-West Berlint Aquarium, [5]-Ostania Art Museum, [6]-Berlint Mouseney Land, [7]-Park Avenue Dogland
    @param *mathLVL - Math level [1],[2],[3],[4](MAX)
    @param *mathEXP - Math exp
    @param *peLVL - PE level [1],[2],[3],[4](MAX)
    @param *peEXP - PE exp
    @param *damianBP - Damian Desmond BP
    @param *beckyBP - Becky Blackbell BP
    @param *hendersonBP - Mr. Henderson BP
    @param *bondBP - Bond Forger BP
    @param *code - Outing Code Seed
*/
void gameloop(char* name, int* day, int* daycount, int* outing, int* actionPoint, int* cameraRoll, int* mathLVL, int* mathEXP, int* peLVL, int* peEXP, int* damianBP, int* beckyBP, int* hendersonBP, int* bondBP, int* code, int* Cout1, int* Cout2, int* Cout3, int* Cout4, int* Cout5, int* Cout6, int* Cout7)
{
    // Starts the color
    start_color();
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // SELECTED COLOR

    int quit = 0;           // [0]-Continue, [1]-QUIT
    int input, dcounting;   // [input] - players input (Arrow key / Enter Key), [dcounting] - time of the day (2 - Morning/Afternoon, 3 - Morning/Afternoon/Evening)
    int options;            // Number of options
    int index = 1;          // index of the options
    int height, width;      // the max height and max width of the screen (terminal)
    int inDialogue = 0;

    getmaxyx(stdscr, height, width);

    // Loops for 41 days (day 0 to day 40), ends when its above 40 or the player press the quit key
    while(*daycount <= 40 && quit != 1)
    {
        // Checks if its school day then set it to 2 times else (outing day) set it to 3 times
        if (*daycount % 4 != 0)
        {
            dcounting = 2;
        } else
        {
            dcounting = 3;
        }

        // Loops through the day: Morning -> Afternoon -> Evening (Only on Outing day)
        for (int j = *day; j <= dcounting && quit != 1; j=j)    // Day won't move unless pressed enter (or does an action)
        {
            *day = j; // Syncronizes day with j (Important specially when game is continued from a saved file)

            mainUI(height, width, day, daycount, outing, actionPoint, cameraRoll, mathLVL, mathEXP, peLVL, peEXP, damianBP, beckyBP, hendersonBP, bondBP);

            if (!inDialogue)
            {
                dialogueOptions(*day, *daycount);
                inDialogue = 1;
            }

            /* Display the options */
            if ((*daycount % 4 != 0) && *day == 1) // If its school day and morning
            {
                options = 4;

                // Display choices
                mvprintw(height-12,(width-50)/2,"%-50s","  Bond with Damian");
                mvprintw(height-11,(width-50)/2,"%-50s","  Bond with Becky");
                mvprintw(height-10,(width-50)/2,"%-50s","  Bond with Mr. Henderson");
                mvprintw(height-9,(width-50)/2,"%-50s","  Proceed Home");

                // Adds color when its selected based on the index
                attron(COLOR_PAIR(2));
                switch (index)
                {
                case 1:
                    mvprintw(height-12,(width-50)/2,"%-50s","> Bond with Damian");
                    break;
                case 2:
                    mvprintw(height-11,(width-50)/2,"%-50s","> Bond with Becky");
                    break;
                case 3:
                    mvprintw(height-10,(width-50)/2,"%-50s","> Bond with Mr. Henderson");
                    break;
                case 4:
                    mvprintw(height-9,(width-50)/2,"%-50s","> Proceed Home");
                    break;
                default:
                    break;
                }
                attroff(COLOR_PAIR(2));
                
            } else if ((*daycount % 4 != 0) && *day == 2) // If its school day and afternoon
            {
                options = 4;

                // Display choices
                mvprintw(height-12,(width-50)/2,"%-50s","  Study Math with Loid");
                mvprintw(height-11,(width-50)/2,"%-50s","  Train Physical Education with Yor");
                mvprintw(height-10,(width-50)/2,"%-50s","  Play with Bond");
                mvprintw(height-9,(width-50)/2,"%-50s","  Slack Off");

                // Adds color when its selected based on the index
                attron(COLOR_PAIR(2));
                switch (index)
                {
                case 1:
                    mvprintw(height-12,(width-50)/2,"%-50s","> Study Math with Loid");
                    break;
                case 2:
                    mvprintw(height-11,(width-50)/2,"%-50s","> Train Physical Education with Yor");
                    break;
                case 3:
                    mvprintw(height-10,(width-50)/2,"%-50s","> Play with Bond");
                    break;
                case 4:
                    mvprintw(height-9,(width-50)/2,"%-50s","> Slack Off");
                    break;
                default:
                    break;
                }
                attroff(COLOR_PAIR(2));
            } else if ((*daycount % 4 == 0) && *day == 1) // If its outing day and morning
            {
                options = 1;

                // Display the only choice 
                attron(COLOR_PAIR(2));
                mvprintw(height-12,(width-50)/2,"%-50s","> Go to Ooting!");
                attroff(COLOR_PAIR(2));
            } else if ((*daycount % 4 == 0) && *day == 2) // If its outing day and afternoon
            {
                options = 2;

                // Display choices
                mvprintw(height-12,(width-50)/2,"%-50s","  Take a Memorable Photo for the Project");
                mvprintw(height-11,(width-50)/2,"%-50s","  Go Home");

                // Adds color when its selected based on the index
                attron(COLOR_PAIR(2));
                switch (index)
                {
                case 1:
                    mvprintw(height-12,(width-50)/2,"%-50s","> Take a Memorable Photo for the Project");
                    break;
                case 2:
                    mvprintw(height-11,(width-50)/2,"%-50s","> Go Home");
                    break;
                default:
                    break;
                }
                attroff(COLOR_PAIR(2));
            } else // If its outing day and evening (aka Family Meeting)
            {
                options = 7;
                
                // Display choices
                mvprintw(height-12,(width-50)/2,"%-50s","  Park");
                mvprintw(height-11,(width-50)/2,"%-50s","  City Mall");
                mvprintw(height-10,(width-50)/2,"%-50s","  Ostania Beach");
                mvprintw(height-9,(width-50)/2,"%-50s","  West Berlint Aquarium");
                mvprintw(height-8,(width-50)/2,"%-50s","  Ostania Art Museum");
                mvprintw(height-7,(width-50)/2,"%-50s","  Berlint Mouseney Land");
                mvprintw(height-6,(width-50)/2,"%-50s","  Park Avenue Dogland");

                // Check if player already tried the venue then show the scoring and Checks whether the necessary requirements are not achieved then append "LOCKED"
                switch (*Cout1 / 10000)
                {
                case 1:
                    mvprintw(height-12,((width-50)/2)+25,"- NOT GOOD");
                    break;
                case 2:
                    mvprintw(height-12,((width-50)/2)+25,"- OKAY");
                    break;
                case 3:
                    mvprintw(height-12,((width-50)/2)+25,"- VERY GOOD");
                    break;
                case 4:
                    mvprintw(height-12,((width-50)/2)+25,"- PERFECT");
                    break;
                default:
                    break;
                }
                switch (*Cout2 / 10000)
                {
                case 1:
                    mvprintw(height-11,((width-50)/2)+25,"- NOT GOOD");
                    break;
                case 2:
                    mvprintw(height-11,((width-50)/2)+25,"- OKAY");
                    break;
                case 3:
                    mvprintw(height-11,((width-50)/2)+25,"- VERY GOOD");
                    break;
                case 4:
                    mvprintw(height-11,((width-50)/2)+25,"- PERFECT");
                    break;
                default:
                    break;
                }
                switch (*Cout3 / 10000)
                {
                case 1:
                    mvprintw(height-10,((width-50)/2)+25,"- NOT GOOD");
                    break;
                case 2:
                    mvprintw(height-10,((width-50)/2)+25,"- OKAY");
                    break;
                case 3:
                    mvprintw(height-10,((width-50)/2)+25,"- VERY GOOD");
                    break;
                case 4:
                    mvprintw(height-10,((width-50)/2)+25,"- PERFECT");
                    break;
                default:
                    break;
                }
                switch (*Cout4 / 10000)
                {
                case 1:
                    mvprintw(height-9,((width-50)/2)+25,"- NOT GOOD");
                    break;
                case 2:
                    mvprintw(height-9,((width-50)/2)+25,"- OKAY");
                    break;
                case 3:
                    mvprintw(height-9,((width-50)/2)+25,"- VERY GOOD");
                    break;
                case 4:
                    mvprintw(height-9,((width-50)/2)+25,"- PERFECT");
                    break;
                default:
                    if (*beckyBP != 5)
                    {
                        mvprintw(height-9,((width-50)/2)+25,"- LOCKED");
                    }
                    break;
                }
                switch (*Cout5 / 10000)
                {
                case 1:
                    mvprintw(height-8,((width-50)/2)+25,"- NOT GOOD");
                    break;
                case 2:
                    mvprintw(height-8,((width-50)/2)+25,"- OKAY");
                    break;
                case 3:
                    mvprintw(height-8,((width-50)/2)+25,"- VERY GOOD");
                    break;
                case 4:
                    mvprintw(height-8,((width-50)/2)+25,"- PERFECT");
                    break;
                default:
                    if (*hendersonBP != 5)
                    {
                        mvprintw(height-8,((width-50)/2)+25,"- LOCKED");
                    }
                    break;
                }
                switch (*Cout6 / 10000)
                {
                case 1:
                    mvprintw(height-7,((width-50)/2)+25,"- NOT GOOD");
                    break;
                case 2:
                    mvprintw(height-7,((width-50)/2)+25,"- OKAY");
                    break;
                case 3:
                    mvprintw(height-7,((width-50)/2)+25,"- VERY GOOD");
                    break;
                case 4:
                    mvprintw(height-7,((width-50)/2)+25,"- PERFECT");
                    break;
                default:
                    if (*damianBP != 5)
                    {
                        mvprintw(height-7,((width-50)/2)+25,"- LOCKED");
                    }
                    break;
                }
                switch (*Cout7 / 10000)
                {
                case 1:
                    mvprintw(height-6,((width-50)/2)+25,"- NOT GOOD");
                    break;
                case 2:
                    mvprintw(height-6,((width-50)/2)+25,"- OKAY");
                    break;
                case 3:
                    mvprintw(height-6,((width-50)/2)+25,"- VERY GOOD");
                    break;
                case 4:
                    mvprintw(height-6,((width-50)/2)+25,"- PERFECT");
                    break;
                default:
                    if (*bondBP != 5)
                    {
                        mvprintw(height-6,((width-50)/2)+25,"- LOCKED");
                    }
                    break;
                }

                // Adds color when its selected based on the index
                attron(COLOR_PAIR(2));
                switch (index)
                {
                case 1:
                    mvprintw(height-12,(width-50)/2,"%-50s","> Park");
                    switch (*Cout1 / 10000)
                    {
                    case 1:
                        mvprintw(height-12,((width-50)/2)+25,"- NOT GOOD");
                        break;
                    case 2:
                        mvprintw(height-12,((width-50)/2)+25,"- OKAY");
                        break;
                    case 3:
                        mvprintw(height-12,((width-50)/2)+25,"- VERY GOOD");
                        break;
                    case 4:
                        mvprintw(height-12,((width-50)/2)+25,"- PERFECT");
                        break;
                    default:
                        break;
                    }
                    break;
                case 2:
                    mvprintw(height-11,(width-50)/2,"%-50s","> City Mall");
                    switch (*Cout2 / 10000)
                    {
                    case 1:
                        mvprintw(height-11,((width-50)/2)+25,"- NOT GOOD");
                        break;
                    case 2:
                        mvprintw(height-11,((width-50)/2)+25,"- OKAY");
                        break;
                    case 3:
                        mvprintw(height-11,((width-50)/2)+25,"- VERY GOOD");
                        break;
                    case 4:
                        mvprintw(height-11,((width-50)/2)+25,"- PERFECT");
                        break;
                    default:
                        break;
                    }
                    break;
                case 3:
                    mvprintw(height-10,(width-50)/2,"%-50s","> Ostania Beach");
                    switch (*Cout3 / 10000)
                    {
                    case 1:
                        mvprintw(height-10,((width-50)/2)+25,"- NOT GOOD");
                        break;
                    case 2:
                        mvprintw(height-10,((width-50)/2)+25,"- OKAY");
                        break;
                    case 3:
                        mvprintw(height-10,((width-50)/2)+25,"- VERY GOOD");
                        break;
                    case 4:
                        mvprintw(height-10,((width-50)/2)+25,"- PERFECT");
                        break;
                    default:
                        break;
                    }
                    break;
                case 4:
                    mvprintw(height-9,(width-50)/2,"%-50s","> West Berlint Aquarium");
                    switch (*Cout4 / 10000)
                    {
                    case 1:
                        mvprintw(height-9,((width-50)/2)+25,"- NOT GOOD");
                        break;
                    case 2:
                        mvprintw(height-9,((width-50)/2)+25,"- OKAY");
                        break;
                    case 3:
                        mvprintw(height-9,((width-50)/2)+25,"- VERY GOOD");
                        break;
                    case 4:
                        mvprintw(height-9,((width-50)/2)+25,"- PERFECT");
                        break;
                    default:
                        if (*beckyBP != 5)
                        {
                            mvprintw(height-9,((width-50)/2)+25,"- LOCKED");
                        }
                        break;
                    }
                    break;
                case 5:
                    mvprintw(height-8,(width-50)/2,"%-50s","> Ostania Art Museum");
                    switch (*Cout5 / 10000)
                    {
                    case 1:
                        mvprintw(height-8,((width-50)/2)+25,"- NOT GOOD");
                        break;
                    case 2:
                        mvprintw(height-8,((width-50)/2)+25,"- OKAY");
                        break;
                    case 3:
                        mvprintw(height-8,((width-50)/2)+25,"- VERY GOOD");
                        break;
                    case 4:
                        mvprintw(height-8,((width-50)/2)+25,"- PERFECT");
                        break;
                    default:
                        if (*hendersonBP != 5)
                        {
                            mvprintw(height-8,((width-50)/2)+25,"- LOCKED");
                        }
                        break;
                    }
                    break;
                case 6:
                    mvprintw(height-7,(width-50)/2,"%-50s","> Berlint Mouseney Land");
                    switch (*Cout6 / 10000)
                    {
                    case 1:
                        mvprintw(height-7,((width-50)/2)+25,"- NOT GOOD");
                        break;
                    case 2:
                        mvprintw(height-7,((width-50)/2)+25,"- OKAY");
                        break;
                    case 3:
                        mvprintw(height-7,((width-50)/2)+25,"- VERY GOOD");
                        break;
                    case 4:
                        mvprintw(height-7,((width-50)/2)+25,"- PERFECT");
                        break;
                    default:
                        if (*damianBP != 5)
                        {
                            mvprintw(height-7,((width-50)/2)+25,"- LOCKED");
                        }
                        break;
                    }
                    break;
                case 7:
                    mvprintw(height-6,(width-50)/2,"%-50s","> Park Avenue Dogland");
                    switch (*Cout7 / 10000)
                    {
                    case 1:
                        mvprintw(height-6,((width-50)/2)+25,"- NOT GOOD");
                        break;
                    case 2:
                        mvprintw(height-6,((width-50)/2)+25,"- OKAY");
                        break;
                    case 3:
                        mvprintw(height-6,((width-50)/2)+25,"- VERY GOOD");
                        break;
                    case 4:
                        mvprintw(height-6,((width-50)/2)+25,"- PERFECT");
                        break;
                    default:
                        if (*bondBP != 5)
                        {
                            mvprintw(height-6,((width-50)/2)+25,"- LOCKED");
                        }
                        break;
                    }
                    break;
                default:
                    break;
                }
                attroff(COLOR_PAIR(2));
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
                        if (*day == 1) // Check whether its Morning or Afternoon
                        {
                            switch (index)
                            {
                            case 1:
                                if (*actionPoint > 0)
                                {
                                    *actionPoint -= 1;
                                    // Clean the options
                                    for (int i = 0; i < 8; i++)
                                    {
                                        mvprintw(height-(6+i),(width-50)/2,"%-50c",' ');
                                    }
                                    cleanDialogue();
                                    *actionPoint += bondGame(damianBP, 1, mathLVL, peLVL);
                                    cleanDialogue();
                                    inDialogue = 0;
                                } else
                                {
                                    j--; // RESET since there is no action point
                                }
                                break;                                
                            case 2:
                                if (*actionPoint > 0)
                                {
                                    *actionPoint -= 1;
                                    // Clean the options
                                    for (int i = 0; i < 8; i++)
                                    {
                                        mvprintw(height-(6+i),(width-50)/2,"%-50c",' ');
                                    }
                                    cleanDialogue();
                                    *actionPoint += bondGame(beckyBP, 2, mathLVL, peLVL);                            
                                    cleanDialogue();
                                    inDialogue = 0;
                                } else
                                {
                                    j--; // RESET since there is no action point
                                }
                                break;
                            case 3:
                                if (*actionPoint > 0)
                                {
                                    *actionPoint -= 1;
                                    // Clean the options
                                    for (int i = 0; i < 8; i++)
                                    {
                                        mvprintw(height-(6+i),(width-50)/2,"%-50c",' ');
                                    }
                                    cleanDialogue();
                                    *actionPoint += bondGame(hendersonBP, 3, mathLVL, peLVL);                                   
                                    cleanDialogue();
                                    inDialogue = 0;
                                } else
                                {
                                    j--; // RESET since there is no action point
                                }
                                break;
                            default:
                                cleanDialogue();
                                inDialogue = 0;
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
                                    // Clean the options
                                    for (int i = 0; i < 8; i++)
                                    {
                                        mvprintw(height-(6+i),(width-50)/2,"%-50c",' ');
                                    }
                                    cleanDialogue();
                                    *actionPoint += mathGame(mathLVL, mathEXP);                                    
                                    cleanDialogue();
                                    inDialogue = 0;
                                } else
                                {
                                    j--; // RESET since there is no action point
                                }                        
                                break;
                            case 2:
                                if (*actionPoint > 0)
                                {
                                    *actionPoint -= 1;
                                    // Clean the options
                                    for (int i = 0; i < 8; i++)
                                    {
                                        mvprintw(height-(6+i),(width-50)/2,"%-50c",' ');
                                    }
                                    cleanDialogue();
                                    *actionPoint += peGame(peLVL, peEXP);                                    
                                    cleanDialogue();
                                    inDialogue = 0;
                                } else
                                {
                                    j--; // RESET since there is no action point
                                }
                                break;
                            case 3:
                                if (*actionPoint > 0)
                                {
                                    *actionPoint -= 1;
                                    // Clean the options
                                    for (int i = 0; i < 8; i++)
                                    {
                                        mvprintw(height-(6+i),(width-50)/2,"%-50c",' ');
                                    }
                                    cleanDialogue();
                                    *actionPoint += bondGame(bondBP, 4, mathLVL, peLVL);                                    
                                    cleanDialogue();
                                    inDialogue = 0;
                                } else
                                {
                                    j--; // RESET since there is no action point
                                }
                                break;
                            default:
                                cleanDialogue();
                                inDialogue = 0;
                                break;
                            }
                        }
                    } else
                    {
                        if (*day == 1) // Check whether its Morning or Afternoon or Evening (Family Meeting)
                        {
                            cleanDialogue();
                            inDialogue = 0;
                        } else if (*day == 2)
                        {
                            if (index == 1)
                            {
                                if (*actionPoint > 0)
                                {
                                    *actionPoint -= 1;
                                    // Clean the options
                                    for (int i = 0; i < 8; i++)
                                    {
                                        mvprintw(height-(6+i),(width-50)/2,"%-50c",' ');
                                    }
                                    cleanDialogue();
                                    // Starts the memorable minigame
                                    switch (*outing)
                                    {
                                    case 1:
                                        memorableGame(actionPoint, cameraRoll, outing, code, Cout1);
                                        break;
                                    case 2:
                                        memorableGame(actionPoint, cameraRoll, outing, code, Cout2);
                                        break;
                                    case 3:
                                        memorableGame(actionPoint, cameraRoll, outing, code, Cout3);
                                        break;
                                    case 4:
                                        memorableGame(actionPoint, cameraRoll, outing, code, Cout4);
                                        break;
                                    case 5:
                                        memorableGame(actionPoint, cameraRoll, outing, code, Cout5);
                                        break;
                                    case 6:
                                        memorableGame(actionPoint, cameraRoll, outing, code, Cout6);
                                        break;
                                    case 7:
                                        memorableGame(actionPoint, cameraRoll, outing, code, Cout7);
                                        break;
                                    default:
                                        break;
                                    }
                                    cleanDialogue();
                                    inDialogue = 0;
                                } else 
                                {
                                    j--;
                                }
                                
                            } else
                            {
                                cleanDialogue();
                                inDialogue = 0;
                            }

                            *outing = 0;        // memorable is over, choose again
                        } else
                        {
                            // Set the venue of the next Outing to whatever index is
                            // If outing venue is already perfect then it cannot be picked again
                            // [4][5][6][7] have requirements before getting selected
                            switch (index)
                            {
                            case 1:
                                if (*Cout1 / 10000 == 4)
                                {
                                    j--;
                                } else
                                {
                                    *outing = index;
                                    cleanDialogue();
                                    inDialogue = 0;  
                                }
                                break;
                            case 2:
                                if (*Cout2 / 10000 == 4)
                                {
                                    j--;
                                } else
                                {
                                    *outing = index;
                                    cleanDialogue();
                                    inDialogue = 0;  
                                }
                                break;
                            case 3:
                                if (*Cout3 / 10000 == 4)
                                {
                                    j--;
                                } else
                                {
                                    *outing = index;
                                    cleanDialogue();
                                    inDialogue = 0;  
                                }
                                break;
                            case 4:
                                if (*Cout4 / 10000 != 4 && *beckyBP == 5)
                                {
                                    *outing = index;
                                    cleanDialogue();
                                    inDialogue = 0;                                    
                                } else
                                {
                                    j--;
                                }
                                break;
                            case 5:
                                if (*Cout5 / 10000 != 4 && *hendersonBP == 5)
                                {
                                    *outing = index;
                                    cleanDialogue();
                                    inDialogue = 0;                                  
                                } else
                                {
                                    j--;
                                }
                                break;
                            case 6:
                                if (*Cout6 / 10000 != 4 && *damianBP == 5)
                                {
                                    *outing = index;  
                                    cleanDialogue();
                                    inDialogue = 0;                                    
                                } else
                                {
                                    j--;
                                }
                                break;
                            case 7:
                                if (*Cout7 / 10000 != 4 && *bondBP == 5)
                                {
                                    *outing = index;
                                    cleanDialogue();
                                    inDialogue = 0;                                   
                                } else
                                {
                                    j--;
                                }
                                break;
                            
                            default:
                                *outing = index;
                                break;
                            }

                            *cameraRoll = 5;    // Refill
                        }
                    }

                    // Reset the index back to the top
                    index = 1;

                    // Clean the options
                    for (int i = 0; i < 8; i++)
                    {
                        mvprintw(height-(6+i),(width-50)/2,"%-50c",' ');
                    }
                    
                    j++; // Only proceed to next when entered
                    break;

                case 'Q':       // Capital Q
                case 'q':       // Q
                    savegame(name, day, daycount, outing, actionPoint, cameraRoll, mathLVL, mathEXP, peLVL, peEXP, damianBP, beckyBP, hendersonBP, bondBP, code, Cout1, Cout2, Cout3, Cout4, Cout5, Cout6, Cout7);
                    quit = 1;
                    break;
                default:
                    break;

            }

        }

        // Checks if its fourth day to replenish the action point if its below 3 and everyday except 3rd day plus one action point
        if (*daycount % 4 == 3)
        {
            // DO NOTHING
        } else if (*daycount % 4 == 0 || *daycount == 0)
        {
            if (*actionPoint < 3)
            {
                *actionPoint = 3;
            }
        } else
        {
            *actionPoint += 1;
        }

        *daycount += 1; // Next Day
        *day = 1;       // Go back to Morning

    }

    // Checks if the player did not quit and played through 41 days ( 0 - 40 day )
    if (quit != 1)
    {
        clear();
        bordercreate(height, width);


    }

    clear();    // Clear everything
}

/*
    This function sets a fresh data / variables and starts the main game loop
*/
void startgame()
{
    echo();

    char name[30] = "TemporaryFile";
    int day = 3;
    int daycount = 0;
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
    int code = 0;
    int Cout1 = 0;
    int Cout2 = 0;
    int Cout3 = 0;
    int Cout4 = 0;
    int Cout5 = 0;
    int Cout6 = 0;
    int Cout7 = 0;

    mvprintw(30,20,"Enter File Name (No Spaces) (Default: TemporaryFile): ");
    scanw("%s", name);

    noecho();

    clear();    // Cleans the screen (removes the main menu)
    gameloop(name, &day, &daycount, &outing, &activityPoint, &cameraRoll, &mathLVL, &mathEXP, &peLVL, &peEXP, &damianBP, &beckyBP, &hendersonBP, &bondBP, &code, &Cout1, &Cout2, &Cout3, &Cout4, &Cout5, &Cout6, &Cout7);
}

/*
    This function loads existing data to the variables and starts the main game loop
*/
void loadgame()
{
    FILE *fptr;

    char buffer[30];    // Buffer for the data from the file to the variable with 30 characters
    int quit = 0;

    char name[256];     // Can hold 256 characters
    int day = 3;
    int daycount = 0;
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
    int code = 0;
    int Cout1 = 0;
    int Cout2 = 0;
    int Cout3 = 0;
    int Cout4 = 0;
    int Cout5 = 0;
    int Cout6 = 0;
    int Cout7 = 0;

    while (quit != 1)
    {
        echo(); // Enables visible typing

        mvprintw(10,20,"Enter File Name (No Spaces): ");
        scanw("%s", name);

        noecho(); // Disable Visible typing

        // Opens the file with the inputted name
        fptr = fopen(name, "r");

        // Checks whether the file doesn't exist
        if (fptr == NULL)
        {
            quit = 1;
        } else
        {
            // Checks everyline and assign it to the variables
            for (int i = 1; i<=21; i++)
            {
                switch (i)
                {
                case 1:
                    fgets(buffer, 5, fptr);
                    day = atoi(buffer);
                    break;
                case 2:
                    fgets(buffer, 5, fptr);
                    daycount = atoi(buffer);
                    break;
                case 3:
                    fgets(buffer, 5, fptr);
                    outing = atoi(buffer);
                    break;
                case 4:
                    fgets(buffer, 5, fptr);
                    activityPoint = atoi(buffer);
                    break;
                case 5:
                    fgets(buffer, 5, fptr);
                    cameraRoll = atoi(buffer);
                    break;
                case 6:
                    fgets(buffer, 5, fptr);
                    mathLVL = atoi(buffer);
                    break;
                case 7:
                    fgets(buffer, 5, fptr);
                    mathEXP = atoi(buffer);
                    break;
                case 8:
                    fgets(buffer, 5, fptr);
                    peLVL = atoi(buffer);
                    break;
                case 9:
                    fgets(buffer, 5, fptr);
                    peEXP = atoi(buffer);
                    break;
                case 10:
                    fgets(buffer, 5, fptr);
                    damianBP = atoi(buffer);
                    break;
                case 11:
                    fgets(buffer, 5, fptr);
                    beckyBP = atoi(buffer);
                    break;
                case 12:
                    fgets(buffer, 5, fptr);
                    hendersonBP = atoi(buffer);
                    break;
                case 13:
                    fgets(buffer, 5, fptr);
                    bondBP = atoi(buffer);
                    break;
                case 14:
                    fgets(buffer, 30, fptr);
                    code = atoi(buffer);
                    break;
                case 15:
                    fgets(buffer, 30, fptr);
                    Cout1 = atoi(buffer);
                    break;
                case 16:
                    fgets(buffer, 30, fptr);
                    Cout2 = atoi(buffer);
                    break;
                case 17:
                    fgets(buffer, 30, fptr);
                    Cout3 = atoi(buffer);
                    break;
                case 18:
                    fgets(buffer, 30, fptr);
                    Cout4 = atoi(buffer);
                    break;
                case 19:
                    fgets(buffer, 30, fptr);
                    Cout5 = atoi(buffer);
                    break;
                case 20:
                    fgets(buffer, 30, fptr);
                    Cout6 = atoi(buffer);
                    break;
                case 21:
                    fgets(buffer, 30, fptr);
                    Cout7 = atoi(buffer);
                    break;
                default:
                    break;
                }

            }

            fclose(fptr);   // Closes the file and saves it
            clear();        // clears the main menu UI
            quit = 1;
            gameloop(name, &day, &daycount, &outing, &activityPoint, &cameraRoll, &mathLVL, &mathEXP, &peLVL, &peEXP, &damianBP, &beckyBP, &hendersonBP, &bondBP, &code, &Cout1, &Cout2, &Cout3, &Cout4, &Cout5, &Cout6, &Cout7);
        }
    }
    mvprintw(10,20,"%50c", ' '); // Fill with Empty Space
    fclose(fptr);
}

/*
    Main Function which starts the game and shows the main menu
*/
int main()
{
    printf("PLEASE FULLSCREEN FOR THE BEST EXPERIENCE\nMight break when not in fullscreen\n");
    system("pause");

    /* Initialize */
    initscr();              // Start the screen
    start_color();          // Starts color
    noecho();               // Key pressed will not show
    keypad(stdscr, TRUE);   // enables keypad
    curs_set(0);            // Hides the cursor

    int quit = 0;
    int index = 1;
    int input;
    int height, width;

    init_pair(1, COLOR_WHITE, COLOR_BLACK); // NORMAL COLOR
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // SELECTED COLOR
    
    /* LOOPS until quit */
    do {
        getmaxyx(stdscr, height, width);    // Gets the height and width of the terminal screen

        mainmenu(height, width, &index);
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