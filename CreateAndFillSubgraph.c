#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include "headers.h"

void removeSpace(char *arr, int n)
{
    int space = 0;

    int k = 0;

    for (int i = 0; i < n; i++)
    {
        while (k == 0 && i < n && arr[i] == ' ') {  // handle leading spaces in the string
            i++;
        }
        if (arr[i] == ' ')
        {
            if (!space)
            {
                arr[k++] = arr[i];
                space = 1;
            }
        }
        else {
            arr[k++] = arr[i];
            space = 0;
        }
    }

    while ( k > 0 && isspace(arr[k - 1]))  // handle trailing spaces in the string
    --k;
    arr[k] = '\0';
}

SubGraph* createSubGraph(SubGraph **subGraphHead_ref) //use this function to create as sub graphs as you want
{
    SubGraph *new_SubGraph = (SubGraph*) malloc(sizeof(SubGraph));
    SubGraph *last = (*subGraphHead_ref);

    new_SubGraph->head = NULL;
    new_SubGraph->nextGraph = NULL;
    new_SubGraph->prevGraph = NULL;
    new_SubGraph->sources = NULL;
    new_SubGraph->scheduledThisSemester = NULL;
    new_SubGraph->numVertices = 0;
    new_SubGraph->numSources = 0;
    new_SubGraph->numOfFallCourses = 0;
    new_SubGraph->numOfSpringCourses = 0;
    new_SubGraph->bothSemestersEmpty = false;

    if ((*subGraphHead_ref) == NULL)//If the Linked List is empty, then make the new node as head
    {
       (*subGraphHead_ref) = new_SubGraph;
       return new_SubGraph;
    }

    while (last->nextGraph != NULL) // Else traverse till the last node
        last = last->nextGraph;

    last->nextGraph = new_SubGraph; // Change the next of last node
    new_SubGraph->prevGraph = last; //new node previous node is last node

    return new_SubGraph;
}

bool findNumber(int num, int *arr, int arrSize)
{
    bool found = false;

    for(int i=0; i<arrSize; i++)
    {
        if(arr[i] == num)
        {
            found = true;
            break;
        }
    }
    return found;
}

/**get user preference here* send graph type, coursecategory, and user pref array --  returns userpref number*/
int getUserPrefIndex(char *graphType, char *courseCategory, char *courseType, int *userPref)
{
    if(strcasecmp(graphType, "DEPT_REQ") == 0)
    {
        if(strcasecmp(courseType, "TheoryAlgorithm") == 0 )
            return userPref[0];
        if(strcasecmp(courseType, "Network") == 0 )
            return userPref[1];
        if(strcasecmp(courseType, "SystemSoftware") == 0 )
            return userPref[2];
        if(strcasecmp(courseType, "ICDesign") == 0 )
            return userPref[3];
        if(strcasecmp(courseType, "Multimedia") == 0 )
            return userPref[4];
        if(strcasecmp(courseType, "AppProgram") == 0 )
            return userPref[5];
        if(strcasecmp(courseType, "Other") == 0 )
            return userPref[6];
    }
    //if(strcasecmp(graphType, "EE") == 0)
    //{
    //}

    if(strcasecmp(graphType, "GE_REQ") == 0)
    {
        if(strcasecmp(courseCategory, "GE_humanities") == 0)
        {
            if(strcasecmp(courseType, "GeneralArt") == 0 )
                return userPref[0];
            if(strcasecmp(courseType, "StudioArt") == 0 )
                return userPref[1];
            if(strcasecmp(courseType, "PhilosReligious") == 0 )
                return userPref[2];
            if(strcasecmp(courseType, "HumaneHistorical") == 0 )
                return userPref[3];
        }
        else if(strcasecmp(courseCategory, "GE_socialSciences") == 0)
        {
            if(strcasecmp(courseType, "LawPolitics") == 0 )
                return userPref[0];
            if(strcasecmp(courseType, "SPAEGS") == 0 )
                return userPref[1];
            if(strcasecmp(courseType, "MIE") == 0 )
                return userPref[2];
        }
        else if(strcasecmp(courseCategory, "GE_naturalSciences") == 0)
        {
            if(strcasecmp(courseType, "BasicScience") == 0 )
                return userPref[0];
            if(strcasecmp(courseType, "AppliedScience") == 0 )
                return userPref[1];
            if(strcasecmp(courseType, "SciTechSociety") == 0 )
                return userPref[2];
        }
        else //this is for GE core courses
        {
            if(strcasecmp(courseCategory, "GE_core1") == 0 && findNumber(1, userPref, 5) == true) //if course is core1 and user selected core1 as 1 of 5 fields
                return 1;
            else if(strcasecmp(courseCategory, "GE_core2") == 0 && findNumber(2, userPref, 5) == true) //if course is core1 and user selected core1 as 1 of 5 fields
                return 1;
            else if(strcasecmp(courseCategory, "GE_core3") == 0 && findNumber(3, userPref, 5) == true) //if course is core1 and user selected core1 as 1 of 5 fields
                return 1;
            else if(strcasecmp(courseCategory, "GE_core4") == 0 && findNumber(4, userPref, 5) == true) //if course is core1 and user selected core1 as 1 of 5 fields
                return 1;
            else if(strcasecmp(courseCategory, "GE_core5") == 0 && findNumber(5, userPref, 5) == true) //if course is core1 and user selected core1 as 1 of 5 fields
                return 1;
            else if(strcasecmp(courseCategory, "GE_core6") == 0 && findNumber(6, userPref, 5) == true) //if course is core1 and user selected core1 as 1 of 5 fields
                return 1;
            else if(strcasecmp(courseCategory, "GE_core7") == 0 && findNumber(7, userPref, 5) == true) //if course is core1 and user selected core1 as 1 of 5 fields
                return 1;
            else return 2;
        }
    }
    if(strcasecmp(graphType, "PE_REQ") == 0)
    {
        if(strcasecmp(courseType, "Ball") == 0 )
            return userPref[0];
        if(strcasecmp(courseType, "Dance") == 0 )
            return userPref[1];
        if(strcasecmp(courseType, "Water") == 0 )
            return userPref[2];
        if(strcasecmp(courseType, "Martial") == 0 )
            return userPref[3];
        if(strcasecmp(courseType, "StretchRelax") == 0 )
            return userPref[4];
        if(strcasecmp(courseType, "WalkRun") == 0 )
            return userPref[5];
        if(strcasecmp(courseType, "Strength") == 0 )
            return userPref[6];
    }
    if(strcasecmp(graphType, "SERVICE_REQ") == 0)
    {
        return 1;
    }
    return 9999;
}

void getReqData(UserGraph* userGraph)
{
    FILE *fp;

    /** scan data from requirements file and update graph to include the necessary requirements **/
    char requirement[60], reqFile[10];
    int reqData = 0;


    //printf("\n dept: %s\n", department);
    //if(strcasecmp(userGraph->department, "CS") == 0)
        strcpy(reqFile, "CS_requirements.txt");
    //else if(strcasecmp(userGraph->department, "EE") == 0)
        //strcpy(reqFile, "EE_requirements.txt");



   /* opening file for reading */
    fp = fopen(reqFile , "r");
    if(fp == NULL) {
        perror("Error opening file");

    }


    /*******      get requirement data   *******/
    while(fscanf(fp, "%s %d\n", requirement, &reqData) != EOF)
    {
        //if(strcasecmp(userGraph->department, "CS") == 0)
        //{
            if(strcasecmp(requirement, "DEPARTMENT_REQUIREMENTS") == 0)
            {
                fscanf(fp, "%s %d\n", requirement, &reqData);
                userGraph->graphRequirements->totalDeptCredits = reqData;

                fscanf(fp, "%s %d\n", requirement, &reqData);

                userGraph->graphRequirements->numOfDeptCredits = 0;

                userGraph->graphRequirements->requiredSwitch = true;

                fscanf(fp, "%s %d\n", requirement, &reqData);
                userGraph->graphRequirements->requiredCredits = reqData;

                fscanf(fp, "%s %d\n", requirement, &reqData);
                userGraph->graphRequirements->CS_CatA_Switch = reqData;

                fscanf(fp, "%s %d\n", requirement, &reqData);
                userGraph->graphRequirements->CS_CatA_Credits = reqData;

                fscanf(fp, "%s %d\n", requirement, &reqData);
                userGraph->graphRequirements->CS_CatB_Switch = reqData;

                fscanf(fp, "%s %d\n", requirement, &reqData);
                userGraph->graphRequirements->CS_CatB_Credits = reqData;

                fscanf(fp, "%s %d\n", requirement, &reqData);
                userGraph->graphRequirements->CS_CatC_Switch = reqData;

                fscanf(fp, "%s %d\n", requirement, &reqData);
                userGraph->graphRequirements->CS_CatC_Credits = reqData;

                fscanf(fp, "%s %d\n", requirement, &reqData);
                userGraph->graphRequirements->profElectives_Switch = reqData;

                fscanf(fp, "%s %d\n", requirement, &reqData);
                userGraph->graphRequirements->profElectivesCredits = reqData;

                fscanf(fp, "%s %d\n", requirement, &reqData);
                userGraph->graphRequirements->otherElectivesCredits = reqData;
            }
       /* }
        else if(strcasecmp(userGraph->department, "EE") == 0)
        {
            if(strcasecmp(requirement, "DEPARTMENT_REQUIREMENTS") == 0)
            {
            }
        }
*/


        fscanf(fp, "%s %d\n", requirement, &reqData);
        if(strcasecmp(requirement, "SERVICE_REQUIREMENTS") == 0)
        {
            fscanf(fp, "%s %d\n", requirement, &reqData);

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->numOfCourses += reqData;

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->studentService_Switch = reqData;

            userGraph->graphRequirements->serviceLearning_Switch = false; //student need to input this data later

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->serviceSemesterCourseLimit = reqData;

            userGraph->graphRequirements->serviceCourseNo = 0;

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->serviceCoursesRemaining = reqData;
        }

        fscanf(fp, "%s %d\n", requirement, &reqData);
        if(strcasecmp(requirement, "LANGUAGE_REQUIREMENTS") == 0)
        {
            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->totalLangCredits = reqData;

            fscanf(fp, "%s %d\n", requirement, &reqData);

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->collegeChinese_Switch = reqData;

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->chineseSemesterCourseLimit = reqData;

            userGraph->graphRequirements->chineseCourseNo = 0;

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->collegeChineseCredits = reqData;

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->collegeEnglish_Switch = reqData;

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->englishSemesterCourseLimit = reqData;

            userGraph->graphRequirements->englishCourseNo = 0;

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->collegeEnglishCredits = reqData;
        }

        fscanf(fp, "%s %d\n", requirement, &reqData);
        if(strcasecmp(requirement, "PE_REQUIREMENTS") == 0)
        {
            fscanf(fp, "%s %d\n", requirement, &reqData);

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->numOfCourses += reqData;

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->PE_Switch = reqData;

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->PE_SemesterCourseLimit = reqData;

            userGraph->graphRequirements->PE_CourseNo = 0;

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->PE_CoursesRemaining = reqData;
        }

        fscanf(fp, "%s %d\n", requirement, &reqData);
        if(strcasecmp(requirement, "GE_REQUIREMENTS") == 0)
        {
            userGraph->graphRequirements->GE_totalCourseNo = 0;
            userGraph->graphRequirements->GE_Core1 = true;
            userGraph->graphRequirements->GE_Core2 = true;
            userGraph->graphRequirements->GE_Core3 = true;
            userGraph->graphRequirements->GE_Core4 = true;
            userGraph->graphRequirements->GE_Core5 = true;
            userGraph->graphRequirements->GE_Core6 = true;
            userGraph->graphRequirements->GE_Core7 = true;

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->totalGE_Credits = reqData;

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->numOfCourses += reqData;

            userGraph->graphRequirements->totalGE_Credits = 0; //num of credits not important for GE b/c it changes a lot so set to 0

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->GE_Core_Switch = reqData;

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->GE_CoreSemesterCourseLimit = reqData;

            userGraph->graphRequirements->GE_CoreCourseNo = 0;

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->GE_CoreCoursesRemaining = reqData;

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->GE_ElectivesRemaining = reqData;

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->GE_Humanities_Switch = reqData;

            userGraph->graphRequirements->GE_totalHumanitiesNo = 0;

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->GE_SocialSciences_Switch = reqData;

            userGraph->graphRequirements->GE_totalSocialSciencesNo = 0;

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->GE_NaturalSciences_Switch = reqData;

            userGraph->graphRequirements->GE_totalNaturalSciencesNo = 0;

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->otherGE_Switch = reqData;

            fscanf(fp, "%s %d\n", requirement, &reqData);
            userGraph->graphRequirements->otherGE_Credits = reqData;

        }

        fclose(fp);
    }

}


void fillSubGraph(UserGraph* userGraph, SubGraph* graph, char* coursesFile, char* prereqFile)
{
    //get data from file
    FILE *fp;
    char srcNode[200], destNode[200], timeString[20], courseRoom[40], graphType[30];
    int credits, num;
    long long int classTimes[7], *tempTime;
    char courseId[20], courseName[200], semester[7], getRequired[10], choice[5];//, temp_str[200]
    bool required;
    int userPreferenceIndex; //starts at 1, the lower the better
    char courseCategory[30], courseType[30]; // GE_humanities, GE_core1, CS_catA etc
    int GE_coreChosen[5] = {0, 0, 0, 0, 0}, GE_humanitiesChosen[4] = {0, 0, 0, 0}, GE_ssChosen[3] = {0, 0, 0}, GE_nsChosen[3] = {0, 0, 0};
    int DEPT_electiveChosen[7] = {0, 0, 0, 0, 0, 0, 0}, PE_chosen[7] = {0, 0, 0, 0, 0, 0, 0}, service_chosen[5] = {0, 0, 0, 0, 0};

    graph->numOfFallCourses = 0;
    graph->numOfSpringCourses = 0;
    graph->bothSemestersEmpty = false;

    strcpy(graphType, graph->graphType);

    if(strcasecmp(graph->graphType, "DEPT_REQ") == 0)
    {
        //if(strcasecmp(userGraph->department, "CS") == 0)
        //{
            /*******      get user preference data   *******/
            printf("Please select your Professional Elective course preference below.\n");
            printf("\nPlease input your >>PROFESSIONAL ELECTIVES<< course preference: "
                   "\n\n\t[ ] Theory and Algorithm"
                   "\n\t[ ] Computer Networks"
                   "\n\t[ ] System Software"
                   "\n\t[ ] IC Design"
                   "\n\t[ ] Multimedia and Image Processing"
                   "\n\t[ ] Programming and Applications"
                   "\n\t[ ] Other\n");

            printf("\nPlease enter your preference for these courses by choosing a number between 1 - 7 for each course.\n");
            printf("**IMPORTANT** Preference 1 = MOST preferred    and    Preference 7 = LEAST preferred. \n\n");
            printf("\tTheory and Algorithm: ");
            scanf("%d", &num);
            while(num < 1 || num > 7)
            {
                printf("\n%d is not a valid option. Please select 1 - 7: ", num);
                scanf("%d", &num);
            }
            while(findNumber(num, DEPT_electiveChosen, 7) == true)
            {
                printf("\nYou entered option %d more than once. Please select another option: ", num);
                scanf("%d", &num);
            }
            DEPT_electiveChosen[0] = num;


            printf("\tComputer Networks: ");
            scanf("%d", &num);
            while(num < 1 || num > 7)
            {
                printf("\n%d is not a valid option. Please select 1 - 7: ", num);
                scanf("%d", &num);
            }
            while(findNumber(num, DEPT_electiveChosen, 7) == true)
            {
                printf("\nYou entered option %d more than once. Please select another option: ", num);
                scanf("%d", &num);
            }
            DEPT_electiveChosen[1] = num;


            printf("\tSystem Software: ");
            scanf("%d", &num);
            while(num < 1 || num > 7)
            {
                printf("\n%d is not a valid option. Please select 1 - 7: ", num);
                scanf("%d", &num);
            }
            while(findNumber(num, DEPT_electiveChosen, 7) == true)
            {
                printf("\nYou entered option %d more than once. Please select another option: ", num);
                scanf("%d", &num);
            }
            DEPT_electiveChosen[2] = num;


            printf("\tIC Design: ");
            scanf("%d", &num);
            while(num < 1 || num > 7)
            {
                printf("\n%d is not a valid option. Please select 1 - 7: ", num);
                scanf("%d", &num);
            }
            while(findNumber(num, DEPT_electiveChosen, 7) == true)
            {
                printf("\nYou entered option %d more than once. Please select another option: ", num);
                scanf("%d", &num);
            }
            DEPT_electiveChosen[3] = num;


            printf("\tMultimedia and Image Processing: ");
            scanf("%d", &num);
            while(num < 1 || num > 7)
            {
                printf("\n%d is not a valid option. Please select 1 - 7: ", num);
                scanf("%d", &num);
            }
            while(findNumber(num, DEPT_electiveChosen, 7) == true)
            {
                printf("\nYou entered option %d more than once. Please select another option: ", num);
                scanf("%d", &num);
            }
            DEPT_electiveChosen[4] = num;


            printf("\tProgramming and Applications: ");
            scanf("%d", &num);
            while(num < 1 || num > 7)
            {
                printf("\n%d is not a valid option. Please select 1 - 7: ", num);
                scanf("%d", &num);
            }
            while(findNumber(num, DEPT_electiveChosen, 7) == true)
            {
                printf("\nYou entered option %d more than once. Please select another option: ", num);
                scanf("%d", &num);
            }
            DEPT_electiveChosen[5] = num;


            printf("\tOther: ");
            scanf("%d", &num);
            while(num < 1 || num > 7)
            {
                printf("\n%d is not a valid option. Please select 1 - 7: ", num);
                scanf("%d", &num);
            }
            while(findNumber(num, DEPT_electiveChosen, 7) == true)
            {
                printf("\nYou entered option %d more than once. Please select another option: ", num);
                scanf("%d", &num);
            }
            DEPT_electiveChosen[6] = num;

            printf("\nYou Selected: ");
            for (int i = 0; i < 7; i++) {
                printf("-> Option %d ", DEPT_electiveChosen[i]);
            }

            printf("\n\n____________________________________________________\n\n");

            printf("\nThe CS department requires 12 credits of 'Other' electives. These can be fulfilled using ANY course in the school.\n"
                   "Please enter 'CS' to fulfil using CS courses OR enter 'Other' to fulfil using non-CS courses.\n"
                   "\nPlease enter CS or Other: ");
            scanf("%s", choice);

            while(strcasecmp(choice, "CS") != 0 && strcasecmp(choice, "Other") != 0) //if not cs or other
            {
                printf("\n%s is not a valid option. Please enter CS or Other: ", choice);
                scanf("%s", choice);
            }
            if(strcasecmp(choice, "CS") == 0)
            {
                userGraph->graphRequirements->GE_OTHER = false;
                //userGraph->graphRequirements->otherElectives_Switch = true;
                userGraph->graphRequirements->otherGE_Switch = false;
                userGraph->graphRequirements->profElectivesCredits += userGraph->graphRequirements->otherElectivesCredits;
            }
            if(strcasecmp(choice, "Other") == 0)
            {
                userGraph->graphRequirements->GE_OTHER = true;
               // userGraph->graphRequirements->otherElectives_Switch = false;
                userGraph->graphRequirements->otherGE_Switch = true;
            }
        //}
       // else if(strcasecmp(userGraph->department, "EE") == 0)
        //{

        //}


    }
    else if(strcasecmp(graph->graphType, "GE_REQ") == 0)
    {


        /*******      get user preference data   *******/
        printf("\n\n____________________________________________________\n");
        printf("\nPlease select 5 GE core course fields. Fields 1 - 6 are available as follows: "
               "\n\tField 1: Way of Thinking"
               "\n\tField 2: Exploration of Life"
               "\n\tField 3: Art and Literature"
               "\n\tField 4: Society and Culture"
               "\n\tField 5: Science, Technology and Society"
               "\n\tField 6: Historical Analysis\n"
               "\nPlease enter 5 field numbers as shown (ex: 3 2 4 5 6): ");
        for(int i = 0; i < 5; )
        {
            scanf("%d", &num);
            if(num < 1 || num > 6)
            {
                printf("\n%d is not a valid GE course Field. Please select 1 - 6: ", num);
            }
            else //between 1 - 7
            {
                if(findNumber(num, GE_coreChosen, 5) == false) //if number is not already in array
                {
                    GE_coreChosen[i] = num;
                    i++;
                }
                else printf("\nYou entered Field %d more than once. Please select another field: ", num);
            }
        }
        printf("\nYou Selected: ");
        for (int i = 0; i < 5; i++) {
            printf("Field %d, ", GE_coreChosen[i]);
        }
        printf("\n\n____________________________________________________\n\n");

        printf("Please select your General Education Elective course preference below.\n");
        printf("Computer Science Department requires: HUMANITIES and SOCIAL SCIENCES courses\n");
        printf("\nPlease input your >>HUMANITIES<< course preference: "
               "\n\n\t[ ] General Art"
               "\n\t[ ] Studio Art"
               "\n\t[ ] Philosophy and Religious Studies"
               "\n\t[ ] Humane and Historical Studies\n");

        printf("\nPlease enter your preference for these courses by choosing a number between 1 - 4 for each course.\n");
        printf("**IMPORTANT** Preference 1 = MOST preferred    and    Preference 4 = LEAST preferred. \n\n");
        printf("\tGeneral Art: ");
        scanf("%d", &num);
        while(num < 1 || num > 4)
        {
            printf("\n%d is not a valid option. Please select 1 - 4: ", num);
            scanf("%d", &num);
        }
        while(findNumber(num, GE_humanitiesChosen, 4) == true)
        {
            printf("\nYou entered option %d more than once. Please select another option: ", num);
            scanf("%d", &num);
        }
        GE_humanitiesChosen[0] = num;

        printf("\tStudio Art: ");
        scanf("%d", &num);
        while(num < 1 || num > 4)
        {
            printf("\n%d is not a valid option. Please select 1 - 4: ", num);
            scanf("%d", &num);
        }
        while(findNumber(num, GE_humanitiesChosen, 4) == true)
        {
            printf("\nYou entered option %d more than once. Please select another option: ", num);
            scanf("%d", &num);
        }
        GE_humanitiesChosen[1] = num;

        printf("\tPhilosophy and Religious Studies: ");
        scanf("%d", &num);
        while(num < 1 || num > 4)
        {
            printf("\n%d is not a valid option. Please select 1 - 4: ", num);
            scanf("%d", &num);
        }
        while(findNumber(num, GE_humanitiesChosen, 4) == true)
        {
            printf("\nYou entered option %d more than once. Please select another option: ", num);
            scanf("%d", &num);
        }
        GE_humanitiesChosen[2] = num;

        printf("\tHumane and Historical Studies: ");
        scanf("%d", &num);
        while(num < 1 || num > 4)
        {
            printf("\n%d is not a valid option. Please select 1 - 4: ", num);
            scanf("%d", &num);
        }
        while(findNumber(num, GE_humanitiesChosen, 4) == true)
        {
            printf("\nYou entered option %d more than once. Please select another option: ", num);
            scanf("%d", &num);
        }
        GE_humanitiesChosen[3] = num;

        printf("\nYou Selected: ");
        for (int i = 0; i < 4; i++) {
            printf("-> Option %d ", GE_humanitiesChosen[i]);
        }
        printf("\n\n____________________________________________________\n\n");

        printf("Please select your General Education Elective course preference below.\n");
        printf("Computer Science Department requires: HUMANITIES and SOCIAL SCIENCES courses\n");
        printf("\nPlease input your >>SOCIAL SCIENCES<< course preference: "
               "\n\t[ ] Law and Politics"
               "\n\t[ ] Sociology, Psychology, Anthropology, Education, and Gender Studies"
               "\n\t[ ] Management, Informatics, and Economics\n");

        printf("\nPlease enter your preference for these courses by choosing a number between 1 - 3 for each course.\n");
        printf("**IMPORTANT** Preference 1 = MOST preferred    and    Preference 3 = LEAST preferred. \n\n");
        printf("\tLaw and Politics: ");
        scanf("%d", &num);
        while(num < 1 || num > 3)
        {
            printf("\n%d is not a valid option. Please select 1 - 3: ", num);
            scanf("%d", &num);
        }
        while(findNumber(num, GE_ssChosen, 3) == true)
        {
            printf("\nYou entered option %d more than once. Please select another option: ", num);
            scanf("%d", &num);
        }
        GE_ssChosen[0] = num;

        printf("\tSociology, Psychology, Anthropology, Education, and Gender Studies: ");
        scanf("%d", &num);
        while(num < 1 || num > 3)
        {
            printf("\n%d is not a valid option. Please select 1 - 3: ", num);
            scanf("%d", &num);
        }
        while(findNumber(num, GE_ssChosen, 3) == true)
        {
            printf("\nYou entered option %d more than once. Please select another option: ", num);
            scanf("%d", &num);
        }
        GE_ssChosen[1] = num;

        printf("\tManagement, Informatics, and Economics: ");
        scanf("%d", &num);
        while(num < 1 || num > 3)
        {
            printf("\n%d is not a valid option. Please select 1 - 3: ", num);
            scanf("%d", &num);
        }
        while(findNumber(num, GE_ssChosen, 3) == true)
        {
            printf("\nYou entered option %d more than once. Please select another option: ", num);
            scanf("%d", &num);
        }
        GE_ssChosen[2] = num;

        printf("\nYou Selected: ");
        for (int i = 0; i < 3; i++) {
            printf("-> Option %d ", GE_ssChosen[i]);
        }
        printf("\n\n____________________________________________________\n\n");

        if(userGraph->graphRequirements->otherGE_Switch == true)
        {
            userGraph->graphRequirements->totalDeptCredits -= userGraph->graphRequirements->otherElectivesCredits;
            userGraph->graphRequirements->totalGE_Credits += userGraph->graphRequirements->otherGE_Credits;

            printf("You chose to use non-CS courses to fulfil the 'Other Elective' criteria\n\n");
            printf("Please select your General Education Elective course preference below.\n");
            printf("Computer Science Department requires: HUMANITIES and SOCIAL SCIENCES courses\n");
            printf("\nPlease input your >>NATURAL SCIENCES<< course preference: "
                   "\n\t[ ] Basic Science"
                   "\n\t[ ] Applied Science"
                   "\n\t[ ] Science, Technology and Society\n"
                   "\nPlease order the section according to your preference as shown (ex: 3 1 2): ");

            printf("\nPlease enter your preference for these courses by choosing a number between 1 - 3 for each course.\n\n");
            printf("**IMPORTANT** Preference 1 = MOST preferred    and    Preference 3 = LEAST preferred. \n\n");
            printf("\tBasic Science: ");
            scanf("%d", &num);
            while(num < 1 || num > 3)
            {
                printf("\n%d is not a valid option. Please select 1 - 3: ", num);
                scanf("%d", &num);
            }
            while(findNumber(num, GE_nsChosen, 3) == true)
            {
                printf("\nYou entered option %d more than once. Please select another option: ", num);
                scanf("%d", &num);
            }
            GE_nsChosen[0] = num;

            printf("\tApplied Science: ");
            scanf("%d", &num);
            while(num < 1 || num > 3)
            {
                printf("\n%d is not a valid option. Please select 1 - 3: ", num);
                scanf("%d", &num);
            }
            while(findNumber(num, GE_nsChosen, 3) == true)
            {
                printf("\nYou entered option %d more than once. Please select another option: ", num);
                scanf("%d", &num);
            }
            GE_nsChosen[1] = num;

            printf("\tScience, Technology and Society: ");
            scanf("%d", &num);
            while(num < 1 || num > 3)
            {
                printf("\n%d is not a valid option. Please select 1 - 3: ", num);
                scanf("%d", &num);
            }
            while(findNumber(num, GE_nsChosen, 3) == true)
            {
                printf("\nYou entered option %d more than once. Please select another option: ", num);
                scanf("%d", &num);
            }
            GE_nsChosen[2] = num;
            printf("\nYou Selected: ");
            for (int i = 0; i < 3; i++) {
                printf("-> Option %d ", GE_nsChosen[i]);
            }
            printf("\n\n____________________________________________________\n\n");
        }
    }
    else if(strcasecmp(graph->graphType, "PE_REQ") == 0)
    {
        printf("\n\n____________________________________________________\n\n");

        printf("Please select your Physical Education course preference below.\n");
        printf("Computer Science Department requires: 6 Semester of PE courses\n");
        printf("\nPlease input your >>PHYSICAL EDUCATION<< course preference: "
               "\n\n\t[ ] Ball Sports (Soccer, Baseball, Badminton, etc.)"
               "\n\t[ ] Dance Sports (Pop Dance, Jazz Dance, etc.)"
               "\n\t[ ] Water Sports (Swimming, Water Aerobics, etc)"
               "\n\t[ ] Martial Arts Sports (Karate, Tae Kwon Do, etc)"
               "\n\t[ ] Stretching and Relaxation Sports (Yoga, Tai Chi, etc)"
               "\n\t[ ] Walking and Running Sports (Exercise Walking & Jogging, Orienteering, etc )"
               "\n\t[ ] Strength and Muscle Sports (Weight Training, Core Strength, etc)\n");

        printf("\nPlease enter your preference for these courses by choosing a number between 1 - 7 for each course.\n");
        printf("**IMPORTANT** Preference 1 = MOST preferred    and    Preference 7 = LEAST preferred. \n\n");
        printf("\tBall Sports: ");
        scanf("%d", &num);
        while(num < 1 || num > 7)
        {
            printf("\n%d is not a valid option. Please select 1 - 7: ", num);
            scanf("%d", &num);
        }
        while(findNumber(num, PE_chosen, 7) == true)
        {
            printf("\nYou entered option %d more than once. Please select another option: ", num);
            scanf("%d", &num);
        }
        PE_chosen[0] = num;

        printf("\tDance Sports: ");
        scanf("%d", &num);
        while(num < 1 || num > 7)
        {
            printf("\n%d is not a valid option. Please select 1 - 7: ", num);
            scanf("%d", &num);
        }
        while(findNumber(num, PE_chosen, 7) == true)
        {
            printf("\nYou entered option %d more than once. Please select another option: ", num);
            scanf("%d", &num);
        }
        PE_chosen[1] = num;

        printf("\tWater Sports: ");
        scanf("%d", &num);
        while(num < 1 || num > 7)
        {
            printf("\n%d is not a valid option. Please select 1 - 7: ", num);
            scanf("%d", &num);
        }
        while(findNumber(num, PE_chosen, 7) == true)
        {
            printf("\nYou entered option %d more than once. Please select another option: ", num);
            scanf("%d", &num);
        }
        PE_chosen[2] = num;

        printf("\tMartial Arts Sports: ");
        scanf("%d", &num);
        while(num < 1 || num > 7)
        {
            printf("\n%d is not a valid option. Please select 1 - 7: ", num);
            scanf("%d", &num);
        }
        while(findNumber(num, PE_chosen, 7) == true)
        {
            printf("\nYou entered option %d more than once. Please select another option: ", num);
            scanf("%d", &num);
        }
        PE_chosen[3] = num;

        printf("\tStretching and Relaxation Sports: ");
        scanf("%d", &num);
        while(num < 1 || num > 7)
        {
            printf("\n%d is not a valid option. Please select 1 - 7: ", num);
            scanf("%d", &num);
        }
        while(findNumber(num, PE_chosen, 7) == true)
        {
            printf("\nYou entered option %d more than once. Please select another option: ", num);
            scanf("%d", &num);
        }
        PE_chosen[4] = num;

         printf("\tWalking and Running Sports: ");
        scanf("%d", &num);
        while(num < 1 || num > 7)
        {
            printf("\n%d is not a valid option. Please select 1 - 7: ", num);
            scanf("%d", &num);
        }
        while(findNumber(num, PE_chosen, 7) == true)
        {
            printf("\nYou entered option %d more than once. Please select another option: ", num);
            scanf("%d", &num);
        }
        PE_chosen[5] = num;

         printf("\tStrength and Muscle Sports: ");
        scanf("%d", &num);
        while(num < 1 || num > 7)
        {
            printf("\n%d is not a valid option. Please select 1 - 7: ", num);
            scanf("%d", &num);
        }
        while(findNumber(num, PE_chosen, 7) == true)
        {
            printf("\nYou entered option %d more than once. Please select another option: ", num);
            scanf("%d", &num);
        }
        PE_chosen[6] = num;

        printf("\nYou Selected: ");
        for (int i = 0; i < 7; i++) {
            printf("-> Option %d ", PE_chosen[i]);
        }
    }
    else if(strcasecmp(graph->graphType, "SERVICE_REQ") == 0)
    {


    }

   //open file for reading course data
    fp = fopen(coursesFile , "r");
    if(fp == NULL) {
            printf("%s ", coursesFile);
        perror("Error opening file");
    }

    //add nodes to graph
    while(fscanf(fp,"%[^|]%*c %[^|]%*c %d | %s |%[^|]%*c %s | %s | %s\n",//
          courseId, courseName, &credits, timeString, courseRoom, getRequired, courseCategory, courseType)!= EOF)
    {
        removeSpace(courseId, strlen(courseId));
        if(courseId[3] == '1' && courseId[4] == '0')
            strcpy(semester, "Fall");
        else if(courseId[3] == '2' && courseId[4] == '0')
            strcpy(semester, "Spring");
        else if(courseId[3] == '3' && courseId[4] == '0')
            strcpy(semester, "Summer");

        tempTime = convertClassTime(timeString, semester);

        for(int i = 0; i <7; i++){
            classTimes[i] = *(tempTime + i);
        }

        removeSpace(courseName, strlen(courseName));
        removeSpace(courseRoom, strlen(courseRoom));

        if(searchGraph(graph->head, courseName) == false)
        {
            if(strcasecmp(getRequired, "required") == 0)
            {
                required = true;
            }
            else required = false;



        /**get user preference here* send graph type, coursecategory, and user pref array based on graph type if statement here --  returns userpref number
                if(graphtype is ge) then use line below b/c sending ge array but if dept graph send dept array(still need to collect this from user)*/
            if(strcasecmp(graphType, "GE_REQ") == 0)
            {
                /**if()  course category is  core then u need to use this array. but if it's humanities then use a different array*/
                if(strcasecmp(courseCategory, "GE_humanities") == 0)
                {
                    userPreferenceIndex = getUserPrefIndex(graphType, courseCategory, courseType, GE_humanitiesChosen);
                }
                else if(strcasecmp(courseCategory, "GE_socialSciences") == 0)
                {
                    userPreferenceIndex = getUserPrefIndex(graphType, courseCategory, courseType, GE_ssChosen);
                }
                else if(strcasecmp(courseCategory, "GE_naturalSciences") == 0)
                {
                    userPreferenceIndex = getUserPrefIndex(graphType, courseCategory, courseType, GE_nsChosen);
                }
                else
                {
                    userPreferenceIndex = getUserPrefIndex(graphType, courseCategory, courseType, GE_coreChosen);
                }
            }
            if(strcasecmp(graphType, "DEPT_REQ") == 0)
            {
                if(required == false)
                {
                    //if(strcasecmp(userGraph->department, "CS") == 0)
                        userPreferenceIndex = getUserPrefIndex("CS", courseCategory, courseType, DEPT_electiveChosen); //send graph type as cs
                    //if(strcasecmp(userGraph->department, "EE") == 0)
                        //userPreferenceIndex = getUserPrefIndex("EE", courseCategory, courseType, DEPT_electiveChosen); //send graph type as ee
                }
            }
            if(strcasecmp(graphType, "PE_REQ") == 0)
            {
                userPreferenceIndex = getUserPrefIndex(graphType, courseCategory, courseType, PE_chosen);
            }
            if(strcasecmp(graphType, "SERVICE_REQ") == 0)
            {
                userPreferenceIndex = 1;
            }

            addNode(&graph->head, courseId, courseName, credits, semester, required, courseCategory, userPreferenceIndex, classTimes, timeString, courseRoom);
            graph->numVertices++;
        }
        else /***it's a duplicate, check times are different, check semester */
        {
            Node* temp;
            temp = getNode(graph->head, courseName);

            if(strcasecmp(temp->courseSemester, semester) != 0) //course has 2 different semesters, so change semester to both
            {
                strcpy(temp->courseSemester, "Both");
            }
            if(memcmp(classTimes, temp->classTimes->timeSlots, sizeof(classTimes)) != 0)//times are not the same time so you need to add a new time
            {
                addClassTime(&temp->classTimes, classTimes, timeString, courseRoom);
                temp->numOfActiveTimeSlots++;
            }
        }
    }
    fclose(fp);


    //open file for reading prerequisite data
    fp = fopen(prereqFile , "r");
    if(fp == NULL) {
            printf("%s ", prereqFile);
        perror("Error opening file");
    }

    //create edges using prerequisites
    while(fscanf(fp,"%[^|]%*c %[^\n]%*c", srcNode, destNode)!= EOF)
    {
        removeSpace(srcNode, strlen(srcNode));
        removeSpace(destNode, strlen(destNode));
        addEdge(graph, srcNode, destNode);
    }
    fclose(fp);
}

int removeStudentCourses(UserGraph *userGraph, char *studentFile)
{
    //Node* course;
    char userCourse[200];
    FILE *fp;
    SubGraph *gCrawl;
    bool found, validCourse;
    Node *course;
    int remainingCredits = 128, courseCredits, count = 0;

    /* opening file for reading */
    //fp = fopen("StudentData/2yrFall.txt" , "r");
    fp = fopen(studentFile , "r");
    if(fp == NULL) {
        perror("Error opening file");
    }

    printf("\n\n");

    userGraph->checkingOldCourses = true;
    while(fscanf(fp,"%[^|]%*c %d\n", userCourse, &courseCredits)!= EOF)
    {
        removeSpace(userCourse, strlen(userCourse));
        gCrawl = userGraph->head;
        while(gCrawl)
        {
            found = searchGraph(gCrawl->head, userCourse);
            if(found)
            {
                course = getNode(gCrawl->head, userCourse);
                validCourse = checkGraphRequirements(userGraph, gCrawl, course);
                if(validCourse == false) //user took too many of a certain kind of course. ex: if they took 10 GE courses the last course will not fulfil anything because you only need 9, so it's just extra
                {
                    printf("[ %s ] DOES NOT fulfil any %s course requirements.\n", course->courseName, gCrawl->graphType);
                }
                else if(validCourse == true)
                {
                    remainingCredits -= course->credits;
                }
                deleteNode(gCrawl, course);

                break;
            }

            gCrawl = gCrawl->nextGraph;
        }
        if(!found)//if u didn't find the course then assume it's fits into "other courses"
        {
            count += courseCredits;
            printf("Course [ %s ] NOT found.\n", userCourse);
            if(userGraph->graphRequirements->GE_OTHER == true && count <= 12) //12 is num of Other courses needed
            {
                userGraph->graphRequirements->otherGE_Credits -= courseCredits;
                userGraph->graphRequirements->totalGE_Credits -= courseCredits;
                userGraph->totalDegreeCredits -= courseCredits;
                remainingCredits -= courseCredits;

                if(userGraph->graphRequirements->totalGE_Credits < 1)
                    userGraph->graphRequirements->otherGE_Switch = false;
            }

            else if(userGraph->graphRequirements->GE_OTHER == false && count <= 12)//12 is num of Other courses needed
            {
                userGraph->graphRequirements->profElectivesCredits -= courseCredits;
                userGraph->graphRequirements->totalDeptCredits -= courseCredits;
                userGraph->totalDegreeCredits -= courseCredits;
                remainingCredits -= courseCredits;
            }
        }

        userGraph->graphRequirements->numOfDeptCredits = 0;
        userGraph->graphRequirements->chineseCourseNo = 0;
        userGraph->graphRequirements->englishCourseNo = 0;
        userGraph->graphRequirements->GE_CoreCourseNo = 0;
        userGraph->graphRequirements->GE_totalCourseNo = 0;
        userGraph->graphRequirements->PE_CourseNo = 0;
        userGraph->graphRequirements->serviceCourseNo = 0;

    }

    userGraph->checkingOldCourses = false;
    fclose(fp);

    return remainingCredits;
}



