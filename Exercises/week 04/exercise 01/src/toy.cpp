#include "toy.h"

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

namespace seneca
{
    string trim(const string &str)
    {
        // p1 is the position of the first non-space character
        size_t p1 = str.find_first_not_of(' ');
        if (p1 == string::npos)
            return "";

        // p2 is the position of the last non-space character
        size_t p2 = str.find_last_not_of(' ');
        if (p2 == string::npos)
            return "";

        return str.substr(p1, p2 - p1 + 1);
    }

    Toy::Toy() : m_id(0), m_name(""), m_numItems(0), m_price(0.0) {}

    Toy::Toy(const string &strToy)
    {
        // extract the id
        size_t p1 = strToy.find(':');
        m_id = stoi(trim(strToy.substr(0, p1)));

        // extract the name
        size_t p2 = strToy.find(':', p1 + 1);
        m_name = trim(strToy.substr(p1 + 1, p2 - p1 - 1));

        // extract the number of items
        size_t p3 = strToy.find(':', p2 + 1);
        m_numItems = stoi(trim(strToy.substr(p2 + 1, p3 - p2 - 1)));

        // extract the price
        m_price = stod(trim(strToy.substr(p3 + 1)));
    }

    void Toy::update(int numItems)
    {
        m_numItems = numItems;
    }

    ostream &operator<<(ostream &os, const Toy &toy)
    {
        double subtotal = toy.m_numItems * toy.m_price;
        double tax = subtotal * Toy::HST;
        double total = subtotal + tax;

        os << "Toy ";
        os << right << setw(8) << setfill('0') << toy.m_id << ": ";

        os << right << setw(24) << setfill('.') << toy.m_name << " ";

        os << right << setw(2) << setfill(' ') << toy.m_numItems << " items @ ";
        os << right << setw(6) << toy.m_price << "/item  ";
        os << "subtotal: " << right << setw(7) << fixed << setprecision(2) << subtotal << "  ";
        os << "tax: " << right << setw(6) << tax << "  ";
        os << "total: " << right << setw(7) << total << endl;

        return os;
    }
}