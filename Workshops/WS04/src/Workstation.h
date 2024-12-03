#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include "CustomerOrder.h"
#include "Station.h"
#include <deque>
#include <iostream>
#include <string>

namespace seneca {

extern std::deque<CustomerOrder> g_pending;
extern std::deque<CustomerOrder> g_completed;
extern std::deque<CustomerOrder> g_incomplete;

class Workstation : public Station {
  std::deque<CustomerOrder> m_orders;

  Workstation *m_pNextStation;

public:
  Workstation(const std::string &record);

  Workstation(const Workstation &) = delete;

  Workstation &operator=(const Workstation &) = delete;

  Workstation(Workstation &&) noexcept = delete;

  Workstation &operator=(Workstation &&) noexcept = delete;

  void fill(std::ostream &os);

  bool attemptToMoveOrder();

  void setNextStation(Workstation *station = nullptr);

  Workstation *getNextStation() const;

  void display(std::ostream &os) const;

  Workstation &operator+=(CustomerOrder &&order);
};

} // namespace seneca

#endif // SENECA_WORKSTATION_H