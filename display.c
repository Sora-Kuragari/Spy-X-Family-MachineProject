#include <stdlib.h>

// Checks if you are using linux because ncurses have different path on linux than windows
#ifdef linux
#include <ncurses.h>
#else
#include <ncurses\ncurses.h>
#endif

/* DISPLAYS */

/*
    This function creates the border of the screen
*/
void bordercreate()
{
    /* Starts color and create a pair color (foreground, background)*/
    start_color();
    init_pair(1,COLOR_WHITE, COLOR_BLACK);

    /* CREATES THE BORDER */
    for (int i = 0; i <153; i++)
    {
        for (int j = 0; j<34; j++)
        {
            /* Move the cursor */
            move(j,i);
            
            // Checks if its on the end of the x-axis
            if (i==0 || i==152)
            {
                // Checks if its on the end of the y-axis
                if (j==0 || j==33)
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
                if (j==0 || j==33)
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
    @param index is a pointer to index which tells which button is selected
*/
void mainmenu(int *index)
{
    bordercreate(); // Calls bordercreate function
    // Display the Controls
    mvprintw(33, 36, "| [^][v][<][>] - USE ARROW KEYS TO MOVE |-------| [ENTER] - TO SELECT AN OPTION |");

    // Create a for loop grid
    for (int x=0; x < 153; x++)
    {
        for (int y = 0; y < 34; y++)
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
void mainUI(int* day, int* daycount, int* outing, int* activityPoint, int* cameraRoll, int* mathLVL, int* mathEXP, int* peLVL, int* peEXP, int* damianBP, int* beckyBP, int* hendersonBP, int* bondBP)
{
    bordercreate();

    // Display Controls
    mvprintw(33, 18, "| [^][v][<][>] - USE ARROW KEYS TO MOVE |-------| [ENTER] - TO SELECT AN OPTION |-------| [q/Q] - BACK TO MAIN MENU |");
    
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
    mvprintw(2, 131, "***LEVELS***");
    // Display math level and math exp and math exp requirement
    if (*mathLVL > 3)
    {
        // if 4(max) display MAX
        mvprintw(3, 124, "Math LVL:%9d - MAX", *mathLVL - 1); 
    } else
    {
        // if below 4 display the exp and exp requirement -> [1]-5, [2]-10, [3]-15
        mvprintw(3, 124, "Math LVL:%9d - %02d/%02d", *mathLVL, *mathEXP, *mathLVL * 5); 
    }
    // Display pe level and pe exp and pe exp requirement
    if (*peLVL > 3)
    {
        // if 4(max) display MAX
        mvprintw(4, 124, "Pe LVL:%11d - MAX", *peLVL - 1);
    } else
    {
        // if below 4 display the exp and exp requirement -> [1]-5, [2]-10, [3]-15
        mvprintw(4, 124, "Pe LVL:%11d - %02d/%02d", *peLVL, *peEXP, *peLVL * 5); 
    }
    
    /* CURRENT BP */
    mvprintw(5, 128, "***BOND POINTS***");
    if (*damianBP == 5)
    {
        // if 5 then add MAX
        mvprintw(6, 124, "Damian Desmond:%3d - MAX", *damianBP);
    } else
    {
        mvprintw(6, 124, "Damian Desmond:%3d", *damianBP);
    }
    if (*beckyBP == 5)
    {
        // if 5 then add MAX
        mvprintw(7, 124, "Becky Blackbell:%2d - MAX", *beckyBP);
    } else
    {
        mvprintw(7, 124, "Becky Blackbell:%2d", *beckyBP);
    }
    if (*hendersonBP == 5)
    {
        // if 5 then add MAX
        mvprintw(8, 124, "Mr. Henderson:%4d - MAX", *hendersonBP);
    } else
    {
        mvprintw(8, 124, "Mr. Henderson:%4d", *hendersonBP);
    }
    if (*bondBP == 5)
    {
        // if 5 then add MAX
        mvprintw(9, 124, "Bond Forger:%6d - MAX", *bondBP);
    } else
    {
        mvprintw(9, 124, "Bond Forger:%6d", *bondBP);
    }

    refresh();
}


/* DIALOGUE */
void dialoguefunc()
{
    // start_color();
    // // Dialogue text - White text / Blue background
    // init_pair(3,COLOR_BLACK,COLOR_CYAN);

    // // Creates the colored box
    // for (int x = 0; x < 153; x++)
    // {
    //     for (int y = 0; y < 34; y++)
    //     {
    //         move(y,x);
    //         if (x >= 25 && x <= 127)
    //         {
    //             if (y >= 17 && y <=22)
    //             {
    //                 attron(COLOR_PAIR(3));
    //                 addch(' ');
    //                 attroff(COLOR_PAIR(3));
    //             }
    //         }
    //     }
    // }

    

}