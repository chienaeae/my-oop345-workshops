#include "timeMonitor.h"

#include <iostream>
#include <chrono>

#include "event.h"

using namespace std;

namespace seneca
{
    void TimeMonitor::startEvent(const char *name)
    {
        m_name = name;
        m_startTime = chrono::steady_clock::now();
    }

    Event TimeMonitor::stopEvent()
    {
        m_endTime = chrono::steady_clock::now();
        chrono::nanoseconds duration = chrono::duration_cast<chrono::nanoseconds>(m_endTime - m_startTime);

        return Event(m_name.c_str(), duration);
    }

};