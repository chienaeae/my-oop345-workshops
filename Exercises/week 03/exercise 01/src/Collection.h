#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include "Pair.h"
#include <iostream>
#include <stdio.h>

namespace seneca {

template <typename T, int CAPACITY> class Collection {
  T *m_data;
  int m_size;
  int m_capacity;

  static T m_defaultDate;

public:
  Collection() : m_size(0), m_capacity(10) { m_data = new T[m_capacity]; }

  virtual ~Collection() { delete[] m_data; }

  int size() const { return m_size; }

  void display(std::ostream &os = std::cout) const {
    std::cout << "----------------------\n";
    std::cout << "| Collection Content |\n";
    std::cout << "----------------------\n";

    for (int i = 0; i < m_size; i++) {
      os << m_data[i] << "\n";
    }
    std::cout << "----------------------\n";
  }

  virtual bool add(const T &item) {
    if (m_size == m_capacity && m_capacity < CAPACITY) {
      int newCapacity = m_capacity *= 2;
      if (newCapacity > CAPACITY) {
        newCapacity = CAPACITY;
      }

      T *temp = new T[newCapacity];

      for (int i = 0; i < m_size; i++) {
        temp[i] = m_data[i];
      }

      delete[] m_data;

      m_data = temp;
      m_capacity = newCapacity;
    }

    if (m_size < m_capacity) {
      m_data[m_size++] = item;
      return true;
    }
    return false;
  }

  // Note: returns a copy of the element stored in the collection at the
  // specified index.
  const T &operator[](int index) const {
    if (index < 0 || index >= m_size) {
      return m_defaultDate;
    }
    return m_data[index];
  }
};

template <typename T, int CAPACITY>
T Collection<T, CAPACITY>::m_defaultDate = T{};

template <>
Pair Collection<Pair, 100>::m_defaultDate = Pair{"No Key", "No Value"};

} // namespace seneca

#endif