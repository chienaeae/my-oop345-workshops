#include "SongCollection.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>
#include <vector>

namespace seneca {

std::string getFullLengthString(int totalSeconds) {
  int hours = totalSeconds / 3600;
  int minutes = (totalSeconds % 3600) / 60;
  int seconds = totalSeconds % 60;
  return std::to_string(hours) + ":" + (minutes < 10 ? "0" : "") +
         std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") +
         std::to_string(seconds);
}

std::string getLengthString(int totalSeconds) {
  int minutes = totalSeconds / 60;
  int seconds = totalSeconds % 60;
  return std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") +
         std::to_string(seconds);
}
std::string trim(const std::string &str) {
  if (str.empty()) {
    return str;
  }

  std::string result = str;
  size_t start = result.find_first_not_of(" \t\n\r\f\v");
  result = (start == std::string::npos) ? "" : result.substr(start);

  size_t end = result.find_last_not_of(" \t\n\r\f\v");
  result = (end == std::string::npos) ? "" : result.substr(0, end + 1);

  return result;
}

SongCollection::SongCollection(const std::string &filename) {
  std::ifstream file(filename);
  if (!file) {
    throw std::runtime_error("Could not open file " + filename);
  }
  std::string line;

  while (std::getline(file, line)) {

    Song song;
    // TITLE, ARTIST and ALBUM have exactly 25 characters
    std::string title = line.substr(0, 25);
    std::string artist = line.substr(25, 25);
    std::string album = line.substr(50, 25);
    // YEAR, LENGTH and PRICE have exactly 5 characters
    std::string year = line.substr(75, 5);
    std::string length = line.substr(80, 5);
    std::string price = line.substr(85, 5);

    song.m_artist = trim(artist);
    song.m_title = trim(title);
    song.m_album = trim(album);
    song.m_year = trim(year);

    std::string lengthString = trim(length);
    if (lengthString.empty()) {
      song.m_length = 0;
    } else {
      song.m_length = std::stoi(lengthString);
    }

    std::string priceString = trim(price);
    if (priceString.empty()) {
      song.m_price = 0.0;
    } else {
      song.m_price = std::stod(priceString);
    }

    songs.push_back(song);
  }
}

void SongCollection::display(std::ostream &os) const {
  std::for_each(songs.begin(), songs.end(),
                [&os](const Song &song) { os << song << std::endl; });

  os << "----------------------------------------------------------------------"
        "------------------\n";

  int totalSeconds = 0;
  std::for_each(songs.begin(), songs.end(), [&totalSeconds](const Song &song) {
    totalSeconds += song.m_length;
  });

  os << "|                                                        "
        "Total Listening Time: "
     << getFullLengthString(totalSeconds) << " |\n";
}

void SongCollection::sort(const std::string &field) {
  std::sort(songs.begin(), songs.end(), [field](const Song &a, Song &b) {
    if (field == "title") {
      return a.m_title < b.m_title;
    }
    if (field == "length") {
      return a.m_length < b.m_length;
    }
    return a.m_artist < b.m_artist;
  });
}

void SongCollection::cleanAlbum() {
  std::for_each(songs.begin(), songs.end(), [](Song &song) {
    if (song.m_album == "[None]") {
      song.m_album = "";
    }
  });
}

bool SongCollection::inCollection(const std::string &artist) const {
  auto exists =
      std::find_if(songs.begin(), songs.end(), [&artist](const Song &song) {
        return song.m_artist == artist;
      });

  return exists != songs.end();
}

std::list<Song>
SongCollection::getSongsForArtist(const std::string &artist) const {
  std::list<Song> songsForArtist;
  std::copy_if(songs.begin(), songs.end(), std::back_inserter(songsForArtist),
               [&artist](const Song &song) { return song.m_artist == artist; });
  return songsForArtist;
}

std::ostream &operator<<(std::ostream &os, const Song &song) {
  os << "| " << std::setw(20) << std::left << song.m_title << " | "
     << std::setw(15) << std::left << song.m_artist << " | " << std::setw(20)
     << std::left << song.m_album << " | " << std::setw(6) << std::right
     << song.m_year << " | " << getLengthString(song.m_length) << " | "
     << song.m_price << " |";
  return os;
}

} // namespace seneca
