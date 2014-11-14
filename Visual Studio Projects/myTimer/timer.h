//--------------------------------------------------------------------
//
//  Laboratory C                                             timer.h
//
//  Class declaration for the Timer ADT
//
//
//  from "A Laboratory Course in C++ Data Structures" (Roberge,Brandle,Whittington)
//--------------------------------------------------------------------

// Insert a declaration for SystemTime here.
#include <time.h>

typedef clock_t SystemTime;

class Timer
{
  public:

    // Start and stop the timer
    void start ();
    void stop ();

    // Compute the elapsed time (in seconds)
    double getElapsedTime () const;

  private:

    SystemTime startTime,   // Time that the timer was started
               stopTime;    // Time that the timer was stopped
};
