#ifndef Shapes_hpp
#define Shapes_hpp

#include "Entity.hpp"

class Cube : public Entity{
    virtual void generateGeometry() override;
public:
    
    Cube();
};

class Sphere : public Entity{
    virtual void generateGeometry() override;
    
    int res = 12;
public:
    
    Sphere(int = 12);
};

class RandomPoints : public Entity{
    virtual void generateGeometry() override;
    int len = 10;
public:
    
    RandomPoints(int len = 10);
};

#endif /* Shapes_hpp */
