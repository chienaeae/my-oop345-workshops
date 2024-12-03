#include "Utilities.h"

#include <string>

namespace seneca {

char Utilities::m_delimiter = ',';

void Utilities::trim(std::string &str) {
  size_t pos = str.find_last_not_of(' ');
  if (pos != std::string::npos) {
    str = str.substr(0, pos + 1);
  }

  pos = str.find_first_not_of(' ');
  if (pos != std::string::npos) {
    str = str.substr(pos);
  }
}

void Utilities::setFieldWidth(size_t newWidth) { m_widthField = newWidth; }

size_t Utilities::getFieldWidth() const { return m_widthField; }

std::string Utilities::extractToken(const std::string &str, size_t &next_pos,
                                    bool &more) {
  if (str[next_pos] == m_delimiter) {
    more = false;
    throw std::string("ERROR: No token found");
  } else if (next_pos >= str.length()) {
    more = false;
    throw std::string("ERROR: No token found");
  }

  std::string extractedToken;
  size_t pos = str.find(m_delimiter, next_pos);
  extractedToken = str.substr(next_pos, pos - next_pos);

  if (pos == std::string::npos) {
    more = false;
  } else {
    next_pos += extractedToken.length() + 1;
    more = true;
  }

  trim(extractedToken);

  // updates the current object's m_widthField data member if its current
  // value is less than the size of the token extracted.
  if (extractedToken.length() > getFieldWidth()) {
    setFieldWidth(extractedToken.length());
  }

  return extractedToken;
}

void Utilities::setDelimiter(char newDelimiter) { m_delimiter = newDelimiter; }

char Utilities::getDelimiter() { return m_delimiter; }

} // namespace seneca
