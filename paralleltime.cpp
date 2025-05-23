#include "paralleltime.h"

ParallelTime::ParallelTime()
{
    start();
}

void ParallelTime::start() {
    start_hr = std::chrono::high_resolution_clock::now();
    start_clock = clock();
    isStopped = false;
}

void ParallelTime::stop() {
    stop_hr = std::chrono::high_resolution_clock::now();
    stop_clock = clock();
    isStopped = true;
}

std::string ParallelTime::print() {
    const std::chrono::high_resolution_clock::time_point _stop_hr =
            isStopped ? stop_hr : std::chrono::high_resolution_clock::now();
    const clock_t _stop_clock = isStopped ? stop_clock : clock();

    const double time_hr = std::chrono::duration_cast<std::chrono::duration<double>>(_stop_hr - start_hr).count();
    const double time_clock = static_cast<double>(_stop_clock - start_clock) / CLOCKS_PER_SEC;
    return ": " + std::to_string(time_hr) + "s, CPU time: " + std::to_string(time_clock) + " parallelisation: " + std::to_string(time_clock / time_hr);
}

std::string ParallelTime::printms() {
    const std::chrono::high_resolution_clock::time_point _stop_hr =
            isStopped ? stop_hr : std::chrono::high_resolution_clock::now();
    const clock_t _stop_clock = isStopped ? stop_clock : clock();

    const double time_hr = std::chrono::duration_cast<std::chrono::duration<double>>(_stop_hr - start_hr).count();
    const double time_clock = static_cast<double>(_stop_clock - start_clock) / CLOCKS_PER_SEC;
    return ": " + std::to_string(time_hr*1000) + "ms, CPU time: " + std::to_string(time_clock*1000) + "ms parallelisation: " + std::to_string(time_clock / time_hr);
}

double ParallelTime::realTime() {
    const std::chrono::high_resolution_clock::time_point _stop_hr =
            isStopped ? stop_hr : std::chrono::high_resolution_clock::now();

    const double time_hr = std::chrono::duration_cast<std::chrono::duration<double>>(_stop_hr - start_hr).count();
    return time_hr;
}

double ParallelTime::cpuTime() {
    const clock_t _stop_clock = isStopped ? stop_clock : clock();
    const double time_clock = static_cast<double>(_stop_clock - start_clock) / CLOCKS_PER_SEC;
    return time_clock;
}

double ParallelTime::parallelisation() {
  return cpuTime() / realTime();
}

std::string ParallelTime::functionName(std::string const & name)
{
  return name.substr(0, name.find_first_of("("));
}

void ParallelTime::display(const std::string &comment)
{
  if (comment.empty()) {
    std::cout << "Time: " << print() << std::endl;
  }
  else {
    std::cout << "Time for " << comment << ": " << print() << std::endl;
  }
}

ParallelTimeAutoStop::ParallelTimeAutoStop(const std::string &_comment) : comment(_comment)
{
}

ParallelTimeAutoStop::~ParallelTimeAutoStop()
{
  t.display(comment);
}
