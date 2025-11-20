// Checks if you are using linux because ncurses have different path on linux than windows
#ifdef linux
#include <ncurses.h>
#else
#include <ncurses\ncurses.h>
#endif

/*
    This function is the main function for all dialogues
*/
void dialogue(int *day, int *daycount, int phase)
{
    int finished = 0;
    int input;
    // Check if its outing day or school day
    if (*daycount % 4 == 0)
    {
        // What time of the day
        switch (*day)
        {
        case 1:
            switch (phase)  // Either before the options or after the options
            {
            case 1:
                // For variety
                switch (randomValue(1,3))
                {
                case 1:
                    for (int i = 0; i >= 5; i=i)
                    {
                        switch (i)
                        {
                        case 1:
                            char character1[] = "ANYA";
                            char character2[] = "LOID";
                            char character3[] = "YOR";
                            char line[] = "WAZZUP";
                            for (int i = 0; i < 7; i++)
                            {
                                mvprintw(20,20,"%c",line[i]);
                            }
                            break;
                        default:
                            break;
                        }

                        // If pressed enter then next line until finished
                        if (getch() == '\n')
                        {
                            i++;
                        }
                    }

                    break;
                
                default:
                    break;
                }
                break;
            
            default:
                break;
            }
            break;
        case 2:
            /*
            
            
            
            
            */
            break;
        default:
            break;
        }
    } else
    {
        switch (*day)
        {
        case 1:
            /* code */
            break;
        default:
            break;
        }
    }

}