#include "guild.h"

#include <iostream>
#include <string>

using namespace std;

namespace seneca {

void Guild::addMember(Character *c) {
  int index = findMember(c->getName());
  if (index != -1) {
    return;
  }

  if (m_size == m_capacity) {
    m_capacity *= 2;
    Character **temp = new Character *[m_capacity];
    for (size_t i = 0; i < m_size; ++i) {
      temp[i] = m_members[i];
    }
    delete[] m_members;
    m_members = temp;
  }

  c->setHealthMax(c->getHealthMax() + 300);
  c->setHealth(c->getHealthMax());

  m_members[m_size++] = c;
}

void Guild::removeMember(const std::string &c) {
  int index = findMember(c);
  if (index == -1) {
    return;
  }

  m_members[index]->setHealthMax(m_members[index]->getHealthMax() - 300);
  m_members[index]->setHealth(m_members[index]->getHealthMax());

  for (size_t i = index; i < m_size - 1; ++i) {
    m_members[i] = m_members[i + 1];
  }
  m_size--;
}

Character *Guild::operator[](size_t idx) const {
  if (idx >= m_size) {
    return nullptr;
  }

  return m_members[idx];
}

void Guild::showMembers() const {
  if (m_capacity == 0) {
    cout << "No guild." << m_name << "\n";
    return;
  }

  cout << "[Guild] " << m_name << "\n";
  for (size_t i = 0; i < m_size; ++i) {
    cout << "    " << i + 1 << ": " << *m_members[i] << "\n";
  }
}

} // namespace seneca