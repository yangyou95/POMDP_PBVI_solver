#include "../Include/Belief.h"

Belief::Belief(const std::vector<double> b)
{
    this->pb_states = b;
}

const std::vector<double> Belief::GetBelief() const{
    return this->pb_states;
};

unsigned long  Belief::GetSize() const{
    return this->pb_states.size();
}
Belief& Belief::operator=(const Belief& o){
    this->pb_states = o.pb_states;
    return *this;
};
double Belief:: operator[](int i){
    return this->pb_states[i];
};

bool Belief:: operator==(Belief& o){
    bool res = true;
    if (o.GetSize()!=this->GetSize()){
        throw("Two belief point sizes don't match!");
    }
    for (unsigned long i = 0;i < this->GetBelief().size();i++){
        if(this->pb_states[i]!= o[i]){
            res = false;
            return res;
        } 
    }
    return res;
};

void Belief::PrintBelief(){
    std::cout << "<";
    for (unsigned long i = 0;i < this->GetBelief().size();i++){
        std::cout << this->GetBelief()[i] << " ";
    }
    std::cout << ">"<< std::endl;

};


Belief::~Belief()
{
}