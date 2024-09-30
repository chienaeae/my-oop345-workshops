#ifndef SENECA_TOY_H
#define SENECA_TOY_H

#include <string>
#include <iostream>

namespace seneca
{
    class Toy
    {
        static constexpr double HST = 0.13;

        unsigned int m_id;
        std::string m_name;
        int m_numItems;
        double m_price; // without tax

    public:
        Toy();

        // The string will be in the format of:
        // ID:NAME:NUM:PRICE
        Toy(const std::string &toy);

        void update(int numItems);

        // Toy ID: NAME QTY items @ PRICE/item  subtotal: SUBTOTAL  tax: TAX  total: TOTAL_PRICE<endl>
        friend std::ostream &operator<<(std::ostream &os, const Toy &toy);
    };

}

#endif