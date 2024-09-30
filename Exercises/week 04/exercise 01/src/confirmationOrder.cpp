#include "confirmationOrder.h"

#include <iostream>

using namespace std;

namespace seneca
{
    ConfirmationOrder::ConfirmationOrder() : m_capacity(2), m_numToys(0), m_pToys(nullptr)
    {
        m_pToys = new const Toy *[m_capacity];
    }

    ConfirmationOrder::ConfirmationOrder(const ConfirmationOrder &other)
    {
        m_capacity = other.m_capacity;
        m_numToys = other.m_numToys;
        m_pToys = new const Toy *[m_capacity];

        for (size_t i = 0; i < m_numToys; i++)
        {
            m_pToys[i] = other.m_pToys[i];
        }
    }

    ConfirmationOrder &ConfirmationOrder::operator=(const ConfirmationOrder &other)
    {
        if (this != &other)
        {
            m_capacity = other.m_capacity;
            m_numToys = other.m_numToys;
            m_pToys = new const Toy *[m_capacity];

            for (size_t i = 0; i < m_numToys; i++)
            {
                m_pToys[i] = other.m_pToys[i];
            }
        }
        return *this;
    }

    ConfirmationOrder::ConfirmationOrder(ConfirmationOrder &&other) noexcept
        : m_capacity(other.m_capacity), m_numToys(other.m_numToys), m_pToys(other.m_pToys)
    {
        other.m_capacity = 0;
        other.m_numToys = 0;
        other.m_pToys = nullptr;
    }

    ConfirmationOrder &ConfirmationOrder::operator=(ConfirmationOrder &&other) noexcept
    {
        if (this != &other)
        {
            m_capacity = other.m_capacity;
            m_numToys = other.m_numToys;
            m_pToys = other.m_pToys;

            other.m_capacity = 0;
            other.m_numToys = 0;
            other.m_pToys = nullptr;
        }

        return *this;
    }

    bool ConfirmationOrder::isExist(const Toy &toy) const
    {
        for (size_t i = 0; i < m_numToys; i++)
        {
            if (m_pToys[i] == &toy)
            {
                return true;
            }
        }

        return false;
    }

    void ConfirmationOrder::resize()
    {
        m_capacity *= 2;
        const Toy **newToys = new const Toy *[m_capacity];
        for (size_t i = 0; i < m_numToys; i++)
        {
            newToys[i] = m_pToys[i];
        }

        delete[] m_pToys;
        m_pToys = newToys;
    }

    bool ConfirmationOrder::isFull() const
    {
        return m_numToys == m_capacity;
    }

    ConfirmationOrder &ConfirmationOrder::operator+=(const Toy &toy)
    {
        if (isExist(toy))
        {
            return *this;
        }

        if (isFull())
        {
            resize();
        }

        m_pToys[m_numToys++] = &toy;
        return *this;
    }

    ConfirmationOrder &ConfirmationOrder::operator-=(const Toy &toy)
    {
        if (!isExist(toy))
        {
            return *this;
        }

        size_t foundIndex = 0;

        for (size_t i = 0; i < m_numToys; i++)
        {
            if (m_pToys[i] == &toy)
            {
                foundIndex = i;
                break;
            }
        }

        for (size_t i = foundIndex + 1; i < m_numToys; i++)
        {
            m_pToys[i - 1] = m_pToys[i];
        }

        m_numToys--;
        return *this;
    }

    ostream &operator<<(ostream &os, const ConfirmationOrder &cOrder)
    {
        os << "--------------------------\n";
        os << "Confirmations to Send (" << cOrder.m_numToys << " toys)\n";
        os << "--------------------------\n";

        if (cOrder.m_numToys == 0)
        {
            os << "There are no confirmations to send!\n";
        }
        else
        {
            for (size_t i = 0; i < cOrder.m_numToys; i++)
            {
                os << *cOrder.m_pToys[i];
            }
        }

        os << "--------------------------\n";

        return os;
    }
}