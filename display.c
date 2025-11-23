#include <stdlib.h>
#include <ncurses\ncurses.h>

/* DISPLAYS */

/*
    This function creates the border of the screen
    Preconditions: all params are positive integers
    @param height - the max height of the screen
    @param width - the max width of the screen
*/
void bordercreate(int height, int width)
{
    /* Starts color and create a pair color (foreground, background)*/
    start_color();
    init_pair(1,COLOR_WHITE, COLOR_BLACK);

    /* CREATES THE BORDER */
    for (int i = 0; i <width; i++)
    {
        for (int j = 0; j<height; j++)
        {
            /* Move the cursor */
            move(j,i);
            
            // Checks if its on the end of the x-axis
            if (i==0 || i==width-1)
            {
                // Checks if its on the end of the y-axis
                if (j==0 || j==height-1)
                {
                    attron(COLOR_PAIR(1));      // Turn on set color for the text
                    addch('+');                 // Add the Corner Border
                    attroff(COLOR_PAIR(1));     // Turn on set color for the text
                } else
                {
                    attron(COLOR_PAIR(1));      // Turn on set color for the text
                    addch('|');                 // Add the Left / Right Border
                    attroff(COLOR_PAIR(1));     // Turn on set color for the text
                }
            } else
            {
                // Checks if its on the end of the y-axis but not on the end of x-axis
                if (j==0 || j==height-1)
                {
                    attron(COLOR_PAIR(1));      // Turn on set color for the text
                    addch('-');                 // Add the Top / Bottom Border
                    attroff(COLOR_PAIR(1));     // Turn on set color for the text
                }
            }
        }
    }
}

/*
    This function display the main menu
    Preconditions: all params are positive integers
    @param height - the max height of the screen
    @param width - the max width of the screen
    @param *index is a pointer to index which tells which button is selected
*/
void mainmenu(int height, int width, int *index)
{
    bordercreate(height, width); // Calls bordercreate function
    // Display the Controls
    mvprintw(height-1, (width-82)/2, "| [^][v][<][>] - USE ARROW KEYS TO MOVE |-------| [ENTER] - TO SELECT AN OPTION |");

    // Create a for loop grid
    for (int x=0; x < height-1; x++)
    {
        for (int y = 0; y < width-1; y++)
        {
            move(y,x); // Move to y,x

            // ends of box in x-axis
            if (x==15 || x==40)
            {
                // ends of box in y-axis (corner)
                if (y==5 || y==9 || y==14 || y==18 || y==23 || y==27)
                {
                    // If index means it is selected
                    if (*index==1 && (y==5 || y==9))
                    {
                        attron(COLOR_PAIR(2));  // Set the selected color to put
                        addch('+');
                        attroff(COLOR_PAIR(2)); // Remove the selected color to put
                    } else if (*index == 2 && (y==14 || y==18))
                    {
                        attron(COLOR_PAIR(2));  // Set the selected color to put
                        addch('+');
                        attroff(COLOR_PAIR(2)); // Remove the selected color to put
                    } else if (*index == 3 && (y==23 || y==27))
                    {
                        attron(COLOR_PAIR(2));  // Set the selected color to put
                        addch('+');
                        attroff(COLOR_PAIR(2)); // Remove the selected color to put
                    } else  
                    {
                        attron(COLOR_PAIR(1));  // Set the normal color to put
                        addch('+');
                        attroff(COLOR_PAIR(1)); // Remove the normal color to put
                    }
                
                    // Between the ends of the box in the y-axis
                } else if ((y>5 && y<9) || (y>14 && y<18) || (y>23 && y<27)) {
                    // If index means it is selected
                    if (*index==1 && (y>5 && y<9))
                    {
                        attron(COLOR_PAIR(2));  // Set the selected color to put
                        addch('|');
                        attroff(COLOR_PAIR(2)); // Remove the selected color to put
                    } else if (*index == 2 && (y>14 && y<18))
                    {
                        attron(COLOR_PAIR(2));  // Set the selected color to put
                        addch('|');
                        attroff(COLOR_PAIR(2)); // Remove the selected color to put
                    } else if (*index == 3 && (y>23 && y<27))
                    {
                        attron(COLOR_PAIR(2));  // Set the selected color to put
                        addch('|');
                        attroff(COLOR_PAIR(2)); // Remove the selected color to put
                    } else
                    {
                        attron(COLOR_PAIR(1));  // Set the normal color to put
                        addch('|');
                        attroff(COLOR_PAIR(1)); // Remove the normal color to put
                    }
                }
                // Check if between the ends of the box in the x-axis
            } else if (x>15 && x<40)
            {
                // Check if in the top/bottom of the box in y-axis
                if (y==5 || y==9 || y==14 || y==18 || y==23 || y==27)
                {
                    // If index means it is selected
                    if (*index==1 && (y==5 || y==9))
                    {
                        attron(COLOR_PAIR(2));  // Set the selected color to put
                        addch('-');
                        attroff(COLOR_PAIR(2)); // Remove the selected color to put
                    } else if (*index == 2 && (y==14 || y==18))
                    {
                        attron(COLOR_PAIR(2));  // Set the selected color to put
                        addch('-');
                        attroff(COLOR_PAIR(2)); // Remove the selected color to put
                    } else if (*index == 3 && (y==23 || y==27))
                    {
                        attron(COLOR_PAIR(2));  // Set the selected color to put
                        addch('-');
                        attroff(COLOR_PAIR(2)); // Remove the selected color to put
                    } else
                    {
                        attron(COLOR_PAIR(1));  // Set the normal color to put
                        addch('-');
                        attroff(COLOR_PAIR(1)); // Remove the normal color to put
                    }
                }
            }
        }
    }

    // TEXT in the box
    if (*index ==1)
    {
        attron(COLOR_PAIR(2));
    }
    mvprintw(7, 23, "START GAME");
    attroff(COLOR_PAIR(2));
    if (*index ==2)
    {
        attron(COLOR_PAIR(2));
    }
    mvprintw(16, 23, "LOAD GAME");
    attroff(COLOR_PAIR(2));
    if (*index ==3)
    {
        attron(COLOR_PAIR(2));
    }
    mvprintw(25, 23, "QUIT GAME");
    attroff(COLOR_PAIR(2));
}

/*
    This function creates the UI for the gameloop
    @param height - the max height of the screen
    @param width - the max width of the screen
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
*/
void mainUI(int height, int width, int* day, int* daycount, int* outing, int* activityPoint, int* cameraRoll, int* mathLVL, int* mathEXP, int* peLVL, int* peEXP, int* damianBP, int* beckyBP, int* hendersonBP, int* bondBP)
{
    bordercreate(height, width);

    // Display Controls
    mvprintw(height-1, (width-118)/2, "| [^][v][<][>] - USE ARROW KEYS TO MOVE |-------| [ENTER] - TO SELECT AN OPTION |-------| [q/Q] - BACK TO MAIN MENU |");
    
    /* Display the Daycount, Time of Day, Type of Day */
    switch (*day) // Sets Time of Day: 1-Morning, 2-Afternoon, 3-Evening
    { // Extra spaces for removing excess from previous
        case 1:
            mvprintw(2,2,"Day:   %02d - %-10s",*daycount,"Morning");
            break;
        case 2:
            mvprintw(2,2,"Day:   %02d - %-10s",*daycount,"Afternoon");
            break;
        case 3:
            mvprintw(2,2,"Day:   %02d - %-10s",*daycount,"Evening");
            break;
        default:
            mvprintw(2,2,"Day:   %02d - %-10s",*daycount,"ERROR");
            break;
    }
    // Checks whether it is School day or Outing Day or MEETING
    if (*daycount == 0 || (*daycount % 4 == 0 && *day == 3))
    { // Extra spaces for removing excess from previous
        mvprintw(3,9,"FAMILY MEETING ");
    } else if (*daycount % 4 == 0)
    {
        mvprintw(3,9,"%-16s","OUTING DAY");
    } else
    {
        mvprintw(3,9,"%-16s","SCHOOL DAY");
    }

    /* Display the next outing venue */
    mvprintw(5,2, "Next Outing Venue:");
    // Checks whether what is the next outing place
    switch (*outing) 
    { // Extra spaces for removing excess from previous
        case 1:
            mvprintw(6,7,"%-25s","Park");
            break;
        case 2:
            mvprintw(6,7,"%-25s","City Mall");
            break;
        case 3:
            mvprintw(6,7,"%-25s","Ostania Beach");
            break;
        case 4:
            mvprintw(6,7,"%-25s","West Berlint Aquarium");
            break;
        case 5:
            mvprintw(6,7,"%-25s","Ostania Art Museum");
            break;
        case 6:
            mvprintw(6,7,"%-25s","Berlint Mouseney Land");
            break;
        case 7:
            mvprintw(6,7,"%-25s","Park Avenue Dogland");
            break;
        default:
            mvprintw(6,7,"%-25s","Undecided");
            break;
    }

    /* Activity Points */
    mvprintw(8,2,"ACTIVITY POINTS: %2d", *activityPoint);

    /* Camera Rolls */
    mvprintw(9,2,"CAMERA ROLLS:    %d", *cameraRoll);

    /* Current Levels */
    mvprintw(2, width-23, "***LEVELS***");
    // Display math level and math exp and math exp requirement
    if (*mathLVL > 3)
    {
        // if 4(max) display MAX
        mvprintw(3, width-30, "Math LVL:%9d - MAX", *mathLVL - 1); 
    } else
    {
        // if below 4 display the exp and exp requirement -> [1]-5, [2]-10, [3]-15
        mvprintw(3, width-30, "Math LVL:%9d - %02d/%02d", *mathLVL, *mathEXP, *mathLVL * 5); 
    }
    // Display pe level and pe exp and pe exp requirement
    if (*peLVL > 3)
    {
        // if 4(max) display MAX
        mvprintw(4, width-30, "Pe LVL:%11d - MAX", *peLVL - 1);
    } else
    {
        // if below 4 display the exp and exp requirement -> [1]-5, [2]-10, [3]-15
        mvprintw(4, width-30, "Pe LVL:%11d - %02d/%02d", *peLVL, *peEXP, *peLVL * 5); 
    }
    
    /* CURRENT BP */
    mvprintw(5, width-23, "***BOND POINTS***");
    if (*damianBP == 5)
    {
        // if 5 then add MAX
        mvprintw(6, width-30, "Damian Desmond:%3d - MAX", *damianBP);
    } else
    {
        mvprintw(6, width-30, "Damian Desmond:%3d", *damianBP);
    }
    if (*beckyBP == 5)
    {
        // if 5 then add MAX
        mvprintw(7, width-30, "Becky Blackbell:%2d - MAX", *beckyBP);
    } else
    {
        mvprintw(7, width-30, "Becky Blackbell:%2d", *beckyBP);
    }
    if (*hendersonBP == 5)
    {
        // if 5 then add MAX
        mvprintw(8, width-30, "Mr. Henderson:%4d - MAX", *hendersonBP);
    } else
    {
        mvprintw(8, width-30, "Mr. Henderson:%4d", *hendersonBP);
    }
    if (*bondBP == 5)
    {
        // if 5 then add MAX
        mvprintw(9, width-30, "Bond Forger:%6d - MAX", *bondBP);
    } else
    {
        mvprintw(9, width-30, "Bond Forger:%6d", *bondBP);
    }

    refresh();
}


/* DIALOGUE */
void cleanDialogue()
{
    int height, width;
    getmaxyx(stdscr, height, width);
    for (int i = 0; i < 34; i++)
    {
        mvprintw(height-(35-i), (width-100)/2, "%100c", ' ');
    }
}

/*
    This function show the scoring/conclusion of the minigames
    Preconditions: A minigame must call this function. *LVL, *EXP are pointers to positive integer. All non-pointer param are positive interger
    @param *LVL - A pointer to the player's (Math, PE, Bond) level
    @param *EXP - A pointer to the player's (Math, PE) EXP or just placeholder
    @param expGained - EXP gain based on correct/question in Math and PE, or BP increase in Bonding or closest guess in outing
    @param correct - number of correct input in Math and PE, or integer-equivalent for bonding [1] - Damian Desmonds, [2] - Becky Blackbell, [3] - Mr. Henderson, [4] - Bond Forger, or outing venue
    @param question - number of questions in Math and PE, or number of additional AP gained in bonding, or score of the guess in outing
    @param gametype - what minigame is being used [1] - Math, [2] - PE, [3] - Outing, [4] - Bonding
*/
void showscore(int *LVL, int *EXP, int expGained, int correct, int question, int gametype)
{
    int height, width;
    getmaxyx(stdscr, height, width);

    cleanDialogue();

    switch (gametype)
    {
        case 1: // Math
            mvprintw(height-31, (width-20)/2, "[ GAME CONCLUSION ]");
            mvprintw(height-29, (width-21)/2, "Total Score: %d / %d", correct, question);
            mvprintw(height-28, (width-15)/2, "EXP Gained: %d", expGained);

            if (*LVL == 4)
            {
                mvprintw(height-26, (width-24)/2, "Current Math level: MAX");
                mvprintw(height-25, (width-22)/2, "Current Math EXP: MAX");

            } else 
            {
                mvprintw(height-26, (width-23)/2, "Current Math level: %d", *LVL);
                mvprintw(height-25, (width-26)/2, "Current Math EXP: %d / %d", *EXP, *LVL*5);
            }

            mvprintw(height-24, (width-27)/2, "Press [Enter] to continue!");
            break;
        case 2: // PE
            mvprintw(height-31, (width-20)/2, "[ GAME CONCLUSION ]");
            mvprintw(height-29, (width-21)/2, "Total Score: %d / %d", correct, question);
            mvprintw(height-28, (width-15)/2, "EXP Gained: %d", expGained);

            if (*LVL == 4)
            {
                mvprintw(height-26, (width-24)/2, "Current PE level: MAX");
                mvprintw(height-25, (width-22)/2, "Current PE EXP: MAX");

            } else 
            {
                mvprintw(height-26, (width-23)/2, "Current PE level: %d", *LVL);
                mvprintw(height-25, (width-26)/2, "Current PE EXP: %d / %d", *EXP, *LVL*5);
            }

            mvprintw(height-24, (width-27)/2, "Press [Enter] to continue!");
            break;
        case 3: // Outing
            mvprintw(height-31, (width-22)/2, "[ OUTING CONCLUSION ]");

            switch (correct)
            {
            case 1:
                mvprintw(height-29, (width-19)/2, "Outing Venue: Park");
                break;
            case 2:
                mvprintw(height-29, (width-24)/2, "Outing Venue: City Mall");
                break;
            case 3:
                mvprintw(height-29, (width-28)/2, "Outing Venue: Ostania Beach");
                break;
            case 4:
                mvprintw(height-29, (width-36)/2, "Outing Venue: West Berlint Aquarium");
                break;
            case 5:
                mvprintw(height-29, (width-33)/2, "Outing Venue: Ostania Art Museum");
                break;
            case 6:
                mvprintw(height-29, (width-36)/2, "Outing Venue: Berlint Mouseney Land");
                break;
            case 7:
                mvprintw(height-29, (width-34)/2, "Outing Venue: Park Avenue Dogland");
                break;
            
            default:
                break;
            }

            switch (question)
            {
            case 1:
                mvprintw(height-28, (width-16)/2, "Score: Not Good");
                mvprintw(height-26, (width-20)/2, "Closest Guess: %d", expGained);
                break;
            case 2:
                mvprintw(height-28, (width-12)/2, "Score: Okay");
                mvprintw(height-26, (width-20)/2, "Closest Guess: %d", expGained);
                break;
            case 3:
                mvprintw(height-28, (width-17)/2, "Score: Very Good");
                mvprintw(height-26, (width-20)/2, "Closest Guess: %d", expGained);
                break;
            case 4:
                mvprintw(height-28, (width-15)/2, "Score: Perfect");
                mvprintw(height-26, (width-14)/2, "Correct: %d", expGained);
                break;
            default:
                break;
            }
            
            break;
        case 4: // Bonding
            mvprintw(height-31, (width-23)/2, "[ BONDING CONCLUSION ]");
            mvprintw(height-29, (width-16)/2, "Bond Gained: %d", expGained);
            mvprintw(height-28, (width-18)/2, "Additional AP: %d", question);

            switch (correct)
            {
            case 1:
                if (*LVL == 5)
                {
                    mvprintw(height-26, (width-31)/2, "Current Damian Desmond BP: MAX");

                } else 
                {
                    mvprintw(height-26, (width-30)/2, "Current Damian Desmond BP: %d", *LVL);
                }
                break;
            case 2:
                if (*LVL == 5)
                {
                    mvprintw(height-26, (width-32)/2, "Current Becky Blackbell BP: MAX");

                } else 
                {
                    mvprintw(height-26, (width-31)/2, "Current Becky Blackbell BP: %d", *LVL);
                }
                break;
            case 3:
                if (*LVL == 5)
                {
                    mvprintw(height-26, (width-30)/2, "Current Mr. Henderson BP: MAX");

                } else 
                {
                    mvprintw(height-26, (width-29)/2, "Current Mr. Henderson BP: %d", *LVL);
                }
                break;
            case 4:
                if (*LVL == 5)
                {
                    mvprintw(height-26, (width-28)/2, "Current Bond Forger BP: MAX");

                } else 
                {
                    mvprintw(height-26, (width-27)/2, "Current Bond Forger BP: %d", *LVL);
                }
                break;
            
            default:
                break;
            }

            mvprintw(height-24, (width-27)/2, "Press [Enter] to continue!");
            break;
    }
    noecho();
    curs_set(0);
}