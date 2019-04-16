#include "Window.hpp"

Pixel::Pixel(Uint32 color){
    breakInt(color);
}

void Pixel::breakInt(Uint32 color){
    a = color & 0xFF; color >>= 8;
    b = color & 0xFF; color >>= 8;
    g = color & 0xFF; color >>= 8;
    r = color & 0xFF;
}


Window::Window(int hpix, int wpix, int ypos, int xpos)
:h(hpix),  w(wpix),  y(ypos),  x(xpos){
    
    bool success = true;
    
    win  = SDL_CreateWindow("Test",x,y,w,h,SDL_WINDOW_SHOWN);
    ren  = SDL_CreateRenderer(win, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(ren);
    
    surf = SDL_CreateRGBSurface(0, w, h, 32,REDMASK,GREENMASK,BLUEMASK,ALPHAMASK); // in case you want a surface to manip.
    pixels = (Uint32*)(surf->pixels);

    
    if(win == nullptr){
        printf("Problem Creating Window.\n");
        success = false;
    }
    
    if (ren == nullptr){
        printf("Problem Creating Renderer.\n");
        printf("%s\n", SDL_GetError());
    }
    
    if(surf == nullptr){
        printf("Problem Getting Window Surface.\n");
        printf("%s", SDL_GetError());
    }
    
    if(!ren & !surf) success = false;
    
    if(!success){
        win  = nullptr;
        ren  = nullptr;
        surf = nullptr;
    }
}

Window::~Window(){
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
}

void Window::clear(Uint32 color = 0xFF0000FF){
    
    Pixel p(color);
    
    SDL_SetRenderDrawColor(ren, p.r, p.g, p.b, p.a);
    
    SDL_RenderClear(ren);
}

void Window::blit(SDL_Surface* surf, int y, int x, float scale, Uint32 colorMod){
    
    
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren,surf);
    
    {
        colorMod |= 0xFF;
        Uint8* c = (Uint8*)&colorMod;
        SDL_SetTextureColorMod(tex, c[3], c[2], c[1]);
    }
    
    if(tex == nullptr){
        printf("Could Not Generate Texture.\n");
        return;
    }
    
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surf->w*scale;
    rect.h = surf->h*scale;
    
    SDL_RenderCopy(ren, tex, NULL, &rect);
    SDL_DestroyTexture(tex);
}

bool Window::applyPixel(int row, int col, Uint32 color){
    int ind;
    if(col < w && col >= 0 && row < h && row >= 0){
        ind = row * w + col;
        pixels[ind] = color;
        return true;
    }
    return false;
}

int clamp(int inp, int min, int max){
    if(inp < min) inp = min;
    if(inp > max) inp = max;
    return inp;
}

void Window::drawLine(int x1, int y1, int x2, int y2, Uint32 color){
    float slope = 0;
    int larger;
    
    
    
    
    if(x1 != x2 && y1 != y2){
        slope = (y2 - y1)/(float)(x2 - x1);
        if(slope*slope>1){
            int uppery = (y2>y1)?y2:y1;
            int lowery = (y2>y1)?y1:y2;
            uppery = clamp(uppery, 0, h);
            lowery = clamp(lowery, 0, h);
            
            for(int y = lowery, x; y < uppery; y++){
                x = (y - y1)/slope + x1;
                applyPixel(y, x, color);
            }
        }else{
            int upperx = (x2>x1)?x2:x1;
            int lowerx = (x2>x1)?x1:x2;
            upperx = clamp(upperx, 0, w);
            lowerx = clamp(lowerx, 0, w);
            
            for(int x = lowerx, y; x < upperx; x++){
                y = (x - x1)*slope + y1;
                applyPixel(y, x, color);
            }
        }
    }
    
    
    
    
    
//    if(x1 != x2 && y1 != y2){
//        slope = (y2 - y1)/(float)(x2 - x1);
//        if(slope*slope>1){
//            larger = (y2>y1)?1:-1;
//            for(int y = y1+larger, x; y != y2; y+=larger){
//                x = (y - y1)/slope + x1;
//                applyPixel(y, x, color);
//            }
//        }else{
//            larger = (x2>x1)?1:-1;
//            for(int x = x1+larger, y; x != x2; x+=larger){
//                y = (x - x1)*slope + y1;
//                applyPixel(y, x, color);
//            }
//        }
//        return;
//    }
    
    if(x1 == x2 && y1 == y2){
        return;
    }
    if(y1 == y2){
        int upperx = (x2>x1)?x2:x1;
        int lowerx = (x2>x1)?x1:x2;
        upperx = clamp(upperx, 0, w);
        lowerx = clamp(lowerx, 0, w);

        for(int x = lowerx; x < upperx; x++)
            applyPixel(y1, x, color);
        return;
    }
    if(x1 == x2){
        int uppery = (y2>y1)?y2:y1;
        int lowery = (y2>y1)?y1:y2;
        uppery = clamp(uppery, 0, h);
        lowery = clamp(lowery, 0, h);

        for(int y = lowery; y < uppery; y++)
            applyPixel(y, x1, color);
        return;
    }
    

}


void Window::update(){
    blit(surf, 0, 0);
    SDL_RenderPresent(ren);
    SDL_FillRect(surf, nullptr, 0x0);
}
