#ifndef SENECA_PROTEINDATABASE_H
#define SENECA_PROTEINDATABASE_H

#include <string>

namespace seneca {

class ProteinDatabase {
  size_t m_size;
  std::string *m_uniqueIDs;
  std::string *m_proteins;

public:
  ProteinDatabase();
  ProteinDatabase(const std::string &filename);

  // Copy constructor and copy assignment operator
  ProteinDatabase(const ProteinDatabase &other);
  ProteinDatabase &operator=(const ProteinDatabase &other);

  // Move constructor and move assignment operator
  ProteinDatabase(ProteinDatabase &&other) noexcept;
  ProteinDatabase &operator=(ProteinDatabase &&other) noexcept;

  ~ProteinDatabase();

  size_t readNumOfProteins(const std::string &filename);

  size_t size() const;

  std::string operator[](size_t) const;

  std::string getUID(size_t) const;
};

} // namespace seneca

#endif