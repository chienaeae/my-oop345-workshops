#ifndef SENECA_FILE_H
#define SENECA_FILE_H

#include "Flags.h"
#include "Resource.h"

namespace seneca {

class File : public Resource {
  std::string m_contents;

public:
  File(const std::string name, const std::string contents);

  void update_parent_path(const std::string &path) override;

  std::string name() const override;

  int count() const override;

  std::string path() const override;

  size_t size() const override;

  NodeType type() const override;

  ~File() override = default;
};
} // namespace seneca

#endif