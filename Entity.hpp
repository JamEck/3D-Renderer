#ifndef Entity_hpp
#define Entity_hpp

#include "Matrix.hpp"
#include "Window.hpp"

class Entity{
protected:
    Matrix points;
    Matrix edges;
    Matrix transMat;
    float scale = 1.0;
    float angle = 0.0;

    void updatePoints();
    void transformPoints();
    void genTransMat();
    struct position{float x = 0,y = 0,z = 0;}pos;
    
    bool showEdges = true;
    
    virtual void generateGeometry() = 0;
public:
    
    Entity();
    constexpr static float PI = 3.14159265;
    void setPos(float, float, float);
    void addPos(float, float, float);
    void setScale(float);
    void addScale(float);
    void setAngle(float);
    void addAngle(float);
    void toggleEdges(bool = true);
    
    Matrix& verts();
    Matrix& getPoints();
    
    void project(Window&, Uint32 = 0xFFFFFFFF);
};

#endif /* Entity_hpp */
