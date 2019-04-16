#ifndef Window_hpp
#define Window_hpp

#include <SDL2/SDL.h>

#define REDMASK   0xFF000000
#define GREENMASK 0x00FF0000
#define BLUEMASK  0x0000FF00
#define ALPHAMASK 0x000000FF

class Pixel{
public:
    Uint8 r = 0x00;
    Uint8 g = 0x00;
    Uint8 b = 0x00;
    Uint8 a = 0xFF;
    
    Pixel(){}
    Pixel(Uint32);
    
    
    void breakInt(Uint32);
};


class Window{
public:
    SDL_Window* win = nullptr;
    SDL_Renderer *ren = nullptr;
    SDL_Surface *surf = nullptr;
    Uint32* pixels = nullptr;
    
    int x = 10, y = 10;
    int w = 1200, h = 800;
    //    int w = 600, h = 480;
    unsigned int length = w*h;
    
    float zs = 1.0; // distance from screen
    
    Window(int,int,int = 0,int = 0);
    ~Window();
    
    void clear(Uint32);
    void blit(SDL_Surface*, int, int, float = 1.0, Uint32 = 0xFFFFFFFF);
    void update();
    bool applyPixel(int row, int, Uint32);
    void drawLine(int x1, int y1, int x2, int y2, Uint32 color = 0xFFFFFFFF);
};


#endif /* Window_hpp */
