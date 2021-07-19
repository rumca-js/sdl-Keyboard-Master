#ifndef _H_TIMEUPDATEABLEITEM_H_
#define _H_TIMEUPDATEABLEITEM_H_

class TimeUpdateableItem {
   unsigned long long time_accumulated_ms;
   unsigned long long release_ms;

#ifdef _C_STD_C14___
   std::chrono::time_point<std::chrono::system_clock> last_time_stamp;
#else
   std::time_t t last_time_stamp;
#endif

   void updateTime();
   virtual void timeUpdateEvent() = 0;
};

#endif // _H_TIMEUPDATEABLEITEM_H_
