#include "Shapes.hpp"

Cube::Cube(){
    generateGeometry();
}

void Cube::generateGeometry(){
    points.create( 8, 4);
    edges .create(12, 2);
    for(int i = 0; i < 8; i++){
        points.item(i, 0) = ((i & 1)>0)?1:-1;
        points.item(i, 1) = ((i & 2)>0)?1:-1;
        points.item(i, 2) = ((i & 4)>0)?1:-1;
        points.item(i, 3) = 1;
    }
    
    // just list out edge connections
    edges.item(0,0) = 0; edges.item(0,1) = 1;
    edges.item(1,0) = 0; edges.item(1,1) = 2;
    edges.item(2,0) = 0; edges.item(2,1) = 4;
    edges.item(3,0) = 7; edges.item(3,1) = 3;
    edges.item(4,0) = 7; edges.item(4,1) = 5;
    edges.item(5,0) = 7; edges.item(5,1) = 6;
    edges.item(6,0) = 4; edges.item(6,1) = 6;
    edges.item(7,0) = 4; edges.item(7,1) = 5;
    edges.item(8,0) = 1; edges.item(8,1) = 3;
    edges.item(9,0) = 2; edges.item(9,1) = 3;
    edges.item(10,0) = 2; edges.item(10,1) = 6;
    edges.item(11,0) = 1; edges.item(11,1) = 5;
    
    points.backup();
}

Sphere::Sphere(int resolution){
    res = resolution;
    generateGeometry();
}

void Sphere::generateGeometry(){
    int vnum  = res*(res/2-1)+2; // number of vertices
    int ednum = res*(res-1);    // number of edges

    points.create(vnum, 4);
    edges.create(ednum, 2);
    
    int i = 1; // for indexing the points
    int div = res/2; // number of divisions
    float phi = 0, theta = 0;
    float trig[4];
    for(int v = 1; v < div; v++){ // v for angle from vertical axis
        phi = v/(float)div*PI;
        for(int a = 0; a < res; a++){ // h for angle around vertical axis
            theta = a/(float)res*2*PI;
            
            trig[0] = std::sin(phi);
            trig[1] = std::cos(phi);
            trig[2] = std::sin(theta);
            trig[3] = std::cos(theta);
            
            
            points.item(i, 0) = trig[0]*trig[3];
            points.item(i, 1) = trig[0]*trig[2];
            points.item(i, 2) = trig[1];
            points.item(i, 3) = 1;
            i++;
        }
    }
    
    
    // make edges
    int ind = 0;
    int ind_offset = vnum - 2;
    for(int ring = 0, ringMax = res/2-1; ring < ringMax; ring++){ // for each ring
        for(int vert = 0; vert < res; vert++){     // for each vertex on each ring
            edges.item(ind, 0) = ind+1;
            edges.item(ind, 1) = ((vert+1)%res)? ind+2 : ind-res+2;
            
            edges.item(ind+ind_offset, 0) = ind+1; // = edges.item(ind, 0);
            
            int temp = ind+1-res; // just to reduce calculations
            edges.item(ind+ind_offset, 1) = temp; // = edges.item(ind, 0) - res;
            
            // dont let it be less than zero:
            if(temp < 0) edges.item(ind+ind_offset, 1) = 0;
            
            ind++;
        }
    }
    
    vnum--; // sub 1 to index last point
    
    // for the final 'res' edges
    for(int vert = 0; vert < res; vert++){// for each vertex on the last ring
        edges.item(ind+ind_offset+vert, 0) = edges.item(ind+ind_offset-res+vert, 0);
        edges.item(ind+ind_offset+vert, 1) = vnum;
    }
    
    points.item(   0, 2) =  1;
    points.item(   0, 3) =  1;
    points.item(vnum, 2) = -1;
    points.item(vnum, 3) =  1;
    
    points.backup();
}

RandomPoints::RandomPoints(int length){
    len = length;
    generateGeometry();
}

void RandomPoints::generateGeometry(){
    points.create(len,4);
    points.fillRandom(1,-1);
    
    for(int i = 0; i < len; i++){
        points.item(i, 3) = 1;
    }
    
    points.backup();
}









