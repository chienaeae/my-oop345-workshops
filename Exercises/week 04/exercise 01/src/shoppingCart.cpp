#include "shoppingCart.h"

#include <utility>
#include <iostream>
#include <string>

using namespace std;

namespace seneca
{

    ShoppingCart::ShoppingCart(const string &name, int age, const Toy *toys[], size_t count)
    {
        m_name = name;
        m_ageOfChild = age;
        m_numToys = count;
        m_pToys = new const Toy *[m_numToys];
        for (size_t i = 0; i < m_numToys; i++)
        {
            m_pToys[i] = new Toy(*toys[i]);
        }
    }

    ShoppingCart::ShoppingCart(const ShoppingCart &other)
    {
        m_name = other.m_name;
        m_ageOfChild = other.m_ageOfChild;
        m_numToys = other.m_numToys;
        m_pToys = new const Toy *[m_numToys];

        for (size_t i = 0; i < m_numToys; i++)
        {
            m_pToys[i] = new Toy(*other.m_pToys[i]);
        }
    }

    ShoppingCart &ShoppingCart::operator=(const ShoppingCart &other)
    {
        if (this != &other)
        {
            clear();
            m_name = other.m_name;
            m_ageOfChild = other.m_ageOfChild;
            m_numToys = other.m_numToys;

            m_pToys = new const Toy *[m_numToys];
            for (size_t i = 0; i < m_numToys; i++)
            {
                m_pToys[i] = new Toy(*other.m_pToys[i]);
            }
        }
        return *this;
    }

    ShoppingCart::ShoppingCart(ShoppingCart &&other) noexcept
        : m_name(std::move(other.m_name)),
          m_ageOfChild(other.m_ageOfChild),
          m_numToys(other.m_numToys),
          m_pToys(other.m_pToys)
    {
        other.m_ageOfChild = 0;
        other.m_numToys = 0;
        other.m_pToys = nullptr;
    }

    ShoppingCart &ShoppingCart::operator=(ShoppingCart &&other) noexcept
    {
        if (this != &other)
        {
            clear();
            m_name = std::move(other.m_name);
            m_ageOfChild = other.m_ageOfChild;
            m_numToys = other.m_numToys;
            m_pToys = other.m_pToys;

            other.m_ageOfChild = 0;
            other.m_numToys = 0;
            other.m_pToys = nullptr;
        }
        return *this;
    }

    ShoppingCart::~ShoppingCart()
    {
        clear();
    }

    void ShoppingCart::clear()
    {
        // First clean up each toy
        for (size_t i = 0; i < m_numToys; i++)
        {
            delete m_pToys[i];
        }

        // Then clean up the array of pointers
        delete[] m_pToys;
    }

    ostream &ShoppingCart::printHeader(ostream &os) const
    {
        static unsigned int count = 0;
        count++;
        os << "--------------------------\n";
        os << "Order " << count << ": ";
        if (m_pToys == nullptr)
        {
            os << "This shopping cart is invalid.\n";
        }
        else
        {
            os << "Shopping for " << m_name << " " << m_ageOfChild << " years old (" << m_numToys << " toys)\n";
        }

        os << "--------------------------\n";
        return os;
    }

    ostream &ShoppingCart::printContent(ostream &os) const
    {
        if (m_pToys == nullptr)
        {
            return os;
        }

        for (size_t i = 0; i < m_numToys; i++)
        {
            os << *m_pToys[i];
        }

        os << "--------------------------\n";
        return os;
    }

    ostream &operator<<(ostream &os, const ShoppingCart &cart)
    {
        cart.printHeader(os);
        cart.printContent(os);
        return os;
    }
}