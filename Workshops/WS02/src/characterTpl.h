#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H

#include "character.h"
#include <iostream>

namespace seneca {

template <typename T> class CharacterTpL : public Character {
  int m_healthMax;
  T m_health;

public:
  CharacterTpL(const char *name, int healthMax)
      : Character(name), m_healthMax(healthMax) {
    m_health = (int)m_healthMax;
  }

  CharacterTpL(const CharacterTpL &other)
      : Character(other.getName().c_str()), m_healthMax(other.m_healthMax) {
    m_health = (int)other.m_healthMax;
  }

  void takeDamage(int dmg) override {
    m_health -= dmg;
    if (m_health < 0) {
      m_health = 0;
    }

    if (Character::isAlive() == false) {
      std::cout << "    " << Character::getName() << " has been defeated!\n";
    } else {
      std::cout << "    " << Character::getName() << " took " << dmg
                << " damage, " << getHealth() << " health remaining.\n";
    }
  }

  int getHealth() const override { return static_cast<int>(m_health); }

  int getHealthMax() const override { return m_healthMax; }

  void setHealth(int health) override { m_health = health; }

  void setHealthMax(int health) override { m_healthMax = health; }
};

} // namespace seneca

#endif