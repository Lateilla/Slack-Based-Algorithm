#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <stdbool.h>

typedef struct Edge
{
    bool visited;
    struct Node *nodeToFrom; //node that edge is going to or coming from
    struct Edge *nextEdge; //points to next edge in the adjacency list
    struct Edge *prevEdge;
} Edge;

// Represents an adjacency list node
typedef struct Node
{
    /*Scheduling Data*/
    bool active;
    bool required;
    int fanOut; //when you add an edge to edgeFromNode you need to +1 to this
    int credits;
    int numOfActiveTimeSlots;
    struct Time *classTimes;
    char courseSemester[7];
    int conflictCount;
    int userPreferenceIndex;
    char courseCategory[30];

    /*Critical Path data*/
    bool visited;
    int forwardPass;
    int backwardPass;
    int time;
    int slack;
    int inDegree; //how many prerequisite nodes
    int inDegreeReseter; //use to reset inDegree after topsort
    int pathLength; //length of the path from this node to the last node in the graph

    /* Basic data*/
    char courseName[200];
    char courseId[20];
    struct Node *nextNode;
    struct Node *prevNode;
	struct Edge *edgeFromNode;
	struct Edge *edgeToNode;
} Node;

typedef struct Time
{
    bool active;
    int timeSlotConflictCount;
    long long int timeSlots[7];
    char timeString[20];
    char courseRoom[40];
    struct Time *nextTime;
} Time;


/* Represents first node in adjacency list.
The adjacency list is made up of edges that point to other nodes.
The head node's edgeFromNode is the first edge in the successor adjacency list
and edgeToNode is the first edge in the predecessor adjacency list.
nextEdge is the next edge in the node's adjacency list so
nextEdge points to the next node in the adjacency list
*/

/*A graph is a linked list of nodes. graph node points to the head node
Size of array will be V (number of vertices in graph) */
typedef struct SubGraph
{
    char graphType[20]; //if graph category is 'DEPT_REQ' then only check the requirements for department and if graph category is 'UNI_REQ' then only check university requirements
	int numVertices;
	int numSources;
	int numOfFallCourses;
	int numOfSpringCourses;
	bool bothSemestersEmpty;
	struct Node *head;
	struct Edge *sources;
	struct Edge *scheduledThisSemester;
	struct SubGraph *nextGraph; //points to next edge in the adjacency list
    struct SubGraph *prevGraph;
} SubGraph;

typedef struct UserGraph //represents department graph. this graph contains all the smaller requirement graphs for the department. it's like a container that holds all the requirements to graduate
{
    int minCredits;  //credits the user chose
    char department[10];
    int totalDegreeCredits;
    int totalNumOfCourses;
    int totalCreditsScheduled;
    struct GraphRequirements *graphRequirements;
	int numSubGraphs;
	int numSemestersScheduled;
	struct SubGraph *head;
	long long int semesterTimetable[7];
	long long int unavailableDays[7];
	bool semestersEmptyError;
	int numOfFallCourses;
	int numOfSpringCourses;
	int numOfSemesters;
	bool checkingOldCourses; //tells program whether checking old courses or not when fulfilling requirements
} UserGraph;

typedef struct GraphRequirements
{
    int totalCredits; //total credits remaining in this graph before end of degree
    int numOfCourses; //min courses required before end of degree
    bool GE_OTHER;
    int GE_totalCourseNo; //total number of ge course scheduled so far this semester
    int totalGE_Credits;
    bool GE_Core1;
    bool GE_Core2;
    bool GE_Core3;
    bool GE_Core4;
    bool GE_Core5;
    bool GE_Core6;
    bool GE_Core7;
    bool GE_Core_Switch; //general education core course
    int GE_CoreSemesterCourseLimit; //#of ge course that can be scheduled this semester
    int GE_CoreCourseNo; //# of GE core courses already scheduled this semester
    int GE_CoreCoursesRemaining; //# of ge courses remaining before end of degree
    int GE_ElectivesRemaining; //# of ge courses remaining before end of degree
    bool GE_Humanities_Switch; //general education elective course
    int GE_totalHumanitiesNo;//# of humanities course so far
    bool GE_SocialSciences_Switch; //general education elective course
    int GE_totalSocialSciencesNo;//# of social sciences course so far
    bool GE_NaturalSciences_Switch; //general education elective course
    int GE_totalNaturalSciencesNo;//# of natural sciences course so far
    bool otherGE_Switch; /**add these credits to ge or cs depending on what student decides that they want */
    int otherGE_Credits; //# of other elective credits remaining before end of degree

    int totalLangCredits;
    bool collegeChinese_Switch;
    int chineseSemesterCourseLimit; //#of chinese courses that can be scheduled this semester
    int chineseCourseNo; //# of chinese courses already scheduled this semester
    int collegeChineseCredits; //# of chinese credits remaining before end of degree
    bool collegeEnglish_Switch;
    int englishSemesterCourseLimit; //#of english courses that can be scheduled this semester
    int englishCourseNo; //# of english courses already scheduled this semester
    int collegeEnglishCredits; //# of English credits remaining before end of degree

    bool PE_Switch;
    int PE_SemesterCourseLimit; //#of PE courses that can be scheduled this semester
    int PE_CourseNo; //# of pe courses already scheduled this semester
    int PE_CoursesRemaining; //# of PE courses remaining before end of degree
    bool studentService_Switch;
    bool serviceLearning_Switch;
    int serviceSemesterCourseLimit; //#of chinese courses that can be scheduled this semester
    int serviceCourseNo; //# of pe courses already scheduled this semester
    int serviceCoursesRemaining; //# of student service learning credits remaining before end of degree

    int totalDeptCredits;
    int deptCreditLimit; //#num of cs courses that should be scheduled each semester. this balances out what kind of courses are scheduled each semester
    int numOfDeptCredits; //#num of dept creds already scheduled this semester
    bool requiredSwitch;
    int requiredCredits;
    bool CS_CatA_Switch;
    int CS_CatA_Credits; //# of catA credits remaining before end of degree
    bool CS_CatB_Switch;
    int CS_CatB_Credits; //# of catB credits remaining before end of degree
    bool CS_CatC_Switch;
    int CS_CatC_Credits; //# of catC credits remaining before end of degree
    bool profElectives_Switch;
    int profElectivesCredits; //# of professional elective credits remaining before end of degree
    int otherElectivesCredits; //# of other elective credits remaining before end of degree
}GraphRequirements;


/**Functions are divided into sections**/

void freeEdges(Edge *edge);
void freeNodes(Node *node);
void freeSubGraphs(SubGraph *g);
void freeGraph(UserGraph *G);

/***********Creating the sub graphs: includes adding all data and edges to create a complete sub graph***********/
bool searchGraph(struct Node *head, char *nodeName); //linear search to find a node
Node* getNode(Node *graphHead_ref, char *nodeName); //returns the node if it exists
void insertFirstEdge(Edge **head_ref, Node** data); //inserts first edge
void insertEdgeAtFront(Edge **head_ref, Node** data); //inserts a new edge on the front of the list.
void addClassTime(Time **head_ref, long long int *classTimes, char *timeString, char *courseRoom); //adds a class time to the course, there can be multiple classtimes
void addNode(Node **head_ref, char *courseId, char *name, int credits, char *semester, bool required, char *courseCategory, int userPreferenceIndex, long long int *classTimes, char *timeString, char *courseRoom);
void addEdge(SubGraph *graph, char *src, char *dest);
SubGraph* createSubGraph(SubGraph **subGraphHead_ref);
long long* convertClassTime(char *timeString, char *semester);
void removeSpace(char *arr, int n); // Removes all extra whitespace from a string before filling subgraph
int getUserPrefIndex(char *graphType, char *courseCategory, char *courseType, int *userPref);
void getReqData(UserGraph* userGraph); //get requirement dta for the department
void fillSubGraph(UserGraph* userGraph, SubGraph *graph, char *coursesFile, char* prereqFile);
int removeStudentCourses(UserGraph *userGraph, char *studentFile);

/************Functions that are needed to facilitate scheduling of courses**********/
void topSort(SubGraph* graph);
void criticalPath (SubGraph* graph);
bool findTimeConflictInteger(long long int a, long long int b);
bool findTimeConflict(long long int *a, long long int *b); //just binary addition
bool findTimeSlotConflictCount(Time *a, Time *b); //find conflict count for each time slot and return conflict or not between 2 courses
void findCourseConflictCount(Edge* sourceHead); //send source nodes here to find their conflict count
Time* selectTimeSlot(Node* course); //select the time slot with the lowest conflict
void deleteEdge(Edge** edgeHead, char *name);
void deleteNode(SubGraph* graph, Node *node);
void printGraph(SubGraph* graph);

/***********Finds the schedule for a user***********/
void findSchedule(UserGraph* graph, char *currentSemester);
bool checkDeptRequirements(UserGraph *userGraph, SubGraph *currentGraph, Node *selectedCourse);
bool checkGraphRequirements(UserGraph *graph, SubGraph *currentGraph, Node *selectedCourse);

/***********Determines which time slots are unavailable***********/
void unavailable(UserGraph* graph, char *timeslots);


#endif
