#include <iostream>
#include "Timer.hpp"
#include "Matrix.hpp"
#include "EventManager.hpp"
#include "Entity.hpp"
#include "Shapes.hpp"
#include "Window.hpp"

#define WHITE 0xFFFFFFFF
#define RED   0xFF0000FF
#define GREEN 0x00FF00FF
#define BLUE  0x0000FFFF

int main(){
    
    Sphere sphere(12);
    Sphere sphere2(4);
    Cube cube;
    RandomPoints rando(40);
    
    rando.toggleEdges(false);
    
    sphere .setPos( 0, 0, 10);
    sphere2.setPos( 1, 1.2, 10);
    cube   .setPos(-1, 1.5, 10);
    rando  .setPos( 1,-1, 10);

    Window win(400,640,50,200);
    EventManager e;
    
    int focus = 0;
    Entity* selectedEntity = &sphere;
    
    Timer t;
    while(e.quit == 0){
        e.checkEvents();
        
        if(e.k.getStateOf(e.k.bind.jump).checkPress()){
            focus = (focus+1)%4;
            switch(focus){
                case 0:
                    selectedEntity = &sphere;
                    break;
                case 1:
                    selectedEntity = &cube;
                    break;
                case 2:
                    selectedEntity = &rando;
                    break;
                case 3:
                    selectedEntity = &sphere2;
                    break;
            }
        }
        
        if(e.k.getStateOf(e.k.bind.left   ).held) selectedEntity->addPos(-.1,  0,  0);
        if(e.k.getStateOf(e.k.bind.right  ).held) selectedEntity->addPos( .1,  0,  0);
        if(e.k.getStateOf(e.k.bind.up     ).held) selectedEntity->addPos(  0,  0, .1);
        if(e.k.getStateOf(e.k.bind.down   ).held) selectedEntity->addPos(  0,  0,-.1);
        if(e.k.getStateOf(e.k.bind.attack ).held) selectedEntity->addAngle( 0.05);
        if(e.k.getStateOf(e.k.bind.special).held) selectedEntity->addAngle(-0.05);
        if(e.k.getStateOf(e.k.bind.grab   ).held) win.zs+=0.01;// decrease FOV //selectedEntity->addScale( 0.05);
        if(e.k.getStateOf(e.k.bind.shield ).held) win.zs-=0.01;// increase FOV //selectedEntity->addScale(-0.05);

//        win.clear(0x8080A0FF);
        win.clear(0xFF);
        
        t.start();
        sphere .project(win, (focus == 0)?RED:WHITE);
        cube   .project(win, (focus == 1)?RED:WHITE);
        rando  .project(win, (focus == 2)?RED:WHITE);
        sphere2.project(win, (focus == 3)?RED:WHITE);
        
        
        t.stop();
        
        
        win.update();
        

        
//        if(!(t.avg.iterations()%100))
//            std::cout << "projection time: " << t.elapsed() << "\t average: " << t.avg.check() << std::endl;

    }
    
    std::cout << "average projection time: " << t.avg.check() << std::endl;


    
}
