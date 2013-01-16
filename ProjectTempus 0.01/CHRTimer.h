#pragma once

#include <Windows.h>

// Author: Jonathan Wood
// Source: http://www.blackbeltcoder.com/Articles/time/c-high-resolution-timer

class CHRTimer
{
protected:

    LARGE_INTEGER m_liStart;
    LARGE_INTEGER m_liStop;

public:

    CHRTimer(void)
    {
        m_liStart.QuadPart = m_liStop.QuadPart = 0;
    }

    ~CHRTimer(void)
    {
    }

    // Starts the timer
    void Start()
    {
        ::QueryPerformanceCounter(&m_liStart);
    }

    // Stops the timer
    void Stop()
    {
        ::QueryPerformanceCounter(&m_liStop);
    }

    // Returns the counter at the last Start()
    LONGLONG GetStartCounter()
    {
        return m_liStart.QuadPart;
    }

    // Returns the counter at the last Stop()
    LONGLONG GetStopCounter()
    {
        return m_liStop.QuadPart;
    }

    // Returns the interval between the last Start() and Stop()
    LONGLONG GetElapsed()
    {
        return (m_liStop.QuadPart - m_liStart.QuadPart);
    }

    // Returns the interval between the last Start() and Stop() in seconds
    double GetElapsedAsSeconds()
    {
        LARGE_INTEGER liFrequency;
        ::QueryPerformanceFrequency(&liFrequency);
        return ((double)GetElapsed() / (double)liFrequency.QuadPart);
    }
};