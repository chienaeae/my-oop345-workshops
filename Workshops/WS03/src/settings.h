// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
//
// Chia-Yu Chien
// 157049222
// cchien8@myseneca.ca

#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

namespace seneca {

class Settings {
public:
  int m_maxSummaryWidth = 80;

  bool m_tableView = false;
};

extern Settings g_settings;
} // namespace seneca

#endif // SENECA_SETTINGS_H
