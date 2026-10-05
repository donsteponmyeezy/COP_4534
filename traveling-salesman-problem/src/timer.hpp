#pragma once

#include <sys/time.h>
#include <cstddef>

class Timer
{
public:
  void start()
  {
    gettimeofday(&start_time, NULL);
  }

  // Returns time in seconds as a double
  double get_elapsed_seconds()
  {
    gettimeofday(&end_time, NULL);
    long seconds = end_time.tv_sec - start_time.tv_sec;
    long microseconds = end_time.tv_usec - start_time.tv_usec;
    return seconds + (microseconds / 1000000.0);
  }

private:
  struct timeval start_time;
  struct timeval end_time;
};