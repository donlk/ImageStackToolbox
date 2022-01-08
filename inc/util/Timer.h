#ifndef TIMER
#define TIMER

#include <chrono>

class Timer final{
	public:
		Timer();

		void start();
		void stop();

		std::chrono::microseconds getElapsedMicros();
		std::chrono::milliseconds getElapsedMillis();
		std::chrono::seconds getElapsedSeconds();

	private:
		std::chrono::duration<double> getElapsedInternal();

	private:
		bool started, stopped;
		std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
};

#endif
