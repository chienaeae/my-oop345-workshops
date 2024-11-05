#ifndef SENECA_FILESYSTEM_H
#define SENECA_FILESYSTEM_H

#include "Directory.h"
#include "Resource.h"

#include <string>

namespace seneca {

class Filesystem {
  Directory *m_root;
  Directory *m_current;

public:
  Filesystem(const std::string &filename, const std::string &rootName = "");

  Filesystem(const Filesystem &other) = delete;
  Filesystem &operator=(const Filesystem &other) = delete;

  Filesystem(Filesystem &&other) noexcept;

  Filesystem &operator=(Filesystem &&other) noexcept;

  Directory *handle_parent_path(const std::string &path);

  Filesystem &operator+=(Resource *resource);

  Directory *change_directory(const std::string &path = "");

  Directory *get_current_directory() const;

  ~Filesystem();
};

} // namespace seneca

#endif