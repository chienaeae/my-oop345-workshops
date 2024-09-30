#ifndef SENECA_CONFIRMATIONORDER_H
#define SENECA_CONFIRMATIONORDER_H

#include <iostream>
#include <string>

#include "toy.h"

namespace seneca
{
    class ConfirmationOrder
    {
        // DO NOT manage the memory (life) of the Toys !!
        size_t m_capacity;
        size_t m_numToys;
        const Toy **m_pToys;

        bool isExist(const Toy &toy) const;

        void resize();

        bool isFull() const;

    public:
        ConfirmationOrder();

        // Copy constructor and copy assignment operator
        ConfirmationOrder(const ConfirmationOrder &other);

        ConfirmationOrder &operator=(const ConfirmationOrder &other);

        // Move constructor and move assignment operator
        ConfirmationOrder(ConfirmationOrder &&other) noexcept;

        ConfirmationOrder &operator=(ConfirmationOrder &&other) noexcept;

        ConfirmationOrder &operator+=(const Toy &toy);

        ConfirmationOrder &operator-=(const Toy &toy);

        friend std::ostream &operator<<(std::ostream &os, const ConfirmationOrder &cOrder);
    };
}

#endif