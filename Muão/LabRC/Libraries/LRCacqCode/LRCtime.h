#include <stdint.h> //C types
#include <sys/time.h>
#include <time.h>

///////////////////////////////////////////////////////////////////////////////////

class LRCtime {

 public:

  LRCtime();
  ~LRCtime();
  int GetTime1970sec();
  int GetTime1970usec();
  int GetTimeSeconds();
  int GetTimeMinutes();
  int GetTimeHours();
  int GetTimeDay();
  int GetTimeMonth();
  int GetTimeYear();

  double GetTimefull();

 private:
  time_t now;
  tm *time_tm;
  timeval time_tv;
};
