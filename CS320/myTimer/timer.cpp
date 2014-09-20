//--------------------------------------------------------------------
//
//  Laboratory C                                          timer.cpp
//
//  SOLUTION: Implementation of the Timer ADT
//
//
//  from "A Laboratory Course in C++ Data Structures" (Roberge,Brandle,Whittington)
//--------------------------------------------------------------------

#include <iostream>
#include <ctime>
#include "timer.h"

//--------------------------------------------------------------------

void Timer::start ()

// Starts the timer.

{
    //startTime = times( NULL );
    startTime = clock();
}

//--------------------------------------------------------------------

void Timer::stop ()

// Stops the timer.

{
    //stopTime = times( NULL );
    stopTime = clock();
}

//--------------------------------------------------------------------

double Timer::getElapsedTime () const

// Computes the length of the time interval from startTime to
// stopTime (in seconds).

{
    return  double ( stopTime - startTime ) / (CLOCKS_PER_SEC) ;
}
