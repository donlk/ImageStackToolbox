// Copyright (c) 2022 András Lehotay-Kéry

#include "../../inc/util/Timer.h"

#include <iostream>

using namespace std;

Timer::Timer(): started(false), stopped(true){
	// NOOP
}

std::chrono::microseconds Timer::getElapsedMicros(){
	return chrono::duration_cast<chrono::microseconds>(getElapsedInternal());
}

std::chrono::milliseconds Timer::getElapsedMillis(){
	return chrono::duration_cast<chrono::milliseconds>(getElapsedInternal());
}

std::chrono::seconds Timer::getElapsedSeconds(){
	return chrono::duration_cast<chrono::seconds>(getElapsedInternal());
}

std::chrono::duration<double> Timer::getElapsedInternal(){
	if(!started){
		cerr << "[Timer][getElapsedInternal] Timer hasnt't started yet." << endl;
		return std::chrono::duration<double>::min();
	}

	if(stopped){
		return endTime - startTime;
	}else{
		return chrono::system_clock::now() - startTime;
	}
}

void Timer::start(){
	startTime = chrono::system_clock::now();
	started = true;
	stopped = false;
}

void Timer::stop(){
	endTime = chrono::system_clock::now();
	stopped = true;
	started = false;
}
