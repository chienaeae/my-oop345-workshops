// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
//
// Chia-Yu Chien
// 157049222
// cchien8@myseneca.ca

#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include "book.h"
#include "mediaItem.h"
#include <iostream>
#include <string>

namespace seneca {

class Book : public MediaItem {
  std::string m_author;

  std::string m_country;

  double m_price;

  Book();

public:
  void display(std::ostream &out = std::cout) const override;

  static Book *createItem(const std::string &strBook);
};

} // namespace seneca

#endif // SENECA_BOOK_H
