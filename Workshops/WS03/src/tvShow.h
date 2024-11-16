// I declare that this submission is the result of my own work and I only copied
// the code that my professor provided to complete my workshops and assignments.
// This submitted piece of work has not been shared with any other student or
// 3rd party content provider.
//
// Chia-Yu Chien
// 157049222
// cchien8@myseneca.ca

#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include "mediaItem.h"
#include <list>
#include <sstream>
#include <string>
#include <vector>

namespace seneca {

class TvShow : public MediaItem {

  struct TvEpisode {
    const TvShow *m_show{};
    unsigned short m_numberOverall{};
    unsigned short m_season{};
    unsigned short m_numberInSeason{};
    std::string m_airDate{};
    unsigned int m_length{};
    std::string m_title{};
    std::string m_summary{};
  };

  std::string m_id;

  std::vector<TvEpisode> m_episodes;

  TvShow();

public:
  static TvShow *createItem(const std::string &strTvShow);

  void display(std::ostream &out = std::cout) const override;

  static unsigned int calculateSeconds(std::string &strTime) {
    // Format: "HH:MM:SS"
    if (strTime.find(':') != std::string::npos) {
      strTime.replace(strTime.find(':'), 1, " ");
    }
    if (strTime.find(':') != std::string::npos) {
      strTime.replace(strTime.find(':'), 1, " ");
    }
    if (strTime.find('.') != std::string::npos) {
      strTime.replace(strTime.find('.'), 1, " ");
    }
    std::stringstream ss(strTime);
    unsigned int hours = 0, minutes = 0, seconds = 0;
    ss >> hours >> minutes >> seconds;
    return hours * 3600 + minutes * 60 + seconds;
  }

  template <typename Collection_t>
  static void addEpisode(Collection_t &col, const std::string &strEpisode) {
    std::string temp = strEpisode;
    MediaItem::trim(temp);
    if (temp.empty() || temp[0] == '#') {
      throw "Not a valid episode.";
    }

    // Format:
    // "ID,EPISODE_NUMBER,SEASON_NUMBER,EPISODE_IN_SEASON,AIR_DATE,LENGTH,TITLE,SUMMARY"
    TvEpisode episode;
    size_t pos = 0;

    // ID
    pos = temp.find(',');
    std::string strId = temp.substr(0, pos);
    MediaItem::trim(strId);
    TvShow *show = nullptr;
    for (size_t i = 0; i < col.size(); i++) {
      show = dynamic_cast<TvShow *>(col[i]);
      if (show && show->m_id == strId) {
        episode.m_show = show;
        break;
      }
    }

    if (!show) {
      throw std::runtime_error("Invalid show ID: " + strId);
    }

    temp = temp.substr(pos + 1);

    // EPISODE_NUMBER
    pos = temp.find(',');
    std::string strEpisodeNumber = temp.substr(0, pos);
    MediaItem::trim(strEpisodeNumber);
    episode.m_numberOverall = std::stoi(strEpisodeNumber);
    temp = temp.substr(pos + 1);

    // SEASON_NUMBER
    pos = temp.find(',');
    std::string strSeason = temp.substr(0, pos);
    MediaItem::trim(strSeason);
    if (strSeason.empty()) {
      episode.m_season = 1;
    } else {
      episode.m_season = std::stoi(strSeason);
    }
    temp = temp.substr(pos + 1);

    // EPISODE_IN_SEASON
    pos = temp.find(',');
    std::string strEpisodeInSeason = temp.substr(0, pos);
    MediaItem::trim(strEpisodeInSeason);
    episode.m_numberInSeason = std::stoi(strEpisodeInSeason);
    temp = temp.substr(pos + 1);

    // AIR_DATE
    pos = temp.find(',');
    std::string strAirDate = temp.substr(0, pos);
    MediaItem::trim(strAirDate);
    episode.m_airDate = strAirDate;
    temp = temp.substr(pos + 1);

    // LENGTH
    pos = temp.find(',');
    std::string strLength = temp.substr(0, pos);
    MediaItem::trim(strLength);
    episode.m_length = calculateSeconds(strLength);
    temp = temp.substr(pos + 1);

    // TITLE
    pos = temp.find(',');
    std::string strTitle = temp.substr(0, pos);
    MediaItem::trim(strTitle);
    episode.m_title = strTitle;
    temp = temp.substr(pos + 1);

    // SUMMARY
    MediaItem::trim(temp);
    episode.m_summary = temp;

    show->m_episodes.push_back(episode);
  }

  double getEpisodeAverageLength() const;

  std::list<std::string> getLongEpisodes() const;
};

} // namespace seneca

#endif // SENECA_TVSHOW_H