#include "Matrix.hpp"

Matrix::Matrix(){}
Matrix::Matrix(Matrix& other){copy(other);}
Matrix::Matrix(int h, int w){create(h,w);}
Matrix::~Matrix(){clearAns();}

float Matrix::clamp(float val, float min, float max){
    if(val < min) val = min;
    if(val > max) val = max;
    return val;
}

void Matrix::clearAns(){
    if(answer) delete answer;
    answer = nullptr;
}

void Matrix::fill(float item){for(int i = 0; i < siz; i++) data[i] = item;}

void Matrix::eye(int size){
    create(size,size);
    for(int i = 0; i < siz; i+=size+1)
        data[i] = 1;
}

void Matrix::fillRandom(int upper, int lower){
    srand(clock());
    if(upper <= lower) lower = upper;
    
    int diff = upper - lower;
    diff = diff*100 + 1;
    for(int i = 0; i < siz; i++) data[i] = (rand()%diff)/100.0 + lower;
}

int Matrix::map2Dto1D(int row, int col){return row*cols + col;}

float& Matrix::item(int ind){return data[ind];}
float& Matrix::item(int row, int col){return data[map2Dto1D(row, col)];}

std::vector<float>& Matrix::getData(){return data;}

float& Matrix::operator[](int ind){return data[ind];}
float& Matrix::operator()(int ind){return data[ind];}
float& Matrix::operator()(int row, int col){return data[map2Dto1D(row, col)];}

void Matrix::operator= (Matrix& other){copy(other);}

void Matrix::backup(){
    clearAns();
    answer = new Matrix(*this);
}

Matrix& Matrix::transpose(){
    clearAns();
    answer = new Matrix(cols,rows);
    
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            answer->item(c,r) = (*this)(r,c);
        }
    }
    return *answer;
}

Matrix& Matrix::pad(int padCode, float inp){
    clearAns();
    
    char* padDir = (char*)&padCode;
    
    answer = new Matrix(
                        rows + padDir[3] + padDir[2],
                        cols + padDir[1] + padDir[0]
                        );
    answer->fill(inp);
    for(int r = 0, R = padDir[3]; r < rows; r++, R++){
        for(int c = 0, C = padDir[1]; c < cols; c++, C++){
            answer->item(R,C) = item(r,c);
        }
    }
    
    return *answer;
}

Matrix& Matrix::row(int rowNum){
    rowNum = clamp(rowNum, 0, rows);
    
    clearAns();
    answer = new Matrix(1,cols);
    
    for(int i = rowNum*cols, c = 0; c < cols; i++, c++){
        answer->item(c) = data[i];
    }
    return *answer;
}

Matrix& Matrix::col(int colNum){
    colNum = clamp(colNum, 0, cols);
    
    clearAns();
    answer = new Matrix(rows,1);
    
    for(int i = colNum, r = 0; r < rows; i+=cols, r++){
        answer->item(r) = data[i];
    }
    return *answer;
}

void Matrix::setRow(int rowNum, Matrix& inp){
    if(inp.height() == 1 && inp.width() == cols){
        
        rowNum = clamp(rowNum, 0, rows-1);
        
        for(int i = rowNum*cols, c = 0; c < cols; i++, c++){
            data[i] = inp[c];
        }
    }else{
        Matrix::noConformError(*this, inp);
    }
}

void Matrix::setCol(int colNum, Matrix& inp){
    if(inp.width() == 1 && inp.height() == rows){
        colNum = clamp(colNum, 0, cols-1);
        
        for(int i = colNum, r = 0; r < rows; i+=cols, r++){
            data[i] = inp[r];
        }
    }else{
        Matrix::noConformError(*this, inp);
    }
}

Matrix& Matrix::operator+(Matrix& other){
    if(rows != other.height() || cols != other.width()) noConformError(*this, other);
    
    Matrix* tempAns = new Matrix(rows,cols);
    
    for(int i = 0; i < siz; i++)
        tempAns->data[i] = this->data[i] + other[i];
    
    
    other.clearAns();
    other.answer = tempAns;
    return *tempAns;
}



Matrix& Matrix::dot(Matrix& other, bool who){
    if(cols != other.height()) noConformError(*this, other);
    
    Matrix* tempAns = new Matrix(rows,other.width());
    
    for(int r = 0; r < tempAns->rows; r++){
        for(int c = 0; c < tempAns->cols; c++){
            int ind = tempAns->map2Dto1D(r,c);
            (*tempAns)[ind] = 0;
            
            for(int dot = 0; dot < cols; dot++){
                (*tempAns)[ind] += (*this)(r,dot) * other(dot, c);
            }
        }
    }
    
    if(who){
        other.clearAns();
        other.answer = tempAns;
    }else{
        clearAns();
        answer = tempAns;
    }
    
    return *tempAns;
}



Matrix& Matrix::operator* (Matrix& other){return dot(other,1);}


Matrix& Matrix::operator* (float num){
    
    Matrix* tempans = new Matrix(rows, cols);
    
    for(int i = 0; i < siz; i++){
        tempans->item(i) = data[i]*num;
    }
    
    clearAns();
    answer = tempans;
    return *tempans;
}

Matrix& Matrix::operator/ (float num){
    
    Matrix* tempans = new Matrix(rows, cols);
    
    for(int i = 0; i < siz; i++){
        tempans->item(i) = data[i]/num;
    }
    
    clearAns();
    answer = tempans;
    return *tempans;
}

Matrix& Matrix::operator+ (float num){
    
    Matrix* tempans = new Matrix(rows, cols);
    
    for(int i = 0; i < siz; i++){
        tempans->item(i) = data[i]+num;
    }
    
    clearAns();
    answer = tempans;
    return *tempans;
}

Matrix& Matrix::operator- (float num){
    
    Matrix* tempans = new Matrix(rows, cols);
    
    for(int i = 0; i < siz; i++){
        tempans->item(i) = data[i]-num;
    }
    
    clearAns();
    answer = tempans;
    return *tempans;
}

void Matrix::operator*= (float num){
    for(int i = 0; i < siz; i++){
        data[i]*=num;
    }
}

void Matrix::operator/= (float num){
    for(int i = 0; i < siz; i++){
        data[i]/=num;
    }
}

void Matrix::operator+= (float num){
    for(int i = 0; i < siz; i++){
        data[i]+=num;
    }
}

void Matrix::operator-= (float num){
    for(int i = 0; i < siz; i++){
        data[i]-=num;
    }
}


void Matrix::create(int h,int w){
    if(h < 1) h = 1;
    if(w < 1) w = 1;
    clearAns();
    rows = h, cols = w, siz = h*w;
    data.assign(siz, 0);
}



void Matrix::copy(Matrix& other){
    create(other.height(), other.width());
    data = other.data;
}


int Matrix::width(){return cols;}

int Matrix::height(){return rows;}

int Matrix::size(){return siz;}

Matrix& Matrix::ans(){
    if(!answer){
        std::cout << "\nNo Ans exists.\nReturning Parent Matrix.\n";
        return *this;
    }
    return *answer;
}

Matrix& Matrix::lastAns(){
    Matrix* curr = this;
    while(curr->answer) curr = curr->answer;
    return *curr;
}

void Matrix::noConformError(Matrix& A, Matrix& B){
    std::cout << "Matrices do not conform!\n";
    std::cout << "Mat A: " << &A
    << " " << A.height() << "x" << A.width() << std::endl;
    std::cout << "Mat B: " << &B
    << " " << B.height() << "x" << B.width() << std::endl;
    std::exit(0);
}


double Matrix::mag(){
    float sqsum = 0;
    for(int i = 0; i < siz; i++){
        sqsum += data[i]*data[i];
    }
    
    return std::sqrt(sqsum);
}


Matrix& Matrix::norm(){
    
    float mag = this->mag();
    
    Matrix* tempAns = new Matrix(rows,cols);
    
    for(int i = 0; i < siz; i++){
        tempAns->data[i] = this->data[i]/mag;
    }
    
    clearAns();
    answer = tempAns;
    return *tempAns;
}


Matrix& Matrix::sum(bool dim){
    int dimRemaining = (dim)?cols:rows;
    Matrix* tempAns = new Matrix(dim?1:dimRemaining, dim?dimRemaining:1);
    
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            tempAns->data[dim?c:r] += (*this)(r, c);
        }
    }
    clearAns();
    answer = tempAns;
    return *answer;
}


bool Matrix::hasAns(){return (answer>0);}



void Matrix::print(bool linear){
    int i = 0;
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            std::cout << std::setw(9) << std::setprecision(3) << data[i++] << " ";
        }
        if(!linear) std::cout << "\n";
    }
    std::cout << "\n";
}
