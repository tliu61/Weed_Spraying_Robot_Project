#include <std.h>
#include <log.h>
#include <clk.h>
#include <gbl.h>
#include <bcache.h>

#include <mem.h> // MEM_alloc calls
#include <que.h> // QUE functions
#include <sem.h> // Semaphore functions
#include <sys.h> 
#include <tsk.h> // TASK functions
#include <math.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <c6x.h> // register defines
#include "pQueue.h"

#include "projectinclude.h"
#include "c67fastMath.h" // sinsp,cossp, tansp
#include "evmomapl138.h"
#include "evmomapl138_i2c.h"
#include "evmomapl138_timer.h"
#include "evmomapl138_led.h"
#include "evmomapl138_dip.h"
#include "evmomapl138_gpio.h"
#include "evmomapl138_vpif.h"
#include "evmomapl138_spi.h"
#include "COECSL_edma3.h"
#include "COECSL_mcbsp.h"
#include "COECSL_registers.h"

#include "mcbsp_com.h"
#include "ColorVision.h"
#include "ColorLCD.h"
#include "sharedmem.h"
#include "LCDprintf.h"
#include "ladar.h"
#include "xy.h"
#include "MatrixMath.h"

#define FEETINONEMETER 3.28083989501312

extern EDMA3_CCRL_Regs *EDMA3_0_Regs;

volatile uint32_t index;

// test variables
extern float enc1;  // Left motor encoder
extern float enc2;  // Right motor encoder
extern float enc3;
extern float enc4;
extern float adcA0;  // ADC A0 - Gyro_X -400deg/s to 400deg/s  Pitch
extern float adcB0;  // ADC B0 - External ADC Ch4 (no protection circuit)
extern float adcA1;  // ADC A1 - Gyro_4X -100deg/s to 100deg/s  Pitch
extern float adcB1;  // ADC B1 - External ADC Ch1
extern float adcA2;  // ADC A2 -    Gyro_4Z -100deg/s to 100deg/s  Yaw
extern float adcB2;  // ADC B2 - External ADC Ch2
extern float adcA3;  // ADC A3 - Gyro_Z -400deg/s to 400 deg/s  Yaw
extern float adcB3;  // ADC B3 - External ADC Ch3
extern float adcA4;  // ADC A4 - Analog IR1
extern float adcB4;  // ADC B4 - USONIC1
extern float adcA5;  // ADC A5 -    Analog IR2
extern float adcB5;  // ADC B5 - USONIC2
extern float adcA6;  // ADC A6 - Analog IR3
extern float adcA7;  // ADC A7 - Analog IR4
extern float compass;
extern float switchstate;

//A* variables
char map[176]=
{   '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    'x', 'x', 'x', 'x', '0', '0', '0', 'x', 'x', 'x', 'x',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'   };


typedef struct{
    int r;      //in feet
    int c;      //in feet
    int x;
    int y;
    int tally;
    int f;
    int idx1;
    int idx2;
    int idx3;
    int hv; //horizontal 0 or vertical 1
} obstacle;

obstacle obs[57]={{2-1, 1-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {4-1, 1-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {6-1, 1-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {8-1, 1-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {10-1,1-1, 0, 0, 0, 0, 0, 0, 0, 0},

                  {2-1, 3-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {4-1, 3-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {6-1, 3-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {8-1, 3-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {10-1,3-1, 0, 0, 0, 0, 0, 0, 0, 0},

                  {2-1, 5-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {4-1, 5-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {6-1, 5-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {8-1, 5-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {10-1,5-1, 0, 0, 0, 0, 0, 0, 0, 0},


                  {2-1, 7-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {4-1, 7-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {6-1, 7-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {8-1, 7-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {10-1,7-1, 0, 0, 0, 0, 0, 0, 0, 0},


                  {2-1, 9-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {4-1, 9-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {6-1, 9-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {8-1, 9-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {10-1,9-1, 0, 0, 0, 0, 0, 0, 0, 0},


                  {2-1, 11-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {4-1, 11-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {6-1, 11-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {8-1, 11-1, 0, 0, 0, 0, 0, 0, 0, 0},
                  {10-1,11-1, 0, 0, 0, 0, 0, 0, 0, 0},



                  {3-1, 2-1, 0, 0, 0, 0, 0, 0, 0, 1},
                  {5-1, 2-1, 0, 0, 0, 0, 0, 0, 0, 1},
                  {7-1, 2-1, 0, 0, 0, 0, 0, 0, 0, 1},
                  {9-1, 2-1, 0, 0, 0, 0, 0, 0, 0, 1},
                  {11-1,2-1, 0, 0, 0, 0, 0, 0, 0, 1},

                  {3-1, 4-1, 0, 0, 0, 0, 0, 0, 0, 1},
                  {5-1, 4-1, 0, 0, 0, 0, 0, 0, 0, 1},
                  {7-1, 4-1, 0, 0, 0, 0, 0, 0, 0, 1},
                  {9-1, 4-1, 0, 0, 0, 0, 0, 0, 0, 1},
                  {11-1,4-1, 0, 0, 0, 0, 0, 0, 0, 1},

                  {3-1, 6-1, 0, 0, 0, 0, 0, 0, 0, 1},
                  {5-1, 6-1, 0, 0, 0, 0, 0, 0, 0, 1},
                  {7-1, 6-1, 0, 0, 0, 0, 0, 0, 0, 1},
                  {9-1, 6-1, 0, 0, 0, 0, 0, 0, 0, 1},
                  {11-1,6-1, 0, 0, 0, 0, 0, 0, 0, 1},

                  {3-1, 8-1, 0, 0, 0, 0, 0, 0, 0, 1},
                  {5-1, 8-1, 0, 0, 0, 0, 0, 0, 0, 1},
                  {7-1, 8-1, 0, 0, 0, 0, 0, 0, 0, 1},
                  {9-1, 8-1, 0, 0, 0, 0, 0, 0, 0, 1},
                  {11-1,8-1, 0, 0, 0, 0, 0, 0, 0, 1},

                  {3-1, 10-1, 0, 0, 0, 0, 0, 0, 0, 1},
                  {5-1, 10-1, 0, 0, 0, 0, 0, 0, 0, 1},
                  {7-1, 10-1, 0, 0, 0, 0, 0, 0, 0, 1},
                  {9-1, 10-1, 0, 0, 0, 0, 0, 0, 0, 1},
                  {11-1,10-1, 0, 0, 0, 0, 0, 0, 0, 1},

                  {11, 4, 0, 0, 0, 0, 0, 0, 0, 0},//left entrance
                  {11, 6, 0, 0, 0, 0, 0, 0, 0, 0}//right entrance

};
float weedx=-100.0, newweedx=-100.0, weedy=-100.0, newweedy=-100.0;
int labviewcolor=0, newlabviewcolor=0; //0 for blue 1 for pink
int weed_send[5];

int i,j;
int timer = 0;
int timecounter=0;
int newcentroidr=0;
int newcentroidc=0;
int newcentroid=0;
float newx=0, newy=0;


int loc0=-100, loc1=-100;

float col1;
float row1;



int weedcolor=0;
int rows=0, cols=0, rowe=3, cole=8;
int obs_send[57];
int astarrunning=0;
int astaridx=0;
float vref = 0;
float turn = 0;

int tskcount = 0;
char fromLinuxstring[LINUX_COMSIZE + 2];
char toLinuxstring[LINUX_COMSIZE + 2];

float LVvalue1 = 0;
float LVvalue2 = 0;
int new_LV_data = 0;

int newnavdata = 0;
float newvref = 0;
float newturn = 0;

extern sharedmemstruct *ptrshrdmem;

float x_pred[3][1] = {{0},{0},{0}};                 // predicted state

//more kalman vars
float B[3][2] = {{1,0},{1,0},{0,1}};            // control input model
float u[2][1] = {{0},{0}};          // control input in terms of velocity and angular velocity
float Bu[3][1] = {{0},{0},{0}}; // matrix multiplication of B and u
float z[3][1];                          // state measurement
float eye3[3][3] = {{1,0,0},{0,1,0},{0,0,1}};   // 3x3 identity matrix
float K[3][3] = {{1,0,0},{0,1,0},{0,0,1}};      // optimal Kalman gain
#define ProcUncert 0.0001
#define CovScalar 10
float Q[3][3] = {{ProcUncert,0,ProcUncert/CovScalar},
                 {0,ProcUncert,ProcUncert/CovScalar},
                 {ProcUncert/CovScalar,ProcUncert/CovScalar,ProcUncert}};   // process noise (covariance of encoders and gyro)
#define MeasUncert 1
float R[3][3] = {{MeasUncert,0,MeasUncert/CovScalar},
                 {0,MeasUncert,MeasUncert/CovScalar},
                 {MeasUncert/CovScalar,MeasUncert/CovScalar,MeasUncert}};   // measurement noise (covariance of LADAR)
float S[3][3] = {{1,0,0},{0,1,0},{0,0,1}};  // innovation covariance
float S_inv[3][3] = {{1,0,0},{0,1,0},{0,0,1}};  // innovation covariance matrix inverse
float P_pred[3][3] = {{1,0,0},{0,1,0},{0,0,1}}; // predicted covariance (measure of uncertainty for current position)
float temp_3x3[3][3];               // intermediate storage
float temp_3x1[3][1];               // intermediate storage
float ytilde[3][1];                 // difference between predictions

// deadreckoning
float vel1 = 0,vel2 = 0;
float vel1old = 0,vel2old = 0;
float enc1old = 0,enc2old = 0;

// SETTLETIME should be an even number and divisible by 3
#define SETTLETIME 6000
int settlegyro = 0;
float gyro_zero = 0;
float gyro_angle = 0;
float old_gyro = 0;
float gyro_drift = 0;
float gyro = 0;
int gyro_degrees = 0;
float gyro_radians = 0.0;
float gyro_x = 0,gyro_y = 0;
float gyro4x_gain = 1;
int safecounter=0;

int statePos = 0;   // index into robotdest
int robotdestSize = 10;  // number of positions to use out of robotdest
pose robotdest[10];  // array of waypoints for the robot

extern float newLADARdistance[LADAR_MAX_DATA_SIZE];  //in mm
extern float newLADARangle[LADAR_MAX_DATA_SIZE];        // in degrees
float LADARdistance[LADAR_MAX_DATA_SIZE];
float LADARangle[LADAR_MAX_DATA_SIZE];
extern pose ROBOTps;
extern pose LADARps;
extern float newLADARdataX[LADAR_MAX_DATA_SIZE];
extern float newLADARdataY[LADAR_MAX_DATA_SIZE];
float LADARdataX[LADAR_MAX_DATA_SIZE];
float LADARdataY[LADAR_MAX_DATA_SIZE];
extern int newLADARdata;

// Optitrack Variables
int trackableIDerror = 0;
int firstdata = 1;
volatile int new_optitrack = 0;
volatile float previous_frame = -1;
int frame_error = 0;
volatile float Optitrackdata[OPTITRACKDATASIZE];
pose OPTITRACKps;
float temp_theta = 0.0;
float tempOPTITRACK_theta = 0.0;
volatile int temp_trackableID = -1;
int trackableID = -1;
int errorcheck = 1;
int weeddetectcounter = 0;



//subfunctions
//A*
node_t neighbors[8];        //used to get a list of neighboring nodes
int currDist = 0;   //distance traveled from starting point
int pathLen = 0;            //used to keep track of number of points in reconstructed path
int pathRow[400];           //reconstructed path in reverse order
int pathCol[400];
char map[176];
int mapRowSize = 16;
int mapColSize = 11;
dictElem_t nodeTrack[176];      //to track location of nodes in the heap, and to track parents of nodes technically only needs to be mapRowSize*mapColsize long
heap_t openSet, closedSet;


//Vision Variables
extern int blueflag;
extern volatile float blue_object_x;
extern volatile float blue_object_y;
extern volatile int blue_numpels;
extern volatile float pink_object_x;
extern volatile float pink_object_y;
extern volatile int pink_numpels;

//Vision coordata transfer
extern volatile int new_coordata;
float blue_x = 0.0; //blue_x = blue_object_x
float blue_y = 0.0;
float pink_x = 0.0;
float pink_y = 0.0;
int blue_numberPix = 0; //number of pixels of the blue object
int pink_numberPix = 0;
float blue_distance = 0.0;
float pink_distance = 0.0;

int timeout = 0; //counting down time tracker
int blueweed = 0; //no of blue weeds sprayed
int pinkweed = 0;

int alreadyfound = 0;
typedef struct{
    int c;
    float x;
    float y;
} weed;

weed weedarray[5] = {{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0},{0, 0, 0}};
float speedgain = 1.2;
int weed_counter = 0;
int weed_index = -1;

int straightline(int ncol, int nrow){

    if ((pathCol[astaridx-2]==ncol) || (pathRow[astaridx-2]==nrow)){
        speedgain=2;
        return 1;
    }

    //speedgain=1;
    return 0;

}


//preconditions: rowCurr, colCurr, rowGoal, and colGoal are feasible locations in the matrix
//returns the distance between two points as the sum of the row and column differences "Manhattan" distance on a square grid
int heuristic(int rowCurr, int colCurr, int rowGoal, int colGoal)
{
    return (int)(sqrt(abs(rowGoal-rowCurr)*abs(rowGoal-rowCurr) + abs(colGoal-colCurr)*abs(colGoal-colCurr))+0.5);
}

//assumes that canTravel is called with neighboring points of a valid starting point
//precondition: row, col must be valid indices for a matrix
//returns 0 for false and 1 for true
//(row, col) is considered an unacceptable traveling point if it is represented as an 'x' in map, or if it is out of bounds of the map
int canTravel(int row, int col)
{
    //check for out of bounds
    int mapIdx = row*mapColSize + col;      //map data stored as 1d array
    if(mapIdx >= (mapRowSize*mapColSize) || mapIdx < 0)     //index out of bounds
        return 0;       //0 for cannot travel
    else if(col >= mapColSize || col < 0)           //too many columns, will result in a location in the next row
        return 0;
    else if(map[mapIdx] == 'x') //wall reached, cannot travel
        return 0;
    else
        return 1;
}

//parameters rowCurr and colCurr must be valid starting points
//returns the number of neighbors which are viable traveling points
//fills the node_t array called neighbors, with neighboring nodes to which the path can travel
//note: not using diagonal neighbors here, so there are only for possibilities for neighboring nodes
int getNeighbors(int rowCurr, int colCurr)
{
    node_t nodeToAdd;
    int numNeighbors = 0;
    int up=0;
    int down=0;
    int right=0;
    int left=0;
    if(canTravel(rowCurr-1, colCurr) == 1)  //can travel up
    {
        nodeToAdd.row = rowCurr-1;
        nodeToAdd.col = colCurr;
        nodeToAdd.diaflag=0;
        neighbors[numNeighbors] = nodeToAdd;
        numNeighbors++;
        up=1;
    }
    if(canTravel(rowCurr, colCurr-1) == 1)  //can travel left
    {
        nodeToAdd.row = rowCurr;
        nodeToAdd.col = colCurr-1;
        nodeToAdd.diaflag=0;
        neighbors[numNeighbors] = nodeToAdd;
        numNeighbors++;
        left=1;
    }
    if(canTravel(rowCurr,colCurr+1) == 1)   //can travel right
    {
        nodeToAdd.row = rowCurr;
        nodeToAdd.col = colCurr+1;
        nodeToAdd.diaflag=0;
        neighbors[numNeighbors] = nodeToAdd;
        numNeighbors++;
        right=1;
    }
    if(canTravel(rowCurr+1, colCurr) == 1)  //can travel down
    {
        nodeToAdd.row = rowCurr+1;
        nodeToAdd.col = colCurr;
        nodeToAdd.diaflag=0;
        neighbors[numNeighbors] = nodeToAdd;
        numNeighbors++;
        down=1;
    }
    nodeToAdd.diaflag=0;
    if (up && left && canTravel(rowCurr-1, colCurr-1)){//upleft
        nodeToAdd.row = rowCurr-1;
        nodeToAdd.col = colCurr-1;
        nodeToAdd.diaflag=1;
        neighbors[numNeighbors] = nodeToAdd;
        numNeighbors++;

    }
    nodeToAdd.diaflag=0;
    if (up && right && canTravel(rowCurr-1, colCurr+1)){
        nodeToAdd.row = rowCurr-1;
        nodeToAdd.col = colCurr+1;
        nodeToAdd.diaflag=1;
        neighbors[numNeighbors] = nodeToAdd;
        numNeighbors++;

    }
    nodeToAdd.diaflag=0;
    if (down && left && canTravel(rowCurr+1, colCurr-1)){
        nodeToAdd.row = rowCurr+1;
        nodeToAdd.col = colCurr-1;
        nodeToAdd.diaflag=1;
        neighbors[numNeighbors] = nodeToAdd;
        numNeighbors++;

    }
    nodeToAdd.diaflag=0;
    if (down && right && canTravel(rowCurr+1, colCurr+1)){
        nodeToAdd.row = rowCurr+1;
        nodeToAdd.col = colCurr+1;
        nodeToAdd.diaflag=1;
        neighbors[numNeighbors] = nodeToAdd;
        numNeighbors++;

    }



    return numNeighbors;
}

//helper function called inside astar to return the path from the goal point back to the starting point
//the list of points is put into the array pathRow and pathCol in reverse order, pathLen is the number of inserted points
void reconstructPath(int rowEnd, int colEnd, dictElem_t nodeTrack[])
{
    pathLen = 0;        //global variable, reset so start inserting at beginning of path array
    int currRow = rowEnd;
    int currCol = colEnd;
    while(currRow != 400 && currCol != 400)
    {
        //while node is not null "400", put it into path starting at end point
        pathRow[pathLen] = currRow;  //global array for Row
        pathCol[pathLen] = currCol;  //global array for Column
        pathLen++;
        //  printf("currPath: (%d, %d), %d\n", pathRow[pathLen-1], pathCol[pathLen-1], pathLen);
        int nodeTrackIdx = currRow*mapColSize+currCol;
        currRow = nodeTrack[nodeTrackIdx].parentRow;
        currCol = nodeTrack[nodeTrackIdx].parentCol;
        //  printf("next location: (%d, %d), %d\n", currRow, currCol, pathLen);
    }
    if (pathLen > 2) {
        astaridx=pathLen-2;  // Dan Block change from pathLen-1 to -2
    }else {
        astaridx=pathLen-1;
    }

    //  printf("done with reconstruction\n");
}

//path planning algorithm
//parameters rowStart, colStart, rowEnd, and colEnd must be valid locations
//they must be both within the indices of the matrix size and must not be points where barriers ('x') exist
void astar(int rowStart, int colStart, int rowEnd, int colEnd)
{
    //pseudo code instruction: initialize open and closed sets
    //initialize a dictionary to keep track of parents of nodes for easy reconstruction and for keeping track of
    //  heap indexes for easy retrieval from heaps
    //set the values of the dictionary, open and closed sets to be zero
    // so that no old values sitting in memory will produce weird results
    int resetNodeCnt;
    for(resetNodeCnt=0; resetNodeCnt<176; resetNodeCnt++)
    {
        nodeTrack[resetNodeCnt].heapId = ' ';
        nodeTrack[resetNodeCnt].heapIdx = 0;
        nodeTrack[resetNodeCnt].parentRow = 0;
        nodeTrack[resetNodeCnt].parentCol = 0;
    }

    startHeap(&openSet);
    startHeap(&closedSet);
    currDist = 0;
    node_t start;

    /* initialize a start node to be the starting position
        since this is the start node, it should have zero distance traveled from the start, the normal predicted distance to the goal,
        and the total distance is the sum of the distance traveled from the start and the distance to the goal.*/
    /* update the dictionary, use row and column location as a key in the dictionary,
        use 400 for null parent values and don't forget to indicate which heap, open or closed set, the node is being placed*/
    /* put starting node on open set*/

    start.row = rowStart;
    start.col = colStart;
    start.distTravelFromStart = 0;
    start.distToGoal = heuristic(rowStart,colStart,rowEnd,colEnd);
    start.totalDist = start.distTravelFromStart+start.distToGoal;
    int startIdx = (start.row*mapColSize)+start.col;
    (nodeTrack[startIdx]).heapId = 'o';     //o for open set
    nodeTrack[startIdx].parentRow = 400;    //use 400 as NULL, if 400, know reached beginning in reconstruction
    nodeTrack[startIdx].parentCol = 400;    //no parent value = 400 since out of bounds
    if(rowStart == rowEnd && colStart == colEnd)        //if start point is the end point, don't do anything more!!!
        return;
    push(start, &openSet, nodeTrack, mapColSize); // put start node on the openSet

    char goalFound = 'f'; //false

    /*while open set not empty and goal not yet found*/
    while(openSet.numElems > 0 && goalFound != 't')
    {

        /*find the node with the least total distance (f_score) on the open list, call it q (called minDistNode in code)*/
        node_t minDistNode = peek(openSet); //find node with least total cost, make that the current node

        /*set the current distance to the current node's distance traveled from the start.*/
        //1.  currDist is set to q's distance traveled from the Start.  Explain why this could be different from the Manhattan distance to the Start position
        //    This question is just asking for comments.
        //Because that there might be obstacles in the path calculated by manhattan distance, so the actual distance traveled from the Start might be greater than or equal to the Manhattan distance
        currDist = minDistNode.distTravelFromStart;

        (nodeTrack[(minDistNode.row*mapColSize)+minDistNode.col]).heapId = 'r';     //r for removed from any set

        //2.  pop q (which is currently the minimum) off which queue?
        // Choose one of these two lines of code
        // IF the Openset
        pop(&openSet, nodeTrack, mapColSize);               //we always pop from openset because the nodes in the closedset are already evaluated
        // IF closedSet
        //pop(&closedSet, nodeTrack, mapColSize);

        /*generate q's 4 neighbors*/
        // 3.  Pass q's row and col to getNeighbors
        int numNeighbors = getNeighbors(minDistNode.row, minDistNode.col);  //get list of neighbors
        //q is the current node, which is just poped from openset, minDistNode in our case
        /*for each neighbor*/
        int cnt = 0;
        for(cnt = 0; cnt<numNeighbors; cnt++)   //for each found neighbor
        {
            // 4. Just add comments here.  Find where the structure node_t is defined and inside commments here copy its definition for
            // viewing reference.
            // All the answer for 4. will be commented.
            node_t next = neighbors[cnt];

            /*          typedef struct node
            {
                int row;
                int col;
                int distTravelFromStart;
                int distToGoal;
                int totalDist;
                int pushOrder;      //order that element was pushed onto the heap
            } node_t;*/

            /*if neighbor is the goal, stop the search*/
            /*update the dictionary so this last node's parents are set to the current node*/
            if((next.row == rowEnd) && (next.col == colEnd))        //if neighbor is the goal, found the end, so stop the search
            {
                // 5.  set current neighbor's parents.  Set parentRow to q's row.  Set parentCol to q's col since q is the parent of this neighbor
                (nodeTrack[next.row*mapColSize+next.col]).parentRow = minDistNode.row;   //set goal node's parent position to current position
                (nodeTrack[next.row*mapColSize+next.col]).parentCol = minDistNode.col;
                goalFound = 't';
                break;
            }

            /*neighbor.distTravelFromStart (g) = q.distTravelFromStart + distance between neighbor and q which is always 1 when search just top left bottom right*/
            // 6.  Set this neighbor's distance traveled from the start.  Remember you have the variable "currDist" that is the distance of q to Start
            next.distTravelFromStart = currDist+1;
            if (next.diaflag){
                next.distTravelFromStart=next.distTravelFromStart+0.414;
            }

            /*neighbor.distToGoal (h) = distance from goal to neighbor, heuristic function  (estimated distance to goal)*/
            // 7.  Pass the correct parameters to "heuristic" to calculate the distance this neighbor is from the goal.
            //  Remember that we have the variables rowEnd and colEnd which are the grid coordinates of the goal
            next.distToGoal = heuristic(next.row, next.col, rowEnd, colEnd);

            /*neighbor.totalDist (f) = neighbor.distTravelFromStart + neighbor.distToGoal
                (total estimated distance as sum of distance traveled from start and distance to goal)*/
            // 8.  Find f, (totalDist) for this neighbor
            next.totalDist = next.distTravelFromStart+next.distToGoal;


            // 9.  Just comments for this question.
            // Explain in your own words (not copying the comments below) what the next 19 lines of C code are doing

            /*if a node with the same position as neighbor is in the OPEN list
                which has a lower total distance than neighbor, skip putting this neighbor onto the open set*/
            //check if node is on the open set already
            int nodeTrackIdx = (next.row*mapColSize)+next.col;
            char skipPush = 'f';
            if(nodeTrack[nodeTrackIdx].heapId == 'o')   //on the open set
            {
                int heapIndex = nodeTrack[nodeTrackIdx].heapIdx;
                node_t fromOpen = openSet.elems[heapIndex];
                if(fromOpen.totalDist <= next.totalDist)
                    skipPush = 't';     //skip putting this node onto the openset, a better one already on there
            }

            /*if a node with the same position as neighbor is in the CLOSED list
                which has a lower f than neighbor, skip putting this neighbor onto the open set*/
            else if(nodeTrack[nodeTrackIdx].heapId == 'c')      //on closed set
            {
                int heapIndex = nodeTrack[nodeTrackIdx].heapIdx;
                node_t fromClosed = closedSet.elems[heapIndex];
                if(fromClosed.totalDist <= next.totalDist)
                    skipPush = 't';     //skip putting this node onto the openset, already part of possible solution
            }

            /*if not skipping putting this node on the set, then push node onto the open set
                and update the dictionary to indicate the node is on the open set and set the parents of this node to the current node*/
            //(can't be an ordinary else to the things above because then it won't push onto the open set if already on open or closed set)
            if(skipPush != 't')
            {
                nodeTrack[nodeTrackIdx].heapId = 'o';       //mark in nodetrack that this is going onto the open set
                (nodeTrack[nodeTrackIdx]).parentRow = minDistNode.row;   //set neighbor's parent position to current position
                (nodeTrack[nodeTrackIdx]).parentCol = minDistNode.col;
                //10.  push this neighbor on which queue?
                // Choose one of these two lines of code
                // IF openSet
                push(next, &openSet, nodeTrack, mapColSize);
                // IF closedSet
                //push(next, &closedSet, nodeTrack, mapColSize);

            }
        }/* end for loop*/

        int nodeTrackIdx = minDistNode.row*mapColSize+minDistNode.col;
        nodeTrack[nodeTrackIdx].heapId = 'c';
        //11.  push q (current node) on which queue?
        // Choose one of these two lines of code
        // IF openSet
        //push(minDistNode, &openSet, nodeTrack, mapColSize);
        // IF closedSet
        push(minDistNode, &closedSet, nodeTrack, mapColSize);

    }  /*end while loop*/

    /*if a path was found from the start to the goal, then reconstruct the path*/
    if(goalFound == 't')
        // 12.  Pass the correct varaibles to "reconstructPath" in order for it to fill in the global arrays pathRow, pathCol
        //     and integer pathLen.  Note that the path is in reverse order in pathRow and pathCol.
        reconstructPath(rowEnd, colEnd, nodeTrack);
}

//SM

void runastar(void) {

    while(1) {
        SEM_pend(&SEM_astar,SYS_FOREVER);
        astar(rows, cols, rowe, cole);
        // copy path
        astarrunning = 0;
        if(!GET_ASTAR_COMMAND) {
            //For now, Update the shared variables that need to be sent for astar

            for (i=0;i<176;i++) {
                ptrshrdmem->sharedAstarMap[i] = map[i];
            }

            BCACHE_wb((void *)ptrshrdmem,sizeof(sharedmemstruct),EDMA3_CACHE_WAIT);
            SET_ASTAR_COMMAND;
        }

    }


}



pose UpdateOptitrackStates(pose localROBOTps, int * flag);


void ComWithLinux(void) {

    int i = 0;
    TSK_sleep(100);

    while(1) {

        BCACHE_inv((void *)ptrshrdmem,sizeof(sharedmemstruct),EDMA3_CACHE_WAIT);

        if (GET_DATA_FROM_LINUX) {

            if (newnavdata == 0) {
                newvref = ptrshrdmem->Floats_to_DSP[0];
                newturn = ptrshrdmem->Floats_to_DSP[1];
                newnavdata = 1;
            }

            CLR_DATA_FROM_LINUX;

        }

        if (GET_LVDATA_FROM_LINUX) {

            if (ptrshrdmem->DSPRec_size > 256) ptrshrdmem->DSPRec_size = 256;
            for (i=0;i<ptrshrdmem->DSPRec_size;i++) {
                fromLinuxstring[i] = ptrshrdmem->DSPRec_buf[i];
            }
            fromLinuxstring[i] = '\0';

            if (new_LV_data == 0) {
                sscanf(fromLinuxstring,"%f%f",&LVvalue1,&LVvalue2);
                new_LV_data = 1;
            }

            CLR_LVDATA_FROM_LINUX;

        }

        if ((tskcount%6)==0) {
            if (GET_LVDATA_TO_LINUX) {
                if (newcentroid){
                    row1 = newx;//newcentroidr[0];
                    col1 = newy;
                    loc0 = newcentroidr;
                    loc1 = newcentroidc;
                    weedx=newweedx;
                    weedy=newweedy;
                    labviewcolor=newlabviewcolor;
                    newcentroid=0;
                }
                // Default
                //ptrshrdmem->DSPSend_size = sprintf(toLinuxstring,"1.0 1.0 1.0 1.0");
                // you would do something like this
                //row1, col1, loc, color
                ptrshrdmem->DSPSend_size = sprintf(toLinuxstring,"%.3f %.3f %d %d %.3f %.3f %d ",row1, col1, loc0, loc1, weedx, weedy, labviewcolor);

                for (i=0;i<ptrshrdmem->DSPSend_size;i++) {
                    ptrshrdmem->DSPSend_buf[i] = toLinuxstring[i];
                }

                // Flush or write back source
                BCACHE_wb((void *)ptrshrdmem,sizeof(sharedmemstruct),EDMA3_CACHE_WAIT);

                CLR_LVDATA_TO_LINUX;

            }
        }

        if (GET_DATAFORFILE_TO_LINUX) {

            // This is an example write to scratch
            // The Linux program SaveScratchToFile can be used to write the
            // ptrshrdmem->scratch[0-499] memory to a .txt file.
            //          for (i=100;i<300;i++) {
            //              ptrshrdmem->scratch[i] = (float)i;
            //          }

            // Flush or write back source
            BCACHE_wb((void *)ptrshrdmem,sizeof(sharedmemstruct),EDMA3_CACHE_WAIT);

            CLR_DATAFORFILE_TO_LINUX;

        }

        tskcount++;
        TSK_sleep(40);
    }


}


/*
 *  ======== main ========
 */
Void main()
{
    col1=-100;
    row1=-100;

    int i = 0;
    for (i=0;i<400;i++){
        pathRow[i]=0;
        pathCol[i]=0;
    }
    for (i=0;i<5;i++){
        weed_send[i]=0;
    }

    for (i=0;i<57;i++){
        obs[i].x=obs[i].c-5;
        obs[i].y=11-obs[i].r;
        obs_send[i]=0;
        if ((obs[i].r%2)==0){           //row at even number, then the wall must be vertical
            obs[i].idx1=(obs[i].r)*11+obs[i].c;
            if (obs[i].r>1){
                obs[i].idx2=(obs[i].r-1)*11+obs[i].c;
            }
            if (obs[i].r<15){
                obs[i].idx3=(obs[i].r+1)*11+obs[i].c;

            }
        }else{                          //horizontal wall
            obs[i].idx1=(obs[i].r)*11+obs[i].c;
            if (obs[i].c>1){
                obs[i].idx2=(obs[i].r)*11+obs[i].c-1;
            }
            if (obs[i].c<10){
                obs[i].idx3=(obs[i].r)*11+obs[i].c+1;
            }
        }

    }
    // unlock the system config registers.
    SYSCONFIG->KICKR[0] = KICK0R_UNLOCK;
    SYSCONFIG->KICKR[1] = KICK1R_UNLOCK;

    SYSCONFIG1->PUPD_SEL |= 0x10000000;  // change pin group 28 to pullup for GP7[12/13] (LCD switches)

    // Initially set McBSP1 pins as GPIO ins
    CLRBIT(SYSCONFIG->PINMUX[1], 0xFFFFFFFF);
    SETBIT(SYSCONFIG->PINMUX[1], 0x88888880);  // This is enabling the McBSP1 pins

    CLRBIT(SYSCONFIG->PINMUX[16], 0xFFFF0000);
    SETBIT(SYSCONFIG->PINMUX[16], 0x88880000);  // setup GP7.8 through GP7.13
    CLRBIT(SYSCONFIG->PINMUX[17], 0x000000FF);
    SETBIT(SYSCONFIG->PINMUX[17], 0x00000088);  // setup GP7.8 through GP7.13


    //Rick added for LCD DMA flagging test
    GPIO_setDir(GPIO_BANK0, GPIO_PIN8, GPIO_OUTPUT);
    GPIO_setOutput(GPIO_BANK0, GPIO_PIN8, OUTPUT_HIGH);

    GPIO_setDir(GPIO_BANK0, GPIO_PIN0, GPIO_INPUT);
    GPIO_setDir(GPIO_BANK0, GPIO_PIN1, GPIO_INPUT);
    GPIO_setDir(GPIO_BANK0, GPIO_PIN2, GPIO_INPUT);
    GPIO_setDir(GPIO_BANK0, GPIO_PIN3, GPIO_INPUT);
    GPIO_setDir(GPIO_BANK0, GPIO_PIN4, GPIO_INPUT);
    GPIO_setDir(GPIO_BANK0, GPIO_PIN5, GPIO_INPUT);
    GPIO_setDir(GPIO_BANK0, GPIO_PIN6, GPIO_INPUT);

    GPIO_setDir(GPIO_BANK7, GPIO_PIN8, GPIO_OUTPUT);
    GPIO_setDir(GPIO_BANK7, GPIO_PIN9, GPIO_OUTPUT);
    GPIO_setDir(GPIO_BANK7, GPIO_PIN10, GPIO_OUTPUT);
    GPIO_setDir(GPIO_BANK7, GPIO_PIN11, GPIO_OUTPUT);
    GPIO_setDir(GPIO_BANK7, GPIO_PIN12, GPIO_INPUT);
    GPIO_setDir(GPIO_BANK7, GPIO_PIN13, GPIO_INPUT);

    GPIO_setOutput(GPIO_BANK7, GPIO_PIN8, OUTPUT_HIGH);
    GPIO_setOutput(GPIO_BANK7, GPIO_PIN9, OUTPUT_HIGH);
    GPIO_setOutput(GPIO_BANK7, GPIO_PIN10, OUTPUT_HIGH);
    GPIO_setOutput(GPIO_BANK7, GPIO_PIN11, OUTPUT_HIGH);

    CLRBIT(SYSCONFIG->PINMUX[13], 0xFFFFFFFF);
    SETBIT(SYSCONFIG->PINMUX[13], 0x88888811); //Set GPIO 6.8-13 to GPIOs and IMPORTANT Sets GP6[15] to /RESETOUT used by PHY, GP6[14] CLKOUT appears unconnected

#warn GP6.15 is also connected to CAMERA RESET This is a Bug in my board design Need to change Camera Reset to different IO.

    GPIO_setDir(GPIO_BANK6, GPIO_PIN8, GPIO_OUTPUT);
    GPIO_setDir(GPIO_BANK6, GPIO_PIN9, GPIO_OUTPUT);
    GPIO_setDir(GPIO_BANK6, GPIO_PIN10, GPIO_OUTPUT);
    GPIO_setDir(GPIO_BANK6, GPIO_PIN11, GPIO_OUTPUT);
    GPIO_setDir(GPIO_BANK6, GPIO_PIN12, GPIO_OUTPUT);
    GPIO_setDir(GPIO_BANK6, GPIO_PIN13, GPIO_INPUT);


    // on power up wait until Linux has initialized Timer1
    while ((T1_TGCR & 0x7) != 0x7) {
        for (index=0;index<50000;index++) {}  // small delay before checking again

    }

    USTIMER_init();

    // Turn on McBSP1
    EVMOMAPL138_lpscTransition(PSC1, DOMAIN0, LPSC_MCBSP1, PSC_ENABLE);

    // If Linux has already booted It sets a flag so no need to delay
    if ( GET_ISLINUX_BOOTED == 0) {
        USTIMER_delay(4*DELAY_1_SEC);  // delay allowing Linux to partially boot before continuing with DSP code
    }

    // init the us timer and i2c for all to use.
    I2C_init(I2C0, I2C_CLK_100K);
    init_ColorVision();
    init_LCD_mem(); // added rick

    EVTCLR0 = 0xFFFFFFFF;
    EVTCLR1 = 0xFFFFFFFF;
    EVTCLR2 = 0xFFFFFFFF;
    EVTCLR3 = 0xFFFFFFFF;

    init_DMA();
    init_McBSP();

    init_LADAR();

    CLRBIT(SYSCONFIG->PINMUX[1], 0xFFFFFFFF);
    SETBIT(SYSCONFIG->PINMUX[1], 0x22222220);  // This is enabling the McBSP1 pins

    CLRBIT(SYSCONFIG->PINMUX[5], 0x00FF0FFF);
    SETBIT(SYSCONFIG->PINMUX[5], 0x00110111);  // This is enabling SPI pins

    CLRBIT(SYSCONFIG->PINMUX[16], 0xFFFF0000);
    SETBIT(SYSCONFIG->PINMUX[16], 0x88880000);  // setup GP7.8 through GP7.13
    CLRBIT(SYSCONFIG->PINMUX[17], 0x000000FF);
    SETBIT(SYSCONFIG->PINMUX[17], 0x00000088);  // setup GP7.8 through GP7.13

    init_LCD();

    LADARps.x = 3.5/12; // 3.5/12 for front mounting
    LADARps.y = 0;
    LADARps.theta = 1;  // not inverted

    OPTITRACKps.x = 0;
    OPTITRACKps.y = 0;
    OPTITRACKps.theta = 0;

    for(i = 0;i<LADAR_MAX_DATA_SIZE;i++)
    { LADARdistance[i] = LADAR_MAX_READING; } //initialize all readings to max value.

    // ROBOTps will be updated by Optitrack during gyro calibration
    // TODO: specify the starting position of the robot
    ROBOTps.x = 0;          //the estimate in array form (useful for matrix operations)
    ROBOTps.y = 0;
    ROBOTps.theta = 0;  // was -PI: need to flip OT ground plane to fix this
    x_pred[0][0] = ROBOTps.x; //estimate in structure form (useful elsewhere)
    x_pred[1][0] = ROBOTps.y;
    x_pred[2][0] = ROBOTps.theta;

    // TODO: defined destinations that moves the robot around and outside the course
    robotdest[0].x = -5;    robotdest[0].y = -3;
    robotdest[1].x = 3; robotdest[1].y = 7;
    //middle of bottom
    robotdest[2].x = -3;     robotdest[2].y = 7;

    //outside the course
    robotdest[3].x = 5;        robotdest[3].y = -3;
    //back to middle
    robotdest[4].x = -4;     robotdest[4].y = 11;
    robotdest[5].x = 0;     robotdest[5].y = 11;
    robotdest[6].x = 4;     robotdest[6].y = 11;
    robotdest[7].x = 0;     robotdest[7].y = 11;
    robotdest[8].x = -2;     robotdest[8].y = -4;
    robotdest[9].x = 2;     robotdest[9].y = -4;

    // flag pins
    GPIO_setDir(IMAGE_TO_LINUX_BANK, IMAGE_TO_LINUX_FLAG, GPIO_OUTPUT);
    GPIO_setDir(OPTITRACKDATA_FROM_LINUX_BANK, OPTITRACKDATA_FROM_LINUX_FLAG, GPIO_OUTPUT);
    GPIO_setDir(DATA_TO_LINUX_BANK, DATA_TO_LINUX_FLAG, GPIO_OUTPUT);
    GPIO_setDir(DATA_FROM_LINUX_BANK, DATA_FROM_LINUX_FLAG, GPIO_OUTPUT);
    GPIO_setDir(DATAFORFILE_TO_LINUX_BANK, DATAFORFILE_TO_LINUX_FLAG, GPIO_OUTPUT);
    GPIO_setDir(LVDATA_FROM_LINUX_BANK, LVDATA_FROM_LINUX_FLAG, GPIO_OUTPUT);
    GPIO_setDir(LVDATA_TO_LINUX_BANK, LVDATA_TO_LINUX_FLAG, GPIO_OUTPUT);


    CLR_OPTITRACKDATA_FROM_LINUX;  // Clear = tell linux DSP is ready for new Opitrack data
    CLR_DATA_FROM_LINUX;  // Clear = tell linux that DSP is ready for new data
    CLR_DATAFORFILE_TO_LINUX;  // Clear = linux not requesting data
    SET_DATA_TO_LINUX;  // Set = put float array data into shared memory for linux
    SET_IMAGE_TO_LINUX;  // Set = put image into shared memory for linux
    CLR_LVDATA_FROM_LINUX;  // Clear = tell linux that DSP is ready for new LV data
    SET_LVDATA_TO_LINUX;  // Set = put LV char data into shared memory for linux

    // clear all possible EDMA 
    EDMA3_0_Regs->SHADOW[1].ICR = 0xFFFFFFFF;

    // Add your init code here
}


long timecount= 0;
int whichled = 0;
int robotstate = 1;
int visionstate = 0;
// This SWI is Posted after each set of new data from the F28335
void RobotControl(void) {

    int newOPTITRACKpose = 0;
    int i = 0;
    speedgain=1.5;

    //Vision Coordinates Data Transfer
    if (new_coordata==1){

        blue_x = blue_object_x;
        blue_y = blue_object_y;
        pink_x = pink_object_x;
        pink_y = pink_object_y;

        blue_numberPix = blue_numpels;
        pink_numberPix = pink_numpels;

        blue_distance = ((0.0046874*blue_y)*(0.0046874*blue_y)+(0.68131*blue_y)+39.509)/12.0;
        pink_distance = ((0.0046874*pink_y)*(0.0046874*pink_y)+(0.68131*pink_y)+39.509)/12.0;

        new_coordata = 0;
    }


    if (0==(timecount%1000)) {
        switch(whichled) {
        case 0:
            SETREDLED;
            CLRBLUELED;
            CLRGREENLED;
            whichled = 1;
            break;
        case 1:
            CLRREDLED;
            SETBLUELED;
            CLRGREENLED;
            whichled = 2;
            break;
        case 2:
            CLRREDLED;
            CLRBLUELED;
            SETGREENLED;
            whichled = 0;
            break;
        default:
            whichled = 0;
            break;
        }
    }

    if (GET_OPTITRACKDATA_FROM_LINUX) {

        if (new_optitrack == 0) {
            for (i=0;i<OPTITRACKDATASIZE;i++) {
                Optitrackdata[i] = ptrshrdmem->Optitrackdata[i];
            }
            new_optitrack = 1;
        }

        CLR_OPTITRACKDATA_FROM_LINUX;

    }

    if (new_optitrack == 1) {
        OPTITRACKps = UpdateOptitrackStates(ROBOTps, &newOPTITRACKpose);
        new_optitrack = 0;
    }

    // using 400deg/s gyro
    gyro = adcA3*3.0/4096.0;
    if (settlegyro < SETTLETIME) {
        settlegyro++;
        if (settlegyro < (SETTLETIME/3)) {
            // do nothing
        } else if (settlegyro < (2*SETTLETIME/3)) {
            gyro_zero = gyro_zero + gyro/(SETTLETIME/3);
        } else {
            gyro_drift += (((gyro-gyro_zero) + old_gyro)*.0005)/(SETTLETIME/3);
            old_gyro = gyro-gyro_zero;
        }
        if(settlegyro%500 == 0) {
            LCDPrintfLine(1,"Cal Gyro -- %.1fSecs", (float)(SETTLETIME - settlegyro)/1000.0 );
            LCDPrintfLine(2,"");
        }
        enc1old = enc1;
        enc2old = enc2;
        newOPTITRACKpose = 0;

        SetRobotOutputs(0,0,0,0,0,0,0,0,0,0);
    } else {

        gyro_angle = gyro_angle - ((gyro-gyro_zero) + old_gyro)*.0005 + gyro_drift;
        old_gyro = gyro-gyro_zero;
        gyro_radians = (gyro_angle * (PI/180.0)*400.0*gyro4x_gain);

        // Kalman filtering
        vel1 = (enc1 - enc1old)/(193.0*0.001);  // calculate actual velocities
        vel2 = (enc2 - enc2old)/(193.0*0.001);
        if (fabsf(vel1) > 10.0) vel1 = vel1old; // check for encoder roll-over should never happen
        if (fabsf(vel2) > 10.0) vel2 = vel2old;
        enc1old = enc1; // save past values
        enc2old = enc2;
        vel1old = vel1;
        vel2old = vel2;

        // Step 0: update B, u
        B[0][0] = cosf(ROBOTps.theta)*0.001;
        B[1][0] = sinf(ROBOTps.theta)*0.001;
        B[2][1] = 0.001;
        u[0][0] = 0.5*(vel1 + vel2);    // linear velocity of robot
        u[1][0] = (gyro-gyro_zero)*(PI/180.0)*400.0*gyro4x_gain;    // angular velocity in rad/s (negative for right hand angle)

        // Step 1: predict the state and estimate covariance
        Matrix3x2_Mult(B, u, Bu);                   // Bu = B*u
        Matrix3x1_Add(x_pred, Bu, x_pred, 1.0, 1.0); // x_pred = x_pred(old) + Bu
        Matrix3x3_Add(P_pred, Q, P_pred, 1.0, 1.0); // P_pred = P_pred(old) + Q
        // Step 2: if there is a new measurement, then update the state
        if (1 == newOPTITRACKpose) {
            newOPTITRACKpose = 0;
            z[0][0] = OPTITRACKps.x;    // take in the LADAR measurement
            z[1][0] = OPTITRACKps.y;
            // fix for OptiTrack problem at 180 degrees
            if (cosf(ROBOTps.theta) < -0.99) {
                z[2][0] = ROBOTps.theta;
            }
            else {
                z[2][0] = OPTITRACKps.theta;
            }
            // Step 2a: calculate the innovation/measurement residual, ytilde
            Matrix3x1_Add(z, x_pred, ytilde, 1.0, -1.0);    // ytilde = z-x_pred
            // Step 2b: calculate innovation covariance, S
            Matrix3x3_Add(P_pred, R, S, 1.0, 1.0);                          // S = P_pred + R
            // Step 2c: calculate the optimal Kalman gain, K
            Matrix3x3_Invert(S, S_inv);
            Matrix3x3_Mult(P_pred,  S_inv, K);                              // K = P_pred*(S^-1)
            // Step 2d: update the state estimate x_pred = x_pred(old) + K*ytilde
            Matrix3x1_Mult(K, ytilde, temp_3x1);
            Matrix3x1_Add(x_pred, temp_3x1, x_pred, 1.0, 1.0);
            // Step 2e: update the covariance estimate   P_pred = (I-K)*P_pred(old)
            Matrix3x3_Add(eye3, K, temp_3x3, 1.0, -1.0);
            Matrix3x3_Mult(temp_3x3, P_pred, P_pred);
        }   // end of correction step

        // set ROBOTps to the updated and corrected Kalman values.
        ROBOTps.x = x_pred[0][0];
        ROBOTps.y = x_pred[1][0];
        ROBOTps.theta = x_pred[2][0];

        // uses xy code to step through an array of positions

        //call Astar at the first 0.5s
        if (timecount == 250){
            //statePos = (statePos+1)%robotdestSize;
            timer = 0;
            if (robotdest[statePos].y>0){
                rowe=11-(int)(robotdest[statePos].y+0.5);
            }
            else{
                rowe=11-(int)(robotdest[statePos].y-0.5);
            }
            if (robotdest[statePos].x>0){
                cole=(int)(robotdest[statePos].x+0.5)+5;
            }
            else{
                cole=(int)(robotdest[statePos].x-0.5)+5;
            }
            // reastar with new statepos
            if(astarrunning==0) {

                SEM_post(&SEM_astar);
                astarrunning = 1;
            }
        }

        if (newLADARdata == 1) {
            newLADARdata = 0;
            for (i=0;i<228;i++) {
                LADARdistance[i] = newLADARdistance[i];
                LADARangle[i] = newLADARangle[i];
                LADARdataX[i] = newLADARdataX[i];
                LADARdataY[i] = newLADARdataY[i];
            }
            //obstacle detection part
            for (i=1; i<228;i=i+10){
                if ((LADARdataX[i]>-5.7) && (LADARdataX[i]<5.7) && (LADARdataY[i]>-0.3) && (LADARdataY[i]<10.3)){
                    for (j=0;j<57;j++){
                        if (((LADARdataX[i]-obs[j].x)*(LADARdataX[i]-obs[j].x)+(LADARdataY[i]-obs[j].y)*(LADARdataY[i]-obs[j].y))<0.0625){
                            obs[j].tally++;
                            //horizontal 0 vertical 1
                            if(((int)(ROBOTps.y+0.5) - obs[j].y >= 1) && (obs[j].hv == 0)){//robot is at the north side of wall and wall is horizontal
                                if(j == 14){ //south of this wall is left entrance
                                    obs[55].tally++;
                                }else if(j == 19){ //south of this wall is right entrance
                                    obs[56].tally++;
                                }else if((obs[i].r != 9)&&(j+1<57)){
                                    obs[j+1].tally++; //rest of the wall we predict that the south of it is also a wall
                                }
                            }else if(((int)(ROBOTps.y+0.5) - obs[j].y <= -1) && (obs[j].hv == 0)){//robot is at the south side of wall and wall is horizontal
                                if(j == 55){ //south of this wall is left entrance
                                    obs[14].tally++;
                                }else if(j == 56){ //south of this wall is right entrance
                                    obs[19].tally++;
                                }else if((obs[j].r != 1)&&(j-1>=0)){ //if the wall is in first row, do nothing
                                    obs[j-1].tally++; //rest of the wall we predict that the north of it is also a wall
                                }
                            }else if((ROBOTps.x - (obs[j].x*1.0) < -1) && (obs[j].hv == 1)){//robot is at the west side of the wall and wall is vertical
                                if((obs[j].c != 9)&&(j+5<57)){ //if not the rightmost column
                                    //we predict that the right of it is also a wall
                                    obs[j+5].tally++;
                                }
                            }else if((ROBOTps.x - (obs[j].x*1.0) >= 1) && (obs[j].hv == 1)){//robot is at the east side of the wall and wall is vertical
                                if((obs[j].c != 1)&&(j-5>=0)){
                                    obs[j-5].tally++;
                                }
                            }
                            //above cases are used to predict the other side of a wall

                        }
                        if (obs[j].tally>10 && obs[j].f==0){
                            obs[j].f=1;


                        }
                    }
                }
            }
            for(i = 0; i < 57; i++){
                //these cases below are used to predict other walls when two of the walls are present in a square
                if((obs[i].hv == 0) && (obs[i].r != 11) && (obs[i].f == 1)){ //if a horizontal wall that is not a entrance
                    //this wall should not be in row 1 or entrance
                    //                    if((obs[i].r != 1) && (obs[i-1].f == 1)){ //if north of it is also a wall
                    //                        //here we predict that a square is formed
                    //                        if(obs[i].c != 10){
                    //                            obs[i+29].f = 1;
                    //                        }
                    //                        if(obs[i].c != 0){
                    //                            obs[i+24].f = 1;
                    //                        }
                    //                    }else if((obs[i].r != 9) && (obs[i+1].f == 1)){ //if south of this wall is a wall (should not be in row9)
                    //                        if(obs[i].c != 0){
                    //                            obs[i+25].f = 1;
                    //                        }
                    //                        if(obs[i].c != 10){
                    //                            obs[i+30].f = 1;
                    //                        }
                    //                    }
                }else if((obs[i].hv ==1) && (obs[i].f == 1) && (obs[i].r != 10)){ //if a vertical wall
                    //                    if((obs[i].c != 1) && (obs[i-5].f == 1)){
                    //                        //if not the leftmost wall of left of it is also a wall
                    //                        obs[i-30].f = 1;
                    //                        obs[i-29].f = 1;
                    //                    }else if((obs[i].c != 9) && (obs[i+5].f == 1)){
                    //                        obs[i-25].f = 1;
                    //                        obs[i-24].f = 1;
                    //                    }
                }else if((obs[i].r == 11) && (obs[i].c == 4) && (obs[i].f == 1)){//left entrance is a wall
                    if(obs[14].f == 1){
                        obs[39].f = 1;
                        obs[44].f = 1;
                    }
                }else if((obs[i].r == 11) && (obs[i].c == 6) && (obs[i].f == 1)){//right entrance is a wall
                    if(obs[19].f == 1){
                        obs[44].f = 1;
                        obs[49].f = 1;
                    }
                }else if((obs[i].hv ==1) && (obs[i].c == 1) && (obs[i].f == 1) && (obs[i+5].f != 1)){
                    //                                        if((i != 34) && (i-29>=0)){
                    //                                            obs[i-29].f = 1;
                    //                                        }
                    //                                        if(i-30>=0){
                    //                                            obs[i-30].f = 1;
                    //                                        }
                }else if((obs[i].hv ==1) && (obs[i].c == 9) && (obs[i].f == 1) && (obs[i-5].f != 1)){
                    //                                        if((i != 54) && (i-24>=0)){
                    //                                            obs[i-24].f = 1;
                    //                                        }
                    //                                        if(i-25>=0){
                    //                                            obs[i-25].f = 1;
                    //                                        }
                }
            }

            //edge cases
            if((obs[14].f == 1) && (obs[55].f == 1)){
                obs[39].f = 1;
                obs[44].f = 1;
            }else if((obs[19].f == 1) && (obs[56].f == 1)){
                obs[49].f = 1;
                obs[44].f = 1;
            }else if((obs[49].f == 1) && (obs[54].f == 1)){
                obs[24].f = 1;
            }else if((obs[34].f == 1) && (obs[39].f == 1)){
                obs[9].f = 1;
            }else if((obs[29].f == 1) && (obs[28].f != 1)){
                obs[54].f = 1;
            }else if((obs[4].f == 1) && (obs[3].f != 1)){
                obs[34].f = 1;
            }else if((obs[9].f == 1) && (obs[8].f != 1)){
                obs[34].f = 1;
                obs[39].f = 1;
            }else if((obs[24].f == 1) && (obs[23].f != 1)){
                obs[49].f = 1;
                obs[54].f = 1;
            }else if((obs[30].f == 1) && (obs[35].f != 1)){
                obs[0].f = 1;
                obs[1].f = 1;
            }else if((obs[31].f == 1) && (obs[36].f != 1)){
                obs[1].f = 1;
                obs[2].f = 1;
            }else if((obs[32].f == 1) && (obs[37].f != 1)){
                obs[2].f = 1;
                obs[3].f = 1;
            }else if((obs[33].f == 1) && (obs[38].f != 1)){
                obs[3].f = 1;
                obs[4].f = 1;
            }else if((obs[34].f == 1) && (obs[39].f != 1)){
                obs[4].f = 1;
            }
            //if there is a new obstacle, recall Astar

        }

        if (ROBOTps.y>0){
            rows=11-(int)(ROBOTps.y+0.5);
        }
        else{
            rows=11-(int)(ROBOTps.y-0.5);
        }
        if (ROBOTps.x>0){
            cols=(int)(ROBOTps.x+0.5)+5;
        }
        else{
            cols=(int)(ROBOTps.x-0.5)+5;
        }


        if (newcentroid==0){

            newx=ROBOTps.x;
            newy=ROBOTps.y;

            int break_loop = 0;
            if (weed_index>=0){
                if (weed_send[weed_index]==0){
                    newweedx=weedarray[weed_index].x;
                    newweedy=weedarray[weed_index].y;
                    newlabviewcolor=weedarray[weed_index].c;
                    weed_send[weed_index]=1;
                }else {
                    newweedx=-100;
                    newweedy=-100;
                }
            }

            for (i=0;i<57;i++){
                if((obs[i].f==1) && (obs_send[i]==0)&& (break_loop==0)){
                    newcentroidc = obs[i].c;
                    newcentroidr = obs[i].r;
                    obs_send[i]=1;
                    break_loop=1;
                    map[obs[i].idx1]='x';
                    map[obs[i].idx2]='x';
                    map[obs[i].idx3]='x';
                    map[0]='0';
                    if (astarrunning==0){
                        if (robotdest[statePos].y>0){
                            rowe=11-(int)(robotdest[statePos].y+0.5);
                        }
                        else{
                            rowe=11-(int)(robotdest[statePos].y-0.5);
                        }
                        if (robotdest[statePos].x>0){
                            cole=(int)(robotdest[statePos].x+0.5)+5;
                        }
                        else{
                            cole=(int)(robotdest[statePos].x-0.5)+5;
                        }
                        SEM_post(&SEM_astar);
                        astarrunning=1;
                    }

                }

            }
            if(break_loop==0) {
                newcentroidc = -100;
                newcentroidr = -100;
            }


            newcentroid=1;
        }

        //        int check = 0;
        //        j = 3;
        //        if( j-5 >=0 ) {
        //            check = 1;
        //        }
        if ((timecount%200)==0) {
            //LCDPrintfLine(1,"x:%.2f,y:%.2f",ROBOTps.x,ROBOTps.y);
            //LCDPrintfLine(1,"r:%d,c:%d s:%d",pathRow[astaridx], pathCol[astaridx],statePos);
            LCDPrintfLine(1,"r:%.1f,c:%.1f %d",weedarray[weed_index].x, weedarray[weed_index].y,weed_index);
            LCDPrintfLine(2,"p%d b%d r%d v%d",pinkweed,blueweed,robotstate, visionstate);
            //LCDPrintfLine(2,"%.1f",blue_x);

        }
        if (astarrunning){
            vref=0;
            turn=0;
        }


        //Vision Algorithm
        switch(robotstate)  {

        case 1:
            timecounter=0;
            // leave vref and turn equal to wallfollow
            if(astarrunning==0 && timer>1000) {
                while(  ((ROBOTps.y<-0.9)&& (astaridx>0) && (pathRow[astaridx]>12))      ){//we can ignore points
                    astaridx = astaridx -1;
                }

                float x_des = (float)(pathCol[astaridx]-5.0);
                float y_des =  (float)(11.0-pathRow[astaridx]);



                if( xy_control(&vref, &turn, 1.0, ROBOTps.x, ROBOTps.y, x_des,y_des, ROBOTps.theta, 0.3, 0.6))
                {
                    if (astaridx > 0) {
                        astaridx--;          //reverse order

                    }
                    else {
                        if (statePos==9){
                            robotstate=3;
                        }else{

                            statePos = (statePos+1)%robotdestSize;
                        }
                        timer = 0;
                        if (robotdest[statePos].y>0){
                            rowe=11-(int)(robotdest[statePos].y+0.5);
                        }
                        else{
                            rowe=11-(int)(robotdest[statePos].y-0.5);
                        }
                        if (robotdest[statePos].x>0){
                            cole=(int)(robotdest[statePos].x+0.5)+5;
                        }
                        else{
                            cole=(int)(robotdest[statePos].x-0.5)+5;
                        }
                        // reastar with new statepos
                        if(astarrunning==0) {

                            SEM_post(&SEM_astar);
                            astarrunning = 1;
                        }
                    }
                }
            }
            timer++;


            if (timeout > 0) {
                timeout--;
            } else {

                //vision algorithm
                if ( (blue_numberPix > 60) && (blue_distance < 40) && (blueweed < 3) && (ROBOTps.y>0) && (pinkweed+blueweed<5)){
                    speedgain=1;
                    turn = (0 - blue_x)*0.05;
                    if(abs(blue_x)<10){
                        timeout = 1000;
                        float pred_x = ROBOTps.x + blue_distance * cosf(ROBOTps.theta);
                        float pred_y = ROBOTps.y + blue_distance * sinf(ROBOTps.theta);
                        alreadyfound = 0;
                        speedgain=1.5;
                        for(i = 0; i <= weed_index; i++){
                            float distance = (pred_x-weedarray[i].x)*(pred_x-weedarray[i].x)+(pred_y-weedarray[i].y)*(pred_y-weedarray[i].y);
                            if((distance<1) && (weedarray[i].c==0)){
                                //this case means that the weed is already detected
                                alreadyfound = 1;
                                //break;
                            }
                        }
                        if(!alreadyfound){
                            if(weed_index < 4){
                                weed_index++;
                            }
                            if(weed_counter < 5){
                                weed_counter++;
                            }
                            weedarray[weed_index].x = pred_x;
                            weedarray[weed_index].y = pred_y;
                            weedarray[weed_index].c = 0; //0 represents blue
                            blueweed++;
                            safecounter=0;
                            robotstate = 2; //go to weed
                        }else{
                            robotstate = 1;
                            //break;
                        }
                        weeddetectcounter = 0;
                    }
                    weeddetectcounter++;
                }

                if ( (pink_numberPix > 60) && (pink_distance < 40) && (pinkweed < 3)&& (ROBOTps.y>0) && (pinkweed+blueweed<5) ){
                    speedgain=1;
                    turn = (0 - pink_x)*0.05;
                    if(abs(pink_x)<10){
                        timeout = 1000;
                        float pred_x = ROBOTps.x + pink_distance * cosf(ROBOTps.theta);
                        float pred_y = ROBOTps.y + pink_distance * sinf(ROBOTps.theta);
                        alreadyfound = 0;
                        speedgain=1.5;
                        for(i = 0; i <= weed_index; i++){
                            float distance = (pred_x-weedarray[i].x)*(pred_x-weedarray[i].x)+(pred_y-weedarray[i].y)*(pred_y-weedarray[i].y);
                            if((distance<1) && (weedarray[i].c==1)){
                                //this case means that the weed is already detected
                                alreadyfound = 1;
                                break;
                            }
                        }
                        if(!alreadyfound){
                            pinkweed++;
                            if(weed_index < 4){
                                weed_index++;
                            }
                            if(weed_counter < 5){
                                weed_counter++;
                            }
                            weedarray[weed_index].x = pred_x;
                            weedarray[weed_index].y = pred_y;
                            weedarray[weed_index].c = 1; //0 represents blue
                            safecounter=0;
                            robotstate = 2; //go to weed
                        }else{
                            robotstate = 1;
                            break;
                        }
                        weeddetectcounter = 0;
                    }
                    weeddetectcounter++;
                }

            }

            break;
        case 2:
            safecounter++;
            //vref = 0.0;
            //turn = 0.0;

            /*            if ((timecount%200)==0) {
                //LCDPrintfLine(1,"x:%.2f,y:%.2f",ROBOTps.x,ROBOTps.y);
                LCDPrintfLine(1,"%d %d %d",pinkweed,blueweed,weed_counter);
                LCDPrintfLine(2,"%d %.1f %.1f",weed_index,weedarray[weed_index].x,weedarray[weed_index].y);
            }*/

            if ((weedarray[weed_index].x<-5.5) || (weedarray[weed_index].x>5.5) || (weedarray[weed_index].y<0.5) || (weedarray[weed_index].y>11.5) || safecounter>6000){
                robotstate=1;
                break;

            }
            if (xy_control(&vref, &turn, 1.0, ROBOTps.x, ROBOTps.y, weedarray[weed_index].x,weedarray[weed_index].y, ROBOTps.theta, 0.15, 0.25)){
                timecounter++;
                vref=0;
                //if back distance
                if (timecounter>1000){
                    timecounter=0;


                    if (robotdest[statePos].y>0){
                        rowe=11-(int)(robotdest[statePos].y+0.5);
                    }
                    else{
                        rowe=11-(int)(robotdest[statePos].y-0.5);
                    }
                    if (robotdest[statePos].x>0){
                        cole=(int)(robotdest[statePos].x+0.5)+5;
                    }
                    else{
                        cole=(int)(robotdest[statePos].x-0.5)+5;
                    }
                    // reastar with new statepos
                    if(astarrunning==0) {

                        SEM_post(&SEM_astar);
                        astarrunning = 1;
                    }
                    vref=1;
                    robotstate=1;
                }
            }

            break;
        case 3:
            speedgain=0;
            break;
        default:
            break;

        }
        if ((ROBOTps.y<0) && (robotstate!=3)){
            speedgain=3.5;
        }

        SetRobotOutputs(speedgain*vref,turn,2+3*(blueweed+1),2+3*(pinkweed+1),0,0,0,0,0,0);

        timecount++;
    }
}

pose UpdateOptitrackStates(pose localROBOTps, int * flag) {

    pose localOPTITRACKps;

    // Check for frame errors / packet loss
    if (previous_frame == Optitrackdata[OPTITRACKDATASIZE-1]) {
        frame_error++;
    }
    previous_frame = Optitrackdata[OPTITRACKDATASIZE-1];

    // Set local trackableID if first receive data
    if (firstdata){
        //trackableID = (int)Optitrackdata[OPTITRACKDATASIZE-1]; // removed to add new trackableID in shared memory
        trackableID = Optitrackdata[OPTITRACKDATASIZE-2];
        firstdata = 0;
    }

    // Check if local trackableID has changed - should never happen
    if (trackableID != Optitrackdata[OPTITRACKDATASIZE-2]) {
        trackableIDerror++;
        // do some sort of reset(?)
    }

    // Save position and yaw data
    if (isnan(Optitrackdata[0]) != 1) {  // this checks if the position data being received contains NaNs
        // check if x,y,yaw all equal 0.0 (almost certainly means the robot is untracked)
        if ((Optitrackdata[0] != 0.0) && (Optitrackdata[1] != 0.0) && (Optitrackdata[2] != 0.0)) {
            // save x,y
            // adding 2.5 so everything is shifted such that optitrack's origin is the center of the arena (while keeping all coordinates positive)
            // This was the old way for Optitrack coordinates
            //localOPTITRACKps.x = Optitrackdata[0]*FEETINONEMETER; // was 2.5 for size = 5
            //localOPTITRACKps.y = -1.0*Optitrackdata[1]*FEETINONEMETER+4.0;

            // This is the new coordinates for Motive
            localOPTITRACKps.x = -1.0*Optitrackdata[0]*FEETINONEMETER;
            localOPTITRACKps.y = Optitrackdata[1]*FEETINONEMETER+4.0;

            // make this a function
            temp_theta = fmodf(localROBOTps.theta,(float)(2*PI));//(theta[trackableID]%(2*PI));
            tempOPTITRACK_theta = Optitrackdata[2];
            if (temp_theta > 0) {
                if (temp_theta < PI) {
                    if (tempOPTITRACK_theta >= 0.0) {
                        // THETA > 0, kal in QI/II, OT in QI/II
                        localOPTITRACKps.theta = ((int)((localROBOTps.theta)/(2*PI)))*2.0*PI + tempOPTITRACK_theta*2*PI/360.0;
                    } else {
                        if (temp_theta > (PI/2)) {
                            // THETA > 0, kal in QII, OT in QIII
                            localOPTITRACKps.theta = ((int)((localROBOTps.theta)/(2*PI)))*2.0*PI + PI + (PI + tempOPTITRACK_theta*2*PI/360.0);
                        } else {
                            // THETA > 0, kal in QI, OT in QIV
                            localOPTITRACKps.theta = ((int)((localROBOTps.theta)/(2*PI)))*2.0*PI + tempOPTITRACK_theta*2*PI/360.0;
                        }
                    }
                } else {
                    if (tempOPTITRACK_theta <= 0.0) {
                        // THETA > 0, kal in QIII, OT in QIII
                        localOPTITRACKps.theta = ((int)((localROBOTps.theta)/(2*PI)))*2.0*PI + PI + (PI + tempOPTITRACK_theta*2*PI/360.0);
                    } else {
                        if (temp_theta > (3*PI/2)) {
                            // THETA > 0, kal in QIV, OT in QI
                            localOPTITRACKps.theta = ((int)((localROBOTps.theta)/(2*PI)))*2.0*PI + 2*PI + tempOPTITRACK_theta*2*PI/360.0;
                        } else {
                            // THETA > 0, kal in QIII, OT in QII
                            localOPTITRACKps.theta = (floorf((localROBOTps.theta)/((float)(2.0*PI))))*2.0*PI + tempOPTITRACK_theta*2*PI/360.0;
                        }
                    }
                }
            } else {
                if (temp_theta > -PI) {
                    if (tempOPTITRACK_theta <= 0.0) {
                        // THETA < 0, kal in QIII/IV, OT in QIII/IV
                        localOPTITRACKps.theta = ((int)((localROBOTps.theta)/(2*PI)))*2.0*PI + tempOPTITRACK_theta*2*PI/360.0;
                    } else {
                        if (temp_theta < (-PI/2)) {
                            // THETA < 0, kal in QIII, OT in QII
                            localOPTITRACKps.theta = ((int)((localROBOTps.theta)/(2*PI)))*2.0*PI - PI + (-PI + tempOPTITRACK_theta*2*PI/360.0);
                        } else {
                            // THETA < 0, kal in QIV, OT in QI
                            localOPTITRACKps.theta = ((int)((localROBOTps.theta)/(2*PI)))*2.0*PI + tempOPTITRACK_theta*2*PI/360.0;
                        }
                    }
                } else {
                    if (tempOPTITRACK_theta >= 0.0) {
                        // THETA < 0, kal in QI/II, OT in QI/II
                        localOPTITRACKps.theta = ((int)((localROBOTps.theta)/(2*PI)))*2.0*PI - PI + (-PI + tempOPTITRACK_theta*2*PI/360.0);
                    } else {
                        if (temp_theta < (-3*PI/2)) {
                            // THETA < 0, kal in QI, OT in QIV
                            localOPTITRACKps.theta = ((int)((localROBOTps.theta)/(2*PI)))*2.0*PI - 2*PI + tempOPTITRACK_theta*2*PI/360.0;
                        } else {
                            // THETA < 0, kal in QII, OT in QIII
                            localOPTITRACKps.theta = ((int)((localROBOTps.theta)/(2*PI)))*2.0*PI + tempOPTITRACK_theta*2*PI/360.0;
                        }
                    }
                }
            }
            *flag = 1;
        }
    }
    return localOPTITRACKps;
}


