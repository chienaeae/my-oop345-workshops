#ifndef SENECA_SPAMFILTERPLUGIN_H
#define SENECA_SPAMFILTERPLUGIN_H

#include "plugin.h"
#include <string>

namespace seneca
{
    class SpamFilterPlugin : public Plugin
    {
        static const size_t MAX_SPAM_IDENTIFIERS = 50;

        std::string m_spamIdentifiers[MAX_SPAM_IDENTIFIERS];

        size_t m_identifierCount;

        size_t m_spamCount;

    public:
        SpamFilterPlugin(const char *filenamr);

        void operator()(Message &msg);

        void showStats() const;
    };
}

#endif