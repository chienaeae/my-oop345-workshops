#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H

#include <chrono>
#include <string>

#include "event.h"

namespace seneca
{

    class TimeMonitor
    {

        std::chrono::steady_clock::time_point m_startTime;
        std::chrono::steady_clock::time_point m_endTime;
        std::string m_name;

    public:
        void startEvent(const char *name);

        Event stopEvent();
    };

}

#endif // SENECA_TIMEMONITOR_H