#ifndef PARALLELTIME_H
#define PARALLELTIME_H

#include <chrono>
#include <string>
#include <iostream>

class ParallelTime
{
    std::chrono::high_resolution_clock::time_point start_hr, stop_hr;
    clock_t start_clock, stop_clock;
    bool isStopped = false;
public:
    ParallelTime();
    void start();
    void stop();
    std::string print();
    std::string printms();
    double realTime();
    double cpuTime();
    double parallelisation();

    static std::string functionName(const std::string &name);
};

class ParallelTimeAutoStop
{
public:
  std::string comment;

  ParallelTimeAutoStop(std::string const & _comment = "");

  ~ParallelTimeAutoStop();

private:

  ParallelTime t;
};

#define PARALLELTIME_EXEC(code) \
  t.start(); \
  code; \
  std::cout << "Time for " << #code << ": " << t.print() << std::endl;

#define PARALLELTIME_FUNCTION() \
  ParallelTimeAutoStop paralleltime_auto_stop_object{ParallelTime::functionName(__PRETTY_FUNCTION__)};

#endif // PARALLELTIME_H
