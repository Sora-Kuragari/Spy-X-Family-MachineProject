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
int scoring(int* XP, int correct, int question)
{
    int AP = -1;

    // Convert the integer to float
    float numerator = correct;
    float denominator = question;

    float correctPercent = (numerator / denominator) * 100;

    if (correctPercent == 100)
    {
        *XP += 3;
        switch(randomValue(1,2))
        {
            case 1:
                // No additional AP for you :(
                break;
            case 2:
                AP = 1; // WINNER! Award 1 AP
        }
    } else if (correctPercent >= 80)
    {
        *XP += 2;
    } else if (correctPercent >= 60)
    {
        *XP += 1;
    }

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
            mvprintw(20, 50, "%d + %d = ???", num1, num2);
            break;

        case 2:
            total = num1 - num2;
            mvprintw(20, 50, "%d - %d = ???", num1, num2);
            break;

        case 3:
            total = num1 * num2;
            mvprintw(20, 50, "%d * %d = ???", num1, num2);
            break;
        
        default:
            break;
        }        

        printw("%d", total);

        // scanf equivalent in curses
        scanw("%d", &input);

        if (input == total)
        {
            correct += 1;
        }

        mvprintw(20,50,"%50c",' ');

    }

    mvprintw(20,50,"COrrect: %d", correct);

    AP = scoring(mathEXP, correct, question);
    levelup(mathLVL, mathEXP);
    getch();

    noecho();           // Key pressed will not show
    curs_set(0);        // Hides the cursor
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
    //int input;
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

        // Display the prompts
        switch (prompt)
        {
        case 1:
            mvprintw(20,50,"Up!");
            break;
        case 2:
            mvprintw(20,50,"Down!");
            break;
        case 3:
            mvprintw(20,50,"Left!");
            break;
        case 4:
            mvprintw(20,50,"Right!");
            break;
        case 5:
            mvprintw(20,50,"North!");
            break;
        case 6:
            mvprintw(20,50,"South!");
            break;
        case 7:
            mvprintw(20,50,"East!");
            break;
        case 8:
            mvprintw(20,50,"West!");
            break;
        case 9:
            mvprintw(20,50,"UP AHEAD!");
            break;
        case 10:
            mvprintw(20,50,"BEHIND YOU!");
            break;
        case 11:
            mvprintw(20,50,"TO THE LEFT!");
            break;
        case 12:
            mvprintw(20,50,"TO THE RIGHT!");
            break;
        case 13:
            mvprintw(20,50,"Northwest!");
            break;
        case 14:
            mvprintw(20,50,"Northeast!");
            break;
        case 15:
            mvprintw(20,50,"Southwest!");
            break;
        case 16:
            mvprintw(20,50,"Southeast!");
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

    }

    additionalAP = scoring(peEXP, correct, 10);
    levelup(peLVL, peEXP);

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
                }
                break;
            case 3:
                if (randomValue(0,100) <= 50)
                {
                    *bondLVL += 1;
                }
                break;
            case 4:
                if (randomValue(0,100) <= 75)
                {
                    *bondLVL += 1;
                }
                break;            
            default:
                break;
            }

            // Awards 3 AP when bondLVL reaches 5
            if (*bondLVL == 5)
            {
                additionalAP = 3;
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
            }
        } else
        {        
            if (randomValue(0,100) <= 75)
            {
                *bondLVL += 1;
            }
            
            // Awards 3 AP when bondLVL reaches 5
            if (*bondLVL == 5)
            {
                additionalAP = 3;
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
                }
                break;
            case 3:
                if (randomValue(0,100) <= 75)
                {
                    *bondLVL += 1;
                }
                break;
            case 4:
                *bondLVL += 1;
                break;            
            default:
                break;
            }

            // Awards 3 AP when bondLVL reaches 5
            if (*bondLVL == 5)
            {
                additionalAP = 3;
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
            }
        } else
        {        
            *bondLVL += 1;
            
            // Awards 3 AP when bondLVL reaches 5
            if (*bondLVL == 5)
            {
                additionalAP = 3;
            }
        }
        break;
    
    default:
        break;
    }

    return additionalAP;
}

/*
    This function is the memorable minigame
*/
int memorableGame(int *cameraRoll, int *outing, int *code, int *closestGuess)
{
    int outingCode = 0;
    int guess;

    // If code doesn't exist then generate one
    mvprintw(20,20,"%d", *code);
    if (*code == 0)
    {
        *code = time(0);
    }
    mvprintw(20,20,"%d", *code);

    srand(*code);       // Sets the seed

    // Loops until the outing venue's code
    for (int i = 0; i < *outing; i++)
    {
        outingCode = randomValue(0,1000);
    }

    for (int i = *cameraRoll; i > 0 && guess != outingCode; i--)
    {
        scanw("%d", &guess);
        
        if (guess == outingCode)
        {
            // PERFECT
            mvprintw(20,20,"PERFECT");
        } else if (guess >= outingCode - 10 && guess <= outingCode + 10)
        {
            // VERY GOOD
            mvprintw(20,20,"VERY GOOD");
        } else if (guess >= outingCode - 100 && guess <= outingCode + 100)
        {
            // OKAY
            mvprintw(20,20,"OKAY");
        } else
        {
            // NOT GOOD
            mvprintw(20,20,"NOT GOOD");
        }

        *cameraRoll = *cameraRoll - 1;
        mvprintw(9,2,"CAMERA ROLLS:    %d", *cameraRoll);   // Refreshes the display whenever a camera roll is used
        refresh();
    }

    mvprintw(20,20,"%d",outingCode);
    getch();

    return 0;
}