#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include "characterTpl.h"
#include "health.h"
#include <iostream>

namespace seneca {

template <typename Weapon_t> class Archer : public CharacterTpL<SuperHealth> {
  int m_baseAttack;
  int m_baseDefense;

  Weapon_t m_weapon;

public:
  Archer(const char *name, int healthMax, int baseAttack, int baseDefense,
         Weapon_t weapon)
      : CharacterTpL<SuperHealth>(name, healthMax), m_baseAttack(baseAttack),
        m_baseDefense(baseDefense), m_weapon(weapon) {}

  Archer(const Archer &other) : CharacterTpL<SuperHealth>(other) {
    m_baseAttack = other.m_baseAttack;
    m_baseDefense = other.m_baseDefense;
    m_weapon = other.m_weapon;
  }

  int getAttackAmnt() const override { return m_baseAttack * 1.3; }

  int getDefenseAmnt() const override { return m_baseDefense * 1.2; }

  Character *clone() const override { return new Archer(*this); }

  void attack(Character *enemy) override {
    std::cout << CharacterTpL<SuperHealth>::getName() << " is attacking "
              << enemy->getName() << ".\n";
    int dmg = getAttackAmnt();
    std::cout << "Archer deals " << dmg << " ranged damage!\n";
    enemy->takeDamage(dmg);
  }

  void takeDamage(int dmg) override {
    std::cout << CharacterTpL<SuperHealth>::getName() << " is attacked for "
              << dmg << "damage.\n";
    std::cout << "    Archer has a defense of " << getDefenseAmnt()
              << ". Reducing damage received.\n";

    dmg -= getDefenseAmnt();
    if (dmg < 0) {
      dmg = 0;
    }

    CharacterTpL<SuperHealth>::takeDamage(dmg);
  }
};

} // namespace seneca

#endif