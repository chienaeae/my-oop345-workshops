#include "Station.h"
#include "Utilities.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

namespace seneca {

size_t Station::m_widthField = 0;

size_t Station::m_id_generator = 0;

Station::Station(const std::string &record) : m_id(++m_id_generator) {
  Utilities utilities;

  size_t next_pos = 0;
  bool more = true;

  std::string nameStr = utilities.extractToken(record, next_pos, more);
  std::string serialNumberStr = utilities.extractToken(record, next_pos, more);
  std::string quantityStr = utilities.extractToken(record, next_pos, more);

  if (m_widthField < utilities.getFieldWidth()) {
    m_widthField = utilities.getFieldWidth();
  }

  std::string descriptionStr = utilities.extractToken(record, next_pos, more);

  m_name = nameStr;
  m_serialNumber = std::stoul(serialNumberStr);
  m_quantity = std::stoul(quantityStr);
  m_description = descriptionStr;
}

const std::string &Station::getItemName() const { return m_name; }

size_t Station::getNextSerialNumber() { return m_serialNumber++; }

size_t Station::getQuantity() const { return m_quantity; }

void Station::updateQuantity() {
  if (m_quantity > 0) {
    m_quantity--;
  }
}

void Station::display(std::ostream &os, bool full) const {
  os << std::right << std::setw(3) << std::setfill('0') << m_id << " | "
     << std::setw(m_widthField) << std::setfill(' ') << std::left << m_name
     << " | " << std::setw(6) << std::right << std::setfill('0')
     << m_serialNumber << std::setfill(' ') << " | ";

  if (full) {
    os << std::setw(4) << std::right << m_quantity << " | " << m_description;
  }

  os << std::endl;
}

} // namespace seneca
