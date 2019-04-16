#include "Timer.hpp"

void Averager::reset(){
    avg = 0;
    count = 0;
}

float Averager::update(float inp){
    avg = avg*count + inp;
    count++;
    avg /= (float)count;
    return avg;
}

float Averager::check(){
    return avg;
}

int Averager::iterations(){
    return count;
}

void Timer::update(decltype(s)& inp){
    inp = std::chrono::high_resolution_clock::now();
}

decltype(Timer::s) Timer::start(){
    update(s);
    return s;
}

decltype(Timer::e) Timer::stop(){
    update(e);
    d = e - s;
    avg.update(d.count());
    return e;
}

double Timer::elapsed(){
    return d.count();
}
