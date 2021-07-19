#include "TimeUpdateableItem.h"

#include <iostream>


TimeUpdateableItem::TimeUpdateableItem() {
    last_time_stamp = std::chrono::high_resolution_clock::now();
	time_accumulated_ms = 0;
	release_ms = 0;
}

/**
 * C++14 required
 */
void TimeUpdateableItem::updateTime() {
#ifdef _C_STD_C14___
    auto now = std::chrono::high_resolution_clock::now();
    auto elapsed = now - last_time_stamp;

	//std::cout << "Elapsed: "<<elapsed.count() << std::endl;

    long long msec = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

	//std::cout << "Elapsed [ms]: "<<msec << std::endl;

    time_accumulated_ms += msec;

    last_time_stamp = now;
#else
     std::time_t t = std::time(0);
     std::tm* now = std::localtime(&t);
#endif

	 if (isLimitReached())
		 limitRelease();
}

bool TimeUpdateableItem::isLimitReached() {
    if (time_accumulated_ms >= release_ms)
    {
        return true;
    }
    return false;
}

void TimeUpdateableItem::limitRelease() {
	if (isLimitReached() ) {
		time_accumulated_ms = time_accumulated_ms - release_ms;
		timeUpdateEvent();
	}
}

void TimeUpdateableItem::setReleaseTime(unsigned long long aReleaseTime)
{
	release_ms = aReleaseTime;
}

void TimeUpdateableItem::timeUpdateEvent() {
	std::cout << "Time update event" << std::endl;
}
