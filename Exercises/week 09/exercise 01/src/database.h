#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H

#define MAX_SIZE 20

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

namespace seneca {

enum class Err_Status {
  Err_Success,
  Err_NotFound,
  Err_OutOfMemory,
};

template <typename T> class Database {
  std::string m_filename;

  int m_size;

  std::string m_keys[MAX_SIZE];

  T m_values[MAX_SIZE];

  static std::shared_ptr<Database<T>> m_instance;

  Database(const std::string &filename) : m_filename(filename), m_size(0) {
    std::cout << "[" << m_instance << "] Database(const std::string&)"
              << std::endl;

    std::ifstream file(m_filename);
    if (file.is_open()) {
      while (!file.eof() && m_size < MAX_SIZE) {
        file >> m_keys[m_size];
        file >> m_values[m_size];
        m_keys[m_size].replace(m_keys[m_size].find('_'), 1, " ");
        encryptDecrypt(m_values[m_size]);
        ++m_size;
      }
      file.close();
    }
  }

  void encryptDecrypt(T &value);

public:
  static std::shared_ptr<Database<T>>
  getInstance(const std::string &dbFileName) {
    if (m_instance == nullptr) {
      m_instance = std::shared_ptr<Database<T>>(new Database(dbFileName));
    }

    return m_instance;
  }

  Err_Status GetValue(const std::string &key, T &value) {
    for (int i = 0; i < m_size; ++i) {
      if (m_keys[i] == key) {
        value = m_values[i];
        return Err_Status::Err_Success;
      }
    }
    return Err_Status::Err_NotFound;
  }

  Err_Status SetValue(const std::string &key, const T &value) {
    if (m_size == MAX_SIZE) {
      return Err_Status::Err_OutOfMemory;
    }

    m_keys[m_size] = key;
    m_values[m_size] = value;
    ++m_size;
    return Err_Status::Err_Success;
  }

  ~Database() {
    std::cout << "[" << m_instance << "] ~Database()" << std::endl;

    std::ofstream file(m_filename + ".bkp.txt");
    if (file.is_open()) {
      for (int i = 0; i < m_size; ++i) {
        std::string key = m_keys[i];

        T value = m_values[i];
        encryptDecrypt(value);

        file << std::left << std::setw(25) << key << " -> " << value
             << std::endl;
      }
    }
    file.close();
  }
};

template <>
inline void Database<std::string>::encryptDecrypt(std::string &value) {
  const char secret[]{"secret encryption key"};

  for (char &c : value) {
    for (size_t i = 0; i < sizeof(secret) / sizeof(secret[0]); i++) {
      c = c ^ secret[i];
    }
  }
}

template <> inline void Database<long long>::encryptDecrypt(long long &value) {
  const char secret[]{"super secret encryption key"};

  char *charSecret = reinterpret_cast<char *>(&value);
  for (size_t i = 0; i < sizeof(value); i++) {
    for (size_t j = 0; j < sizeof(secret) / sizeof(secret[0]); j++) {
      charSecret[i] = charSecret[i] ^ secret[j];
    }
  }
}

template <typename T> std::shared_ptr<Database<T>> Database<T>::m_instance{};

} // namespace seneca

#endif // SENECA_DATABASE_H
