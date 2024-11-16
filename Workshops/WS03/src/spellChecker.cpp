#include "spellChecker.h"

#include <fstream>
#include <iomanip>
#include <sstream>

namespace seneca {

SpellChecker::SpellChecker(const char *filename) {
  for (size_t i = 0; i < 6; i++) {
    m_misCount[i] = 0;
  }

  std::ifstream file(filename);
  if (!file) {
    throw std::runtime_error("Could not open file: " + std::string(filename));
  }

  size_t i = 0;
  std::string line;
  while (std::getline(file, line)) {
    if (i >= 6 || line.empty()) {
      break;
    }

    // Format: "BAD_WORD GOOD_WORD"
    std::stringstream ss(line);
    ss >> m_badWords[i] >> m_goodWords[i];
    i++;
  }
}

void SpellChecker::operator()(std::string &text) {
  for (size_t i = 0; i < 6; i++) {
    std::string::size_type pos = 0;
    while ((pos = text.find(m_badWords[i], pos)) != std::string::npos) {
      text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
      pos += m_goodWords[i].length();
      m_misCount[i]++;
    }
  }
}

void SpellChecker::showStatistics(std::ostream &out) const {
  out << "Spellchecker Statistics\n";
  for (size_t i = 0; i < 6; i++) {
    out << std::left << std::setw(15) << m_badWords[i] << ": " << m_misCount[i]
        << " replacements\n";
  }
}

} // namespace seneca