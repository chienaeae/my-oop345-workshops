#include "CustomerOrder.h"
#include "Utilities.h"

#include <iostream>
#include <string>
#include <vector>

namespace seneca {

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder(const std::string &str) : m_lstItem(nullptr) {
  Utilities utilities;

  bool more = true;
  size_t next_pos = 0;

  // Extract
  std::string customerNameStr = utilities.extractToken(str, next_pos, more);
  std::string orderNameStr = utilities.extractToken(str, next_pos, more);

  std::vector<std::string> items;
  while (more) {
    std::string itemNameStr = utilities.extractToken(str, next_pos, more);
    items.push_back(itemNameStr);
  }

  if (m_widthField < utilities.getFieldWidth()) {
    m_widthField = utilities.getFieldWidth();
  }

  // Assign
  m_name = customerNameStr;
  m_product = orderNameStr;
  m_cntItem = items.size();
  m_lstItem = new Item *[m_cntItem];

  for (size_t i = 0; i < m_cntItem; i++) {
    m_lstItem[i] = new Item(items[i]);
  }
}

CustomerOrder::CustomerOrder(CustomerOrder &&other) noexcept
    : m_name(std::move(other.m_name)), m_product(std::move(other.m_product)),
      m_cntItem(other.m_cntItem), m_lstItem(other.m_lstItem) {
  other.m_lstItem = nullptr;
  other.m_cntItem = 0;
}

CustomerOrder &CustomerOrder::operator=(CustomerOrder &&other) noexcept {
  if (this != &other) {
    if (m_lstItem != nullptr) {
      for (size_t i = 0; i < m_cntItem; i++) {
        delete m_lstItem[i];
      }
      delete[] m_lstItem;
    }

    m_lstItem = other.m_lstItem;
    other.m_lstItem = nullptr;

    m_cntItem = other.m_cntItem;
    other.m_cntItem = 0;

    m_name = other.m_name;
    other.m_name = "";

    m_product = other.m_product;
    other.m_product = "";
  }

  return *this;
}

CustomerOrder::~CustomerOrder() {
  if (m_lstItem != nullptr) {
    for (size_t i = 0; i < m_cntItem; i++) {
      delete m_lstItem[i];
    }
    delete[] m_lstItem;
  }
}

bool CustomerOrder::isOrderFilled() const {
  for (size_t i = 0; i < m_cntItem; i++) {
    if (!m_lstItem[i]->m_isFilled) {
      return false;
    }
  }

  return true;
}

bool CustomerOrder::isItemFilled(const std::string &itemName) const {
  for (size_t i = 0; i < m_cntItem; i++) {
    if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
      return false;
    }
  }

  return true;
}

void CustomerOrder::fillItem(Station &station, std::ostream &os) {
  Item *item = nullptr;

  for (size_t i = 0; i < m_cntItem; i++) {
    if (m_lstItem[i]->m_itemName == station.getItemName() &&
        !m_lstItem[i]->m_isFilled) {
      item = m_lstItem[i];

      if (station.getQuantity() > 0) {
        item->m_serialNumber = station.getNextSerialNumber();
        item->m_isFilled = true;
        station.updateQuantity();
        os << "    Filled " << m_name << ", " << m_product << " ["
           << item->m_itemName << "]" << std::endl;
        return;
      } else {
        os << "    Unable to fill " << m_name << ", " << m_product << " ["
           << item->m_itemName << "]" << std::endl;
      }
    }
  }
}

void CustomerOrder::display(std::ostream &os) const {
  os << m_name << " - " << m_product << std::endl;

  for (size_t i = 0; i < m_cntItem; i++) {
    m_lstItem[i]->display(os);
  }
}

} // namespace seneca
