#include "AlphaVector.h"

AlphaVector::AlphaVector(std::vector<double> V, const unsigned int aI)
{
    this->values = V;
    this->action_Index = aI;
}

AlphaVector::~AlphaVector()
{
}

unsigned int AlphaVector:: GetSize() const{
    return this->values.size();
};

double AlphaVector::operator[](unsigned int i){
    return this->values[i];
};

bool AlphaVector::operator==(AlphaVector & alpha){
    if (this->action_Index == alpha.action_Index)
    {
        for (int i = 0; i<this->GetSize();i++){
            if (this->values[i]!=alpha[i]){
                return false;
            }
        }
        
    }else
    {
        return false;
    }
    return true;
    
};

bool AlphaVector::operator!=(AlphaVector & alpha){
    return !(*this == alpha);
}

unsigned int AlphaVector:: GetActionIndex() const {
    return this->action_Index;
};

void  AlphaVector::ChangeValue(unsigned int sI, double v){
    this->values[sI] = v;
};

void AlphaVector::Print(){
    cout << "The action index in this alpha vector: " << this->action_Index << endl;
    std::cout << "<";
    for (unsigned int i = 0;i < this->GetSize();i++){
        std::cout << this->values[i] << " ";
    }
    std::cout << ">"<< std::endl;
};
