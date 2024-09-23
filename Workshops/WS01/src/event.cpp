#include "event.h"

#include <iostream>
#include <chrono>
#include <string>
#include <iomanip>
#include "settings.h"

using namespace std;

namespace seneca
{
    Event::Event() : m_event_name(""), m_duration(chrono::nanoseconds(0)) {}

    Event::Event(const char *name, const chrono::nanoseconds &duration)
        : m_event_name(name), m_duration(duration) {}

    ostream &operator<<(ostream &os, const Event &event)
    {
        static uint counter = 0;
        counter++;
        os << right << setw(2) << counter << ": "
           << right << setw(40) << event.m_event_name
           << " -> ";

        if (g_settings.m_time_units == "seconds")
        {
            os << right << setw(2) << chrono::duration_cast<chrono::seconds>(event.m_duration).count();
        }
        else if (g_settings.m_time_units == "milliseconds")
        {
            os << right << setw(5) << chrono::duration_cast<chrono::milliseconds>(event.m_duration).count();
        }
        else if (g_settings.m_time_units == "microseconds")
        {
            os << right << setw(8) << chrono::duration_cast<chrono::microseconds>(event.m_duration).count();
        }
        else
        {
            os << right << setw(11) << chrono::duration_cast<chrono::nanoseconds>(event.m_duration).count();
        }

        os << " " << g_settings.m_time_units;
        return os;
    }
};