// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
//
// Chia-Yu Chien
// 157049222
// cchien8@myseneca.ca

#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include "mediaItem.h"
#include <string>
#include <vector>

namespace seneca {

class Collection {
  std::string m_name;
  std::vector<MediaItem *> m_items;
  void (*m_observer)(const Collection &, const MediaItem &);

public:
  Collection(const std::string &name);
  Collection(const Collection &other) = delete;
  Collection &operator=(const Collection &other) = delete;
  Collection(Collection &&other) noexcept = delete;
  Collection &operator=(Collection &&other) noexcept = delete;

  ~Collection();

  const std::string &name() const;

  size_t size() const;

  void setObserver(void (*observer)(const Collection &, const MediaItem &));

  Collection &operator+=(MediaItem *item);

  MediaItem *operator[](size_t idx) const;

  MediaItem *operator[](const std::string &title) const;

  void removeQuotes();

  void sort(const std::string &field);
};

std::ostream &operator<<(std::ostream &os, const Collection &collection);

} // namespace seneca

#endif // SENECA_COLLECTION_H
