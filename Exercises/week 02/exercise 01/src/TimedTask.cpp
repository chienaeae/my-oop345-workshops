#include "TimedTask.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

namespace seneca {

TimedTask::TimedTask() : m_numTasks(0) {}

void TimedTask::startClock() { m_startTime = chrono::steady_clock::now(); }

void TimedTask::stopClock() { m_endTime = chrono::steady_clock::now(); }

void TimedTask::addTask(const char *taskName) {
  if (m_numTasks == MAX_TASKS) {
    return;
  }

  m_tasks[m_numTasks].m_taskName = taskName;
  m_tasks[m_numTasks].m_unitsOfTime = "nanoseconds";
  m_tasks[m_numTasks].m_duration =
      chrono::duration_cast<chrono::nanoseconds>(m_endTime - m_startTime);
  m_numTasks++;
}

ostream &operator<<(ostream &os, const TimedTask &task) {
  os << "--------------------------\n"
     << "Execution Times:\n"
     << "--------------------------\n";
  for (size_t i = 0; i < task.m_numTasks; i++) {
    os << "  " << left << setw(21) << task.m_tasks[i].m_taskName << right
       << setw(11) << task.m_tasks[i].m_duration.count() << " "
       << task.m_tasks[i].m_unitsOfTime << '\n';
  }
  os << "--------------------------\n";
  return os;
}

} // namespace seneca