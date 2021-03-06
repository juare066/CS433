//==============================================================================
//HW#: HW3
//Name: Fernando Juarez & Michael Trani
//Date: November 1, 2019
//Course: CS433 HW3
//Complier:  g++
//File type: main.cpp - main class of the assignment, acts as the driver class
// of the overall assignment, based on the number of processes selected from the
// user and scheduling algorithms it reads user input and performs the desired
// algorithm: Most code was provided by Professor.
//==============================================================================
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <sstream>
#include "Event.h"
#include "FCFSScheduler.h"
#include "SJFScheduler.h"

using namespace std;

int main(int argc, char** argv) {
    printf("\n=================================================================");
    printf("\nCS 433 Programming Assignment 3");
    printf("\nAuthor: Fernando Juarez and Michael Trani");
    printf("\nDate: 11/04/2019");
    printf("\nCourse: CS433 (Operating Systems)");
    printf("\nDescription : Program to simulate CPU scheduling algorithms");
    printf("\n=================================================================\n");
    // pass arguments to get different scheduling algorithms
    FCFSScheduler scheduler;
    
    if(string(argv[1]) == "1") {
        printf("*****************Simulating FCFS scheduler **********************");
        FCFSScheduler scheduler;
    } else if(string(argv[1]) == "2") {
        printf("****************Simulating SJF scheduler **********************");
        SJFScheduler scheduler;
    }
    
    istringstream ss(argv[2]);
    int processes;
    if (!(ss >> processes)) {
        cerr << "Invalid number " << argv[2] << '\n';
        return 0;
    }
    
    //int run = false; //Loop flag
    int clock = 0; //Clock counter
    int endClock = 300000;
    
    // generate some process arrival events
    for(int i = 0; i < processes; i++) {
        /* Instantiate a Process Arrival Event */
        Event* rEvent = new Event();
        /* Instantiate the process the event describes */
        Process* rProcess = new Process(rEvent);
        //rProcess->print();
        /* Index the process */
        scheduler.processTable.insert(pair<int,Process*>(rProcess->id, rProcess));
        /* Add the event to the EventQueue*/
        scheduler.eventQueue.push(rEvent);
    }
    
    Event* e;
    
    while(clock < endClock && !scheduler.eventQueue.empty()) {
        /* Get the next Event in EventQueue */
        //printf("\nFetching Event...");
        e = scheduler.eventQueue.top();
        clock = e->arrived;
        scheduler.clock = clock;
        
        /* Handle the next Event */
        scheduler.handleEvent(e);
//        printf("\nEventQ size: ");
//        printf("%i", scheduler.eventQueue.size());
//        printf("\nProcQ size: ");
//        printf("%i", scheduler.processQueue.size());
        scheduler.eventQueue.pop(); // remove from queue
        //update stats
        //sleep(2);
    }
    
    int numProc = 0;
    int totalTime = 0;
    int totalWait = 0;
    int temp = 0;
    int process = 0;
    int turnAround = totalTime/numProc;
    // for(temp = 0; temp < numProc; temp++);
    //printf("\nProcess %i:",temp++);

    for(auto it = scheduler.processTable.begin (); it != scheduler.processTable.end(); ++it) {
      // PCB* p = scheduler.get_process(i);
        //std::cout << " " << it->first << ":" << it->second;
	printf("\nProcess %i:", process++);
        printf("\nArrival Time: ", it->second->start);
        printf("\nFinish Time: %i ms", it->second->finish, " ms");
	printf("\nTurnAround: ", turnAround);
        printf("\nIO Time: %i ms", it->second->ioTime, " ms");
        printf("\nWait Time: %i ms", it->second->waitingTime());
        printf("\n");
        
        if(it->second->finish > 0) {
            temp = it->second->finish - it->second->start;
            totalTime = totalTime + temp;
            temp = it->second->waitingTime();
            totalWait = totalWait + temp;
            numProc++;
        }
      }
    
    printf("Total wait: %i", totalWait);
    
    int avgTurnAround = totalTime/numProc;
    int avgWait = totalWait/numProc;
    int throughput = (numProc*100000)/endClock;
    int cpuUtilization = (((endClock - avgWait)*100)/endClock);
    
    printf("\n\nJobs Completed: %i", numProc);
    printf("\nAverage Turnaround Time: %i ms", avgTurnAround);
    printf("\nAverage Wait Time: %i ms", avgWait);
    printf("\nThroughput: 0.0%i jobs/ms", throughput);
    printf("\nCPU Utilization: %i\n", cpuUtilization, " %");
    
    return 0;
}
