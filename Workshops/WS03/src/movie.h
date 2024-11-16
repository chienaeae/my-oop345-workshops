// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
//
// Chia-Yu Chien
// 157049222
// cchien8@myseneca.ca

#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include "mediaItem.h"

namespace seneca {

class Movie : public MediaItem {
  Movie();

public:
  void display(std::ostream &out = std::cout) const override;

  static Movie *createItem(const std::string &strMovie);
};

} // namespace seneca

#endif // SENECA_MOVIE_H