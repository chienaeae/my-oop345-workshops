#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

#include <string>

namespace seneca
{
    class Settings
    {
    public:
        bool m_show_all;
        bool m_verbose;
        // Possible values are seconds, milliseconds, microseconds, nanoseconds (default nanoseconds).
        std::string m_time_units = "nanoseconds";
    };

    extern Settings g_settings;
}

#endif // SENECA_SETTINGS_H