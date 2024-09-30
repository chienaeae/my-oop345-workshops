#ifndef SENECA_SHOPPINGCART_H
#define SENECA_SHOPPINGCART_H

#include <string>

#include "toy.h"

#include <iostream>
namespace seneca
{
    class ShoppingCart
    {
        std::string m_name;
        unsigned int m_ageOfChild;
        size_t m_numToys;
        const Toy **m_pToys;

        std::ostream &printHeader(std::ostream &os) const;

        std::ostream &printContent(std::ostream &os) const;

    public:
        ShoppingCart(const std::string &name, int age, const Toy *toys[], size_t count);

        // Copy constructor and copy assignment operator
        ShoppingCart(const ShoppingCart &other);
        ShoppingCart &operator=(const ShoppingCart &other);

        // Move constructor and move assignment operator
        ShoppingCart(ShoppingCart &&other) noexcept;
        ShoppingCart &operator=(ShoppingCart &&other) noexcept;

        ~ShoppingCart();

        void clear();

        friend std::ostream &operator<<(std::ostream &os, const ShoppingCart &cart);
    };
}

#endif