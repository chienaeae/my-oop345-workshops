#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <string>

namespace seneca {

class Station {
  int m_id;
  std::string m_name;
  std::string m_description;
  unsigned int m_serialNumber;
  unsigned int m_quantity;

  static size_t m_widthField;

  static size_t m_id_generator;

public:
  Station(const std::string &record);

  const std::string &getItemName() const;

  size_t getNextSerialNumber();

  size_t getQuantity() const;

  void updateQuantity();

  void display(std::ostream &os, bool full) const;
};

} // namespace seneca

#endif // SENECA_STATION_H
