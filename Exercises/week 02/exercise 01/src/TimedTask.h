#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H

#include <chrono>
#include <string>

namespace seneca {

struct Task {
  std::string m_taskName;
  std::string m_unitsOfTime;
  std::chrono::duration<long, std::nano> m_duration;
};

class TimedTask {
  static const size_t MAX_TASKS = 10;
  size_t m_numTasks;

  std::chrono::steady_clock::time_point m_startTime;
  std::chrono::steady_clock::time_point m_endTime;

  Task m_tasks[MAX_TASKS];

public:
  TimedTask();
  void startClock();
  void stopClock();
  void addTask(const char *taskName);

  friend std::ostream &operator<<(std::ostream &os, const TimedTask &task);
};

} // namespace seneca

#endif