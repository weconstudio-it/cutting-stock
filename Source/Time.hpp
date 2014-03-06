#ifndef TIME_H
#define TIME_H

#include <sys/time.h>
#include <exception>


#define MEGA 1000000


//
// Utlity classes to measure runtime.
//


// Represents a time stamp.
class Time {

private:

    struct timeval time;

public:

    // Default constructor. Gets the total time elapsed since EPOCH until the present
    // invocation time.
    Time() {
        gettimeofday(&time, 0);
    }

    // Gets the total microseconds from this time stamp.
    long getMicroseconds() {
        return ((long) time.tv_sec) * MEGA + ((long) time.tv_usec);
    }

    // Gets the total seconds from this time stamp.
    long getSeconds() {
        return (long)time.tv_sec;
    }
};


// Exception thrown when an invalid operation is requested for a timer.
class TimerInvalidOperationException: public std::exception {
    virtual const char* what() const throw() {
        return "Invalid operation on this timer.";
    }
};


// A timer to measure elapsed runtime.
class Timer {

private:

    Time *after, *before;
    bool running;

public:

    Timer() {
        running = false;
        after = before = 0;
    }

    ~Timer() {
        if (before != 0)
            delete before;
        if (after != 0)
            delete after;
    }

    // Stars the timer.
    void start()
    {
        if (!running) {
            if (before != 0)
                delete before;
            before = new Time();
            running = true;
        }
    }

    // Stops the timer.
    void stop() {
        if (running) {
            if (after != 0)
                delete after;
            after = new Time();
            running = false;
        }
    }

    bool isRunning() {
        return running;
    }

    // Gets the total whole microseconds elapsed between the start and the stop operations.
    // The timer needs to be stopped. If the timer is running, throws TimerInvalidOperationException.
    long getMicroseconds() {
        if (!running)
            return after->getMicroseconds() - before->getMicroseconds();
        else
            throw TimerInvalidOperationException();
    }

    // Gets the total whole seconds elapsed between the start and the stop operations.
    // The timer needs to be stopped. If the timer is running, throws
    // TimerInvalidOperationException.
    int getSeconds() {
        if (!running)
            return (int) (after->getSeconds() - before->getSeconds());
        else
            throw TimerInvalidOperationException();
    }
};

#endif
