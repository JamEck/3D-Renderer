#ifndef EventManager_hpp
#define EventManager_hpp
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

struct ButtonState{
    bool held = false;
    bool trig = false;
    Uint32 timestamp = 0;
    Uint32 code = 0;
    
    bool checkPress();
    bool checkRelease();
};

class MouseManager{
public:
    
    MouseManager();
    
    struct{
        int x = 0;
        int y = 0;
    }pos;
    struct{
        int x = 0;
        int y = 0;
    }vel;
    
    ButtonState  left;
    ButtonState right;
    
    bool checkTriggers();
    void clearTriggers();
    void update(SDL_Event&);
private:
    void setPos(int, int);
    void checkClick(SDL_Event&);
    void checkPos(SDL_Event&);

};

class KeyboardManager{
public:
    struct{
        Uint32 quit  = SDL_SCANCODE_ESCAPE;
        Uint32 up    = SDL_SCANCODE_W;
        Uint32 left  = SDL_SCANCODE_A;
        Uint32 down  = SDL_SCANCODE_S;
        Uint32 right = SDL_SCANCODE_D;
        Uint32 jump  = SDL_SCANCODE_SPACE;
        Uint32 attack  = SDL_SCANCODE_K;
        Uint32 special = SDL_SCANCODE_P;
        Uint32 grab = SDL_SCANCODE_APOSTROPHE;
        Uint32 shield = SDL_SCANCODE_RSHIFT;
        Uint32 start = SDL_SCANCODE_RETURN;
    }bind;
    
    std::vector<ButtonState> ks;

    bool change = false; // store if there were any key changes
    
    KeyboardManager();
    
    void setBindings();
    void clearTriggers();
    void update(SDL_Event&); // returns whether any button states changed
    void printButtons();
    ButtonState& getStateOf(Uint32&);
    ButtonState& operator[] (Uint32&);
};

class EventManager{
private:
    SDL_Event e;
public:
    bool quit = false;
    MouseManager mouse;
    KeyboardManager k;
    
    void checkEvents();
};

#endif /* EventManager_hpp */
