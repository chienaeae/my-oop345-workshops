#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H

#include <iostream>

namespace seneca {

extern double g_taxrate;
extern double g_dailydiscount;

class FoodOrder {
    char m_customerName[11];
    char* m_orderDescription;
    double m_price;
    bool m_isDailySpecial;

public:
    FoodOrder();
    FoodOrder(const FoodOrder& other);
    FoodOrder& operator= (const FoodOrder& other);
    ~FoodOrder();
    void read(std::istream& in);
    void display() const;
};

}

#endif