#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "headers.h"

bool checkDeptRequirements(UserGraph *userGraph, SubGraph *currentGraph, Node *selectedCourse)
{
    //if(strcasecmp(userGraph->department, "CS") == 0)
    //{
        if(selectedCourse->required == true)
        {
            if(userGraph->graphRequirements->requiredSwitch == true)
            {
                userGraph->graphRequirements->numOfDeptCredits += selectedCourse->credits;
                userGraph->graphRequirements->totalDeptCredits -= selectedCourse->credits;
                userGraph->graphRequirements->requiredCredits -= selectedCourse->credits;
                userGraph->totalDegreeCredits -= selectedCourse->credits;

                if(userGraph->graphRequirements->requiredCredits < 1)
                    userGraph->graphRequirements->requiredSwitch = false;

                return true;
            }

        }
        else if(selectedCourse->required == false) //course is optional so check which requirements it fulfils
        {
            if(userGraph->graphRequirements->CS_CatA_Switch == true && strcasecmp(selectedCourse->courseCategory, "CS_catA") == 0) //still needs catA credits and course is catA
            {
                userGraph->graphRequirements->numOfDeptCredits += selectedCourse->credits;
                userGraph->graphRequirements->totalDeptCredits -= selectedCourse->credits;
                userGraph->totalDegreeCredits -= selectedCourse->credits;
                userGraph->graphRequirements->CS_CatA_Credits -= selectedCourse->credits;

                if(userGraph->graphRequirements->CS_CatA_Credits < 1 )
                    userGraph->graphRequirements->CS_CatA_Switch = false;

                return true;
            }
            if(userGraph->graphRequirements->CS_CatB_Switch == true && strcasecmp(selectedCourse->courseCategory, "CS_catB") == 0) //still needs catB credits and course is catB
            {
                userGraph->graphRequirements->numOfDeptCredits += selectedCourse->credits;
                userGraph->graphRequirements->totalDeptCredits -= selectedCourse->credits;
                userGraph->totalDegreeCredits -= selectedCourse->credits;
                userGraph->graphRequirements->CS_CatB_Credits -= selectedCourse->credits;

                if(userGraph->graphRequirements->CS_CatB_Credits < 1 )
                    userGraph->graphRequirements->CS_CatB_Switch = false;

                return true;
            }
            if(userGraph->graphRequirements->CS_CatC_Switch == true && strcasecmp(selectedCourse->courseCategory, "CS_catC") == 0) //still needs catC credits and course is catC
            {
                userGraph->graphRequirements->numOfDeptCredits += selectedCourse->credits;
                userGraph->graphRequirements->totalDeptCredits -= selectedCourse->credits;
                userGraph->totalDegreeCredits -= selectedCourse->credits;
                userGraph->graphRequirements->CS_CatC_Credits -= selectedCourse->credits;

                if(userGraph->graphRequirements->CS_CatC_Credits < 1 )
                    userGraph->graphRequirements->CS_CatC_Switch = false;

                return true;
            }
            if((userGraph->graphRequirements->profElectives_Switch == true && userGraph->graphRequirements->CS_CatA_Switch == false &&
               userGraph->graphRequirements->CS_CatB_Switch == false && userGraph->graphRequirements->CS_CatC_Switch == false)//catABC are off OR course is not catABC
               || (userGraph->graphRequirements->profElectives_Switch == true && userGraph->checkingOldCourses == true)) //in case abc is not off but student already took prof elective courses
            {
                userGraph->graphRequirements->numOfDeptCredits += selectedCourse->credits;
                userGraph->graphRequirements->totalDeptCredits -= selectedCourse->credits;
                userGraph->totalDegreeCredits -= selectedCourse->credits;
                userGraph->graphRequirements->profElectivesCredits -= selectedCourse->credits;

                if(userGraph->graphRequirements->profElectivesCredits < 1 )
                    userGraph->graphRequirements->profElectives_Switch = false;

                return true;
            }
        }
    //}
    //else if(strcasecmp(userGraph->department, "EE") == 0)
    //{

    //}

    return false;
}

bool checkGraphRequirements(UserGraph *userGraph, SubGraph *currentGraph, Node *selectedCourse)
{
    if(strcasecmp(currentGraph->graphType, "DEPT_REQ") == 0)
    {
        if(userGraph->graphRequirements->otherGE_Switch == false && userGraph->graphRequirements->numOfCourses < 1) //means all GE courses have been scheduled including otherGE
        {
            return checkDeptRequirements(userGraph,currentGraph,selectedCourse);
        }
        if(userGraph->graphRequirements->otherGE_Switch == false && userGraph->graphRequirements->numOfCourses == 1
            && (selectedCourse->credits + userGraph->graphRequirements->numOfDeptCredits) <= (userGraph->minCredits - 2)) //means selected CS other and only 1 GE course remaining (doesnt include otherGE)
        {
            return checkDeptRequirements(userGraph,currentGraph,selectedCourse);
        }
        if(userGraph->graphRequirements->otherGE_Switch == true && userGraph->graphRequirements->numOfCourses == 1
            && (selectedCourse->credits + userGraph->graphRequirements->numOfDeptCredits) <= (userGraph->minCredits - 2)) //means selected GE other and only 1 GE course remaining
        {
            return checkDeptRequirements(userGraph,currentGraph,selectedCourse);
        }
        if((selectedCourse->credits + userGraph->graphRequirements->numOfDeptCredits) <= userGraph->graphRequirements->deptCreditLimit)
        {
            return checkDeptRequirements(userGraph,currentGraph,selectedCourse);
        }
    }
    else if(strcasecmp(currentGraph->graphType, "LANG_REQ") == 0)
    {
        if(userGraph->graphRequirements->collegeChinese_Switch == true && strcasecmp(selectedCourse->courseCategory, "Chinese") == 0
            && userGraph->graphRequirements->chineseCourseNo < userGraph->graphRequirements->chineseSemesterCourseLimit) //still needs catA credits and course is catA
        {
            userGraph->graphRequirements->totalLangCredits -= selectedCourse->credits;
            userGraph->totalDegreeCredits -= selectedCourse->credits;

            userGraph->graphRequirements->chineseCourseNo++;
            userGraph->graphRequirements->collegeChineseCredits -= selectedCourse->credits;

            if(userGraph->graphRequirements->collegeChineseCredits < 1)
                userGraph->graphRequirements->collegeChinese_Switch = false;

            return true;
        }
        else if(userGraph->graphRequirements->collegeEnglish_Switch == true && strcasecmp(selectedCourse->courseCategory, "English") == 0
            && userGraph->graphRequirements->englishCourseNo < userGraph->graphRequirements->englishSemesterCourseLimit) //still needs catA credits and course is catA
        {
            userGraph->graphRequirements->totalLangCredits -= selectedCourse->credits;
            userGraph->totalDegreeCredits -= selectedCourse->credits;

            userGraph->graphRequirements->englishCourseNo++;
            userGraph->graphRequirements->collegeEnglishCredits -= selectedCourse->credits;

            if(userGraph->graphRequirements->collegeEnglishCredits < 1)
                userGraph->graphRequirements->collegeEnglish_Switch = false;

            return true;
        }
    }
    else if(strcasecmp(currentGraph->graphType, "PE_REQ") == 0)
    {
        if(userGraph->graphRequirements->PE_Switch == true && userGraph->graphRequirements->PE_CourseNo < userGraph->graphRequirements->PE_SemesterCourseLimit)
        {
            userGraph->graphRequirements->numOfCourses--;
            userGraph->totalNumOfCourses--;

            userGraph->graphRequirements->PE_CourseNo++;
            userGraph->graphRequirements->PE_CoursesRemaining--;

            if(userGraph->graphRequirements->PE_CoursesRemaining < 1)
                userGraph->graphRequirements->PE_Switch = false;

            return true;
        }
    }
    else if(strcasecmp(currentGraph->graphType, "SERVICE_REQ") == 0)
    {
        if(userGraph->graphRequirements->studentService_Switch == true && userGraph->graphRequirements->serviceCourseNo < userGraph->graphRequirements->serviceSemesterCourseLimit)
        {
            userGraph->graphRequirements->numOfCourses--;
            userGraph->totalNumOfCourses--;

            userGraph->graphRequirements->serviceCourseNo++;
            userGraph->graphRequirements->serviceCoursesRemaining--;

            if(userGraph->graphRequirements->serviceCoursesRemaining < 1)
            {
                userGraph->graphRequirements->studentService_Switch = false;
                userGraph->graphRequirements->serviceLearning_Switch = false;
            }

            return true;
        }
        if(userGraph->graphRequirements->serviceLearning_Switch == true && userGraph->graphRequirements->serviceCourseNo < userGraph->graphRequirements->serviceSemesterCourseLimit)
        {
            userGraph->graphRequirements->numOfCourses--;
            userGraph->totalNumOfCourses--;

            userGraph->graphRequirements->serviceCourseNo++;
            userGraph->graphRequirements->serviceCoursesRemaining--;

            if(userGraph->graphRequirements->serviceCoursesRemaining < 1)
            {
                userGraph->graphRequirements->studentService_Switch = false;
                userGraph->graphRequirements->serviceLearning_Switch = false;
            }

            return true;
        }
    }
    else if(strcasecmp(currentGraph->graphType, "GE_REQ") == 0)
    {
        if(userGraph->graphRequirements->GE_Core_Switch == true && userGraph->graphRequirements->GE_totalCourseNo < 3)
        {
            if(userGraph->graphRequirements->GE_Core1 == true && strcasecmp(selectedCourse->courseCategory, "GE_core1") == 0)
            {
                userGraph->graphRequirements->numOfCourses--;
                userGraph->totalNumOfCourses--;
                userGraph->graphRequirements->GE_CoreCourseNo++;
                userGraph->graphRequirements->GE_totalCourseNo++;
                userGraph->graphRequirements->GE_CoreCoursesRemaining--;

                userGraph->graphRequirements->GE_Core1 = false;
                if(userGraph->graphRequirements->GE_CoreCoursesRemaining < 1)
                userGraph->graphRequirements->GE_Core_Switch = false;

                return true;
            }
            if(userGraph->graphRequirements->GE_Core2 == true && strcasecmp(selectedCourse->courseCategory, "GE_core2") == 0)
            {
                userGraph->graphRequirements->numOfCourses--;
                userGraph->totalNumOfCourses--;
                userGraph->graphRequirements->GE_CoreCourseNo++;
                userGraph->graphRequirements->GE_totalCourseNo++;
                userGraph->graphRequirements->GE_CoreCoursesRemaining--;

                userGraph->graphRequirements->GE_Core2 = false;
                if(userGraph->graphRequirements->GE_CoreCoursesRemaining < 1)
                userGraph->graphRequirements->GE_Core_Switch = false;

                return true;
            }
            if(userGraph->graphRequirements->GE_Core3 == true && strcasecmp(selectedCourse->courseCategory, "GE_core3") == 0)
            {
                userGraph->graphRequirements->numOfCourses--;
                userGraph->totalNumOfCourses--;
                userGraph->graphRequirements->GE_CoreCourseNo++;
                userGraph->graphRequirements->GE_totalCourseNo++;
                userGraph->graphRequirements->GE_CoreCoursesRemaining--;

                userGraph->graphRequirements->GE_Core3 = false;
                if(userGraph->graphRequirements->GE_CoreCoursesRemaining < 1)
                userGraph->graphRequirements->GE_Core_Switch = false;

                return true;
            }
            if(userGraph->graphRequirements->GE_Core4 == true && strcasecmp(selectedCourse->courseCategory, "GE_core4") == 0)
            {
                userGraph->graphRequirements->numOfCourses--;
                userGraph->totalNumOfCourses--;
                userGraph->graphRequirements->GE_CoreCourseNo++;
                userGraph->graphRequirements->GE_totalCourseNo++;
                userGraph->graphRequirements->GE_CoreCoursesRemaining--;

                userGraph->graphRequirements->GE_Core4 = false;
                if(userGraph->graphRequirements->GE_CoreCoursesRemaining < 1)
                userGraph->graphRequirements->GE_Core_Switch = false;

                return true;
            }
            if(userGraph->graphRequirements->GE_Core5 == true && strcasecmp(selectedCourse->courseCategory, "GE_core5") == 0)
            {
                userGraph->graphRequirements->numOfCourses--;
                userGraph->totalNumOfCourses--;
                userGraph->graphRequirements->GE_CoreCourseNo++;
                userGraph->graphRequirements->GE_totalCourseNo++;
                userGraph->graphRequirements->GE_CoreCoursesRemaining--;

                userGraph->graphRequirements->GE_Core5 = false;
                if(userGraph->graphRequirements->GE_CoreCoursesRemaining < 1)
                userGraph->graphRequirements->GE_Core_Switch = false;

                return true;
            }
            if(userGraph->graphRequirements->GE_Core6 == true && strcasecmp(selectedCourse->courseCategory, "GE_core6") == 0)
            {
                userGraph->graphRequirements->numOfCourses--;
                userGraph->totalNumOfCourses--;
                userGraph->graphRequirements->GE_CoreCourseNo++;
                userGraph->graphRequirements->GE_totalCourseNo++;
                userGraph->graphRequirements->GE_CoreCoursesRemaining--;

                userGraph->graphRequirements->GE_Core6 = false;
                if(userGraph->graphRequirements->GE_CoreCoursesRemaining < 1)
                userGraph->graphRequirements->GE_Core_Switch = false;

                return true;
            }
            if(userGraph->graphRequirements->GE_Core7 == true && strcasecmp(selectedCourse->courseCategory, "GE_core7") == 0)
            {
                userGraph->graphRequirements->numOfCourses--;
                userGraph->totalNumOfCourses--;
                userGraph->graphRequirements->GE_CoreCourseNo++;
                userGraph->graphRequirements->GE_totalCourseNo++;
                userGraph->graphRequirements->GE_CoreCoursesRemaining--;

                userGraph->graphRequirements->GE_Core7 = false;
                if(userGraph->graphRequirements->GE_CoreCoursesRemaining < 1)
                userGraph->graphRequirements->GE_Core_Switch = false;

                return true;
            }
        }

        if(userGraph->graphRequirements->GE_Humanities_Switch == true && strcasecmp(selectedCourse->courseCategory, "GE_Humanities") == 0 && userGraph->graphRequirements->GE_totalCourseNo < 3)
        {
            userGraph->graphRequirements->numOfCourses--;
            userGraph->totalNumOfCourses--;
            userGraph->graphRequirements->GE_totalCourseNo++;
            userGraph->graphRequirements->GE_totalHumanitiesNo++;
            userGraph->graphRequirements->GE_ElectivesRemaining--;

            if(userGraph->graphRequirements->GE_totalHumanitiesNo == 2)
                userGraph->graphRequirements->GE_Humanities_Switch = false;

            if(userGraph->graphRequirements->GE_ElectivesRemaining < 1)
            {
                userGraph->graphRequirements->GE_Humanities_Switch = false;
                userGraph->graphRequirements->GE_SocialSciences_Switch = false;
            }

            return true;
        }
        if(userGraph->graphRequirements->GE_SocialSciences_Switch == true && strcasecmp(selectedCourse->courseCategory, "GE_SocialSciences") == 0 && userGraph->graphRequirements->GE_totalCourseNo < 3)
        {
            userGraph->graphRequirements->numOfCourses--;
            userGraph->totalNumOfCourses--;
            userGraph->graphRequirements->GE_totalCourseNo++;
            userGraph->graphRequirements->GE_totalSocialSciencesNo++;
            userGraph->graphRequirements->GE_ElectivesRemaining--;

            if(userGraph->graphRequirements->GE_totalSocialSciencesNo == 2)
                userGraph->graphRequirements->GE_SocialSciences_Switch = false;

            if(userGraph->graphRequirements->GE_ElectivesRemaining < 1)
            {
                userGraph->graphRequirements->GE_Humanities_Switch = false;
                userGraph->graphRequirements->GE_SocialSciences_Switch = false;
            }

            return true;
        }
        if(userGraph->graphRequirements->GE_NaturalSciences_Switch == true && strcasecmp(selectedCourse->courseCategory, "GE_NaturalSciences") == 0 && userGraph->graphRequirements->GE_totalCourseNo < 3)
        {
        }
        if(userGraph->graphRequirements->otherGE_Switch == true && userGraph->graphRequirements->GE_totalCourseNo < 3 && userGraph->graphRequirements->GE_Humanities_Switch == false
            && userGraph->graphRequirements->GE_SocialSciences_Switch == false && userGraph->graphRequirements->GE_NaturalSciences_Switch == false && userGraph->graphRequirements->GE_Core_Switch == false)
        {
            userGraph->graphRequirements->totalGE_Credits -= selectedCourse->credits;
            userGraph->graphRequirements->otherGE_Credits -= selectedCourse->credits;
            userGraph->totalDegreeCredits -= selectedCourse->credits;
            userGraph->graphRequirements->GE_totalCourseNo++; //this is courses scheduled this semester

            if(userGraph->graphRequirements->totalGE_Credits < 1)
            {
                userGraph->graphRequirements->otherGE_Switch = false;
            }

            return true;
        }
    }

    return false;
}


void findSchedule(UserGraph *graph, char *currentSemester)
{
    Edge *temp, *selectedCourse;
    bool conflict, unavailableConflict, validCourse;
    Time *chosenTimeSlot;
    SubGraph *currentGraph;
    int creditCount;

    currentGraph = graph->head;


    /**   basically this just means if there are any requirements to be fulfilled then keep trying to schedule the courses. if they have all been fulfilled then stop **/
    while(graph->graphRequirements->requiredSwitch == true || graph->graphRequirements->CS_CatA_Switch == true || graph->graphRequirements->CS_CatB_Switch == true ||
          graph->graphRequirements->CS_CatC_Switch == true || graph->graphRequirements->profElectives_Switch == true || graph->graphRequirements->PE_Switch == true ||
          graph->graphRequirements->studentService_Switch == true || graph->graphRequirements->serviceLearning_Switch == true || graph->graphRequirements->collegeChinese_Switch == true ||
          graph->graphRequirements->collegeEnglish_Switch == true || graph->graphRequirements->GE_Core_Switch == true || graph->graphRequirements->GE_Humanities_Switch == true ||
          graph->graphRequirements->GE_SocialSciences_Switch == true || graph->graphRequirements->GE_NaturalSciences_Switch == true || graph->graphRequirements->otherGE_Switch == true)
    {
        if(graph->semestersEmptyError == true )
        {
            printf("\n\n\t\t\t\t*********** ->>>> SYSTEM ERROR!! <<<<- ***********\n"
                    "System is unable to fulfil course requirements. "
                    "Please ensure map's course data and requirement data are correct!\n\n");
            printf("Degree Graph Credits: %d\n", graph->totalDegreeCredits);
            printf("Dept Graph Credits: %d\n", graph->graphRequirements->totalDeptCredits);
            printf("Degree Graph Courses: %d\n", graph->totalNumOfCourses);
            exit(1);
        }
        graph->semestersEmptyError = true;

        printf("\n%s Semester: \n", currentSemester);
        graph->numOfSemesters++;
        creditCount = 0;
        while(currentGraph)
        {
            if(currentGraph->head == NULL)
            {
                if(currentGraph->nextGraph == NULL) //means current graph is last graph in the semester
                    break;
                else
                    currentGraph = currentGraph->nextGraph;
            }

            criticalPath(currentGraph); //recalculate critical path

            int availableSources = 0;
            if(strcasecmp(currentSemester, "Fall") == 0)
            {
                currentGraph->numOfFallCourses = 0;
            }
            else if(strcasecmp(currentSemester, "Spring") == 0)
            {
                currentGraph->numOfSpringCourses = 0;
            }


            temp = currentGraph->sources;
            while(temp)
            {
                if(strcasecmp(temp->nodeToFrom->courseSemester, currentSemester) == 0 || strcasecmp(temp->nodeToFrom->courseSemester, "Both") == 0) //if source semester and current semester are the same or course is in both semesters set course as active
                {
                    temp->nodeToFrom->active = true;
                    availableSources++;
                }
                else //semester not the same so set as inactive;
                    temp->nodeToFrom->active = false;
                temp = temp->nextEdge;
            }

            temp = currentGraph->sources;
            while(temp) /** find all active nodes and set their times to active or inactive depending on the semester */
            {
                if(temp->nodeToFrom->active == true) //if node is active
                {
                    Time *tempTime = temp->nodeToFrom->classTimes;
                    if(strcasecmp(currentSemester, "Fall") == 0)
                    {
                        while(tempTime) /** find all class times to active or inactive depending on the semester */
                        {
                            if(tempTime->timeSlots[0] == 1)
                                tempTime->active = true;
                            else
                            {
                                tempTime->active = false;
                                temp->nodeToFrom->numOfActiveTimeSlots--;
                            }

                            tempTime = tempTime->nextTime;
                        }
                    }
                    if(strcasecmp(currentSemester, "Spring") == 0)
                    {
                        while(tempTime) /** find all class times to active or inactive depending on the semester */
                        {
                            if(tempTime->timeSlots[0] == 2)
                                tempTime->active = true;
                            else
                            {
                                tempTime->active = false;
                                temp->nodeToFrom->numOfActiveTimeSlots--;
                            }

                            tempTime = tempTime->nextTime;
                        }
                    }
                }
                temp = temp->nextEdge;
            }
            findCourseConflictCount(currentGraph->sources);

            /**    this is algorithm level 1   **/
            while((creditCount <= graph->minCredits && availableSources != 0) || (strcasecmp(currentGraph->graphType, "PE_REQ") == 0 && availableSources != 0)
                  || (strcasecmp(currentGraph->graphType, "SERVICE_REQ") == 0 && availableSources != 0))
            {
                temp = currentGraph->sources;
                selectedCourse = temp;

                if(strcasecmp(currentGraph->graphType, "PE_REQ") != 0 && strcasecmp(currentGraph->graphType, "GE_REQ") != 0)
                {
                    while(temp) //go through source nodes
                    {
                        if(temp->nodeToFrom->active == true)//course is active
                        {
                            if(selectedCourse == currentGraph->sources && selectedCourse->nodeToFrom->active == false) // if selectedCourse is the head it might not be active so change selectedCourse to an active node
                                selectedCourse = temp;

                            if(temp->nodeToFrom->required > selectedCourse->nodeToFrom->required) //find the course that is required and print those first. logic is same as choosing course with lowest slack etc
                            {
                                selectedCourse = temp;
                            }
                            else if(temp->nodeToFrom->required == selectedCourse->nodeToFrom->required)
                            {
                                if(temp->nodeToFrom->slack < selectedCourse->nodeToFrom->slack) //the slack is lower so fanout doesn't matter
                                {/** if you only use half of the if statement the solution is no longer optimal**/
                                    selectedCourse = temp;
                                }
                                else if(temp->nodeToFrom->slack == selectedCourse->nodeToFrom->slack) //the slack is equal so check fanout
                                {
                                    if(temp->nodeToFrom->fanOut > selectedCourse->nodeToFrom->fanOut) //the fanout is higher so conflict count doesn't matter
                                    {/** if you only use half of the if statement the solution is no longer optimal**/
                                        selectedCourse = temp;
                                    }
                                    else if(temp->nodeToFrom->fanOut == selectedCourse->nodeToFrom->fanOut)//the fanout is equal so check user index.
                                    {
                                        if(temp->nodeToFrom->userPreferenceIndex < selectedCourse->nodeToFrom->userPreferenceIndex)
                                        {/** if you only use half of the if statement the solution is no longer optimal**/
                                            selectedCourse = temp;
                                        }
                                        else if(temp->nodeToFrom->userPreferenceIndex == selectedCourse->nodeToFrom->userPreferenceIndex) //user index is the same so check conflict count
                                        {
                                            if(temp->nodeToFrom->conflictCount <= selectedCourse->nodeToFrom->conflictCount) //if conflict count <= then change
                                                selectedCourse = temp;

                                        }
                                    }
                                }
                            }
                        }
                        temp = temp->nextEdge;
                    }
                }
                else
                {
                    while(temp) //go through source nodes
                    {
                        if(temp->nodeToFrom->active == true)//course is active
                        {
                            if(selectedCourse == currentGraph->sources && selectedCourse->nodeToFrom->active == false) // if selectedCourse is the head it might not be active so change selectedCourse to an active node
                                selectedCourse = temp;

                            if(temp->nodeToFrom->required > selectedCourse->nodeToFrom->required) //find the course that is required and print those first. logic is same as choosing course with lowest slack etc
                            {
                                selectedCourse = temp;
                            }
                            else if(temp->nodeToFrom->required == selectedCourse->nodeToFrom->required)
                            {

                                if(temp->nodeToFrom->userPreferenceIndex < selectedCourse->nodeToFrom->userPreferenceIndex)
                                {/** if you only use half of the if statement the solution is no longer optimal**/
                                    selectedCourse = temp;
                                }
                                else if(temp->nodeToFrom->userPreferenceIndex == selectedCourse->nodeToFrom->userPreferenceIndex) //user index is the same so check conflict count
                                {
                                    if(graph->graphRequirements->GE_OTHER == true && strcasecmp(currentGraph->graphType, "GE_REQ") == 0
                                        && graph->graphRequirements->numOfCourses < 1) //if you're scheduling other GE schedule highest credit courses first cause u only want to take 3 courses
                                    {
                                    if(temp->nodeToFrom->credits > selectedCourse->nodeToFrom->credits) //if conflict count <= then change
                                            selectedCourse = temp;
                                        else if(temp->nodeToFrom->credits == selectedCourse->nodeToFrom->credits)
                                        {
                                            if(temp->nodeToFrom->conflictCount <= selectedCourse->nodeToFrom->conflictCount) //if conflict count <= then change
                                                selectedCourse = temp;
                                        }
                                    }
                                    else
                                    {
                                        if(temp->nodeToFrom->conflictCount <= selectedCourse->nodeToFrom->conflictCount) //if conflict count <= then change
                                            selectedCourse = temp;
                                    }
                                }
                            }
                        }
                        temp = temp->nextEdge;
                    }
                }


                /**  algorithm level 1 end  */
                /***** you have selected a course by this point *****/


                while(selectedCourse->nodeToFrom->numOfActiveTimeSlots != 0 && selectedCourse->nodeToFrom->active == true)
                {
                    chosenTimeSlot = selectTimeSlot(selectedCourse->nodeToFrom); //select the time slot for the class
                    conflict = findTimeConflict(graph->semesterTimetable, chosenTimeSlot->timeSlots);
                    unavailableConflict = findTimeConflict(graph->unavailableDays, chosenTimeSlot->timeSlots);

                    if(selectedCourse->nodeToFrom->required == true)
                    {
                        if(conflict)
                        {
                            chosenTimeSlot->active = false; //make timeslot inactive cause there is conflict
                            selectedCourse->nodeToFrom->numOfActiveTimeSlots--; //decrease num of active timeslots
                        }
                        else break; //found a time with no conflict so stop searching for a time slot
                    }
                    else if(selectedCourse->nodeToFrom->required == false)
                    {
                        if(conflict || unavailableConflict)
                        {
                            chosenTimeSlot->active = false; //make timeslot inactive cause there is conflict
                            selectedCourse->nodeToFrom->numOfActiveTimeSlots--; //decrease num of active timeslots
                        }
                        else break; //found a time with no conflict so stop searching for a time slot
                    }
                }

                if(selectedCourse->nodeToFrom->numOfActiveTimeSlots == 0) //all timeslots have conflict so set whole course as inactive
                {
                    selectedCourse->nodeToFrom->active = false;
                    availableSources--;
                }


                /**   make sure u have enough credits to schedule in this graph. not only credits for the semester  **/
                        /**  execute algorithm level 2 here */


                if(selectedCourse->nodeToFrom->active == true ) // if the credits are less than the max credits
                {
                    if((creditCount + selectedCourse->nodeToFrom->credits) <= graph->minCredits+1 || strcasecmp(currentGraph->graphType, "PE_REQ") == 0 || strcasecmp(currentGraph->graphType, "SERVICE_REQ") == 0)
                    {
                        validCourse = checkGraphRequirements(graph, currentGraph, selectedCourse->nodeToFrom);

                        if(validCourse == false)
                        {
                            selectedCourse->nodeToFrom->active = false;
                            availableSources--;
                        }
                    }
                    else if((creditCount + selectedCourse->nodeToFrom->credits) > graph->minCredits+1) /** graph->minCredits+1 so that it schedules no more than 1 credit over what the student asked for. without this is it can schedule +2, not much but looks like a lot to the student**/
                    {
                        selectedCourse->nodeToFrom->active = false;
                        availableSources--;
                    }

                }

                if(conflict == false && selectedCourse->nodeToFrom->active == true)//&& (creditCount ) <= graph->minCredits) // if the credits are less than the max credits
                {
                    creditCount += selectedCourse->nodeToFrom->credits;
                    if(strcasecmp(currentSemester, "Fall") == 0)
                        currentGraph->numOfFallCourses++;
                    else if(strcasecmp(currentSemester, "Spring") == 0)
                        currentGraph->numOfSpringCourses++;

                    currentGraph->bothSemestersEmpty = false;
                    graph->semestersEmptyError = false;
                    graph->totalCreditsScheduled += selectedCourse->nodeToFrom->credits;

                    for (int x = 0; x < 7; x++) //put selected class time in the timetable
                        graph->semesterTimetable[x] += chosenTimeSlot->timeSlots[x];

                    printf("%s ", selectedCourse->nodeToFrom->courseName); //print course and remove node
                    printf(": (%s) , %d credits , ", chosenTimeSlot->timeString, selectedCourse->nodeToFrom->credits);//, chosenTimeSlot->courseRoom);

                    if(selectedCourse->nodeToFrom->required)
                        printf("Required");
                    else
                        printf("Optional");

                    printf("\n");

                    insertEdgeAtFront(&currentGraph->scheduledThisSemester, &selectedCourse->nodeToFrom);//add to list of scheduled courses

                    deleteNode(currentGraph, selectedCourse->nodeToFrom);
                    availableSources--; //minus from available sources
                }

            } /**end of function*/

            /**semester is done for THIS GRAPH ONLY we need to clear data, switch graphs and continue processing**/


            //clear scheduled courses
            freeEdges(currentGraph->scheduledThisSemester); //get rid of old scheduled courses
            currentGraph->scheduledThisSemester = NULL;


            if(currentGraph->numOfFallCourses == 0 && currentGraph->numOfSpringCourses == 0 && graph->numSemestersScheduled > 2)
                currentGraph->bothSemestersEmpty = true;

            currentGraph = currentGraph->nextGraph;
        }

        /** need to clear college chinese , engish and other requirement data**/

        graph->graphRequirements->numOfDeptCredits = 0;
        graph->graphRequirements->chineseCourseNo = 0;
        graph->graphRequirements->englishCourseNo = 0;
        graph->graphRequirements->GE_CoreCourseNo = 0;
        graph->graphRequirements->GE_totalCourseNo = 0;
        graph->graphRequirements->PE_CourseNo = 0;
        graph->graphRequirements->serviceCourseNo = 0;

        for (int i = 0; i < 7; i++)  //reset timetable to 0
            graph->semesterTimetable[i] = 0;
        for (int i = 0; i < 7; i++)  //reset unavailable to 0
            graph->unavailableDays[i] = 0;

        /*******************************************************/

        graph->numSemestersScheduled++;

        // switch the semester here
        if(strcasecmp(currentSemester, "Spring") == 0)
        {
            strcpy(currentSemester, "Fall");
        }
        else if(strcasecmp(currentSemester, "Fall") == 0)
        {
          strcpy(currentSemester, "Spring");
        }

        currentGraph = graph->head;// You are starting from the first G' in  the big graph
        while(currentGraph->head == NULL) //go through to the next graph until you find one with nodes in it
        {
            currentGraph = currentGraph->nextGraph;
            if(currentGraph->nextGraph == NULL) //if you found last graph in big graph then just exit the loop cause u already went thought all the graphs and they all have no nodes in them
                break;
        }

        printf("\n");
    }


    /** MAKE SURE ALL CREDIT REQUIREMENTS HAVE BEEN FULFILLED BEFORE EXITING.
    IF SOME REQUIREMENTS ARE NOT FULFILLED PRINT AN ERROR AND ASK USER TO CHECK THE REQUIREMENTS.

    ex: if you need to have 3 credits in otherElective but u ran out of courses before the requirements are done then print error

    ALSO: CONSIDER SCANNING ALL THE USER DATA AND USING IT TO SET THE REQUIREMENTS. THEN COUNT ALL REQUIREMENT CREDITS AND USE THAT TO SET "totalCredits" OF THE GRAPH
    **/



    if(graph->graphRequirements->requiredSwitch == true || graph->graphRequirements->CS_CatA_Switch == true || graph->graphRequirements->CS_CatB_Switch == true
       || graph->graphRequirements->CS_CatC_Switch == true || graph->graphRequirements->profElectives_Switch == true)
    {
            printf("\n\n\t\t\t\t*********** ->>>> MAP ERROR!! <<<<- ***********\n"
                "DEPT_REQ Map requirements NOT fulfilled.\n"
                "Please ensure map's REQUIREMENT DATA, TOTAL CREDITS and NUMBER OF COURSES are correct!\n\n");
    }

    if(graph->graphRequirements->collegeChinese_Switch == true || graph->graphRequirements->collegeEnglish_Switch == true)
    {
        printf("\n\n\t\t\t\t*********** ->>>> MAP ERROR!! <<<<- ***********\n"
                "LANG_REQ Map requirements NOT fulfilled.\n"
                "Please ensure map's REQUIREMENT DATA, TOTAL CREDITS and NUMBER OF COURSES are correct!\n\n");
    }

    if(graph->graphRequirements->GE_Core_Switch == true || graph->graphRequirements->GE_Humanities_Switch == true || graph->graphRequirements->GE_NaturalSciences_Switch == true
        || graph->graphRequirements->GE_SocialSciences_Switch == true || graph->graphRequirements->otherGE_Switch == true)
    {
        printf("\n\n\t\t\t\t*********** ->>>> MAP ERROR!! <<<<- ***********\n"
                "GE_REQ Map requirements NOT fulfilled.\n"
                "Please ensure map's REQUIREMENT DATA, TOTAL CREDITS and NUMBER OF COURSES are correct!\n\n");
    }

    if(graph->graphRequirements->PE_Switch == true)
    {
        printf("\n\n\t\t\t\t*********** ->>>> MAP ERROR!! <<<<- ***********\n"
                "PE_REQ Map requirements NOT fulfilled.\n"
                "Please ensure map's REQUIREMENT DATA, TOTAL CREDITS and NUMBER OF COURSES are correct!\n\n");
    }

    if(graph->graphRequirements->studentService_Switch == true || graph->graphRequirements->serviceLearning_Switch == true)
    {
        printf("\n\n\t\t\t\t*********** ->>>> MAP ERROR!! <<<<- ***********\n"
                "SERVICE_REQ Map requirements NOT fulfilled.\n"
                "Please ensure map's REQUIREMENT DATA, TOTAL CREDITS and NUMBER OF COURSES are correct!\n\n");
    }

    printf("\t\t\t\t\t\t   >>Schedule Complete<<\n\n");
    printf("\t\t\t\t%d Semesters to Complete Degree\n", graph->numOfSemesters);
    printf("\t\t\t\t%d Credits\n", graph->totalCreditsScheduled);
    printf("\t\t\t\t%d Courses\n", graph->totalNumOfCourses);
}
