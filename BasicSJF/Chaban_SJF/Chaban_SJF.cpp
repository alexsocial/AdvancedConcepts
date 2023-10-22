/**************************************************************************************/
//Alex Chaban
//Professor Sorgente
//COP 4610-003
//Due 3/29/2022
//SJF NON-PREEMPTIVE Module
//Description: This project simulates what an Operating System experiences
// when using explicitly non-preemptive Shortest Job First scheduling
// using nine processes with a set of CPU and I/O times.
//Code WILL be tested originally in Visual Studio 2022 as a Console App
//AND online at https://www.onlinegdb.com/online_c++_compiler.
//This is as organized as best as I could at the time.
//*************************************************************************************/



//Encountered a problem using <bits/stdc++.h> alone, so I'm just going to implement fstream,iostream, etc. for my main functions.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#pragma once
using namespace std;

/*
Before starting(note for self):
Step 1: 
    Use an array of struct objects for the processes P1-P9 containing an array of their arrival (CPU) times, burst (i/o) times, and position of arrays.
Step 2:
    Create function swap in case of usage for arrival time switching for the SJF algorithm.
Step 3:
    Arrange arrival times to where it properly calculates the shortest job every time.
Step 4:
    Calculate times with all arrival times and burst times.
Step 5:
    Use main for testing.
*/

//Global Variables
int pCount = 9; //Used in algorithm for how many processes there are for looping
int totTime = 0; //Tells the time in the algorithm
int tEpoch = 0; //Amount of times the epoch ran.
int fEpoch = 0; //Amount of times the epoch was idle.

//*************************************************************************************
//Name:	Structure
//Description: Creates a structure for the SJF algorithm.
//*************************************************************************************
struct Process
{
    int id = 0; //Process ID
    int rTime = 0; //Remaining time in I/O
    vector<int> bTimes; //I/O times
    vector<int> aTimes; //CPU times
    int pos = 0; //Position in arrays
    bool cool = false; //Determines if process is on cooldown
    bool finished = false; //Final determiner for if program is over.
    int wTime = 0; //Waiting time
    int tTime = 0; //Turnabout time
    int eTime = 0; //Response time
    bool firstTime = false; //Checks for response time.
};

//*************************************************************************************
//Name:	Swap
//Condition: Requires two int pointers.
//Description: Swaps two integers memory locations.
//*************************************************************************************
void swap(Process* a, Process* b)
{
    Process temp = *a;
    *a = *b;
    *b = temp;
}

//*************************************************************************************
//Name:	Arrange Arrival Function (Non-Recursive)
//Condition: Requires a Process array and the size of it.
//Description: Arranges the process order based on arrival times recursively.
//*************************************************************************************

void arrivalQueue(Process P[])
{
    for (int i = 0; i < pCount - 1; i++)
    {
        int pos1 = P[i].pos;
        int pos2 = P[i + 1].pos;
        if (P[i].aTimes[pos1] == P[i + 1].aTimes[pos2] && P[i].id > P[i + 1].id) //Making sure processes are in numerical order!!
        {
            swap(P[i], P[i + 1]);
        }
    }
}

//*************************************************************************************
//Name:	Arrange Arrival Function (Recursive)
//Condition: Requires a Process array and the size of it.
//Description: Arranges the process order based on arrival times recursively.
//*************************************************************************************

void arrivalQueue(Process P[], int size)
{
    if (size == 0) //Breaker for the recursion
    {
        return;
    }


    for (int i = 0; i < size - 1; i++) //Sorts smallest to largest
    {
        int pos1 = P[i].pos;
        int pos2 = P[i + 1].pos; //Takes the positions of the two Processes, as to verify what spot in the table they are.
        if (P[i].aTimes[pos1] > P[i + 1].aTimes[pos2]) //Basic swap if prev value is larger.
        {
            swap(P[i], P[i + 1]);
        }
    }

    arrivalQueue(P, (size - 1));
}




//*************************************************************************************
//Name:	Queue Process
//Condition: Requires a Process array.
//Description: Organizes the numerical order of the processes
//Meant to be looped in main function.
//*************************************************************************************

void queueProcess(Process P[])
{
    Process Set; //Takes the first non-cooldown process in the queue.
    int thePos = 0; //temp position
    bool idleCheck = true;
    int tempTime = 0; //Used to track waiting time amongst function.
    for (int i = 0; i < pCount; i++) //Failsafe to prevent on cooldown processes.
    {
        if (P[i].cool == false && P[i].finished == false)
        {
            Set = P[i]; //Makes main finder much easier to use.
            thePos = i; //Sets thePos to the current position in the array before it has to resort.
            if (Set.firstTime == false)
            {
                P[thePos].firstTime = true;
                P[thePos].eTime = totTime;
            }
            idleCheck = false;
            break;
        }
    }
    if (idleCheck == true)
    {
        thePos = pCount;
        fEpoch += 1;
    }
        
        

    //The Output
    cout << "Current Time: " << totTime << endl;
    if (idleCheck == true)
    {
        cout << "Now running: [idle]" << endl;
    }
    else
    {
        cout << "Now running: P" << Set.id << endl;
        cout << "Current Burst for P" << Set.id << ": " << Set.aTimes[Set.pos] << endl;
    }
    
    cout << "......................................................\n" << endl;

    cout << "Ready Queue:\t\tProcess\t\tBurst" << endl; //Will print READY if not on I/O cooldown
    bool rdy = false;
    for (int i = thePos + 1; i < pCount; i++)
    {
        if (P[i].cool == false && P[i].finished == false)
        {
            int pos1 = P[i].pos;
            cout << "\t\t\tP" << P[i].id << "\t\t" << P[i].aTimes[pos1] << endl;
            rdy = true;
        }
    }
    if (rdy == false)
        cout << "\t\t\t[empty]" << endl;

    cout << "......................................................\n" << endl;

    cout << "Now in I/O:\t\tProcess\t\tRemaining I/O Time" << endl; //Will print COOLDOWN if on I/O cooldown
    rdy = false;
    for (int i = 0; i < pCount; i++)
    {
        if (P[i].cool == true)
        {
            cout << "\t\t\tP" << P[i].id << "\t\t" << P[i].rTime << endl;
            rdy = true;
        }
    }
    if (rdy == false)
        cout << "\t\t\t[empty]" << endl;

    cout << "......................................................\n" << endl;

    cout << "Completed:" << endl; //If ALL cpu and i/o times finish for a process, it will be complete
    rdy = false;
    for (int i = 0; i < pCount; i++)
    {
        if (P[i].finished == true)
        {
            cout << "P" << P[i].id << ", ";
            rdy = true;
        }
    }
    cout << "\n" << endl;
    if (rdy == false)
        cout << "[empty]" << endl;

    cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n" << endl;

    //Adding the time, and changing the cooldown, along with checking if it is complete.
    
    //Condition Checkers
    bool loopBreaker = false;
    if (thePos == pCount)
    {
        while (true) //Loop until it something reaches 0 I/O time remaining.
        {
            totTime++;
            tempTime++;
            for (int i = 0; i < pCount; i++)
            {
                if (P[i].cool == true)
                {
                    P[i].rTime = P[i].rTime - 1;
                }
                if (P[i].rTime <= 0 && P[i].finished == false)
                {
                    P[i].cool = false;
                    P[i].rTime = 0;
                    loopBreaker = true;
                    break; //Loop ender
                }
            }
            if (loopBreaker == true)
                break; //break only cancels innermost loop...
        }
    }
    else
    {
        totTime += Set.aTimes[Set.pos];
        tempTime += Set.aTimes[Set.pos];
        if (P[thePos].bTimes[Set.pos] == 0)
        {
            P[thePos].tTime = totTime;
            P[thePos].finished = true;
        }
        if (P[thePos].cool == false && P[thePos].finished == false) //Conversion from I/O ready to I/O cooldown
        {
            P[thePos].cool = true;
            P[thePos].rTime = P[thePos].bTimes[Set.pos] + P[thePos].aTimes[Set.pos]; //Since set and P[thePos] are the same, so are the values.
            P[thePos].pos += 1;
        }
        //Time Tracker and Cooldown Remover
        for (int i = 0; i < pCount; i++)
        {
            if (P[i].cool == true)
            {
                P[i].rTime = P[i].rTime - P[thePos].aTimes[Set.pos];
            }
            if (P[i].rTime <= 0 && P[i].finished == false)
            {
                P[i].cool = false;
                P[i].rTime = 0;
            }
        }
        tEpoch += 1;
    }
    for (int i = thePos + 1; i < pCount; i++)
    {
        if (P[i].cool == false && P[i].finished == false)
        {
            P[i].wTime += tempTime;
        }
    }
    
}

//*************************************************************************************
//Name:	Queue Process
//Condition: Requires a Process array.
//Description: Organizes the numerical order of the processes
//Meant to be looped in main function.
//*************************************************************************************
bool finalCheck(Process P[])
{
    for (int i = 0; i < pCount; i++)
    {
        if (P[i].finished == false)
            return false;
    }
    return true;
}

//*************************************************************************************
//MAIN FUNCTION
//*************************************************************************************
int main()
{
    //Initialize all processes, and for each process, add one to the global pCount.
    //IF YOU ARE USING MULTIPLE TEST CASES, JUST ADD/REMOVE/EDIT THE PROCESS AMOUNT,
    //AND CHANGE TIME CONSTRAINTS, FOLLOWED BY A ZERO AT THE END OF THE I/O TIMES
    //aTimes REPRESENTS CPU TIMES, bTimes REPRESENTS I/O TIMES.
    Process P[9]; //Creates the array
    bool theFinal = false; //Checks the entire array at the very end.
    //Process object creation
    Process P1;
    P1.id = 1;
    P1.aTimes = { 7, 6, 12, 8, 10, 5, 6, 7, 8 };
    P1.bTimes = { 22, 19, 44, 21, 37, 24, 44, 43, 0};
    P[0] = P1;
    Process P2;
    P2.id = 2;
    P2.aTimes = {14, 15, 17, 22, 19, 14, 16, 17, 18};
    P2.bTimes = {48, 44, 42, 37, 76, 41, 31, 43, 0};
    P[1] = P2;
    Process P3;
    P3.id = 3;
    P3.aTimes = {8, 7, 6, 8, 9, 14, 5, 3, 6};
    P3.bTimes = {43, 41, 45, 21, 35, 18, 26, 31, 0};
    P[2] = P3;
    Process P4;
    P4.id = 4;
    P4.aTimes = {13, 4, 5, 12, 8, 15, 6, 5, 3};
    P4.bTimes = {37, 41, 35, 41, 55, 34, 73, 77, 0};
    P[3] = P4;
    Process P5;
    P5.id = 5;
    P5.aTimes = {6, 7, 5, 6, 7, 3, 11, 6, 3, 4};
    P5.bTimes = {34, 21, 44, 32, 28, 48, 44, 33, 28, 0};
    P[4] = P5;
    Process P6;
    P6.id = 6;
    P6.aTimes = {9, 4, 5, 6, 7, 9, 12, 15, 8};
    P6.bTimes = {32, 28, 10, 12, 14, 18, 24, 30, 0};
    P[5] = P6;
    Process P7;
    P7.id = 7;
    P7.aTimes = {14, 17, 11, 15, 4, 7, 16, 10};
    P7.bTimes = {46, 41, 42, 21, 32, 19, 33, 0};
    P[6] = P7;
    Process P8;
    P8.id = 8;
    P8.aTimes = {4, 5, 6, 4, 6, 5, 8, 6, 9, 7};
    P8.bTimes = {64, 53, 44, 73, 87, 66, 25, 33, 41, 0};
    P[7] = P8;
    Process P9;
    P9.id = 9;
    P9.aTimes = {13, 8, 7, 12, 5, 6, 3, 4, 6};
    P9.bTimes = {37, 41, 27, 29, 18, 33, 62, 0};
    P[8] = P9;
    while (theFinal == false)
    {
        arrivalQueue(P, pCount);
        arrivalQueue(P);
        queueProcess(P);
        theFinal = finalCheck(P);
    }

    for (int i = 0; i < pCount; i++)
    {
        for (int j = 0; j < pCount; j++)
        {
            if (P[i].id < P[j].id)
            {
                swap(P[i], P[j]);
            }
        }
    }

    cout << "All processes completed." << endl;
    cout << "Total time: " << totTime << endl;
    double avgTurnTime = 0;
    double avgResTime = 0;
    double avgWaiTime = 0;
    double util = tEpoch;
    util = util / (tEpoch + fEpoch);
    util = util * 100;
    cout << "CPU Utilization: " << util << "%" << endl;
    cout << "Turnabout Time: " << endl;
    for (int i = 0; i < pCount; i++)
    {
        cout << "P" << P[i].id << ": " << P[i].tTime << endl;
        avgTurnTime += P[i].tTime;
    }
    avgTurnTime /= pCount;
    cout << "Average: " << avgTurnTime;

    cout << "\nResponse Time: " << endl;
    for (int i = 0; i < pCount; i++)
    {
        cout << "P" << P[i].id << ": " << P[i].eTime << endl;
        avgResTime += P[i].eTime;
    }
    avgResTime /= pCount;
    cout << "Average: " << avgResTime;

    cout << "\nWaiting Time: " << endl;
    for (int i = 0; i < pCount; i++)
    {
        cout << "P" << P[i].id << ": " << P[i].wTime << endl;
        avgWaiTime += P[i].wTime;
    }
    avgWaiTime /= pCount;
    cout << "Average: " << avgWaiTime;
}


