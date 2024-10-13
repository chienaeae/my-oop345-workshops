#ifndef SENECA_VERIFYIDENTITYPLUGIN_H
#define SENECA_VERIFYIDENTITYPLUGIN_H

#include "plugin.h"
#include "message.h"
#include <string>

namespace seneca
{
    class VerifyIdentityPlugin : public Plugin
    {
        static const size_t MAX_EMAIL_ADDRESSES = 50;

        std::string m_trustedAddresses[MAX_EMAIL_ADDRESSES];

        size_t m_trustedAddressCount;

    public:
        VerifyIdentityPlugin(const char *filename);

        void operator()(Message &msg);

        void showStats() const;
    };
}

#endif