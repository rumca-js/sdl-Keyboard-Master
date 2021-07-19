#ifndef _H_TIMEUPDATEABLEITEM_H_
#define _H_TIMEUPDATEABLEITEM_H_

#define _C_STD_C14___

#include <chrono>

class TimeUpdateableItem {
   protected:
   unsigned long long time_accumulated_ms;
   unsigned long long release_ms;

#ifdef _C_STD_C14___
   std::chrono::time_point<std::chrono::system_clock> last_time_stamp;
#else
   std::time_t last_time_stamp;
#endif

   public:
   TimeUpdateableItem();
   void updateTime();
   bool isLimitReached();
   virtual void limitRelease();
   virtual void timeUpdateEvent();
   void setReleaseTime(unsigned long long aReleaseTime);
};

#endif // _H_TIMEUPDATEABLEITEM_H_
