#ifndef SENECA_SET_H
#define SENECA_SET_H

#include "Collection.h"
#include <stdlib.h>

namespace seneca {

template <typename T> class Set : public Collection<T, 100> {

  bool checkExists(const T &item) {
    for (int i = 0; i < Collection<T, 100>::size(); i++) {
      if (Collection<T, 100>::operator[](i) == item) {
        return true;
      }
    }
    return false;
  }

  bool add(const T &item) override {
    if (checkExists(item)) {
      return false;
    }
    return Collection<T, 100>::add(item);
  }
};

template <> bool Set<double>::checkExists(const double &item) {
  for (int i = 0; i < Collection<double, 100>::size(); i++) {
    if (std::abs(Collection<double, 100>::operator[](i) - item) <= 0.01) {
      return true;
    }
  }
  return false;
}

template <> bool Set<double>::add(const double &item) {
  if (checkExists(item)) {
    return false;
  }
  return Collection<double, 100>::add(item);
}

} // namespace seneca

#endif