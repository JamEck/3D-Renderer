#include "Entity.hpp"

Entity::Entity(){
    transMat.create(4,4);
    genTransMat();
}

void Entity::genTransMat(){
    transMat.fill(0);
    transMat(1,1) = 1;
    transMat(0,0) = std::cos(angle);
    transMat(2,2) = std::cos(angle);
    transMat(0,2) =-std::sin(angle);
    transMat(2,0) = std::sin(angle);
    transMat *= scale;
    transMat(3,0) = pos.x;
    transMat(3,1) = pos.y;
    transMat(3,2) = pos.z;
    transMat(3,3) = 1;
}

void Entity::setPos(float x, float y, float z){
    pos.x = x; pos.y = y, pos.z = z;
    transformPoints();
}
void Entity::addPos(float x, float y, float z){
    pos.x += x; pos.y += y, pos.z += z;
    transformPoints();
}

void Entity::setScale(float scal){
    scale = scal;
    transformPoints();
}
void Entity::addScale(float scal){
    scale += scal;
    transformPoints();
}

void Entity::setAngle(float angl){
    angle = angl;
    transformPoints();
}
void Entity::addAngle(float angl){
    angle += angl;
    transformPoints();
}

void Entity::transformPoints(){
    genTransMat();
    points.dot(transMat,0);
}

Matrix& Entity::verts(){
    return points.ans();
}
Matrix& Entity::getPoints(){
    return points;
}

void Entity::project(Window& win, Uint32 color){
    Matrix x = verts().col(0);
    Matrix y = verts().col(1);
    Matrix z = verts().col(2);

    color |= 0xFF; //make sure its opaque
    
    int larger = (win.w > win.h)?win.w:win.h;
    
    // simple perspective transform:
    // just divide x and y by z and scale to window
    // 'zs' controls FOV
    for(int r = 0; r < points.height(); r++){
        x[r] = x[r]*(win.zs/z[r])*larger + win.w/2;
        y[r] = y[r]*(win.zs/z[r])*larger + win.h/2;
    }
    
    
    if(showEdges){ // apply edges to screen
        if(edges.height()>0){ // if there are edges specified...
            for(int i = 0; i < edges.height(); i++){
                int p1 = edges(i,0), p2 = edges(i,1);
                if(z[p1]>0 && z[p2]>0){
                    win.drawLine(x[p1], y[p1], x[p2], y[p2], color);
                }
            }
        }else{ // else connect points as they are listed in 'points' matrix
            for(int i = 0, imax = points.height()-1; i < imax; i++){
                if(z[i]>0 && z[i+1]>0)
                    win.drawLine(x[i], y[i], x[i+1], y[i+1], color);
            }
        }
    }else{ // apply points to screen
    //if we apply lines, we dont need to apply points
        for(int i = 0; i < points.height(); i++){
            if(z[i]>0){
                win.applyPixel(y[i], x[i], color);
            }
        }
    }
}

void Entity::toggleEdges(bool toggle){
    showEdges = toggle;
}
