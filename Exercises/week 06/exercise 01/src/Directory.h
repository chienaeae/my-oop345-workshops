#ifndef SENECA_DIRECTORY_H
#define SENECA_DIRECTORY_H

#include "Resource.h"

#include <iostream>
#include <string>
#include <vector>

namespace seneca {
class Directory : public Resource {
  std::vector<Resource *> m_contents;

public:
  Directory(const std::string name);

  Directory(const Directory &other) = delete;
  Directory &operator=(const Directory &other) = delete;
  Directory(Directory &&other) noexcept = delete;
  Directory &operator=(Directory &&other) noexcept = delete;

  void update_parent_path(const std::string &path) override;

  std::string name() const override;

  int count() const override;

  std::string path() const override;

  size_t size() const override;

  NodeType type() const override;

  Directory &operator+=(Resource *resource);

  bool contains(const OpFlags &flag, const std::vector<OpFlags> &flags) const;

  bool contains(const FormatFlags &flag,
                const std::vector<FormatFlags> &flags) const;

  Resource *find(const std::string &name,
                 const std::vector<OpFlags> &flags = {}) const;

  void remove(const std::string &name, const std::vector<OpFlags> &flags = {});

  void display(std::ostream &,
               const std::vector<FormatFlags> &flags = {}) const;

  ~Directory() override;
};
} // namespace seneca

#endif