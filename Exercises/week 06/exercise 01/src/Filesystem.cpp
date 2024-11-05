#include "Filesystem.h"

#include "Directory.h"
#include "File.h"
#include <fstream>
#include <iostream>
#include <string>

namespace seneca {
std::string trim(const std::string &str) {
  if (str.empty()) {
    return str;
  }

  std::string result = str;
  size_t start = result.find_first_not_of(" \t\n\r\f\v");
  result = (start == std::string::npos) ? "" : result.substr(start);

  size_t end = result.find_last_not_of(" \t\n\r\f\v");
  result = (end == std::string::npos) ? "" : result.substr(0, end + 1);

  return result;
}

Filesystem::Filesystem(const std::string &filename,
                       const std::string &rootName) {
  m_root = new Directory(rootName);
  m_current = m_root;

  std::ifstream file(filename);
  if (!file) {
    throw std::string("Failed to open file: ") + filename;
  }

  std::string line;
  while (std::getline(file, line)) {

    // Handle the line is a file, the format is `FILE_PATH  |  FILE_CONTENTS`
    if (line.find('|') != std::string::npos) {
      std::string path = trim(line.substr(0, line.find('|')));
      std::string contents = trim(line.substr(line.find('|') + 1));

      // Handle the parent path of the file
      std::string parent_path = path.substr(0, path.rfind('/') + 1);
      m_current = handle_parent_path(parent_path);

      // Handle the name of the file
      std::string name = path.substr(path.rfind('/') + 1);
      File *file = new File(name, contents);
      *m_current += file;
    }
    // Handle the line is a directory, the format is `DIRECTORY_PATH`
    else {
      // Handle the parent path of the directory
      m_current = handle_parent_path(trim(line));
    }
  }

  file.close();
  m_current = m_root;
}

Filesystem::Filesystem(Filesystem &&other) noexcept {
  m_root = other.m_root;
  m_current = other.m_current;
  other.m_root = nullptr;
  other.m_current = nullptr;
}

Filesystem &Filesystem::operator=(Filesystem &&other) noexcept {
  if (this != &other) {
    m_root = other.m_root;
    m_current = other.m_current;
    other.m_root = nullptr;
    other.m_current = nullptr;
    return *this;
  }
  return *this;
}

Directory *Filesystem::handle_parent_path(const std::string &path) {
  Directory *current = m_root;
  size_t pre_slash_pos = 0;
  size_t slash_pos = 0;
  while (true) {
    slash_pos = path.find('/', slash_pos);

    if (slash_pos == std::string::npos) {
      break;
    }

    slash_pos++; // To include the slash in the directory name

    std::string dir_name =
        path.substr(pre_slash_pos, slash_pos - pre_slash_pos);
    pre_slash_pos = slash_pos;

    Resource *res = current->find(dir_name, {});

    if (res == nullptr) {
      res = new Directory(dir_name);
      *current += res;
      current = static_cast<Directory *>(res);

    } else if (res->type() == NodeType::FILE) {
      throw "File already exists: " + dir_name;

    } else if (res->type() == NodeType::DIR) {
      current = static_cast<Directory *>(res);
    }
  }

  return current;
}

Filesystem &Filesystem::operator+=(Resource *resource) {
  *m_current += resource;
  return *this;
}

Directory *Filesystem::change_directory(const std::string &path) {
  if (path.empty()) {
    m_current = m_root;
    return m_current;
  }

  Resource *res = m_current->find(path, {});
  if (res == nullptr) {
    throw std::invalid_argument("Cannot change directory! " + path +
                                " not found!");
  }

  m_current = static_cast<Directory *>(res);
  return m_current;
}

Directory *Filesystem::get_current_directory() const { return m_current; }

Filesystem::~Filesystem() { delete m_root; }
} // namespace seneca
