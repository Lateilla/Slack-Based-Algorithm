#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include "headers.h"

void freeEdges(Edge *edge)
{
	if (edge == NULL)
		return;
	freeEdges(edge->nextEdge);
	free(edge);
}

void freeNodes(Node *node)
{
    if (node == NULL)
		return;
	freeNodes(node->nextNode);
	free(node);
}

void freeSubGraphs(SubGraph *g)
{
    if(g == NULL)
        return;
    freeSubGraphs(g->nextGraph);

	Node* current = g->head;
	while(current)
	{
		freeEdges(g->head->edgeFromNode);
		g->head->edgeFromNode = NULL;
		freeEdges(g->head->edgeToNode);
		g->head->edgeToNode = NULL;
		current = current->nextNode;
	}

	freeNodes(g->head);
	g->head = NULL;
	free(g);
}

void freeGraph(UserGraph *G)
{
    freeSubGraphs(G->head);
    free(G);
}

//linear search to find a node
bool searchGraph(struct Node* head, char *nodeName)
{
    Node* current = head;  // Initialize current
    while (current != NULL)
    {
        if (strcasecmp(current->courseName, nodeName) == 0)
            return true;
        current = current->nextNode;
    }
    return false;
}

//linear search to find a edge
bool searchEdges(struct Edge* head, char *nodeName)
{
    Edge* current = head;  // Initialize current
    while (current != NULL)
    {
        if (strcasecmp(current->nodeToFrom->courseName, nodeName) == 0)
            return true;
        current = current->nextEdge;
    }
    return false;
}

Node* getNode(Node* graphHead_ref, char *nodeName) //returns the node if it exists
{
    Node* current = graphHead_ref;  // Initialize current
    while (current != NULL)
    {
        if (strcasecmp(current->courseName, nodeName) == 0)
            return current;
        current = current->nextNode;
    }


    printf("\n\n\t\t\t\t*********** ->>>> DATA ERROR!! <<<<- ***********\n"
           "Course: \"%s\" NOT found!\n"
           "Please ensure map's course data and prerequisite data match!\n\n", nodeName);
    exit(1);
    //return NULL;
}

/* Given a reference (pointer to pointer) to the head
   of a list and an int, inserts first edge */
void insertFirstEdge(Edge** head_ref, Node** data)
{
    Edge* newEdge = (Edge*) malloc(sizeof(Edge));
    newEdge->nodeToFrom  = *data; //put in node of edge it is pointing to or from
    newEdge->nextEdge = NULL; //this will be last node so make next NULL

    if (*head_ref == NULL) // If the Linked List is empty, then make the new node as head
    {
       *head_ref = newEdge;
       return;
    }
    return;
}

/* Given a reference (pointer to pointer) to the head of a list and
   an int, inserts a new edge on the front of the list. */
void insertEdgeAtFront(Edge** head_ref, Node** data)
{
    Edge* newEdge = (Edge*) malloc(sizeof(Edge));
    newEdge->nodeToFrom = *data;
    newEdge->nextEdge = (*head_ref); //Make next of new node head
    (*head_ref) = newEdge; //move the head to point to the new node
}


//adds a class time to the course, there can be multiple classtimes
void addClassTime(Time** head_ref, long long int *classTimes, char *timeString, char *courseRoom)
{
    Time* newTime = (Time*) malloc(sizeof(Time));

    newTime->active = true;
    newTime->timeSlotConflictCount = 0;
    strcpy(newTime->timeString, timeString);
    strcpy(newTime->courseRoom, courseRoom);

    for (int i = 0; i < 7; i++) {  //put data in new time struct
        newTime->timeSlots[i] = classTimes[i];
    }

    if((*head_ref) == NULL) //this is the first time for the course
    {
        newTime->nextTime = NULL;
        (*head_ref) = newTime;
    }
    else //this isnt the first time so you need to add a time struct at the front
    {
        newTime->nextTime = (*head_ref); //make next of new time the head
        (*head_ref) = newTime; //move the head to point to the new node
    }
}



/* Given a reference (pointer to pointer) to the head
   of a list and an int, appends a new node at the end
   char *name is the same as char name[]
   */
void addNode(Node** head_ref, char *courseId, char *name, int credits, char *semester, bool required, char *courseCategory, int userPreferenceIndex, long long int *classTimes, char *timeString, char *courseRoom)
{
    Node* new_node = (Node*) malloc(sizeof(Node));
    Node *last = (*head_ref);

    strcpy(new_node->courseId, courseId);
    strcpy(new_node->courseName, name);
    new_node->credits = credits;
    new_node->classTimes = NULL;
    addClassTime(&new_node->classTimes, classTimes, timeString, courseRoom);
    new_node->numOfActiveTimeSlots = 1;
    strcpy(new_node->courseSemester, semester);
    new_node->required = required;
    new_node->userPreferenceIndex = userPreferenceIndex;
    strcpy(new_node->courseCategory, courseCategory);

    new_node->conflictCount = 0;
    new_node->nextNode = NULL;
    new_node->prevNode = NULL;
    new_node->edgeFromNode = NULL;
    new_node->edgeToNode = NULL;
    new_node->fanOut = 0;
    new_node->inDegree = 0;
    new_node->inDegreeReseter = 0;
    new_node->time = 1;
    new_node->forwardPass = 0;
    new_node->backwardPass = 999999;
    new_node->slack = 0;
    new_node->pathLength = 0;
    new_node->visited = false;
    new_node->active = true;

    if ((*head_ref) == NULL)//If the Linked List is empty, then make the new node as head
    {
       (*head_ref) = new_node;
       return;
    }

    while (last->nextNode != NULL) // Else traverse till the last node
        last = last->nextNode;

    last->nextNode = new_node; // Change the next of last node
    new_node->prevNode = last; //new node previous node is last node

    return;
}

/* Adds an edge from src to dest. A new node is
added to the adjacency list of src. */
void addEdge(SubGraph* graph, char *src, char *dest)
{
	Node *srcNode  = NULL, *destNode = NULL;

    srcNode = getNode(graph->head, src);
    destNode = getNode(graph->head, dest);

    /*for the source nodes*/
    if (srcNode->edgeFromNode == NULL) //if there is no edges going from this node then create first one
    {
        insertFirstEdge(&srcNode->edgeFromNode, &destNode);
        srcNode->fanOut++;
    }
    else //if there are edges going from this node, put this edge at the front of the list
    {
        if(searchEdges(srcNode->edgeFromNode, destNode->courseName) == false)//check if src already has dest in edgefromnode list
        {
            insertEdgeAtFront(&srcNode->edgeFromNode, &destNode);
            srcNode->fanOut++;
        }
    }

    /*for the destination nodes*/
    if (destNode->edgeToNode == NULL) //if there is no edges going to this node then create first one
    {
        insertFirstEdge(&destNode->edgeToNode, &srcNode);
        destNode->inDegree++;
        destNode->inDegreeReseter++;
    }
    else //if there are edges going to this node, put this edge at the front of the list
    {
        if(searchEdges(destNode->edgeToNode, src) == false)
        {
            insertEdgeAtFront(&destNode->edgeToNode, &srcNode);
            destNode->inDegree++;
            destNode->inDegreeReseter++;
        }
    }
}

//topological sort
//put source nodes at end of list until all nodes have been put
void topSort(SubGraph* graph)
{
    Node *current, *next, *temp;
    int numOfSorted = 0;

    while(numOfSorted < graph->numVertices)
    {
        current = graph->head;

        while(current)
        {
            next = current->nextNode;

            if(current->inDegree == 0 && current->visited == false)//is a source node so put at end of list
            {
                if(current->nextNode == NULL) //node is already at end of node list so do nothing and mark visited true
                {
                    current->visited = true;
                    numOfSorted++;
                }
                else //it's not at the end of list
                {
                    if(current->prevNode != NULL) //if current is not the first node in list. if it's fist node u dnt need this part
                    {
                        temp = current->prevNode; //make next node's previous point to current's prev instead of current
                        temp->nextNode = current->nextNode;
                    }

                    temp = current->nextNode; //make previous node's next point to current's next instead of current
                    temp->prevNode = current->prevNode;

                    if(current->prevNode == NULL) //if it's the first node in the list
                    {
                        graph->head = current->nextNode;
                    }
                    current->nextNode = NULL; //put current at end of node list

                    while(temp->nextNode)//find last node in list
                    {
                        temp = temp->nextNode;
                    }

                    temp->nextNode = current;
                    current->prevNode = temp;

                    Edge *tempEdge = current->edgeFromNode;
                    while(tempEdge) //go through the nodes it's pointing to and reduce the indegree
                    {
                        tempEdge->nodeToFrom->inDegree--;
                        tempEdge = tempEdge->nextEdge;
                    }
                    current->visited = true;
                    numOfSorted++;
                }
            }
            current = next;
        }
    }

    //reset inDegree and visited and get source list
    temp = graph->head;
    freeEdges(graph->sources); //get rid of old sources
    graph->sources = NULL;
    graph->numSources = 0;

    while(temp)//go through all node in list
    {
        temp->visited = false;
        temp->inDegree = temp->inDegreeReseter;
        if(temp->inDegree == 0) //create list of sources
        {
            graph->numSources++;
            temp->conflictCount = 0; //clear previous conflict count
            temp->classTimes->timeSlotConflictCount = 0; //clear timeslot conflict count

            temp->numOfActiveTimeSlots = 0; //start at 0 active timeslots
            Time *timeTemp = temp->classTimes;
            while(timeTemp) //reset all the timeslots to active
            {
                temp->numOfActiveTimeSlots++; //count how many timeslots the course has
                timeTemp->active = true;
                timeTemp = timeTemp->nextTime;
            }

            if(graph->sources == NULL) //if list if empty
                insertFirstEdge(&graph->sources, &temp);
            else
                insertEdgeAtFront(&graph->sources, &temp);
        }
        temp = temp->nextNode;
    }
}

void criticalPath (SubGraph* graph)
{
    topSort(graph);

    Node *current;
    int tmpTime;

    current = graph->head;

    while(current) //reset graph times
    {
        current->forwardPass = 0;
        current->backwardPass = 999999;
        current = current->nextNode;
    }

    current = graph->head;
    while(current->nextNode) //forward pass
    {
        if(current->edgeToNode == NULL)//if it's a source node
            current->forwardPass += current->time;

        Edge* tmpEdge = current->edgeFromNode;
		while (tmpEdge)
		{
			tmpTime = tmpEdge->nodeToFrom->time + current->forwardPass; //forwardPass = current nodeTime + node that it points to's start time

            if(tmpTime > tmpEdge->nodeToFrom->forwardPass) //if the new start time is bigger than the current start time then change to new start time
                tmpEdge->nodeToFrom->forwardPass =  tmpTime;

			tmpEdge = tmpEdge->nextEdge;
		}
        current = current->nextNode;
    }

    while(current)//backward pass
    {
        if(current->edgeFromNode == NULL)//if it's a final node
            current->backwardPass = current->forwardPass;

        Edge* tmpEdge = current->edgeToNode;
		while (tmpEdge)
		{
			tmpTime = current->backwardPass - tmpEdge->nodeToFrom->time; //backwardPass = current node's finish - the node that point's to its time

            if(tmpTime < tmpEdge->nodeToFrom->backwardPass) //if the new start time is bigger than the current start time then change to new start time
                tmpEdge->nodeToFrom->backwardPass =  tmpTime;

			tmpEdge->nodeToFrom->slack = tmpEdge->nodeToFrom->backwardPass - tmpEdge->nodeToFrom->forwardPass;
			tmpEdge = tmpEdge->nextEdge;
		}
		current = current->prevNode;
    }
}

bool findTimeConflictInteger(long long int a, long long int b)
{
    long long int binary1 = a, binary2 = b;
    int carry = 0;

    while (binary1 != 0 || binary2 != 0)
    {
        carry =(binary1 % 10 + binary2 % 10 + carry) / 2;

        if(carry == 1)
            return true;
            //printf(" Day %d. Carry: %d\n", i, carry);

        binary1 = binary1 / 10;
        binary2 = binary2 / 10;
    }

    return false;
}

bool findTimeConflict(long long int *a, long long int *b) //just binary addition
{
    long long int binary1[7], binary2[7];
    int carry = 0, i;

    for (i = 0; i < 7; i++) {
        binary1[i] = a[i];
    }

    for (i = 0; i < 7; i++) {
        binary2[i] = b[i];
    }

    i = 1; //don't copy the first index b/c it represents semester
    while(i < 7)
    {
        while (binary1[i] != 0 || binary2[i] != 0)
        {
            carry =(binary1[i] % 10 + binary2[i] % 10 + carry) / 2;

            if(carry == 1)
                return true;

            binary1[i] = binary1[i] / 10;
            binary2[i] = binary2[i] / 10;
        }
        i++;
    }
    return false;
}

//find conflict count for each time slot and return conflict or not between 2 courses
bool findTimeSlotConflictCount(Time *a, Time *b) //just binary addition
{
    long long int binary1[7], binary2[7];
    int i = 0;
    bool conflict, AB_courseConflict = true;
    Time *tempA, *tempB ;


    tempA = a;
    tempB = b;

    while(tempA)
    {
        if(tempA->active == true)//Time is active
        {
            for (i = 0; i < 7; i++) {
                binary1[i] = tempA->timeSlots[i];
            }

            while(tempB)
            {
                if(tempB->active == true)//Time is active
                {
                    for (i = 0; i < 7; i++) {
                        binary2[i] = tempB->timeSlots[i];
                    }

                    conflict = findTimeConflict(binary1, binary2);

                    if(conflict)
                    {
                        tempA->timeSlotConflictCount++;
                        tempB->timeSlotConflictCount++;
                    }

                    if(conflict == false) //there is at least 1 time slot within the 2 courses that don't conflict
                    {
                        AB_courseConflict = false;
                    }
                }

                tempB = tempB->nextTime;
            }
        }
        tempA = tempA->nextTime;
        tempB = b; //put tempB back to the start of course b times so that you can compare the times against the next A time
    }

    return AB_courseConflict;
}

void findCourseConflictCount(Edge* sourceHead) //send source nodes here to find their conflict count
{
    Edge *temp, *comparedTo; //temp is the node that is being compared to every other node, comparedTo is the node that temp is being compared to
    bool conflict;

    temp = sourceHead;
    comparedTo = temp->nextEdge;

    while(temp->nextEdge)
    {
        while(comparedTo)
        {
            conflict = findTimeSlotConflictCount(temp->nodeToFrom->classTimes, comparedTo->nodeToFrom->classTimes);
            if(conflict)
            {
                temp->nodeToFrom->conflictCount++;
                comparedTo->nodeToFrom->conflictCount++;
            }
            comparedTo = comparedTo->nextEdge;
        }
        temp = temp->nextEdge;
        comparedTo = temp->nextEdge;
    }
}

Time* selectTimeSlot(Node* course) //select the time slot with the lowest conflict
{
    Time *temp, *tCrawl;

    temp = course->classTimes;
    tCrawl = temp;

    while(temp)
    {
        if(temp->active == true)//Time is active
        {
            if(tCrawl == course->classTimes && tCrawl->active == false) // if tCrawl is the head it might not be active so change tCrawl to an active node
                tCrawl = temp;

            if(temp->timeSlotConflictCount <= tCrawl->timeSlotConflictCount)/** if you only use < the solution is no longer optimal**/
                tCrawl = temp;
        }
        temp = temp->nextTime;
    }
    return tCrawl;
}

void deleteEdge(Edge** edgeHead, char *name)
{
    Edge* eCrawl = (*edgeHead); //delete edge from source list
    while(eCrawl)
    {
        if(strcmp(eCrawl->nodeToFrom->courseName, name) == 0) //the first edge is the right one
        { //delete this edge
            (*edgeHead) = eCrawl->nextEdge;
            free(eCrawl);
            break;
        }

        if(strcmp(eCrawl->nextEdge->nodeToFrom->courseName, name) == 0) //if you found the right edge
        { //delete this edge
            Edge* next = eCrawl->nextEdge->nextEdge;
            free(eCrawl->nextEdge);
            eCrawl->nextEdge = next;
            break;
        }
        eCrawl = eCrawl->nextEdge;
    }
}

void deleteNode(SubGraph* graph, Node *node)
{
    Edge *tmpEdge, *tmpEdge2; //head of adjList

    if(node->edgeToNode == NULL)//if it's a source node. (it should be)
    {
        tmpEdge = node->edgeFromNode;
		while(tmpEdge) //delete all edges that point from this node
        {
            deleteEdge(&tmpEdge->nodeToFrom->edgeToNode, node->courseName);
            tmpEdge->nodeToFrom->inDegree--;
            tmpEdge->nodeToFrom->inDegreeReseter--;
            tmpEdge = tmpEdge->nextEdge;
        }

        deleteEdge(&graph->sources, node->courseName);//delete edge from source list

        freeEdges(node->edgeFromNode);//free all edges that point from this node
        node->edgeFromNode = NULL;

        if(graph->head == node)//delete the node (node is head)
        {
            if(graph->head->nextNode == NULL)//head is last node in graph
            {
               graph->head = NULL;
            }
            else{ //head is not the last node in graph
                graph->head = node->nextNode;
                graph->head->prevNode = NULL;
            }

            free(node);
            node = NULL;
            graph->numVertices--;
        }
        else//delete the node (node is not head)
        {
            node->prevNode->nextNode = node->nextNode;
            node->nextNode->prevNode = node->prevNode;
            free(node);
            node = NULL;
            graph->numVertices--;
        }
    }
    else //if it's not a source node
    {
        tmpEdge = node->edgeToNode;
        tmpEdge2 = node->edgeFromNode;
        while(tmpEdge)
        {
            while(tmpEdge2)
            {
                addEdge(graph, tmpEdge->nodeToFrom->courseName, tmpEdge2->nodeToFrom->courseName);
                tmpEdge2 = tmpEdge2->nextEdge;
            }
            tmpEdge = tmpEdge->nextEdge;
            tmpEdge2 = node->edgeFromNode;
        }

        tmpEdge = node->edgeToNode;
		while(tmpEdge) //delete all edges that point to this node
        {
            deleteEdge(&tmpEdge->nodeToFrom->edgeFromNode, node->courseName);
            tmpEdge->nodeToFrom->fanOut--;
            tmpEdge = tmpEdge->nextEdge;
        }

        tmpEdge = node->edgeFromNode;
		while(tmpEdge) //delete all edges that point from this node
        {
            deleteEdge(&tmpEdge->nodeToFrom->edgeToNode, node->courseName);
            tmpEdge->nodeToFrom->inDegree--;
            tmpEdge->nodeToFrom->inDegreeReseter--;
            tmpEdge = tmpEdge->nextEdge;
        }

        freeEdges(node->edgeToNode);//delete all edges that point to this node
        freeEdges(node->edgeFromNode);//delete all edges that point from this node
        node->edgeToNode = NULL;
        node->edgeFromNode = NULL;

        if(graph->head == node)//delete the node (node is head)
        {
            if(graph->head->nextNode == NULL)//head is last node in graph
            {
               graph->head = NULL;
            }
            else{ //head is not the last node in graph
                graph->head = node->nextNode;
                graph->head->prevNode = NULL;
            }

            free(node);
            node = NULL;
            graph->numVertices--;
        }
        else//delete the node (node is not head)
        {
            node->prevNode->nextNode = node->nextNode;
            if(node->nextNode != NULL)
                node->nextNode->prevNode = node->prevNode;
            free(node);
            node = NULL;
            graph->numVertices--;
        }
    }
}

// prints graph
void printGraph(SubGraph* graph)
{
    Node* pCrawl = graph->head;
	printf("%d Nodes in graph\n\n", graph->numVertices);

    Time *ttest;

	while(pCrawl)
    {
        printf("\n\n");

        ttest = pCrawl->classTimes;
        printf("Course: %s | %s | %d | %s | %d | no of time slots: %d |", pCrawl->courseId, pCrawl->courseName, pCrawl->credits, pCrawl->courseSemester, pCrawl->required, pCrawl->numOfActiveTimeSlots);

        while(ttest != NULL)
        {
            for (int i = 0; i < 7; i++) {
                printf(" %lld", ttest->timeSlots[i]);
            }
            printf("              ");

            ttest = ttest->nextTime;
        }


        pCrawl = pCrawl->nextNode;
    }

    printf("\n");

	printf("____________________________________________________\n");
}


int main()
{
    //create user graph
    UserGraph *userGraph = (UserGraph*) malloc(sizeof(UserGraph));
    userGraph->head = NULL;
    userGraph->numSubGraphs = 0;
    userGraph->totalDegreeCredits = 0;
    userGraph->totalNumOfCourses = 0;
    userGraph->totalCreditsScheduled = 0;
    userGraph->numSemestersScheduled = 0;
    userGraph->numOfSemesters = 0;
    for (int i = 0; i < 7; i++) {  //initialise unavailable days to 0
        userGraph->unavailableDays[i] = 0;
    }
    for (int i = 0; i < 7; i++) {  //initialise timetable to 0
        userGraph->semesterTimetable[i] = 0;
    }
    userGraph->semestersEmptyError = false;

    GraphRequirements *emptyGraphRequirements = (GraphRequirements*) malloc(sizeof(GraphRequirements));
    userGraph->graphRequirements = emptyGraphRequirements;

    userGraph->graphRequirements->totalCredits = 0;
    userGraph->graphRequirements->numOfCourses = 0;

/***********************       collect user info         **********************************/

    int numOfCredits, numOfSemesters;
    char semester[7], timeslots[10], student[5], studentFile[20], force[5];
    FILE *fp;

  /*  printf("\t\t\t\t\t\t   Welcome!\n\n\n"
           "\t\t\tPlease fill out the following questionnaire to receive your schedule.\n"
           "\t\t\t  You will need at least 10 minutes to complete this questionnaire.\n\n"
           "\t\t\t\t\tPlease read ALL instructions.\n\n\n"
           "\t\t\t\t\t  Press any key to BEGIN.");
    getch();
    system("cls");*/


    //printf("Department: ");
    //scanf("%s", userGraph->department);
    //while(strcasecmp(userGraph->department, "CS") != 0 && strcasecmp(userGraph->department, "EE") != 0)
    //{
        //printf("\nError: Only CS and EE currently available: ");
        //scanf("%s", userGraph->department);
    //}

    printf("Please enter 'New' if you are a new student (1st Year, 1st Semester), otherwise please enter 'Old'.\n");
    printf("\nAre you a new student or an old student?: ");
    scanf("%s", student);
    while(strcasecmp(student, "New") != 0 && strcasecmp(student, "Old") != 0)
    {
        printf("\nError: Please enter 'New' or 'Old': ");
        scanf("%s", student);
    }

    if(strcasecmp(student, "New") == 0)
    {
        printf("\nEnter MIN credits per semester(Recommended: 16 - 18): ");
        scanf("%d", &userGraph->minCredits);
    }
    else if(strcasecmp(student, "Old") == 0)
    {
        printf("\nStudent ID: ");
        scanf("%s", studentFile);
        strcat(studentFile, ".txt");

        /* just open to check that file is available */
        fp = fopen(studentFile , "r");
        if(fp == NULL) {
            //printf("%s ", subGraphReqFile);
            perror("Error opening file");
            return -1;
        }
        fclose(fp);

        printf("\nNumber of semesters remaining to complete degree: ");
        scanf("%d", &numOfSemesters);

        printf("\nTry to schedule courses within remaining semester AT ALL COSTS? (Yes/No): ");
        scanf("%s", force);

        while(strcasecmp(force, "Yes") != 0 && strcasecmp(force, "No") != 0)
        {
            printf("\nError: Please enter Yes or No: ");
            scanf("%s", force);
        }

        if(strcasecmp(force, "Yes") == 0)
        {
            printf("\n\t>>>> WARNING: This may cause system to disregard some prerequisite relationships!! <<<<"
                   "\n\t>>>> WARNING: This may cause credit overload (above 25 credits per semester)!! <<<<"
                   "\n\nDo you want to continue? (Yes/No): ");
            scanf("%s", force);

            while(strcasecmp(force, "Yes") != 0 && strcasecmp(force, "No") != 0)
            {
                printf("\nError: Please enter Yes or No: ");
                scanf("%s", force);
            }
        }
    }

    printf("\nInput the starting semester(Fall or Spring): ");
    scanf("%s", semester);
    while(strcasecmp(semester, "Spring") != 0 && strcasecmp(semester, "Fall") != 0)
    {
        printf("\nError: %s Semester Unavailable. Please enter Fall or Spring: ", semester);
        scanf("%s", semester);
    }

    printf("\nPlease enter which time slots (if any) you are UNAVAILABLE for class.\n"
           "NOTE: Does NOT apply to required courses and ONLY applies to starting semester.\n\n"
           "Format: Monday = M, Tuesday = T, Wednesday = W, Thursday = R, Friday = F, Saturday = S\n"
           "Time slots are from 1 - 9, a, b, c\n"
           "Please enter time slots as shown (ex: M1 R8 R9 Ra F1 F2 X). "
           "When finished, enter X to continue.\n"
           "Unavailable Times: ");

    scanf("%s", timeslots);

    while(strcasecmp(timeslots, "x") != 0)
    {
        unavailable(userGraph, timeslots);
        scanf("%s", timeslots);
    }

    SubGraph *deptGraph, *langGraph, *GE_Graph, *PE_Graph, *serviceGraph;  //these subgraphs make up the user graph
    int semesterNum, creditLimit;
    float tempSemesterNum, tempCreditLimit;

    getReqData(userGraph);

    /**SERVICE GRAPH*/
    serviceGraph = createSubGraph(&userGraph->head); //use this function to create as sub graphs as you want
    userGraph->numSubGraphs++;
    strcpy(serviceGraph->graphType, "SERVICE_REQ");
    fillSubGraph(userGraph, serviceGraph, "SERVICE_map_data.txt", "SERVICE_map_prereq.txt"); //get data from file and fill graphs with data and prerequisites


    /**DEPT GRAPH*/
    deptGraph = createSubGraph(&userGraph->head); //use this function to create as sub graphs as you want
    userGraph->numSubGraphs++;
    strcpy(deptGraph->graphType, "DEPT_REQ");

    //if(strcasecmp(userGraph->department, "CS") == 0)
        fillSubGraph(userGraph, deptGraph, "CSdept_map_data.txt", "CSdept_map_prereq.txt"); //get data from file and fill graphs with data and prerequisites
    //else if(strcasecmp(userGraph->department, "EE") == 0)
        //fillSubGraph(userGraph, deptGraph, "EEdept_map_data2.txt", "EEdept_map_prereq2.txt");

    tempSemesterNum = (128/(float)userGraph->minCredits); //keep number with decimals. 128 is num of credits for CS gradaution
    semesterNum = tempSemesterNum; //remove decimals

    if(tempSemesterNum > semesterNum)
        semesterNum++;

    tempCreditLimit = userGraph->graphRequirements->totalDeptCredits/(float)semesterNum; //for this to be correct you MUST load CS graph before GE graph. otherwise plz replace totalDeptCredits with 100(CS requires 100 credits)
    creditLimit = tempCreditLimit;

    if(tempCreditLimit > creditLimit)
        creditLimit++;

    userGraph->graphRequirements->deptCreditLimit = creditLimit;

    /**LANG GRAPH*/
    langGraph = createSubGraph(&userGraph->head); //use this function to create as sub graphs as you want
    userGraph->numSubGraphs++;
    strcpy(langGraph->graphType, "LANG_REQ");
    fillSubGraph(userGraph, langGraph, "LANG_map_data.txt", "LANG_map_prereq.txt"); //get data from file and fill graphs with data and prerequisites

    /**PE GRAPH*/
    PE_Graph = createSubGraph(&userGraph->head); //use this function to create as sub graphs as you want
    userGraph->numSubGraphs++;
    strcpy(PE_Graph->graphType, "PE_REQ");
    fillSubGraph(userGraph, PE_Graph, "PE_map_data.txt", "PE_map_prereq.txt"); //get data from file and fill graphs with data and prerequisites

    /**GE GRAPH*/
    GE_Graph = createSubGraph(&userGraph->head); //use this function to create as sub graphs as you want
    userGraph->numSubGraphs++;
    strcpy(GE_Graph->graphType, "GE_REQ");
    fillSubGraph(userGraph, GE_Graph, "GE_map_data.txt", "GE_map_prereq.txt"); //get data from file and fill graphs with data and prerequisites

    //system("cls");

    userGraph->totalDegreeCredits = userGraph->graphRequirements->totalDeptCredits + userGraph->graphRequirements->totalLangCredits + userGraph->graphRequirements->totalGE_Credits;
    userGraph->totalNumOfCourses = userGraph->graphRequirements->numOfCourses;

    float tempCredits;
    int remainingCredits;
    Edge *sourceNode, *tmpEdge;
    Node *endNode;

    if(strcasecmp(student, "Old") == 0)
    {
        remainingCredits = removeStudentCourses(userGraph, studentFile);
        tempCredits = (float)remainingCredits/numOfSemesters;
        userGraph->minCredits = tempCredits;

        if(tempCredits > userGraph->minCredits)
            userGraph->minCredits++;

        if(userGraph->graphRequirements->GE_OTHER == true) //re-add the remaining credits u minused from dept to put in GE other, otherwise scheduling is not great
            tempCreditLimit = (userGraph->graphRequirements->totalDeptCredits + userGraph->graphRequirements->otherGE_Credits)/(float)numOfSemesters;
        else if(userGraph->graphRequirements->GE_OTHER == false)
            tempCreditLimit = userGraph->graphRequirements->totalDeptCredits/(float)numOfSemesters;

        creditLimit = tempCreditLimit;

        if(tempCreditLimit > creditLimit)
            creditLimit++;

        userGraph->graphRequirements->deptCreditLimit = creditLimit;

        if(numOfSemesters > 2 && userGraph->minCredits < 16)
        {
            userGraph->minCredits = 16;
            userGraph->graphRequirements->deptCreditLimit = 12;
        }


        if(strcasecmp(force, "Yes") == 0) //if the student doesn't care and just wants to finish on time
        {
            ///find path length of all nodes, if node semester and user chosen semester are different and node is not both then add 1 to path length

            criticalPath(deptGraph);
            endNode = getNode(deptGraph->head, "END");


            /**This will loosen prerequisite relationships until you can schedule all courses within the timeframe given by the user*/
            for(int num = endNode->forwardPass; num > numOfSemesters; num--)
            {
                sourceNode = deptGraph->sources;
                while(sourceNode)
                {
                    sourceNode->nodeToFrom->pathLength = endNode->forwardPass - sourceNode->nodeToFrom->forwardPass;

                    if(strcasecmp(sourceNode->nodeToFrom->courseSemester, semester) != 0 && strcasecmp(sourceNode->nodeToFrom->courseSemester, "Both") != 0)
                        sourceNode->nodeToFrom->pathLength++;

                    if(sourceNode->nodeToFrom->pathLength > numOfSemesters)//takes longer than remaining semesters to finish if this course stays
                    {
                        tmpEdge = sourceNode->nodeToFrom->edgeToNode;
                        while(tmpEdge) //delete all edges that point to this node
                        {
                            deleteEdge(&tmpEdge->nodeToFrom->edgeFromNode, sourceNode->nodeToFrom->courseName);
                            tmpEdge->nodeToFrom->fanOut--;
                            tmpEdge = tmpEdge->nextEdge;
                        }

                        tmpEdge = sourceNode->nodeToFrom->edgeFromNode;
                        while(tmpEdge) //delete all edges that point from this node
                        {
                            deleteEdge(&tmpEdge->nodeToFrom->edgeToNode, sourceNode->nodeToFrom->courseName);
                            tmpEdge->nodeToFrom->inDegree--;
                            tmpEdge->nodeToFrom->inDegreeReseter--;
                            tmpEdge = tmpEdge->nextEdge;
                        }

                        freeEdges(sourceNode->nodeToFrom->edgeToNode);//delete all edges that point to this node
                        freeEdges(sourceNode->nodeToFrom->edgeFromNode);//delete all edges that point from this node
                        sourceNode->nodeToFrom->edgeToNode = NULL;
                        sourceNode->nodeToFrom->edgeFromNode = NULL;

                        addEdge(deptGraph, sourceNode->nodeToFrom->courseName, "END"); //add egde from this node to end
                    }
                    sourceNode = sourceNode->nextEdge;
                }

                criticalPath(deptGraph);
                endNode = getNode(deptGraph->head, "END");
            }

        }

        printf("\n\ntotalDeptCredits: %d"
               "\nremainingCredits: %d"
               "\nnumOfCredits: %d"
               "\ncreditLimit: %d"
               "\nnumOfSemesters: %d\n\n"
               ,userGraph->graphRequirements->totalDeptCredits, remainingCredits, userGraph->minCredits, userGraph->graphRequirements->deptCreditLimit, numOfSemesters);
    }

    if(strcasecmp(semester, "Spring") == 0)
    {
        strcpy(semester, "Spring");
        findSchedule(userGraph, semester);
    }
    else if(strcasecmp(semester, "Fall") == 0)
    {
        strcpy(semester, "Fall");
        findSchedule(userGraph, semester);
    }


	freeGraph(userGraph);

	printf("\nPress any key to EXIT.");
	getch();
	return 0;
}




