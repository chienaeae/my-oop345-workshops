#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H

#include <iostream>
#include "event.h"

namespace seneca
{
    class Logger
    {
        Event *m_events;
        int m_capacity;
        int m_size;

    public:
        Logger();
        ~Logger();

        Logger(Logger &&other) noexcept;
        Logger &operator=(Logger &&other) noexcept;

        void addEvent(const Event &event);

        friend std::ostream &operator<<(std::ostream &os, const Logger &logger);
    };

}

#endif // SENECA_LOGGER_H