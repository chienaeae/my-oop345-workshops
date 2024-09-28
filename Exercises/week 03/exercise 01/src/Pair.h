#ifndef SENECA_PAIR_H
#define SENECA_PAIR_H

#include <string>

namespace seneca {

class Pair {
  std::string m_key{};
  std::string m_value{};

public:
  const std::string &getKey() const { return m_key; }
  const std::string &getValue() const { return m_value; }
  Pair() {};
  Pair(const std::string &key, const std::string &value)
      : m_key{key}, m_value{value} {};

  // TODO: Add here the missing prototypes for the members
  //           that are necessary if this class is to be used
  //           with the template classes described below.
  //       Implement them in the Pair.cpp file.
  Pair(const Pair &other);

  Pair &operator=(const Pair &other);

  bool operator==(const Pair &other) const { return m_key == other.m_key; };

  bool operator!=(const Pair &other) const { return !(*this == other); }

  friend std::ostream &operator<<(std::ostream &os, const Pair &pair);
};

} // namespace seneca

#endif