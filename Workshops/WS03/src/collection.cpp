#include "collection.h"
#include "mediaItem.h"

#include <algorithm>

namespace seneca {

Collection::Collection(const std::string &name)
    : m_name{name}, m_observer{nullptr} {}

Collection::~Collection() {
  for (auto item : m_items) {
    delete item;
  }
}

const std::string &Collection::name() const { return m_name; }

size_t Collection::size() const { return m_items.size(); }

void Collection::setObserver(void (*observer)(const Collection &,
                                              const MediaItem &)) {
  m_observer = observer;
}

Collection &Collection::operator+=(MediaItem *item) {
  for (auto m_item : m_items) {
    if (m_item->getTitle() == item->getTitle()) {
      delete item;
      return *this;
    }
  }

  m_items.push_back(item);
  if (m_observer) {
    m_observer(*this, *item);
  }

  return *this;
}

MediaItem *Collection::operator[](size_t idx) const {
  if (idx >= m_items.size()) {
    std::string msg = "Bad index " + std::to_string(idx) + " Collection has " +
                      std::to_string(m_items.size()) + " items.";
    throw std::out_of_range(msg);
  }
  return m_items[idx];
}

MediaItem *Collection::operator[](const std::string &title) const {
  auto it =
      std::find_if(m_items.begin(), m_items.end(), [title](MediaItem *item) {
        return item->getTitle() == title;
      });
  return it != m_items.end() ? *it : nullptr;
}

void trimQuotes(std::string &str) {
  if (str.front() == '\"') {
    str = str.substr(1, str.size() - 1);
  }
  if (str.back() == '\"') {
    str = str.substr(0, str.size() - 1);
  }
}

void Collection::removeQuotes() {
  std::for_each(m_items.begin(), m_items.end(), [](MediaItem *item) {
    // For Title
    std::string title = item->getTitle();
    trimQuotes(title);
    item->setTitle(title);

    // For Summary
    std::string summary = item->getSummary();
    trimQuotes(summary);
    item->setSummary(summary);
  });
}

void Collection::sort(const std::string &field) {
  if (field == "title") {
    std::sort(m_items.begin(), m_items.end(), [](MediaItem *a, MediaItem *b) {
      // in ascending order
      return a->getTitle() < b->getTitle();
    });
  } else if (field == "summary") {
    std::sort(m_items.begin(), m_items.end(), [](MediaItem *a, MediaItem *b) {
      // in ascending order
      return a->getSummary() < b->getSummary();
    });
  } else if (field == "year") {
    std::sort(m_items.begin(), m_items.end(), [](MediaItem *a, MediaItem *b) {
      // in ascending order
      return a->getYear() < b->getYear();
    });
  }
}

std::ostream &operator<<(std::ostream &os, const Collection &collection) {
  for (size_t i = 0; i < collection.size(); i++) {
    collection[i]->display(os);
  }

  return os;
}

} // namespace seneca
