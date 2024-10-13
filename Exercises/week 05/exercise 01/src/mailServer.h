#ifndef SENECA_MAILSERVER_H
#define SENECA_MAILSERVER_H

#include "message.h"
#include "plugin.h"
#include <string>

namespace seneca
{
    using Observer_pfn = void (*)(const Message &);

    class MailServer
    {
        std::string m_userName;
        std::string m_userAddress;
        Message *m_inbox;
        size_t m_capacity;
        size_t m_cnt;
        Observer_pfn onNewMailArrived;
        Plugin *m_pluginsp[2];

    public:
        MailServer(const char *name, const char *address);

        MailServer(const MailServer &other);

        MailServer &operator=(const MailServer &other);

        MailServer(MailServer &&other) noexcept;

        MailServer &operator=(MailServer &&other) noexcept;

        ~MailServer();

        void receiveMail(Message msg);

        void addPlugin(Plugin *thePlugin);

        void setObserver(Observer_pfn observer);

        Message &operator[](size_t idx);

        size_t getInboxSize();

        void showInbox();
    };
}

#endif