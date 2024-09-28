#include "Pair.h"

#include <iomanip>
#include <iostream>

using namespace std;

namespace seneca {

Pair::Pair(const Pair &other) {
  m_key = other.m_key;
  m_value = other.m_value;
}

Pair &Pair::operator=(const Pair &other) {
  if (this != &other) {
    m_key = other.m_key;
    m_value = other.m_value;
  }
  return *this;
}

ostream &operator<<(ostream &os, const Pair &pair) {
  os << right << setw(20) << pair.m_key << ": " << pair.m_value;
  return os;
}

}; // namespace seneca