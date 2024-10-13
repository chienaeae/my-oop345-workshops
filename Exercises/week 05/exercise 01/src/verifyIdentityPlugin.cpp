#include "verifyIdentityPlugin.h"

#include <fstream>
#include <iostream>

using namespace std;

namespace seneca
{
    VerifyIdentityPlugin::VerifyIdentityPlugin(const char *filename) : m_trustedAddressCount(0)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Could not open file");
        }

        string trustEmail;
        while (file >> trustEmail && m_trustedAddressCount < MAX_EMAIL_ADDRESSES)
        {
            m_trustedAddresses[m_trustedAddressCount++] = trustEmail;
        }

        file.close();
    }

    void VerifyIdentityPlugin::operator()(Message &msg)
    {
        bool isTrusted = false;
        for (size_t i = 0; i < m_trustedAddressCount; ++i)
        {
            if (msg.m_fromAddress == m_trustedAddresses[i])
            {
                isTrusted = true;
                break;
            }
        }

        if (isTrusted)
        {
            msg.m_subject = "[TRUSTED] " + msg.m_subject;
        }
    }

    void VerifyIdentityPlugin::showStats() const
    {
        cout << "[Identity Checker Plugin] can validate identity for ";

        for (size_t i = 0; i < m_trustedAddressCount; ++i)
        {
            cout << m_trustedAddresses[i];
            if (i != m_trustedAddressCount - 1)
            {
                cout << ", ";
            }
        }

        cout << endl;
    }

} // namespace seneca
