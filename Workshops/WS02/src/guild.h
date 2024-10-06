#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include "character.h"
#include <string>

namespace seneca {

class Guild {
  size_t m_size;
  size_t m_capacity;
  Character **m_members;

  std::string m_name;

  int findMember(const std::string &c) const {
    for (size_t i = 0; i < m_size; ++i) {
      if (m_members[i]->getName() == c) {
        return i;
      }
    }
    return -1;
  }

public:
  Guild()
      : m_size(0), m_capacity(2), m_members(new Character *[m_capacity]),
        m_name("") {}

  Guild(const char *name)
      : m_size(0), m_capacity(2), m_members(new Character *[m_capacity]),
        m_name(name) {}

  Guild(const Guild &other) {
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_members = new Character *[m_capacity];
    for (size_t i = 0; i < m_size; ++i) {
      m_members[i] = other.m_members[i];
    }
    m_name = other.m_name;
  }

  Guild &operator=(const Guild &other) {
    if (this != &other) {
      delete[] m_members;

      m_size = other.m_size;
      m_capacity = other.m_capacity;
      m_members = new Character *[m_capacity];
      for (size_t i = 0; i < m_size; ++i) {
        m_members[i] = other.m_members[i];
      }
      m_name = other.m_name;
    }

    return *this;
  }

  Guild(Guild &&other) noexcept {
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_members = other.m_members;
    m_name = other.m_name;

    other.m_size = 0;
    other.m_capacity = 0;
    other.m_members = nullptr;
    other.m_name = "";
  }

  Guild &operator=(Guild &&other) noexcept {
    if (this != &other) {
      delete[] m_members;

      m_size = other.m_size;
      m_capacity = other.m_capacity;
      m_members = other.m_members;
      m_name = other.m_name;

      other.m_size = 0;
      other.m_capacity = 0;
      other.m_members = nullptr;
      other.m_name = "";
    }
    return *this;
  }

  ~Guild() { delete[] m_members; }

  void addMember(Character *c);

  void removeMember(const std::string &c);

  Character *operator[](size_t idx) const;

  void showMembers() const;
};
} // namespace seneca

#endif