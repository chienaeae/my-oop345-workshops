#include "ProteinDatabase.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

namespace seneca {

ProteinDatabase::ProteinDatabase()
    : m_size(0), m_uniqueIDs(nullptr), m_proteins(nullptr) {}

ProteinDatabase::ProteinDatabase(const std::string &filename)
    : m_size(0), m_uniqueIDs(nullptr), m_proteins(nullptr) {
  // Read the number of proteins in the file
  m_size = ProteinDatabase::readNumOfProteins(filename);
  if (m_size == 0) {
    return;
  }
  m_uniqueIDs = new string[m_size];
  m_proteins = new string[m_size];

  // Re-read the proteins in the file
  ifstream fs(filename);
  if (!fs.is_open()) {
    m_uniqueIDs = nullptr;
    m_proteins = nullptr;
    m_size = 0;
    return;
  }
  string temp;
  string aminoAcids;
  int cursor = -1;
  while (getline(fs, temp)) {
    if (temp.empty()) {
      continue;
    }

    if (temp[0] == '>') {
      cursor++;
      // Read the header of the entry (only the unique ID)
      size_t pos1 = temp.find_first_of('|');
      size_t pos2 = temp.find_last_of('|');
      m_uniqueIDs[cursor] = temp.substr(pos1 + 1, pos2 - pos1 - 1);
    } else {
      // Read the amino acids of the entry
      m_proteins[cursor] += temp;
    }
  }
  fs.close();
}

ProteinDatabase::ProteinDatabase(const ProteinDatabase &other)
    : m_size(other.m_size) {
  if (m_size == 0) {
    return;
  }

  m_uniqueIDs = new string[m_size];
  m_proteins = new string[m_size];
  for (size_t i = 0; i < m_size; i++) {
    m_uniqueIDs[i] = other.m_uniqueIDs[i];
    m_proteins[i] = other.m_proteins[i];
  }
}

ProteinDatabase &ProteinDatabase::operator=(const ProteinDatabase &other) {
  if (this == &other) {
    return *this;
  }

  delete[] m_uniqueIDs;
  delete[] m_proteins;
  m_size = other.m_size;
  if (m_size == 0) {
    return *this;
  }

  m_uniqueIDs = new string[m_size];
  m_proteins = new string[m_size];

  for (size_t i = 0; i < m_size; i++) {
    m_uniqueIDs[i] = other.m_uniqueIDs[i];
    m_proteins[i] = other.m_proteins[i];
  }

  return *this;
}

ProteinDatabase::ProteinDatabase(ProteinDatabase &&other) noexcept
    : m_size(other.m_size), m_uniqueIDs(other.m_uniqueIDs),
      m_proteins(other.m_proteins) {
  other.m_size = 0;
  other.m_uniqueIDs = nullptr;
  other.m_proteins = nullptr;
}

ProteinDatabase &ProteinDatabase::operator=(ProteinDatabase &&other) noexcept {
  if (this == &other) {
    return *this;
  }

  delete[] m_uniqueIDs;
  delete[] m_proteins;

  m_size = other.m_size;
  m_uniqueIDs = other.m_uniqueIDs;
  m_proteins = other.m_proteins;

  other.m_size = 0;
  other.m_uniqueIDs = nullptr;
  other.m_proteins = nullptr;
  return *this;
}

ProteinDatabase::~ProteinDatabase() {
  delete[] m_uniqueIDs;
  delete[] m_proteins;
}

size_t ProteinDatabase::readNumOfProteins(const string &filename) {
  ifstream fs(filename);
  if (!fs.is_open()) {
    return 0;
  }
  size_t count = 0;
  string temp;
  while (getline(fs, temp)) {
    if (temp.empty()) {
      continue;
    }
    if (temp[0] == '>') {
      count++;
    }
  }
  fs.close();
  return count;
}

size_t ProteinDatabase::size() const { return m_size; }

string ProteinDatabase::operator[](size_t idx) const {
  if (idx >= m_size) {
    return "";
  }
  return m_proteins[idx];
}

string ProteinDatabase::getUID(size_t idx) const {
  if (idx >= m_size) {
    return "None";
  }
  return m_uniqueIDs[idx];
}

} // namespace seneca