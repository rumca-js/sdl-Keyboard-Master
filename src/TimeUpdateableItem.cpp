#include "TimeUpdateableItem.h"

/**
 * C++14 required
 */
void TimeUpdateableItem::updateTime() {
#ifdef _C_STD_C14___
    auto now = std::chrono::high_resolution_clock::now();
    auto elapsed = now - last_time_stamp;

    long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    time_accumulated_ms += msec;

    last_time_stamp = now;
#else
     std::time_t t = std::time(0);
     std::tm* now = std::localtime(&t);
#endif
}

bool TimeUpdateableItem::isLimitReached() {
    if (time_accumulated >= reload_ms)
    {
        return true;
    }
    return false;
}

void TimeUpdateableItem::limitRelease() {
    time_accumulated - reload_ms;
}
