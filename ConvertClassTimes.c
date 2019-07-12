#include<string.h>
#include "headers.h"

long long* convertClassTime(char *timeString, char *semester)
{
    static long long classTime[7];
    int length;

    for(int i=0; i<7; i++)
        classTime[i] = 0;

    length = strlen(timeString);

    for(int i = 0; i < length; i+=2)
    {
        //printf("%c %c\n", timeString[i], timeString[i+1]);

        if(strcasecmp(semester, "fall") == 0)
        {
            classTime[0] = 1;
        }
        else if(strcasecmp(semester, "spring") == 0)
        {
            classTime[0] = 2;
        }
         else if(strcasecmp(semester, "summer") == 0)
        {
            classTime[0] = 3;
        }

        if(timeString[i] == 'm' || timeString[i] == 'M')
        {
            switch(timeString[i+1]) //check unavailableDays and 100000000 for conflict. if no conflict then add 100000000 to unavailableDays
            {
                case '1':
                    if(findTimeConflictInteger(classTime[1], 1000000000000) == false)
                        classTime[1] += 1000000000000;
                    break;
                case '2':
                    if(findTimeConflictInteger(classTime[1], 100000000000) == false)
                        classTime[1] += 100000000000;
                    break;
                case '3':
                    if(findTimeConflictInteger(classTime[1], 10000000000) == false)
                        classTime[1] += 10000000000;
                    break;
                case '4':
                    if(findTimeConflictInteger(classTime[1], 1000000000) == false)
                        classTime[1] += 1000000000;
                    break;
                case 'n':
                    if(findTimeConflictInteger(classTime[1], 100000000) == false)
                        classTime[1] += 100000000;
                    break;
                case '5':
                    if(findTimeConflictInteger(classTime[1], 10000000) == false)
                        classTime[1] += 10000000;
                    break;
                case '6':
                    if(findTimeConflictInteger(classTime[1], 1000000) == false)
                        classTime[1] += 1000000;
                    break;
                case '7':
                    if(findTimeConflictInteger(classTime[1], 100000) == false)
                        classTime[1] += 100000;
                    break;
                case '8':
                    if(findTimeConflictInteger(classTime[1], 10000) == false)
                        classTime[1] += 10000;
                    break;
                case '9':
                    if(findTimeConflictInteger(classTime[1], 1000) == false)
                        classTime[1] += 1000;
                    break;
                case 'a':
                    if(findTimeConflictInteger(classTime[1], 100) == false)
                        classTime[1] += 100;
                    break;
                case 'b':
                    if(findTimeConflictInteger(classTime[1], 10) == false)
                        classTime[1] += 10;
                    break;
                case 'c':
                    if(findTimeConflictInteger(classTime[1], 1) == false)
                        classTime[1] += 1;
                    break;
                default: break;
            }
        }
        else if(timeString[i] == 't' || timeString[i] == 'T')
        {
            switch(timeString[i+1]) //check unavailableDays and 100000000 for conflict. if no conflict then add 100000000 to unavailableDays
            {
                case '1':
                    if(findTimeConflictInteger(classTime[2], 1000000000000) == false)
                        classTime[2] += 1000000000000;
                    break;
                case '2':
                    if(findTimeConflictInteger(classTime[2], 100000000000) == false)
                        classTime[2] += 100000000000;
                    break;
                case '3':
                    if(findTimeConflictInteger(classTime[2], 10000000000) == false)
                        classTime[2] += 10000000000;
                    break;
                case '4':
                    if(findTimeConflictInteger(classTime[2], 1000000000) == false)
                        classTime[2] += 1000000000;
                    break;
                case 'n':
                    if(findTimeConflictInteger(classTime[2], 100000000) == false)
                        classTime[2] += 100000000;
                    break;
                case '5':
                    if(findTimeConflictInteger(classTime[2], 10000000) == false)
                        classTime[2] += 10000000;
                    break;
                case '6':
                    if(findTimeConflictInteger(classTime[2], 1000000) == false)
                        classTime[2] += 1000000;
                    break;
                case '7':
                    if(findTimeConflictInteger(classTime[2], 100000) == false)
                        classTime[2] += 100000;
                    break;
                case '8':
                    if(findTimeConflictInteger(classTime[2], 10000) == false)
                        classTime[2] += 10000;
                    break;
                case '9':
                    if(findTimeConflictInteger(classTime[2], 1000) == false)
                        classTime[2] += 1000;
                    break;
                case 'a':
                    if(findTimeConflictInteger(classTime[2], 100) == false)
                        classTime[2] += 100;
                    break;
                case 'b':
                    if(findTimeConflictInteger(classTime[2], 10) == false)
                        classTime[2] += 10;
                    break;
                case 'c':
                    if(findTimeConflictInteger(classTime[2], 1) == false)
                        classTime[2] += 1;
                    break;
                default: break;
            }
        }
        else if(timeString[i] == 'w' || timeString[i] == 'W')
        {
            switch(timeString[i+1]) //check unavailableDays and 100000000 for conflict. if no conflict then add 100000000 to unavailableDays
            {
                case '1':
                    if(findTimeConflictInteger(classTime[3], 100000000000) == false)
                        classTime[3] += 1000000000000;
                    break;
                case '2':
                    if(findTimeConflictInteger(classTime[3], 100000000000) == false)
                        classTime[3] += 100000000000;
                    break;
                case '3':
                    if(findTimeConflictInteger(classTime[3], 10000000000) == false)
                        classTime[3] += 10000000000;
                    break;
                case '4':
                    if(findTimeConflictInteger(classTime[3], 1000000000) == false)
                        classTime[3] += 1000000000;
                    break;
                case 'n':
                    if(findTimeConflictInteger(classTime[3], 100000000) == false)
                        classTime[3] += 100000000;
                    break;
                case '5':
                    if(findTimeConflictInteger(classTime[3], 10000000) == false)
                        classTime[3] += 10000000;
                    break;
                case '6':
                    if(findTimeConflictInteger(classTime[3], 1000000) == false)
                        classTime[3] += 1000000;
                    break;
                case '7':
                    if(findTimeConflictInteger(classTime[3], 100000) == false)
                        classTime[3] += 100000;
                    break;
                case '8':
                    if(findTimeConflictInteger(classTime[3], 10000) == false)
                        classTime[3] += 10000;
                    break;
                case '9':
                    if(findTimeConflictInteger(classTime[3], 1000) == false)
                        classTime[3] += 1000;
                    break;
                case 'a':
                    if(findTimeConflictInteger(classTime[3], 100) == false)
                        classTime[3] += 100;
                    break;
                case 'b':
                    if(findTimeConflictInteger(classTime[3], 10) == false)
                        classTime[3] += 10;
                    break;
                case 'c':
                    if(findTimeConflictInteger(classTime[3], 1) == false)
                        classTime[3] += 1;
                    break;
                default: break;
            }
        }
        else if(timeString[i] == 'r' || timeString[i] == 'R')
        {
            switch(timeString[i+1]) //check unavailableDays and 100000000 for conflict. if no conflict then add 100000000 to unavailableDays
            {
                case '1':
                    if(findTimeConflictInteger(classTime[4], 1000000000000) == false)
                        classTime[4] += 1000000000000;
                    break;
                case '2':
                    if(findTimeConflictInteger(classTime[4], 100000000000) == false)
                        classTime[4] += 100000000000;
                    break;
                case '3':
                    if(findTimeConflictInteger(classTime[4], 10000000000) == false)
                        classTime[4] += 10000000000;
                    break;
                case '4':
                    if(findTimeConflictInteger(classTime[4], 1000000000) == false)
                        classTime[4] += 1000000000;
                    break;
                case 'n':
                    if(findTimeConflictInteger(classTime[4], 100000000) == false)
                        classTime[4] += 100000000;
                    break;
                case '5':
                    if(findTimeConflictInteger(classTime[4], 10000000) == false)
                        classTime[4] += 10000000;
                    break;
                case '6':
                    if(findTimeConflictInteger(classTime[4], 1000000) == false)
                        classTime[4] += 1000000;
                    break;
                case '7':
                    if(findTimeConflictInteger(classTime[4], 100000) == false)
                        classTime[4] += 100000;
                    break;
                case '8':
                    if(findTimeConflictInteger(classTime[4], 10000) == false)
                        classTime[4] += 10000;
                    break;
                case '9':
                    if(findTimeConflictInteger(classTime[4], 1000) == false)
                        classTime[4] += 1000;
                    break;
                case 'a':
                    if(findTimeConflictInteger(classTime[4], 100) == false)
                        classTime[4] += 100;
                    break;
                case 'b':
                    if(findTimeConflictInteger(classTime[4], 10) == false)
                        classTime[4] += 10;
                    break;
                case 'c':
                    if(findTimeConflictInteger(classTime[4], 1) == false)
                        classTime[4] += 1;
                    break;
                default: break;
            }
        }
        else if(timeString[i] == 'f' || timeString[i] == 'F')
        {
            switch(timeString[i+1]) //check unavailableDays and 100000000 for conflict. if no conflict then add 100000000 to unavailableDays
            {
                case '1':
                    if(findTimeConflictInteger(classTime[5], 1000000000000) == false)
                        classTime[5] += 1000000000000;
                    break;
                case '2':
                    if(findTimeConflictInteger(classTime[5], 100000000000) == false)
                        classTime[5] += 100000000000;
                    break;
                case '3':
                    if(findTimeConflictInteger(classTime[5], 10000000000) == false)
                        classTime[5] += 10000000000;
                    break;
                case '4':
                    if(findTimeConflictInteger(classTime[5], 1000000000) == false)
                        classTime[5] += 1000000000;
                    break;
                case 'n':
                    if(findTimeConflictInteger(classTime[5], 100000000) == false)
                        classTime[5] += 100000000;
                    break;
                case '5':
                    if(findTimeConflictInteger(classTime[5], 10000000) == false)
                        classTime[5] += 10000000;
                    break;
                case '6':
                    if(findTimeConflictInteger(classTime[5], 1000000) == false)
                        classTime[5] += 1000000;
                    break;
                case '7':
                    if(findTimeConflictInteger(classTime[5], 100000) == false)
                        classTime[5] += 100000;
                    break;
                case '8':
                    if(findTimeConflictInteger(classTime[5], 10000) == false)
                        classTime[5] += 10000;
                    break;
                case '9':
                    if(findTimeConflictInteger(classTime[5], 1000) == false)
                        classTime[5] += 1000;
                    break;
                case 'a':
                    if(findTimeConflictInteger(classTime[5], 100) == false)
                        classTime[5] += 100;
                    break;
                case 'b':
                    if(findTimeConflictInteger(classTime[5], 10) == false)
                        classTime[5] += 10;
                    break;
                case 'c':
                    if(findTimeConflictInteger(classTime[5], 1) == false)
                        classTime[5] += 1;
                    break;
                default: break;
            }
        }
        else if(timeString[i] == 's' || timeString[i] == 'S')
        {
            switch(timeString[i+1]) //check unavailableDays and 100000000 for conflict. if no conflict then add 100000000 to unavailableDays
            {
                case '1':
                    if(findTimeConflictInteger(classTime[6], 1000000000000) == false)
                        classTime[6] += 1000000000000;
                    break;
                case '2':
                    if(findTimeConflictInteger(classTime[6], 100000000000) == false)
                        classTime[6] += 100000000000;
                    break;
                case '3':
                    if(findTimeConflictInteger(classTime[6], 10000000000) == false)
                        classTime[6] += 10000000000;
                    break;
                case '4':
                    if(findTimeConflictInteger(classTime[6], 1000000000) == false)
                        classTime[6] += 1000000000;
                    break;
                case 'n':
                    if(findTimeConflictInteger(classTime[6], 100000000) == false)
                        classTime[6] += 100000000;
                    break;
                case '5':
                    if(findTimeConflictInteger(classTime[6], 10000000) == false)
                        classTime[6] += 10000000;
                    break;
                case '6':
                    if(findTimeConflictInteger(classTime[6], 1000000) == false)
                        classTime[6] += 1000000;
                    break;
                case '7':
                    if(findTimeConflictInteger(classTime[6], 100000) == false)
                        classTime[6] += 100000;
                    break;
                case '8':
                    if(findTimeConflictInteger(classTime[6], 10000) == false)
                        classTime[6] += 10000;
                    break;
                case '9':
                    if(findTimeConflictInteger(classTime[6], 1000) == false)
                        classTime[6] += 1000;
                    break;
                case 'a':
                    if(findTimeConflictInteger(classTime[6], 100) == false)
                        classTime[6] += 100;
                    break;
                case 'b':
                    if(findTimeConflictInteger(classTime[6], 10) == false)
                        classTime[6] += 10;
                    break;
                case 'c':
                    if(findTimeConflictInteger(classTime[6], 1) == false)
                        classTime[6] += 1;
                    break;
                default: break;
            }
        }
    }

    return classTime;
}
