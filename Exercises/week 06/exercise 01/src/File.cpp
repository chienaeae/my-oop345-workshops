#include "File.h"

#include "Flags.h"
#include "Resource.h"

#include <string>

namespace seneca {
File::File(const std::string name, const std::string contents) {
  // parent member
  m_name = name;
  // member
  m_contents = contents;
}

void File::update_parent_path(const std::string &path) { m_parent_path = path; }

NodeType File::type() const { return NodeType::FILE; }

std::string File::path() const { return m_parent_path + name(); }

std::string File::name() const { return m_name; }

int File::count() const { return -1; }

size_t File::size() const { return m_contents.size(); }

} // namespace seneca
