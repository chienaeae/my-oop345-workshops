#include "LineManager.h"
#include "Workstation.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

namespace seneca {

LineManager::LineManager(const std::string &file,
                         std::vector<Workstation *> &stations)
    : m_activeLine(), m_cntCustomerOrder(0), m_firstStation(nullptr) {
  std::ifstream in(file);
  std::string record;

  if (!in) {
    throw std::string("Unable to open [") + file + "] file.";
  }

  std::set<Workstation *> currentStations;
  std::set<Workstation *> nextStations;

  while (std::getline(in, record)) {
    std::string::size_type next_pos = record.find('|');
    std::string stationName = "";
    std::string nextStationName = "";
    stationName = record.substr(0, next_pos);

    if (next_pos != std::string::npos) {
      nextStationName = record.substr(next_pos + 1);
    }

    // 1. find the current station
    auto currentStation = std::find_if(
        stations.begin(), stations.end(), [stationName](Workstation *station) {
          return station->getItemName() == stationName;
        });

    // 1-1. if the current station is not found, throw an error
    if (currentStation == stations.end()) {
      throw std::string("***Invalid record***: " + record);
    }

    // 1-2. add the current station to the set
    currentStations.insert(*currentStation);

    // 2. if the next station name is not empty, find the next station
    if (!nextStationName.empty()) {
      // 2-1. if the next station is not found, throw an error
      auto nextStation =
          std::find_if(stations.begin(), stations.end(),
                       [nextStationName](Workstation *station) {
                         return station->getItemName() == nextStationName;
                       });

      if (nextStation == stations.end()) {
        throw std::string("***Invalid record***: " + record);
      }

      // 2-2. set the next station to the current station
      (*currentStation)->setNextStation(*nextStation);

      // 2-3. add the next station to the set
      nextStations.insert(*nextStation);
    }

    m_activeLine.push_back(*currentStation);
  }

  // 3. find the starting station
  for (auto station : currentStations) {
    if (nextStations.find(station) == nextStations.end()) {
      if (m_firstStation) {
        throw std::runtime_error("***Multiple Starting Workstations***");
      }
      m_firstStation = station;
    }
  }

  if (!m_firstStation) {
    throw std::runtime_error("***No Starting Workstation***");
  }

  // 4. count the number of customer orders
  m_cntCustomerOrder = g_pending.size();
}

void LineManager::reorderStations() {
  std::vector<Workstation *> reorderedStations;

  Workstation *currentStation = m_firstStation;

  while (currentStation != nullptr) {
    reorderedStations.push_back(currentStation);
    currentStation = currentStation->getNextStation();
  }

  m_activeLine = reorderedStations;
}

bool LineManager::run(std::ostream &os) {
  static size_t calledCount = 0;
  calledCount++;
  os << "Line Manager Iteration: " << calledCount << std::endl;

  // get the first order
  if (!g_pending.empty()) {
    *m_firstStation += std::move(g_pending.front());
    g_pending.pop_front();
  }

  // fill the order and move to the next station
  for (auto station : m_activeLine) {
    station->fill(os);
  }

  for (auto station : m_activeLine) {
    station->attemptToMoveOrder();
  }

  // check if all orders are completed
  if (g_pending.empty() &&
      g_completed.size() + g_incomplete.size() == m_cntCustomerOrder) {
    return true;
  }

  return false;
}

void LineManager::display(std::ostream &os) const {
  for (const auto &station : m_activeLine) {
    station->display(os);
  }
}

} // namespace seneca
