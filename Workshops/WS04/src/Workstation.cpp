#include "Workstation.h"
#include <iostream>
#include <string>

namespace seneca {

std::deque<CustomerOrder> g_pending;
std::deque<CustomerOrder> g_completed;
std::deque<CustomerOrder> g_incomplete;

Workstation::Workstation(const std::string &record)
    : Station(record), m_orders(), m_pNextStation(nullptr) {}

void Workstation::fill(std::ostream &os) {
  if (!m_orders.empty()) {
    m_orders.front().fillItem(*this, os);
  }
}

bool Workstation::attemptToMoveOrder() {
  if (m_orders.empty()) {
    return false;
  }

  // fetch the order
  CustomerOrder &order = m_orders.front();
  std::string itemName = Station::getItemName();

  // check if the item is filled or the station is out of stock
  if (Station::getQuantity() <= 0 || order.isItemFilled(itemName)) {
    if (getNextStation() == nullptr) {
      if (order.isOrderFilled()) {
        g_completed.push_back(std::move(order));
      } else {
        g_incomplete.push_back(std::move(order));
      }
    } else {
      *getNextStation() += std::move(order);
    }
    m_orders.pop_front();
    return true;
  }

  // if the item is not filled or the station is not out of stock, return false
  return false;
}

void Workstation::setNextStation(Workstation *station) {
  if (station != this) {
    m_pNextStation = station;
  }
}

Workstation *Workstation::getNextStation() const { return m_pNextStation; }

void Workstation::display(std::ostream &os) const {
  os << getItemName() << " --> "
     << (getNextStation() == nullptr ? "End of Line"
                                     : getNextStation()->getItemName())
     << std::endl;
}

Workstation &Workstation::operator+=(CustomerOrder &&order) {
  m_orders.push_back(std::move(order));
  return *this;
}

} // namespace seneca
