#include <stdlib.h>
#include <math.h>
#include <time.h>

// Checks if you are using linux because ncurses have different path on linux than windows
#ifdef linux
#include <ncurses.h>
#else
#include <ncurses\ncurses.h>
#endif

/*
    This function generates a random value ranged on a minimum and maximum value
    Precondition: min and max are positive integer
    @param min - minimum limit of the random value
    @param max - maximum limit of the random value
    @return random Value which ranges from the given minimum and maximum value
*/
int randomValue(int min, int max)
{
    int randomValue = rand() % (max - min + 1) + min;
    return randomValue;
}

/*
    This function is responsible in leveling up
    @param LVL - pointer of either math or PE level
    @param XP - pointer of either math or PE EXP
*/
void levelup(int* LVL, int* XP)
{
    if (*LVL == 4)
    {
        // Nothing, its already max
    } else if (*XP >= *LVL * 5)
    {
        *XP -= *LVL * 5;
        *LVL += 1;
    } else
    {
        // Nothing, not enough xp to level up
    }
}

/*
    This function gives exp based on the number of correct over the total number of questions and if perfect, a chance of additional AP
    Preconditions: mathLVL (pointer), correct, question must be a positive integer
    @param *XP - pointer to player's math/pe EXP
    @param correct - number of correct answered
    @param question - number of questions
    @return additionalAP - number of additional AP given based on correct if and only if player is max level 
*/
int scoring(int *LVL, int* XP, int correct, int question, int gametype)
{
    int AP = 0;
    int expGained = 0;

    // Convert the integer to float
    float numerator = correct;
    float denominator = question;

    float correctPercent = (numerator / denominator) * 100;

    if (correctPercent == 100)
    {
        expGained = 3;
        *XP += 3;
        switch(randomValue(1,2))
        {
            case 1:
                // No additional AP for you :(
                break;
            case 2:
                AP = 1; // WINNER! Award 1 AP
                break;
        }
    } else if (correctPercent >= 80)
    {
        *XP += 2;
        expGained = 2;
    } else if (correctPercent >= 60)
    {
        *XP += 1;
        expGained = 1;
    }

    levelup(LVL, XP);

    showscore(LVL, XP, expGained, correct, question, gametype);

    return AP;
}

/*
    This function is the math minigame where based on the player's level, the player must answer the randomly generated
    mathematical equation and based on the percentage of correct / questions, give an appropriate exp or AP
    Preconditions: mathLVL, mathEXP must be a pointer to a positive integer
    @param mathLVL - pointer to player's math level
    @param mathEXP - pointer to player's math exp
    @return additionalAP - gives additional AP if player's math level is MAX and all questions are correct
*/
int mathGame(int* mathLVL, int* mathEXP)
{
    int height, width;
    getmaxyx(stdscr, height, width);

    // Clean the options
    for (int i = 0; i < 7; i++)
    {
        mvprintw(height-(6+i),(width-50)/2,"%-50c",' ');
    }

    srand(time(0)); // Sets the seed
    echo();         // Key pressed is visible when typing
    curs_set(1);    // Shows the cursor

    int input, question;
    int correct = 0;
    int AP = -1;
    int num1, num2, op, total; // First Number, Second Number, Operator, Total

    // Sets the number of questions
    if (*mathLVL < 2)
    {
        question = 5;
    } else {
        question = 10;
    }

    mvprintw(height-20, (width-13)/2, "LOID FORGER:");

    // Loops until all questions are answered
    for (int i = 0; i < question; i++)
    {
        // If less than 2 then only Addition and Subtraction, else Addition, Subtraction and Multiplication
        if (*mathLVL < 2)
        {
            op = randomValue(1,2);
        } else {
            op = randomValue(1,3);
        }
        
        // Generates a 2 random value to add, subtract or multiply based on plr's math lvl
        switch (*mathLVL)
        {
        case 1:
            num1 = randomValue(1, 999);
            num2 = randomValue(1, 999);
            break;
        
        case 2:
            if (op == 3)
            {
                num1 = randomValue(1, 20);
                num2 = randomValue(1, 20); 
            } else {
                num1 = randomValue(1, 9999);
                num2 = randomValue(1, 9999); 
            }
            break;

        case 3:
        case 4:
            if (op == 3)
            {
                num1 = randomValue(1, 50);
                num2 = randomValue(1, 50); 
            } else {
                num1 = randomValue(1, 9999);
                num2 = randomValue(1, 9999); 
            }

        default:
            break;
        }

        // Adds, Subtracts or Multiply the 2 numbers, and also display the question
        switch (op)
        {
        case 1:
            total = num1 + num2;
            mvprintw(height-18, (width-19)/2, "What is %d + %d?", num1, num2);
            break;

        case 2:
            total = num1 - num2;
            mvprintw(height-18, (width-19)/2, "What is %d - %d?", num1, num2);
            break;

        case 3:
            total = num1 * num2;
            mvprintw(height-18, (width-19)/2, "What is %d * %d?", num1, num2);
            break;
        
        default:
            break;
        }

        mvprintw(height-13, (width-15)/2, "Answer: ");

        // scanf equivalent in curses
        scanw("%d", &input);

        if (input == total)
        {
            correct += 1;
        }

        mvprintw(height-18, (width-20)/2,"%-50c",' ');
        mvprintw(height-13, (width-20)/2,"%-50c",' ');

    }

    // Clean
    for (int i = 0; i <= 20; i++)
    {
        mvprintw(height-(20+i), (width-100)/2,"%-100c",' ');
    }

    AP = scoring(mathLVL, mathEXP, correct, question, 1);
    
    getch();
    return AP;
}

/*
    This function is the PE minigame where based on the player's PE lvl, a prompt will be shown and the player must correctly input
    a key based on the prompt, and based on the percentage of correct / questions, give an appropriate exp or AP.
    @param peLVL - pointer to player's PE lvl
    @param peEXP - pointer to player's PE exp
    @return additionalAP - gives additional AP if player's PE level is MAX and all questions are correct
*/
int peGame(int* peLVL, int* peEXP)
{
    int height, width;
    getmaxyx(stdscr, height, width);

    int input;
    int prompt;
    int correct = 0;
    int additionalAP = 0;

    for (int i = 0; i < 10; i++)
    {
        srand(time(0)); // Sets the seed
        
        // Generates a random number for the prompt
        switch (*peLVL)
        {
        case 1:
            prompt = randomValue(1,4);
            break;
        case 2:
            prompt = randomValue(1,8);
            break;
        case 3:
        case 4:
            prompt = randomValue(1,16);
            break;
        default:
            break;
        }

        mvprintw(height-22,(width-12)/2,"YOR FORGER:");
        // Display the prompts
        switch (prompt)
        {
        case 1:
            mvprintw(height-20, (width-4)/2,"Up!");
            break;
        case 2:
            mvprintw(height-20,(width-6)/2,"Down!");
            break;
        case 3:
            mvprintw(height-20,(width-6)/2,"Left!");
            break;
        case 4:
            mvprintw(height-20,(width-7)/2,"Right!");
            break;
        case 5:
            mvprintw(height-20,(width-7)/2,"North!");
            break;
        case 6:
            mvprintw(height-20,(width-7)/2,"South!");
            break;
        case 7:
            mvprintw(height-20,(width-6)/2,"East!");
            break;
        case 8:
            mvprintw(height-20,(width-6)/2,"West!");
            break;
        case 9:
            mvprintw(height-20,(width-10)/2,"UP AHEAD!");
            break;
        case 10:
            mvprintw(height-20,(width-12)/2,"BEHIND YOU!");
            break;
        case 11:
            mvprintw(height-20,(width-13)/2,"TO THE LEFT!");
            break;
        case 12:
            mvprintw(height-20,(width-14)/2,"TO THE RIGHT!");
            break;
        case 13:
            mvprintw(height-20,(width-11)/2,"Northwest!");
            break;
        case 14:
            mvprintw(height-20,(width-11)/2,"Northeast!");
            break;
        case 15:
            mvprintw(height-20,(width-11)/2,"Southwest!");
            break;
        case 16:
            mvprintw(height-20,(width-11)/2,"Southeast!");
            break;
        default:
            break;
        }

        // Checks whether inputted key is the correct key
        switch(input = getch())
        {
            case 'w':
                if (prompt == 1)
                {
                    correct += 1;
                }
                break;
            case 'W':
                if (*peLVL >= 3)
                {
                    if (prompt == 9)
                    {
                        correct += 1;
                    }
                } else {
                    if (prompt == 1)
                    {
                        correct += 1;
                    }
                }
                break;
            case 'a':
                if (prompt == 3)
                {
                    correct += 1;
                }
                break;
            case 'A':
                if (*peLVL >= 3)
                {
                    if (prompt == 11)
                    {
                        correct += 1;
                    }
                } else {
                    if (prompt == 3)
                    {
                        correct += 1;
                    }
                }
                break;
            case 's':
                if (prompt == 2)
                {
                    correct += 1;
                }
                break;
            case 'S':
                if (*peLVL >= 3)
                {
                    if (prompt == 10)
                    {
                        correct += 1;
                    }
                } else {
                    if (prompt == 2)
                    {
                        correct += 1;
                    }
                }
                break;
            case 'd':
                if (prompt == 4)
                {
                    correct += 1;
                }
                break;
            case 'D':
                if (*peLVL >= 3)
                {
                    if (prompt == 12)
                    {
                        correct += 1;
                    }
                } else {
                    if (prompt == 4)
                    {
                        correct += 1;
                    }
                }
                break;
            case '8':
                if (prompt == 5)
                {
                    correct += 1;
                }
                break;
            case '2':
                if (prompt == 6)
                {
                    correct += 1;
                }
                break;
            case '4':
                if (prompt == 8)
                {
                    correct += 1;
                }
                break;
            case '6':
                if (prompt == 7)
                {
                    correct += 1;
                }
                break;
            case '7':
                if (prompt == 13)
                {
                    correct += 1;
                }
                break;
            case '9':
                if (prompt == 14)
                {
                    correct += 1;
                }
                break;
            case '1':
                if (prompt == 15)
                {
                    correct += 1;
                }
                break;
            case '3':
                if (prompt == 16)
                {
                    correct += 1;
                }
                break;
        }

        mvprintw(height-22,(width-50)/2,"%-50c", ' ');
        mvprintw(height-20,(width-50)/2,"%-50c", ' ');
    }

    additionalAP = scoring(peLVL, peEXP, correct, 10, 2);
    getch();

    return additionalAP;
}

/*
    This function is the bonding minigame where a chance to increase the bonding level of the selected character based on
    percentage, and some needing specific levels of math or pe
    Preconditions: bondEXP, mathLVL, peLVL are pointers to a positive integer
    @param *bondLVL - Pointer to a specific character bond level
    @param num - A number that represent which character [1]-Damian, [2]-Becky, [3]-Henderson, [4]-Bond
    @param *mathLVL - Pointer to the player's math level
    @param *peLVL - Pointer to the player's pe level
    @param additionalAP - a chance to get addition AP when bonding a max BP character
*/
int bondGame(int *bondLVL, int num, int *mathLVL, int *peLVL)
{
    int additionalAP = 0;
    int dummyEXP, gained = 0;

    srand(time(0));

    switch (num)
    {
    case 1: // Damian Desmond
        // If BP is already 5
        if (*bondLVL == 5)
        {
            if (randomValue(1,2) > 1)
            {
                additionalAP = 3; // Returning the AP + 2 additional AP
                showscore(bondLVL, &dummyEXP, 0, 1, 2, 4);
            }
        } else
        {
            switch (*peLVL)
            {
            case 1:
                break;
            case 2:
                if (randomValue(0,100) <= 25)
                {
                    *bondLVL += 1;
                    gained = 1;
                }
                break;
            case 3:
                if (randomValue(0,100) <= 50)
                {
                    *bondLVL += 1;
                    gained = 1;
                }
                break;
            case 4:
                if (randomValue(0,100) <= 75)
                {
                    *bondLVL += 1;
                    gained = 1;
                }
                break;            
            default:
                break;
            }

            // Awards 3 AP when bondLVL reaches 5
            if (*bondLVL == 5)
            {
                additionalAP = 3;
                showscore(bondLVL, &dummyEXP, gained, 1, 3, 4);
            } else
            {
            showscore(bondLVL, &dummyEXP, gained, 1, 0, 4);
            }

        }
        break;

    case 2: // Becky Blackbell
        // If BP is already 5
        if (*bondLVL == 5)
        {
            if (randomValue(1,2) > 1)
            {
                additionalAP = 3; // Returning the AP + 2 additional AP
                showscore(bondLVL, &dummyEXP, 0, 2, 2, 4);
            }
        } else
        {        
            if (randomValue(0,100) <= 75)
            {
                *bondLVL += 1;
                gained = 1;
            }
            
            // Awards 3 AP when bondLVL reaches 5
            if (*bondLVL == 5)
            {
                additionalAP = 3;
                showscore(bondLVL, &dummyEXP, gained, 2, 3, 4);
            } else
            {
            showscore(bondLVL, &dummyEXP, gained, 2, 0, 4);
            }
        }
        break;

    case 3: // Mr. Henderson
        // If BP is already 5
        if (*bondLVL == 5)
        {
            if (randomValue(1,2) > 1)
            {
                additionalAP = 3; // Returning the AP + 2 additional AP
                showscore(bondLVL, &dummyEXP, 0, 3, 2, 4);
            }
        } else
        {
            switch (*mathLVL)
            {
            case 1:
                break;
            case 2:
                if (randomValue(0,100) <= 50)
                {
                    *bondLVL += 1;
                    gained = 1;
                }
                break;
            case 3:
                if (randomValue(0,100) <= 75)
                {
                    *bondLVL += 1;
                    gained = 1;
                }
                break;
            case 4:
                *bondLVL += 1;
                gained = 1;
                break;            
            default:
                break;
            }

            // Awards 3 AP when bondLVL reaches 5
            if (*bondLVL == 5)
            {
                additionalAP = 3;
                showscore(bondLVL, &dummyEXP, gained, 3, 3, 4);
            } else
            {
            showscore(bondLVL, &dummyEXP, gained, 3, 0, 4);
            }
        }
        break;

    case 4: // Bond Forger
        // If BP is already 5
        if (*bondLVL == 5)
        {
            if (randomValue(1,2) > 1)
            {
                additionalAP = 3; // Returning the AP + 2 additional AP
                showscore(bondLVL, &dummyEXP, 0, 4, 2, 4);
            }
        } else
        {        
            *bondLVL += 1;
            gained = 1;
            
            // Awards 3 AP when bondLVL reaches 5
            if (*bondLVL == 5)
            {
                additionalAP = 3;
                showscore(bondLVL, &dummyEXP, gained, 4, 3, 4);
            } else
            {
                showscore(bondLVL, &dummyEXP, gained, 4, 0, 4);
            }
        }
        break;
    
    default:
        break;
    }

    getch();

    return additionalAP;
}

/*
    This function is the memorable minigame where the player chooses the venue and must correctly guess the random value from 1 to 1000.
    The player have 5 tries for each run of the memorable minigame.
    Preconditions: all params are a pointer to a positive integers
    @param *actionPoints - players action points
    @param *cameraRoll - player's camera roll count
    @param *outing - player's chosen outing venue [1]-Park, [2]-City Mall, [3]-Ostania Beach, [4]-West Berlint Aquarium, [5]-Ostania Art Museum, [6]-Berlint Mouseney Land, [7]-Park Avenue Dogland
    @param *code - 
*/
void memorableGame(int *actionPoints, int *cameraRoll, int *outing, int *code, int *closestGuess)
{
    int outingCode = 0;
    int closeGuess = 0;
    int guess, score;
    int perfect = 0;
    int close = 0;
    int index = 1;
    int dummyLVL, dummyEXP;
    int height, width;

    getmaxyx(stdscr, height, width);
    echo();

    // If code doesn't exist then generate one
    mvprintw(20,20,"%d", *code);
    if (*code == 0)
    {
        *code = time(0);
    }

    srand(*code);       // Sets the seed

    // Loops until the outing venue's code
    for (int i = 0; i < *outing; i++)
    {
        outingCode = randomValue(0,1000);
    }

    while (!close && !perfect)
    {
        while (!close && !perfect && *cameraRoll > 0)
        {
            closeGuess = *closestGuess % 10000;

            switch (*closestGuess / 10000)
            {
            case 1:
                mvprintw(height-20,(width-30)/2,"Camera Angle Grade: NOT GOOD");
                break;
            case 2:
                mvprintw(height-20,(width-30)/2,"Camera Angle Grade: OKAY");
                break;
            case 3:
                mvprintw(height-20,(width-30)/2,"Camera Angle Grade: VERY GOOD");
                break;
            case 4:
                mvprintw(height-20,(width-30)/2,"Camera Angle Grade: PERFECT");
                break;
            default:
                mvprintw(height-20,(width-30)/2,"Camera Angle Grade:          ");
                break;
            }
            mvprintw(height-19, (width-20)/2,"Closest Angle: %d", closeGuess);
            mvprintw(height-17, (width-25)/2, "Enter Camera Angle: ");

            scanw("%d", &guess);

            mvprintw(height-19, (width-20)/2,"Closest Angle: %d", closeGuess);

            if (abs(guess - outingCode) < abs(closeGuess - outingCode))
            {
                closeGuess = guess;  // Change is guess is closer than the previous closestGuess
            }
            
            if (guess == outingCode)
            {
                // PERFECT
                mvprintw(height-20,(width-3)/2,"Camera Angle Grade: PERFECT");
                *closestGuess = 40000;
                score = 4;
                perfect = 1;
            } else if (guess >= outingCode - 10 && guess <= outingCode + 10)
            {
                // VERY GOOD
                mvprintw(height-20,(width-30)/2,"Camera Angle Grade: VERY GOOD");
                *closestGuess = 30000;
                score = 3;
            } else if (guess >= outingCode - 100 && guess <= outingCode + 100)
            {
                // OKAY
                mvprintw(height-20,(width-30)/2,"Camera Angle Grade: OKAY");
                *closestGuess = 20000;
                score = 2;
            } else
            {
                // NOT GOOD
                mvprintw(height-20,(width-30)/2,"Camera Angle Grade: NOT GOOD");
                *closestGuess = 10000;
                score = 1;
            }

            *cameraRoll = *cameraRoll - 1;
            *closestGuess += closeGuess;
            mvprintw(8,2,"ACTIVITY POINTS: %2d", *actionPoints);
            mvprintw(9,2,"CAMERA ROLLS:    %d", *cameraRoll);   // Refreshes the display whenever a camera roll is used

            mvprintw(height-17, (width-50)/2,"%-50c", ' ');
            refresh();
        }

        // Cleans previous prints
        mvprintw(height-20, (width-50)/2,"%-50c", ' ');
        mvprintw(height-19, (width-50)/2,"%-50c", ' ');
        mvprintw(height-17, (width-50)/2,"%-50c", ' ');

        showscore(&dummyLVL, &dummyEXP, *closestGuess % 10000, *outing, score, 3);

        if (*actionPoints > 0 && !perfect)
        {
            init_pair(2, COLOR_GREEN, COLOR_BLACK);
            mvprintw(height-13, (width-18)/2,"You have more AP:");
            mvprintw(height-12, (width-38)/2,"  Continue Playing Memorable Minigame");
            mvprintw(height-11, (width-38)/2,"  Go Home");

            attron(COLOR_PAIR(2));
            switch (index)
            {
            case 1:
                mvprintw(height-12, (width-38)/2,"> Continue Playing Memorable Minigame");
                break;
            case 2:
                mvprintw(height-11, (width-38)/2,"  Go Home");
                break;
            
            default:
                break;
            }
            attroff(COLOR_PAIR(2));

            switch (getch())
            {
                case KEY_DOWN:
                    index++;
                    if (index > 2)
                    {
                        index = 1;
                    }
                    break;
                case KEY_UP:
                    index--;
                    if (index < 1)
                    {
                        index = 2;
                    }
                    break;
                case '\n':
                    if (index == 1)
                    {
                        *actionPoints -= 1;
                        *cameraRoll = 5;
                        mvprintw(8,2,"ACTIVITY POINTS: %2d", *actionPoints);
                        mvprintw(9,2,"CAMERA ROLLS:    %d", *cameraRoll);   // Refreshes the display whenever a camera roll is used

                        echo();
                    } else
                    {
                        close = 1;
                    }
                    break;
                default:
                    break;
            }
        } else
        {
            mvprintw(height-24, (width-27)/2, "Press [Enter] to continue!");
            getch();
            close = 1;
        }

        for (int i = 0; i < 30; i++)
        {
            // Cleans previous prints
            mvprintw(height-(31-i), (width-50)/2,"%-50c", ' ');
        }

    }

    noecho();
}