#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include "character.h"
#include <string>

namespace seneca {

class Team {
  size_t m_size = 0;
  size_t m_capacity = 0;
  Character **m_team;

  std::string m_name;

  int findMember(const std::string &c) const {
    for (size_t i = 0; i < m_size; ++i) {
      if (m_team[i]->getName() == c) {
        return i;
      }
    }
    return -1;
  }

public:
  Team()
      : m_size(0), m_capacity(2), m_team(new Character *[m_capacity]),
        m_name("") {}

  Team(const char *name)
      : m_size(0), m_capacity(2), m_team(new Character *[m_capacity]),
        m_name(name) {}

  Team(const Team &other) {
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_team = new Character *[m_capacity];
    for (size_t i = 0; i < m_size; ++i) {
      m_team[i] = other.m_team[i]->clone();
    }
    m_name = other.m_name;
  }

  Team &operator=(const Team &other) {
    if (this != &other) {
      for (size_t i = 0; i < m_size; ++i) {
        delete m_team[i];
      }
      delete[] m_team;

      m_size = other.m_size;
      m_capacity = other.m_capacity;
      m_team = new Character *[m_capacity];
      for (size_t i = 0; i < m_size; ++i) {
        m_team[i] = other.m_team[i]->clone();
      }
      m_name = other.m_name;
    }
    return *this;
  }

  Team(Team &&other) noexcept {
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_team = other.m_team;
    m_name = other.m_name;

    other.m_size = 0;
    other.m_capacity = 0;
    other.m_team = nullptr;
    other.m_name = "";
  }

  Team &operator=(Team &&other) noexcept {
    if (this != &other) {
      for (size_t i = 0; i < m_size; ++i) {
        delete m_team[i];
      }
      delete[] m_team;

      m_size = other.m_size;
      m_capacity = other.m_capacity;
      m_team = other.m_team;
      m_name = other.m_name;

      other.m_size = 0;
      other.m_capacity = 0;
      other.m_team = nullptr;
      other.m_name = "";
    }
    return *this;
  }

  ~Team() {
    for (size_t i = 0; i < m_size; ++i) {
      delete m_team[i];
    }
    delete[] m_team;
  }

  void addMember(const Character *c);

  void removeMember(const std::string &c);

  Character *operator[](size_t idx) const;

  void showMembers() const;
};

} // namespace seneca

#endif