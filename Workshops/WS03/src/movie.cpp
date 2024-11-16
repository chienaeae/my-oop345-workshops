#include "movie.h"
#include "mediaItem.h"
#include "settings.h"

#include <iomanip>
#include <string>

namespace seneca {

Movie::Movie() : MediaItem("", "", 0) {}

void Movie::display(std::ostream &out) const {
  if (g_settings.m_tableView) {
    out << "M | ";
    out << std::left << std::setfill('.');
    out << std::setw(50) << this->getTitle() << " | ";
    out << std::right << std::setfill(' ');
    out << std::setw(9) << this->getYear() << " | ";
    out << std::left;
    if (g_settings.m_maxSummaryWidth > -1) {
      if (static_cast<short>(this->getSummary().size()) <=
          g_settings.m_maxSummaryWidth)
        out << this->getSummary();
      else
        out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3)
            << "...";
    } else
      out << this->getSummary();
    out << std::endl;
  } else {
    size_t pos = 0;
    out << this->getTitle() << " [" << this->getYear() << "]\n";
    out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
        << '\n';
    while (pos < this->getSummary().size()) {
      out << "    "
          << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth)
          << '\n';
      pos += g_settings.m_maxSummaryWidth;
    }
    out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
        << std::setfill(' ') << '\n';
  }
}

Movie *Movie::createItem(const std::string &strMovie) {
  if (strMovie.empty() || strMovie[0] == '#') {
    throw "Not a valid movie.";
  }

  Movie *movie = new Movie();

  // Format: "TITLE,YEAR,SUMMARY"
  std::string temp = strMovie;
  size_t pos = 0;

  // TITLE
  pos = temp.find(',');
  std::string strTitle = temp.substr(0, pos);
  MediaItem::trim(strTitle);
  movie->setTitle(strTitle);
  temp = temp.substr(pos + 1);

  // YEAR
  pos = temp.find(',');
  std::string strYear = temp.substr(0, pos);
  MediaItem::trim(strYear);
  movie->setYear(std::stoi(strYear));
  temp = temp.substr(pos + 1);

  // SUMMARY
  MediaItem::trim(temp);
  movie->setSummary(temp);
  return movie;
}
} // namespace seneca
