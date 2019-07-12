#include "headers.h"

void unavailable(UserGraph* graph, char *timeslots)
{
     /***Make this it's own function so that we can call it for all available graphs when student inputs unavailable days
        I can also use this function to create the timeslots for each class so that input file doesn't need to have binary class times**/


       /*if(timeslots[0] == 'm' || timeslots[0] == 'M')
        {
            switch(timeslots[1]) //check unavailableDays and 100000000 for conflict. if no conflict then add 100000000 to unavailableDays
            {
                case '1':
                    if(findTimeConflictInteger(graph->unavailableDays[0], 100000000) == false)
                        graph->unavailableDays[0] += 100000000;
                    break;
                case '2':
                    if(findTimeConflictInteger(graph->unavailableDays[0], 10000000) == false)
                        graph->unavailableDays[0] += 10000000;
                    break;
                case '3':
                    if(findTimeConflictInteger(graph->unavailableDays[0], 1000000) == false)
                        graph->unavailableDays[0] += 1000000;
                    break;
                case '4':
                    if(findTimeConflictInteger(graph->unavailableDays[0], 100000) == false)
                        graph->unavailableDays[0] += 100000;
                    break;
                case '5':
                    if(findTimeConflictInteger(graph->unavailableDays[0], 10000) == false)
                        graph->unavailableDays[0] += 10000;
                    break;
                case '6':
                    if(findTimeConflictInteger(graph->unavailableDays[0], 1000) == false)
                        graph->unavailableDays[0] += 1000;
                    break;
                case '7':
                    if(findTimeConflictInteger(graph->unavailableDays[0], 100) == false)
                        graph->unavailableDays[0] += 100;
                    break;
                case '8':
                    if(findTimeConflictInteger(graph->unavailableDays[0], 10) == false)
                        graph->unavailableDays[0] += 10;
                    break;
                case '9':
                    if(findTimeConflictInteger(graph->unavailableDays[0], 1) == false)
                        graph->unavailableDays[0] += 1;
                    break;
                default: break;
            }
        }*/
        if(timeslots[0] == 'm' || timeslots[0] == 'M')
        {
            switch(timeslots[1]) //check unavailableDays and 100000000 for conflict. if no conflict then add 100000000 to unavailableDays
            {
                case '1':
                    if(findTimeConflictInteger(graph->unavailableDays[1], 1000000000000) == false)
                        graph->unavailableDays[1] += 1000000000000;
                    break;
                case '2':
                    if(findTimeConflictInteger(graph->unavailableDays[1], 100000000000) == false)
                        graph->unavailableDays[1] += 100000000000;
                    break;
                case '3':
                    if(findTimeConflictInteger(graph->unavailableDays[1], 10000000000) == false)
                        graph->unavailableDays[1] += 10000000000;
                    break;
                case '4':
                    if(findTimeConflictInteger(graph->unavailableDays[1], 1000000000) == false)
                        graph->unavailableDays[1] += 1000000000;
                    break;
                case 'n':
                    if(findTimeConflictInteger(graph->unavailableDays[1], 100000000) == false)
                        graph->unavailableDays[1] += 100000000;
                    break;
                case '5':
                    if(findTimeConflictInteger(graph->unavailableDays[1], 10000000) == false)
                        graph->unavailableDays[1] += 10000000;
                    break;
                case '6':
                    if(findTimeConflictInteger(graph->unavailableDays[1], 1000000) == false)
                        graph->unavailableDays[1] += 1000000;
                    break;
                case '7':
                    if(findTimeConflictInteger(graph->unavailableDays[1], 100000) == false)
                        graph->unavailableDays[1] += 100000;
                    break;
                case '8':
                    if(findTimeConflictInteger(graph->unavailableDays[1], 10000) == false)
                        graph->unavailableDays[1] += 10000;
                    break;
                case '9':
                    if(findTimeConflictInteger(graph->unavailableDays[1], 1000) == false)
                        graph->unavailableDays[1] += 1000;
                    break;
                case 'a':
                    if(findTimeConflictInteger(graph->unavailableDays[1], 100) == false)
                        graph->unavailableDays[1] += 100;
                    break;
                case 'A':
                    if(findTimeConflictInteger(graph->unavailableDays[1], 100) == false)
                        graph->unavailableDays[1] += 100;
                    break;
                case 'b':
                    if(findTimeConflictInteger(graph->unavailableDays[1], 10) == false)
                        graph->unavailableDays[1] += 10;
                    break;
                case 'B':
                    if(findTimeConflictInteger(graph->unavailableDays[1], 10) == false)
                        graph->unavailableDays[1] += 10;
                    break;
                case 'c':
                    if(findTimeConflictInteger(graph->unavailableDays[1], 1) == false)
                        graph->unavailableDays[1] += 1;
                    break;
                case 'C':
                    if(findTimeConflictInteger(graph->unavailableDays[1], 1) == false)
                        graph->unavailableDays[1] += 1;
                    break;
                default: break;
            }
        }
        else if(timeslots[0] == 't' || timeslots[0] == 'T')
        {
            switch(timeslots[1]) //check unavailableDays and 100000000 for conflict. if no conflict then add 100000000 to unavailableDays
            {
                case '1':
                    if(findTimeConflictInteger(graph->unavailableDays[2], 1000000000000) == false)
                        graph->unavailableDays[2] += 1000000000000;
                    break;
                case '2':
                    if(findTimeConflictInteger(graph->unavailableDays[2], 100000000000) == false)
                        graph->unavailableDays[2] += 100000000000;
                    break;
                case '3':
                    if(findTimeConflictInteger(graph->unavailableDays[2], 10000000000) == false)
                        graph->unavailableDays[2] += 10000000000;
                    break;
                case '4':
                    if(findTimeConflictInteger(graph->unavailableDays[2], 1000000000) == false)
                        graph->unavailableDays[2] += 1000000000;
                    break;
                case 'n':
                    if(findTimeConflictInteger(graph->unavailableDays[2], 100000000) == false)
                        graph->unavailableDays[2] += 100000000;
                    break;
                case '5':
                    if(findTimeConflictInteger(graph->unavailableDays[2], 10000000) == false)
                        graph->unavailableDays[2] += 10000000;
                    break;
                case '6':
                    if(findTimeConflictInteger(graph->unavailableDays[2], 1000000) == false)
                        graph->unavailableDays[2] += 1000000;
                    break;
                case '7':
                    if(findTimeConflictInteger(graph->unavailableDays[2], 100000) == false)
                        graph->unavailableDays[2] += 100000;
                    break;
                case '8':
                    if(findTimeConflictInteger(graph->unavailableDays[2], 10000) == false)
                        graph->unavailableDays[2] += 10000;
                    break;
                case '9':
                    if(findTimeConflictInteger(graph->unavailableDays[2], 1000) == false)
                        graph->unavailableDays[2] += 1000;
                    break;
                case 'a':
                    if(findTimeConflictInteger(graph->unavailableDays[2], 100) == false)
                        graph->unavailableDays[2] += 100;
                    break;
                case 'A':
                    if(findTimeConflictInteger(graph->unavailableDays[2], 100) == false)
                        graph->unavailableDays[2] += 100;
                    break;
                case 'b':
                    if(findTimeConflictInteger(graph->unavailableDays[2], 10) == false)
                        graph->unavailableDays[2] += 10;
                    break;
                 case 'B':
                    if(findTimeConflictInteger(graph->unavailableDays[2], 10) == false)
                        graph->unavailableDays[2] += 10;
                    break;
                case 'c':
                    if(findTimeConflictInteger(graph->unavailableDays[2], 1) == false)
                        graph->unavailableDays[2] += 1;
                    break;
                case 'C':
                    if(findTimeConflictInteger(graph->unavailableDays[2], 1) == false)
                        graph->unavailableDays[2] += 1;
                    break;
                default: break;
            }
        }
        else if(timeslots[0] == 'w' || timeslots[0] == 'W')
        {
            switch(timeslots[1]) //check unavailableDays and 100000000 for conflict. if no conflict then add 100000000 to unavailableDays
            {
                case '1':
                    if(findTimeConflictInteger(graph->unavailableDays[3], 1000000000000) == false)
                        graph->unavailableDays[3] += 1000000000000;
                    break;
                case '2':
                    if(findTimeConflictInteger(graph->unavailableDays[3], 100000000000) == false)
                        graph->unavailableDays[3] += 100000000000;
                    break;
                case '3':
                    if(findTimeConflictInteger(graph->unavailableDays[3], 10000000000) == false)
                        graph->unavailableDays[3] += 10000000000;
                    break;
                case '4':
                    if(findTimeConflictInteger(graph->unavailableDays[3], 1000000000) == false)
                        graph->unavailableDays[3] += 1000000000;
                    break;
                case 'n':
                    if(findTimeConflictInteger(graph->unavailableDays[3], 100000000) == false)
                        graph->unavailableDays[3] += 100000000;
                    break;
                case '5':
                    if(findTimeConflictInteger(graph->unavailableDays[3], 10000000) == false)
                        graph->unavailableDays[3] += 10000000;
                    break;
                case '6':
                    if(findTimeConflictInteger(graph->unavailableDays[3], 1000000) == false)
                        graph->unavailableDays[3] += 1000000;
                    break;
                case '7':
                    if(findTimeConflictInteger(graph->unavailableDays[3], 100000) == false)
                        graph->unavailableDays[3] += 100000;
                    break;
                case '8':
                    if(findTimeConflictInteger(graph->unavailableDays[3], 10000) == false)
                        graph->unavailableDays[3] += 10000;
                    break;
                case '9':
                    if(findTimeConflictInteger(graph->unavailableDays[3], 1000) == false)
                        graph->unavailableDays[3] += 1000;
                    break;
                case 'a':
                    if(findTimeConflictInteger(graph->unavailableDays[3], 100) == false)
                        graph->unavailableDays[3] += 100;
                    break;
                case 'A':
                    if(findTimeConflictInteger(graph->unavailableDays[3], 100) == false)
                        graph->unavailableDays[3] += 100;
                    break;
                case 'b':
                    if(findTimeConflictInteger(graph->unavailableDays[3], 10) == false)
                        graph->unavailableDays[3] += 10;
                    break;
                case 'B':
                    if(findTimeConflictInteger(graph->unavailableDays[3], 10) == false)
                        graph->unavailableDays[3] += 10;
                    break;
                case 'c':
                    if(findTimeConflictInteger(graph->unavailableDays[3], 1) == false)
                        graph->unavailableDays[3] += 1;
                    break;
                case 'C':
                    if(findTimeConflictInteger(graph->unavailableDays[3], 1) == false)
                        graph->unavailableDays[3] += 1;
                    break;
                default: break;
            }
        }
        else if(timeslots[0] == 'r' || timeslots[0] == 'R')
        {
            switch(timeslots[1]) //check unavailableDays and 100000000 for conflict. if no conflict then add 100000000 to unavailableDays
            {
                case '1':
                    if(findTimeConflictInteger(graph->unavailableDays[4], 1000000000000) == false)
                        graph->unavailableDays[4] += 1000000000000;
                    break;
                case '2':
                    if(findTimeConflictInteger(graph->unavailableDays[4], 100000000000) == false)
                        graph->unavailableDays[4] += 100000000000;
                    break;
                case '3':
                    if(findTimeConflictInteger(graph->unavailableDays[4], 10000000000) == false)
                        graph->unavailableDays[4] += 10000000000;
                    break;
                case '4':
                    if(findTimeConflictInteger(graph->unavailableDays[4], 1000000000) == false)
                        graph->unavailableDays[4] += 1000000000;
                    break;
                case 'n':
                    if(findTimeConflictInteger(graph->unavailableDays[4], 100000000) == false)
                        graph->unavailableDays[4] += 100000000;
                    break;
                case '5':
                    if(findTimeConflictInteger(graph->unavailableDays[4], 10000000) == false)
                        graph->unavailableDays[4] += 10000000;
                    break;
                case '6':
                    if(findTimeConflictInteger(graph->unavailableDays[4], 1000000) == false)
                        graph->unavailableDays[4] += 1000000;
                    break;
                case '7':
                    if(findTimeConflictInteger(graph->unavailableDays[4], 100000) == false)
                        graph->unavailableDays[4] += 100000;
                    break;
                case '8':
                    if(findTimeConflictInteger(graph->unavailableDays[4], 10000) == false)
                        graph->unavailableDays[4] += 10000;
                    break;
                case '9':
                    if(findTimeConflictInteger(graph->unavailableDays[4], 1000) == false)
                        graph->unavailableDays[4] += 1000;
                    break;
                case 'a':
                    if(findTimeConflictInteger(graph->unavailableDays[4], 100) == false)
                        graph->unavailableDays[4] += 100;
                    break;
                case 'A':
                    if(findTimeConflictInteger(graph->unavailableDays[4], 100) == false)
                        graph->unavailableDays[4] += 100;
                    break;
                case 'b':
                    if(findTimeConflictInteger(graph->unavailableDays[4], 10) == false)
                        graph->unavailableDays[4] += 10;
                    break;
                case 'B':
                    if(findTimeConflictInteger(graph->unavailableDays[4], 10) == false)
                        graph->unavailableDays[4] += 10;
                    break;
                case 'c':
                    if(findTimeConflictInteger(graph->unavailableDays[4], 1) == false)
                        graph->unavailableDays[4] += 1;
                    break;
                case 'C':
                    if(findTimeConflictInteger(graph->unavailableDays[4], 1) == false)
                        graph->unavailableDays[4] += 1;
                    break;
                default: break;
            }
        }
        else if(timeslots[0] == 'f' || timeslots[0] == 'F')
        {
            switch(timeslots[1]) //check unavailableDays and 100000000 for conflict. if no conflict then add 100000000 to unavailableDays
            {
                case '1':
                    if(findTimeConflictInteger(graph->unavailableDays[5], 1000000000000) == false)
                        graph->unavailableDays[5] += 1000000000000;
                    break;
                case '2':
                    if(findTimeConflictInteger(graph->unavailableDays[5], 100000000000) == false)
                        graph->unavailableDays[5] += 100000000000;
                    break;
                case '3':
                    if(findTimeConflictInteger(graph->unavailableDays[5], 10000000000) == false)
                        graph->unavailableDays[5] += 10000000000;
                    break;
                case '4':
                    if(findTimeConflictInteger(graph->unavailableDays[5], 1000000000) == false)
                        graph->unavailableDays[5] += 1000000000;
                    break;
                case 'n':
                    if(findTimeConflictInteger(graph->unavailableDays[5], 100000000) == false)
                        graph->unavailableDays[5] += 100000000;
                    break;
                case '5':
                    if(findTimeConflictInteger(graph->unavailableDays[5], 10000000) == false)
                        graph->unavailableDays[5] += 10000000;
                    break;
                case '6':
                    if(findTimeConflictInteger(graph->unavailableDays[5], 1000000) == false)
                        graph->unavailableDays[5] += 1000000;
                    break;
                case '7':
                    if(findTimeConflictInteger(graph->unavailableDays[5], 100000) == false)
                        graph->unavailableDays[5] += 100000;
                    break;
                case '8':
                    if(findTimeConflictInteger(graph->unavailableDays[5], 10000) == false)
                        graph->unavailableDays[5] += 10000;
                    break;
                case '9':
                    if(findTimeConflictInteger(graph->unavailableDays[5], 1000) == false)
                        graph->unavailableDays[5] += 1000;
                    break;
                case 'a':
                    if(findTimeConflictInteger(graph->unavailableDays[5], 100) == false)
                        graph->unavailableDays[5] += 100;
                    break;
                case 'A':
                    if(findTimeConflictInteger(graph->unavailableDays[5], 100) == false)
                        graph->unavailableDays[5] += 100;
                    break;
                case 'b':
                    if(findTimeConflictInteger(graph->unavailableDays[5], 10) == false)
                        graph->unavailableDays[5] += 10;
                    break;
                case 'B':
                    if(findTimeConflictInteger(graph->unavailableDays[5], 10) == false)
                        graph->unavailableDays[5] += 10;
                    break;
                case 'c':
                    if(findTimeConflictInteger(graph->unavailableDays[5], 1) == false)
                        graph->unavailableDays[5] += 1;
                    break;
                case 'C':
                    if(findTimeConflictInteger(graph->unavailableDays[5], 1) == false)
                        graph->unavailableDays[5] += 1;
                    break;
                default: break;
            }
        }
        else if(timeslots[0] == 's' || timeslots[0] == 'S')
        {
            switch(timeslots[1]) //check unavailableDays and 100000000 for conflict. if no conflict then add 100000000 to unavailableDays
            {
                case '1':
                    if(findTimeConflictInteger(graph->unavailableDays[6], 1000000000000) == false)
                        graph->unavailableDays[6] += 1000000000000;
                    break;
                case '2':
                    if(findTimeConflictInteger(graph->unavailableDays[6], 100000000000) == false)
                        graph->unavailableDays[6] += 100000000000;
                    break;
                case '3':
                    if(findTimeConflictInteger(graph->unavailableDays[6], 10000000000) == false)
                        graph->unavailableDays[6] += 10000000000;
                    break;
                case '4':
                    if(findTimeConflictInteger(graph->unavailableDays[6], 1000000000) == false)
                        graph->unavailableDays[6] += 1000000000;
                    break;
                case 'n':
                    if(findTimeConflictInteger(graph->unavailableDays[6], 100000000) == false)
                        graph->unavailableDays[6] += 100000000;
                    break;
                case '5':
                    if(findTimeConflictInteger(graph->unavailableDays[6], 10000000) == false)
                        graph->unavailableDays[6] += 10000000;
                    break;
                case '6':
                    if(findTimeConflictInteger(graph->unavailableDays[6], 1000000) == false)
                        graph->unavailableDays[6] += 1000000;
                    break;
                case '7':
                    if(findTimeConflictInteger(graph->unavailableDays[6], 100000) == false)
                        graph->unavailableDays[6] += 100000;
                    break;
                case '8':
                    if(findTimeConflictInteger(graph->unavailableDays[6], 10000) == false)
                        graph->unavailableDays[6] += 10000;
                    break;
                case '9':
                    if(findTimeConflictInteger(graph->unavailableDays[6], 1000) == false)
                        graph->unavailableDays[6] += 1000;
                    break;
                case 'a':
                    if(findTimeConflictInteger(graph->unavailableDays[6], 100) == false)
                        graph->unavailableDays[6] += 100;
                    break;
                case 'A':
                    if(findTimeConflictInteger(graph->unavailableDays[6], 100) == false)
                        graph->unavailableDays[6] += 100;
                    break;
                case 'b':
                    if(findTimeConflictInteger(graph->unavailableDays[6], 10) == false)
                        graph->unavailableDays[6] += 10;
                    break;
                case 'B':
                    if(findTimeConflictInteger(graph->unavailableDays[6], 10) == false)
                        graph->unavailableDays[6] += 10;
                    break;
                case 'c':
                    if(findTimeConflictInteger(graph->unavailableDays[6], 1) == false)
                        graph->unavailableDays[6] += 1;
                    break;
                case 'C':
                    if(findTimeConflictInteger(graph->unavailableDays[6], 1) == false)
                        graph->unavailableDays[6] += 1;
                    break;
                default: break;
            }
        }
}


