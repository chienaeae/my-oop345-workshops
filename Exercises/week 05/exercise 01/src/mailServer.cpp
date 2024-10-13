#include "mailServer.h"

#include "plugin.h"

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

namespace seneca
{
    MailServer::MailServer(const char *name, const char *address)
        : m_userName(name), m_userAddress(address), m_inbox(new Message[2]), m_capacity(2), m_cnt(0), onNewMailArrived(nullptr)
    {
        for (size_t i = 0; i < 2; ++i)
        {
            m_pluginsp[i] = nullptr;
        }
    }

    MailServer::MailServer(const MailServer &other)
    {
        m_userName = other.m_userName;
        m_userAddress = other.m_userAddress;
        m_capacity = other.m_capacity;
        try
        {
            m_inbox = new Message[m_capacity];
        }
        catch (const std::bad_alloc &e)
        {
            throw std::runtime_error("Memory allocation failed");
        }
        m_cnt = other.m_cnt;
        for (size_t i = 0; i < m_cnt; ++i)
        {
            m_inbox[i] = other.m_inbox[i];
        }
        for (size_t i = 0; i < 2; ++i)
        {
            m_pluginsp[i] = other.m_pluginsp[i];
        }
        // onNewMailArrived = other.onNewMailArrived;
    }

    MailServer &MailServer::operator=(const MailServer &other)
    {
        if (this != &other)
        {
            delete[] m_inbox;
            m_userName = other.m_userName;
            m_userAddress = other.m_userAddress;
            m_capacity = other.m_capacity;
            m_inbox = new Message[m_capacity];
            m_cnt = other.m_cnt;
            for (size_t i = 0; i < m_cnt; ++i)
            {
                m_inbox[i] = other.m_inbox[i];
            }

            for (size_t i = 0; i < 2; ++i)
            {
                m_pluginsp[i] = other.m_pluginsp[i];
            }

            // onNewMailArrived = other.onNewMailArrived;
        }

        return *this;
    }

    MailServer::MailServer(MailServer &&other) noexcept
        : m_userName(other.m_userName), m_userAddress(other.m_userAddress), m_capacity(other.m_capacity),
          m_cnt(other.m_cnt)
    {
        m_inbox = other.m_inbox;
        // onNewMailArrived = other.onNewMailArrived;

        other.m_inbox = nullptr;
        other.m_capacity = 0;
        other.m_cnt = 0;

        for (size_t i = 0; i < 2; ++i)
        {
            m_pluginsp[i] = other.m_pluginsp[i];
            other.m_pluginsp[i] = nullptr;
        }

        // other.onNewMailArrived = nullptr;
    }

    MailServer &MailServer::operator=(MailServer &&other) noexcept
    {
        if (this != &other)
        {
            delete[] m_inbox;
            m_userName = other.m_userName;
            m_userAddress = other.m_userAddress;
            m_inbox = other.m_inbox;
            m_cnt = other.m_cnt;
            // onNewMailArrived = other.onNewMailArrived;
            other.m_inbox = nullptr;
            other.m_capacity = 0;
            other.m_cnt = 0;

            for (size_t i = 0; i < 2; ++i)
            {
                m_pluginsp[i] = other.m_pluginsp[i];
                other.m_pluginsp[i] = nullptr;
            }

            // other.onNewMailArrived = nullptr;
        }

        return *this;
    }

    MailServer::~MailServer()
    {
        delete[] m_inbox;
    }

    void MailServer::receiveMail(Message msg)
    {
        if (msg.m_toAddress != m_userAddress)
        {
            string errMsg = "EXCEPTION: Message intended for [" + msg.m_toAddress + "]";
            throw std::invalid_argument(errMsg);
        }

        if (m_cnt == m_capacity)
        {
            m_capacity *= 2;
            Message *newInbox = new Message[m_capacity];
            for (size_t i = 0; i < m_cnt; ++i)
            {
                newInbox[i] = m_inbox[i];
            }

            delete[] m_inbox;
            m_inbox = newInbox;
        }

        for (size_t i = 0; i < 2; ++i)
        {
            if (m_pluginsp[i] != nullptr)
            {
                (*m_pluginsp[i])(msg);
            }
        }

        if (onNewMailArrived != nullptr)
        {
            (*onNewMailArrived)(msg);
        }

        m_inbox[m_cnt++] = msg;
    }

    void MailServer::addPlugin(Plugin *thePlugin)
    {
        for (size_t i = 0; i < 2; ++i)
        {
            if (m_pluginsp[i] == nullptr)
            {
                m_pluginsp[i] = thePlugin;
                break;
            }
        }
    }

    void MailServer::setObserver(Observer_pfn observer)
    {
        onNewMailArrived = observer;
    }

    Message &MailServer::operator[](size_t idx)
    {
        if (idx >= m_cnt)
        {
            string errMsg = "Index " + to_string(idx) + " is out of bounds.";
            throw std::out_of_range(errMsg);
        }

        return m_inbox[idx];
    }

    size_t MailServer::getInboxSize()
    {
        return m_cnt;
    }

    void MailServer::showInbox()
    {
        for (size_t i = 0; i < m_cnt; i++)
        {
            Message &msg = m_inbox[i];
            string formattedDate = msg.m_date.substr(0, 10);
            cout << right << setw(20) << msg.m_fromName << "  "
                 << left << setw(40) << msg.m_fromAddress << "  "
                 << left << setw(15) << formattedDate << "  "
                 << right << msg.m_subject << "\n";
        }
    }
} // namespace seneca
