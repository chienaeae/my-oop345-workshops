#include "tvShow.h"

#include "settings.h"

#include <algorithm>
#include <iomanip>
#include <numeric>
#include <string>

namespace seneca {

TvShow::TvShow() : MediaItem("", "", 0), m_id("") {}

void TvShow::display(std::ostream &out) const {

  if (g_settings.m_tableView) {
    out << "S | ";
    out << std::left << std::setfill('.');
    out << std::setw(50) << this->getTitle() << " | ";
    out << std::right << std::setfill(' ');
    out << std::setw(2) << this->m_episodes.size() << " | ";
    out << std::setw(4) << this->getYear() << " | ";
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
    for (auto &item : m_episodes) {
      out << std::setfill('0') << std::right;
      out << "    " << 'S' << std::setw(2) << item.m_season << 'E'
          << std::setw(2) << item.m_numberInSeason << ' ';
      if (item.m_title != "")
        out << item.m_title << '\n';
      else
        out << "Episode " << item.m_numberOverall << '\n';

      pos = 0;
      while (pos < item.m_summary.size()) {
        out << "            "
            << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8)
            << '\n';
        pos += g_settings.m_maxSummaryWidth - 8;
      }
    }
    out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
        << std::setfill(' ') << '\n';
  }
}

TvShow *TvShow::createItem(const std::string &strTvShow) {
  if (strTvShow.empty() || strTvShow[0] == '#') {
    throw "Not a valid show.";
  }

  TvShow *tvShow = new TvShow();

  // Format: "ID,TITLE,YEAR,SUMMARY"
  std::string temp = strTvShow;
  size_t pos = 0;

  // ID
  pos = temp.find(',');
  tvShow->m_id = temp.substr(0, pos);
  MediaItem::trim(tvShow->m_id);
  temp = temp.substr(pos + 1);

  // TITLE
  pos = temp.find(',');
  std::string strTitle = temp.substr(0, pos);
  MediaItem::trim(strTitle);
  tvShow->setTitle(strTitle);
  temp = temp.substr(pos + 1);

  // YEAR
  pos = temp.find(',');
  std::string strYear = temp.substr(0, pos);
  MediaItem::trim(strYear);
  tvShow->setYear(std::stoi(strYear));
  temp = temp.substr(pos + 1);

  // SUMMARY
  MediaItem::trim(temp);
  tvShow->setSummary(temp);

  return tvShow;
}

double TvShow::getEpisodeAverageLength() const {
  double totalLength =
      std::accumulate(m_episodes.begin(), m_episodes.end(), 0.0,
                      [](double sum, const TvEpisode &episode) {
                        return sum + episode.m_length;
                      });
  return totalLength / m_episodes.size();
}

std::list<std::string> TvShow::getLongEpisodes() const {
  std::list<std::string> longEpisodes;

  std::for_each(m_episodes.begin(), m_episodes.end(),
                [&longEpisodes](const TvEpisode &episode) {
                  if (episode.m_length > 3600) {
                    longEpisodes.push_back(episode.m_title);
                  }
                });

  return longEpisodes;
}
} // namespace seneca
