// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
//
// Chia-Yu Chien
// 157049222
// cchien8@myseneca.ca

#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <string>
#include <vector>

namespace seneca {

class SpellChecker {
  std::string m_badWords[6];
  std::string m_goodWords[6];
  size_t m_misCount[6];

public:
  SpellChecker(const char *filename);

  void operator()(std::string &text);

  void showStatistics(std::ostream &out) const;
};

} // namespace seneca

#endif // SENECA_SPELLCHECKER_H
