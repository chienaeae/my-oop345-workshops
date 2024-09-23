#include "logger.h"

#include <iostream>
#include <string>

using namespace std;

namespace seneca
{
    Logger::Logger()
    {
        m_events = new Event[10];
        m_capacity = 10;
        m_size = 0;
    }

    Logger::~Logger()
    {
        delete[] m_events;
    }

    Logger::Logger(Logger &&other) noexcept
        : m_events(other.m_events), m_capacity(other.m_capacity), m_size(other.m_size)
    {
        other.m_events = nullptr;
        other.m_capacity = 0;
        other.m_size = 0;
    }

    Logger &Logger::operator=(Logger &&other) noexcept
    {
        if (this != &other)
        {
            delete[] m_events;
            m_events = other.m_events;
            m_capacity = other.m_capacity;
            m_size = other.m_size;

            other.m_events = nullptr;
            other.m_capacity = 0;
            other.m_size = 0;
        }

        return *this;
    }

    void Logger::addEvent(const Event &event)
    {
        if (m_size == m_capacity)
        {
            Event *new_events = new Event[m_capacity * 2];

            for (int i = 0; i < m_size; ++i)
            {
                new_events[i] = m_events[i];
            }

            delete[] m_events;
            m_events = new_events;
            m_capacity *= 2;
        }

        m_events[m_size] = event;
        ++m_size;
    }

    ostream &operator<<(ostream &os, const Logger &logger)
    {
        for (int i = 0; i < logger.m_size; ++i)
        {
            os << logger.m_events[i] << endl;
        }

        return os;
    }
}