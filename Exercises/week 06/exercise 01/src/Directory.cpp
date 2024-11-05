#include "Directory.h"

#include "Flags.h"
#include "Resource.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace seneca {

Directory::Directory(const std::string name) { m_name = name; }

void Directory::update_parent_path(const std::string &path) {
  m_parent_path = path;

  for (auto resource : m_contents) {
    resource->update_parent_path(path + name());
  }
}

NodeType Directory::type() const { return NodeType::DIR; }

std::string Directory::path() const { return m_parent_path + name(); }

std::string Directory::name() const { return m_name; }

int Directory::count() const { return m_contents.size(); }

size_t Directory::size() const {
  size_t total_size = 0;
  for (auto res : m_contents) {
    total_size += res->size();
  }
  return total_size;
}

Directory &Directory::operator+=(Resource *resource) {
  for (auto res : m_contents) {
    if (res->name() == resource->name()) {
      throw "Directory already contains a resource with the same name";
    }
  }

  resource->update_parent_path(path());
  m_contents.push_back(resource);
  return *this;
}

bool Directory::contains(const FormatFlags &flag,
                         const std::vector<FormatFlags> &flags) const {
  return std::find(flags.begin(), flags.end(), flag) != flags.end();
}

bool Directory::contains(const OpFlags &flag,
                         const std::vector<OpFlags> &flags) const {
  return std::find(flags.begin(), flags.end(), flag) != flags.end();
}

Resource *Directory::find(const std::string &name,
                          const std::vector<OpFlags> &flags) const {
  Resource *target = nullptr;

  // Check if the recursive flag is set
  bool recursiveFlag = contains(OpFlags::RECURSIVE, flags);

  // Search for the first resource that matches the name
  if (!recursiveFlag) {
    for (auto res : m_contents) {
      if (res->name() == name) {
        target = res;
        break;
      }
    }

    return target;
  }

  // Recursive search for the first resource that matches the name
  for (auto res : m_contents) {
    if (res->name() == name) {
      target = res;
      break;
    } else if (res->type() == NodeType::DIR) {
      target = static_cast<Directory *>(res)->find(name, flags);
      if (target != nullptr) {
        break;
      }
    }
  }

  return target;
}

void Directory::remove(const std::string &name,
                       const std::vector<OpFlags> &flags) {
  size_t index = -1;
  for (size_t i = 0; i < m_contents.size(); i++) {
    if (m_contents[i]->name() == name) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    throw name + " does not exist in " + path();
  }

  Resource *target = m_contents[index];
  if (target->type() == NodeType::DIR) {
    bool recursiveFlag = contains(OpFlags::RECURSIVE, flags);
    if (!recursiveFlag) {
      throw target->name() +
          " is a directory. Pass the recursive flag to delete directories.";
    }
  }

  m_contents.erase(m_contents.begin() + index);
  delete target;
}

void Directory::display(std::ostream &os,
                        const std::vector<FormatFlags> &flags) const {
  os << "Total size: " << size() << " bytes\n";

  for (auto res : m_contents) {
    // Handle Directory
    if (res->type() == NodeType::DIR) {
      Directory *dir = static_cast<Directory *>(res);
      os << "D | " << std::setw(15) << std::left << res->name();

      if (contains(FormatFlags::LONG, flags)) {
        os << " | " << std::setw(2) << std::right << dir->m_contents.size()
           << " | " << std::setw(10) << std::right << dir->size() << " bytes";
      }
    }
    // Handle File
    else if (res->type() == NodeType::FILE) {
      os << "F | " << std::setw(15) << std::left << res->name();

      if (contains(FormatFlags::LONG, flags)) {
        os << " | " << std::setw(2) << std::right << " "
           << " | " << std::setw(10) << std::right << res->size() << " bytes";
      }
    }

    os << " |\n";
  }
}

Directory::~Directory() {
  for (auto res : m_contents) {
    delete res;
  }
}

} // namespace seneca
