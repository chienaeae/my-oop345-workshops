#include "team.h"

#include <iostream>
#include <string>

using namespace std;

namespace seneca {

void Team::addMember(const Character *c) {
  if (findMember(c->getName()) != -1) {
    return;
  }

  if (m_size == m_capacity) {
    m_capacity *= 2;
    Character **temp = new Character *[m_capacity];
    for (size_t i = 0; i < m_size; ++i) {
      temp[i] = m_team[i];
    }
    delete[] m_team;
    m_team = temp;
  }

  m_team[m_size++] = c->clone();
}

void Team::removeMember(const string &c) {
  int index = findMember(c);
  if (index == -1) {
    return;
  }

  delete m_team[index];

  for (size_t i = index; i < m_size - 1; ++i) {
    m_team[i] = m_team[i + 1];
  }
  m_size--;
}

Character *Team::operator[](size_t idx) const {
  if (idx >= m_size) {
    return nullptr;
  }
  return m_team[idx];
}

void Team::showMembers() const {
  if (m_capacity == 0) {
    cout << "No team.\n";
    return;
  }

  cout << "[Team] " << m_name << "\n";
  for (size_t i = 0; i < m_size; ++i) {
    cout << "    " << i + 1 << ": " << *m_team[i] << "\n";
  }
}

} // namespace seneca