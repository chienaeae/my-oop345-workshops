#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include "Station.h"

#include <iomanip>
#include <string>

namespace seneca {

class CustomerOrder {

  struct Item {
    std::string m_itemName;
    size_t m_serialNumber{0};
    bool m_isFilled{false};

    Item(const std::string &src) : m_itemName(src) {};

    void display(std::ostream &os) const {
      os << "[" << std::right << std::setw(6) << std::setfill('0')
         << m_serialNumber << "] " << std::setw(m_widthField) << std::left
         << std::setfill(' ') << m_itemName << " - "
         << (m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
    }
  };

  static size_t m_widthField;

  std::string m_name;
  std::string m_product;
  size_t m_cntItem;
  Item **m_lstItem;

public:
  CustomerOrder() = default;

  CustomerOrder(const std::string &str);

  CustomerOrder(const CustomerOrder &) {
    throw std::string("Cannot make copies.");
  };

  CustomerOrder &operator=(const CustomerOrder &) = delete;

  CustomerOrder(CustomerOrder &&) noexcept;

  CustomerOrder &operator=(CustomerOrder &&) noexcept;

  ~CustomerOrder();

  bool isOrderFilled() const;

  bool isItemFilled(const std::string &itemName) const;

  void fillItem(Station &station, std::ostream &os);

  void display(std::ostream &os) const;
};

} // namespace seneca

#endif // SENECA_CUSTOMERORDER_H