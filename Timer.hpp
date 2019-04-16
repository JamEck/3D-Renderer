#ifndef Timer_hpp
#define Timer_hpp

#include <chrono>

struct Averager{
private:
    float avg = 0;
    int count = 0;
public:
    void reset();
    
    float update(float);
    
    float check();
    
    int iterations();
};

struct Timer{
private:
    decltype(std::chrono::high_resolution_clock::now()) s;
    decltype(s) e;
    std::chrono::duration<double> d;
    
    void update(decltype(s)&);
    
    
public:
    Averager avg;
    decltype(s) start();
    
    decltype(e) stop();
    
    double elapsed();
};

#endif /* Timer_hpp */
