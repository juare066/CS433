#ifndef EVENT_H
#define EVENT_H

#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include "random.h"

class Event {
public:
    Event();
    Event(int type, int arrived, int burst, int pid);
    Event(Event* orig);
    virtual ~Event();
    void print();
    int processId;
    int scheduled; // Index for Priority Event Queue
    /*
     * Event Types
     * 1 Process Arrival
     * 2 CPU Completion
     * 3 IO Completion
     * 4 Timer Expiration
     */
    int type;
    int arrived;
    bool burstComplete;
    bool ioComplete;
    int timer;
    int burst; // The length of the burst to adjust the process timers by
private:

};

#endif /* EVENT_H */
