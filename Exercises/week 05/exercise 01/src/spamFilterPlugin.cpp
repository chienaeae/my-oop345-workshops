#include "spamFilterPlugin.h"

#include <fstream>
#include <string>
#include <iostream>
#include "message.h"

using namespace std;

namespace seneca
{
    SpamFilterPlugin::SpamFilterPlugin(const char *filename) : m_identifierCount(0), m_spamCount(0)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Could not open file");
        }

        int count = 0;

        // read the file line by line
        std::string spamIdentifier;
        while (file >> spamIdentifier && count < MAX_SPAM_IDENTIFIERS)
        {
            m_spamIdentifiers[m_identifierCount++] = spamIdentifier;
        }

        file.close();
    }

    void SpamFilterPlugin::operator()(Message &msg)
    {
        bool isSpam = false;
        for (int i = 0; i < m_identifierCount; i++)
        {
            if (msg.m_subject.find(m_spamIdentifiers[i]) != std::string::npos)
            {
                m_spamCount++;
                isSpam = true;
                break;
            }
        }

        if (isSpam)
        {
            msg.m_subject = "[SPAM] " + msg.m_subject;
        }
    }

    void SpamFilterPlugin::showStats() const
    {
        cout << "[Spam Filter Plugin] Identified " << m_spamCount << " spam messages.\n";
    }
} // namespace seneca