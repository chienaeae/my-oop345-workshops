#include "FoodOrder.h"

#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>

using namespace std;

namespace seneca {
    double g_taxrate = 0.0f;
    double g_dailydiscount = 0.0f;

    FoodOrder::FoodOrder(): m_customerName(), m_orderDescription(nullptr), m_price(0.0), m_isDailySpecial(false) {
        m_customerName[0] = '\0';
    }

    FoodOrder::FoodOrder(const FoodOrder& other){
        strcpy(m_customerName, other.m_customerName);
        m_price = other.m_price;
        m_isDailySpecial = other.m_isDailySpecial;

        if(other.m_orderDescription != nullptr) {
            m_orderDescription = new char[strlen(other.m_orderDescription) + 1];
            strcpy(m_orderDescription, other.m_orderDescription);
        } else {
            m_orderDescription = nullptr;
        }
    }

    FoodOrder& FoodOrder::operator=(const FoodOrder& other){
        if(this != &other){
            strcpy(m_customerName, other.m_customerName);
            m_price = other.m_price;
            m_isDailySpecial = other.m_isDailySpecial;

            delete[] m_orderDescription;
            if(other.m_orderDescription != nullptr) {
                m_orderDescription = new char[strlen(other.m_orderDescription) + 1];
                strcpy(m_orderDescription, other.m_orderDescription);
            } else {
                m_orderDescription = nullptr;
            }
        }
        return *this;
    }
    FoodOrder::~FoodOrder(){
        delete[] m_orderDescription;
    }

    void FoodOrder::read(istream& in){
        if(in.fail()){
            return;
        }

        // Read Format:
        // <Customer Name>,<Order Description>,<Price>,<Daily Special Status>[newline]
        // 1. Read Customer Name
        in.getline(m_customerName, 10, ',');
        // 2. Read Order Description
        delete[] m_orderDescription;
        m_orderDescription = nullptr;
        string temp;
        getline(in, temp, ',');
        m_orderDescription = new char[temp.length() + 1];
        strcpy(m_orderDescription, temp.c_str());
        // 3. Read Price
        in >> m_price;
        getline(in, temp, ',');
        // 4. Read Daily Special Status
        char special;
        in >> special;
        if(special == 'Y'){
            m_isDailySpecial = true;
        } else {
            m_isDailySpecial = false;
        }
        in.ignore(1000, '\n');
    }

    void FoodOrder::display() const{
        // Note: 
        // holds the number of times that this function has been 
        // called (use a local-to-function variable that remains in 
        // memory for the lifetime of the program
        static int counter = 0;
        counter++;

        if (m_customerName[0] == '\0') {
            // display format: 
            // COUNTER. No Order
            cout  << left << setw(2) << counter << ". No Order" << endl;
            return;            
        }

        // display format:
        // COUNTER. Name          |Order Description        |Price w/Tax |Special Price
        double price = m_price + m_price * g_taxrate;
        cout << left << setw(2) << counter  << ". " 
            << setw(10) << m_customerName  << "|" 
            << setw(25) << m_orderDescription << "|" 
            << setw(12) << fixed << setprecision(2) << price << "|";
        if(m_isDailySpecial){
            cout << right << setw(13) << price / g_dailydiscount << endl;
        } else {
            cout <<  endl;
        }
    }
}