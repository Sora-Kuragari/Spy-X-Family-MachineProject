#include <string.h>
#include <ncurses\ncurses.h>

/*
    This function is the main function for dialogues when picking an action
    Preconditions: Called before picking the actions
    @param *day - time of the day [1] - Morning, [2] - Afternoon, [3] - Evening
    @param *daycount - number of day
*/
void dialogueOptions(int day, int daycount)
{
    int height, width;
    getmaxyx(stdscr, height, width);

    int finished = 0;
    int index = 1;

    char dialogueline[512];

    while (!finished)
    {
        // Outing Day
        if (daycount % 4 == 0)
        {
            switch (day)
            {
            case 1: // Morning
                switch (index)
                {
                    case 1:
                        strcpy(dialogueline, "Ooting day! Ooting day!");
                        mvprintw(height-35, (width-100)/2, "ANYA FORGER: ");
                        for (int i = 0; i < 24; i++)
                        {
                            for (int j = 0; j <= 100000000; j++);
                            mvprintw(height-34, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;
                    case 2:
                        strcpy(dialogueline, "I packed a lunch for everyone! I hope it's alright...");
                        mvprintw(height-32, (width-100)/2, "YOR FORGER: ");
                        for (int i = 0; i < 54; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-31, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;
                    case 3:
                        strcpy(dialogueline, "Now, Anya, remember the point of this outing is to create a good project. Let's all have a ");
                        mvprintw(height-29, (width-100)/2, "LOID FORGER: ");
                        for (int i = 0; i < 92; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-28, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        strcpy(dialogueline, "productive time.");
                        for (int i = 0; i < 17; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-27, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;
                    case 4:
                        strcpy(dialogueline, "(Nods) Anya will make it super productive! And fun! Waku waku!");
                        mvprintw(height-25, (width-100)/2, "ANYA FORGER: ");
                        for (int i = 0; i < 63; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-24, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;

                    default:
                        finished = 1;
                        break;
                }
                break;

            case 2: // Afternoon
                switch (index)
                {
                    case 1:
                        strcpy(dialogueline, "Well, we're here. This seems like a good spot.");
                        mvprintw(height-35, (width-100)/2, "LOID FORGER: ");
                        for (int i = 0; i < 47; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-34, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;
                    case 2:
                        strcpy(dialogueline, "It's so lovely here! The atmosphere is so... peaceful.");
                        mvprintw(height-32, (width-100)/2, "YOR FORGER: ");
                        for (int i = 0; i < 55; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-31, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;
                    case 3:
                        strcpy(dialogueline, "Borf Borf Borf!");
                        mvprintw(height-29, (width-100)/2, "BOND FORGER: ");
                        for (int i = 0; i < 16; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-28, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;
                    case 4:
                        strcpy(dialogueline, "We're here! Time to make memories for the project! And for us!");
                        mvprintw(height-26, (width-100)/2, "ANYA FORGER: ");
                        for (int i = 0; i < 63; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-25, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;
                    default:
                        finished = 1;
                        break;
                }
                break;

            case 3: // Evening – Family Meeting (Decide next outing)
                switch (index)
                {
                    case 1:
                        strcpy(dialogueline, "It's time to plan our next family outing.");
                        mvprintw(height-35, (width-100)/2, "LOID FORGER: ");
                        for (int i = 0; i < 42; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-34, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;
                    case 2:
                        strcpy(dialogueline, "I wonder where we should go.");
                        mvprintw(height-32, (width-100)/2, "YOR FORGER: ");
                        for (int i = 0; i < 29; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-31, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;
                    case 3:
                        strcpy(dialogueline, "The location should be suitable for a family project. Do you have any ideas, Anya?");
                        mvprintw(height-29, (width-100)/2, "LOID FORGER: ");
                        for (int i = 0; i < 83; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-28, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;
                    case 4:
                        strcpy(dialogueline, "Anya is thinking... somewhere with peanuts!");
                        mvprintw(height-26, (width-100)/2, "ANYA FORGER: ");
                        for (int i = 0; i < 44; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-25, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;

                    default:
                        finished = 1;
                        break;
                }
                break;

            default:
                finished = 1;
                break;
            }
        } else        // Regular School Day
        {
            switch (day)
            {
            case 1: // Morning
                switch (index)
                {
                    case 1:
                        strcpy(dialogueline, "(The school bell rings. Anya stands in the courtyard, looking around)");
                        mvprintw(height-35, (width-100)/2, " ");
                        for (int i = 0; i < 70; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-34, ((width-70)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;
                    case 2:
                        strcpy(dialogueline, "(Waving) Anya! Over here! I have so much to tell you!");
                        mvprintw(height-32, (width-100)/2, "BECKY BLACKBELL: ");
                        for (int i = 0; i < 54; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-31, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;
                    case 3:
                        strcpy(dialogueline, "Try not to cause any trouble, Forger.");
                        mvprintw(height-29, (width-100)/2, "DAMIAN DESMOND: ");
                        for (int i = 0; i < 38; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-28, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;
                    case 4:
                        strcpy(dialogueline, "(Adjusting his monocle) A new day at Eden Academy. Let us all strive for elegance.");
                        mvprintw(height-26, (width-100)/2, "MR. HENDERSON: ");
                        for (int i = 0; i < 83; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-25, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;
                    case 5:
                        strcpy(dialogueline, "(Thinking) So many people... So many loud brains... What should Anya do?");
                        mvprintw(height-23, (width-100)/2, "ANYA FORGER: ");
                        for (int i = 0; i < 73; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-22, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;
                    default:
                        finished = 1;
                        break;
                }
                break;

            case 2: // Afternoon – At home
                switch (index)
                {
                    case 1:
                        strcpy(dialogueline, "Welcome home, Anya. Did you have a good day at school?");
                        mvprintw(height-35, (width-100)/2, "LOID FORGER: ");
                        for (int i = 0; i < 55; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-34, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;
                    case 2:
                        strcpy(dialogueline, "Hello, Anya! I made... well, I tried to make a snack.");
                        mvprintw(height-32, (width-100)/2, "YOR FORGER: ");
                        for (int i = 0; i < 54; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-31, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;
                    case 3:
                        strcpy(dialogueline, "(Wagging his tail) Borf Borf Borf!");
                        mvprintw(height-29, (width-100)/2, "BOND FORGER: ");
                        for (int i = 0; i < 35; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-28, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;
                    case 4:
                        strcpy(dialogueline, "Anya's home! Now... should Anya study, train, or play? So many choices!");
                        mvprintw(height-26, (width-100)/2, "ANYA FORGER: ");
                        for (int i = 0; i < 72; i++)
                        {
                            for (int j = 0; j <= 50000000; j++);
                            mvprintw(height-25, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                            refresh();
                        }
                        index++;
                        break;
                    default:
                        finished = 1;
                        break;
                }
                break;

            default:
                finished = 1;
                break;
            }
        }
    }
}

/*
    This function is the main function that handles Bonding Dialogues whether its a success or failure
    Preconditions: Must be called from memorable minigame
    @param character - Bonding Character [1]-Damian, [2]-Becky, [3]-Henderson, [4]-Bond
    @param result - [1] - Bonding Success, [0] - Bonding Failure
*/
void dialogueBonding(int character, int result)
{
    int height, width;
    getmaxyx(stdscr, height, width);

    int finished = 0;
    int index = 1;
    char dialogueline[512];

    while (!finished)
    {
        switch (character)
        {
        case 1: // DAMIAN
            switch (result)
            {
            case 1: // SUCCESS
                switch (index)
                {
                case 1:
                    strcpy(dialogueline, "Anya can climb the rope super fast!");
                    mvprintw(height-35, (width-100)/2, "ANYA FORGER: ");
                    for (int i = 0; i < 36; i++)
                    {
                        for (int j = 0; j <= 50000000; j++);
                        mvprintw(height-34, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                        refresh();
                    }
                    index++;
                    break;
                case 2:
                    strcpy(dialogueline, "Hah! Not bad. But I'm still faster, obviously.");
                    mvprintw(height-32, (width-100)/2, "DAMIAN DESMOND: ");
                    for (int i = 0; i < 47; i++)
                    {
                        for (int j = 0; j <= 50000000; j++);
                        mvprintw(height-31, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                        refresh();
                    }
                    index++;
                    break;
                case 3:
                    strcpy(dialogueline, "Heh. Sy-on boy is impressed.");
                    mvprintw(height-29, (width-100)/2, "ANYA FORGER: ");
                    for (int i = 0; i < 29; i++)
                    {
                        for (int j = 0; j <= 50000000; j++);
                        mvprintw(height-28, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                        refresh();
                    }
                    index++;
                    break;
                
                default:
                    finished = 1;
                    break;
                }
                break;
            
            default:    // FAILED
                switch (index)
                {
                case 1:
                    strcpy(dialogueline, "Anya... can't... reach...");
                    mvprintw(height-35, (width-100)/2, "ANYA FORGER: ");
                    for (int i = 0; i < 26; i++)
                    {
                        for (int j = 0; j <= 50000000; j++);
                        mvprintw(height-34, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                        refresh();
                    }
                    index++;
                    break;
                case 2:
                    strcpy(dialogueline, "Can't even reach the first branch? Don't strain yourself, shorty.");
                    mvprintw(height-32, (width-100)/2, "DAMIAN DESMOND: ");
                    for (int i = 0; i < 66; i++)
                    {
                        for (int j = 0; j <= 50000000; j++);
                        mvprintw(height-31, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                        refresh();
                    }
                    index++;
                    break;
                case 3:
                    strcpy(dialogueline, "Anya will grow! And then...");
                    mvprintw(height-29, (width-100)/2, "ANYA FORGER: ");
                    for (int i = 0; i < 28; i++)
                    {
                        for (int j = 0; j <= 50000000; j++);
                        mvprintw(height-28, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                        refresh();
                    }
                    index++;
                    break;
                
                default:
                    finished = 1;
                    break;
                }
                break;
            }
            break;
        case 2: // BECKY
            switch (result)
            {
            case 1: // SUCCESS
                switch (index)
                {
                case 1:
                    strcpy(dialogueline, "Your hair is so cute like that!");
                    mvprintw(height-35, (width-100)/2, "BECKY BLACKBELL: ");
                    for (int i = 0; i < 32; i++)
                    {
                        for (int j = 0; j <= 50000000; j++);
                        mvprintw(height-34, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                        refresh();
                    }
                    index++;
                    break;
                case 2:
                    strcpy(dialogueline, "Really? Anya looks elegant?");
                    mvprintw(height-32, (width-100)/2, "ANYA FORGER: ");
                    for (int i = 0; i < 28; i++)
                    {
                        for (int j = 0; j <= 50000000; j++);
                        mvprintw(height-31, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                        refresh();
                    }
                    index++;
                    break;
                case 3:
                    strcpy(dialogueline, "So elegant! We're the best, most elegant friends!");
                    mvprintw(height-29, (width-100)/2, "BECKY BLACKBELL: ");
                    for (int i = 0; i < 50; i++)
                    {
                        for (int j = 0; j <= 50000000; j++);
                        mvprintw(height-28, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                        refresh();
                    }
                    index++;
                    break;
                
                default:
                    finished = 1;
                    break;
                }
                break;
            
            default:    // FAILED
                switch (index)
                {
                case 1:
                    strcpy(dialogueline, "So then I told him that shade of red was simply not acceptable.");
                    mvprintw(height-35, (width-100)/2, "BECKY BLACKBELL: ");
                    for (int i = 0; i < 64; i++)
                    {
                        for (int j = 0; j <= 50000000; j++);
                        mvprintw(height-34, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                        refresh();
                    }
                    index++;
                    break;
                case 2:
                    strcpy(dialogueline, "Anya is lost...");
                    mvprintw(height-32, (width-100)/2, "ANYA FORGER: ");
                    for (int i = 0; i < 16; i++)
                    {
                        for (int j = 0; j <= 50000000; j++);
                        mvprintw(height-31, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                        refresh();
                    }
                    index++;
                    break;
                case 3:
                    strcpy(dialogueline, "You just don't get it yet. It's fine.");
                    mvprintw(height-29, (width-100)/2, "BECKY BLACKBELL: ");
                    for (int i = 0; i < 38; i++)
                    {
                        for (int j = 0; j <= 50000000; j++);
                        mvprintw(height-28, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                        refresh();
                    }
                    index++;
                    break;
                
                default:
                    finished = 1;   
                    break;
                }
                break;
            }
            break;
        case 3: // HENDERSON
            switch (result)
            {
            case 1: // SUCCESS
                switch (index)
                {
                case 1:
                    strcpy(dialogueline, "Eight divided by two is four!");
                    mvprintw(height-35, (width-100)/2, "ANYA FORGER: ");
                    for (int i = 0; i < 30; i++)
                    {
                        for (int j = 0; j <= 50000000; j++);
                        mvprintw(height-34, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                        refresh();
                    }
                    index++;
                    break;
                case 2:
                    strcpy(dialogueline, "Excellent! A perfectly elegant division");
                    mvprintw(height-32, (width-100)/2, "MR. HENDERSON: ");
                    for (int i = 0; i < 40; i++)
                    {
                        for (int j = 0; j <= 50000000; j++);
                        mvprintw(height-31, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                        refresh();
                    }
                    index++;
                    break;
                case 3:
                    strcpy(dialogueline, "Anya is a math master!");
                    mvprintw(height-29, (width-100)/2, "ANYA FORGER: ");
                    for (int i = 0; i < 23; i++)
                    {
                        for (int j = 0; j <= 50000000; j++);
                        mvprintw(height-28, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                        refresh();
                    }
                    index++;
                    break;
                
                default:
                    finished = 1;
                    break;
                }
                break;
            
            default:    // FAILED
                switch (index)
                {
                case 1:
                    strcpy(dialogueline, "Ten divided by two is... six?");
                    mvprintw(height-35, (width-100)/2, "ANYA FORGER: ");
                    for (int i = 0; i < 30; i++)
                    {
                        for (int j = 0; j <= 50000000; j++);
                        mvprintw(height-34, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                        refresh();
                    }
                    index++;
                    break;
                case 2:
                    strcpy(dialogueline, "A valiant effort, but the principle of division requires further study.");
                    mvprintw(height-32, (width-100)/2, "MR. HENDERSON: ");
                    for (int i = 0; i < 72; i++)
                    {
                        for (int j = 0; j <= 50000000; j++);
                        mvprintw(height-31, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                        refresh();
                    }
                    index++;
                    break;
                case 3:
                    strcpy(dialogueline, "The numbers are fighting...");
                    mvprintw(height-29, (width-100)/2, "ANYA FORGER: ");
                    for (int i = 0; i < 28; i++)
                    {
                        for (int j = 0; j <= 50000000; j++);
                        mvprintw(height-28, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                        refresh();
                    }
                    index++;
                    break;
                
                default:
                    finished = 1;
                    break;
                }
                break;
            }
            break;
        case 4: // BOND
            switch (index)
            {
            case 1:
                strcpy(dialogueline, "Let's play, Bond!");
                mvprintw(height-35, (width-100)/2, "ANYA FORGER: ");
                for (int i = 0; i < 18; i++)
                {
                    for (int j = 0; j <= 50000000; j++);
                    mvprintw(height-34, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                    refresh();
                }
                index++;
                break;
            case 2:
                strcpy(dialogueline, "Borf Borf Borf!");
                mvprintw(height-32, (width-100)/2, "BOND FORGER: ");
                for (int i = 0; i < 16; i++)
                {
                    for (int j = 0; j <= 50000000; j++);
                    mvprintw(height-31, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                    refresh();
                }
                index++;
                break;
            case 3:
                strcpy(dialogueline, "Bond is the best secret agent dog!");
                mvprintw(height-29, (width-100)/2, "ANYA FORGER: ");
                for (int i = 0; i < 35; i++)
                {
                    for (int j = 0; j <= 50000000; j++);
                    mvprintw(height-28, ((width-100)/2)+4+i, "%c", dialogueline[i]);
                    refresh();
                }
                index++;
                break;
            
            default:
                finished = 1;
                break;
            }
            break;
        
        default:
            break;
        } 
    }
    mvprintw(height-24, (width-27)/2, "Press [Enter] to continue!");
    getch();
    cleanDialogue();
}