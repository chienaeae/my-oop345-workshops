#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <string>

namespace seneca {

class Utilities {
  static char m_delimiter;

  size_t m_widthField = 1;

public:
  void trim(std::string &str);

  void setFieldWidth(size_t newWidth);

  size_t getFieldWidth() const;

  std::string extractToken(const std::string &str, size_t &next_pos,
                           bool &more);

  static void setDelimiter(char newDelimiter);

  static char getDelimiter();
};

} // namespace seneca

#endif // SENECA_UTILITIES_H
