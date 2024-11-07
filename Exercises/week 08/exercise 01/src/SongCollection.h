#ifndef SENECA_SONGCOLLECTION_H
#define SENECA_SONGCOLLECTION_H

#include <iostream>
#include <list>
#include <string>
#include <vector>

namespace seneca {

struct Song {
  std::string m_artist;
  std::string m_title;
  std::string m_album;
  double m_price;
  std::string m_year;
  int m_length;
};

class SongCollection {
  std::vector<Song> songs;

public:
  SongCollection(const std::string &filename);

  void display(std::ostream &os) const;

  void sort(const std::string &field);

  void cleanAlbum();

  bool inCollection(const std::string &artist) const;

  std::list<Song> getSongsForArtist(const std::string &artist) const;
};

std::ostream &operator<<(std::ostream &os, const Song &song);

} // namespace seneca

#endif // !SENECA_SONGCOLLECTION_H
