#ifndef Matrix_hpp
#define Matrix_hpp

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

class Matrix{
protected:
    std::vector<float> data;
    int rows = 0, cols = 0,siz  = 0;
    
    Matrix* answer = nullptr;
    
    int map2Dto1D(int,int);
    
    void clearAns();
    
    
    static void noConformError(Matrix&, Matrix&);
public:
    static float clamp(float,float,float);
    Matrix();
    Matrix(Matrix&);
    Matrix(int,int = 1);
    ~Matrix();
    
    void create(int,int = 1);
    void copy(Matrix&);
    void fill(float);
    void fillRandom(int,int = 0);
    void eye(int = 2);
    
    void backup();
    
    float& item(int);
    float& item(int, int);
    std::vector<float>& getData();
    
    
    float& operator[] (int);
    float& operator() (int);
    float& operator() (int,int);
    
    Matrix& row(int rowNum);
    Matrix& col(int colNum);
    void setRow(int, Matrix&);
    void setCol(int, Matrix&);
    
    Matrix& transpose();
    Matrix& pad(int, float = 0);
    
    
    Matrix& dot(Matrix&, bool = 1);
    
    
    
    Matrix& operator+ (Matrix&);
    Matrix& operator* (Matrix&);
    void operator= (Matrix&);
    
    Matrix& operator*  (float);
    Matrix& operator/  (float);
    Matrix& operator+  (float);
    Matrix& operator-  (float);
    void operator*= (float);
    void operator/= (float);
    void operator+= (float);
    void operator-= (float);
    
    
    double mag();
    Matrix& norm();
    
    Matrix& sum(bool = 0);
    
    void print(bool = false);
    
    int width();
    int height();
    int size();
    bool isFloating();
    bool hasAns();
    
    Matrix& ans();
    Matrix& lastAns();
};

#endif /* Matrix_hpp */
