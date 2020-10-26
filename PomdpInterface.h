#ifndef _POMDPINTERFACE_H_
#define _POMDPINTERFACE_H_1

#include <vector>

class PomdpInterface
{
private:
    /* data */
public:
    PomdpInterface(/* args */){};
    ~PomdpInterface(){};

    virtual int GetSizeOfS()=0;
    virtual int GetSizeOfA()=0;
    virtual int GetSizeOfObs()=0;
    virtual std::vector<double> GetInitBelief()=0;
    virtual double TransFunc(int sI, int aI, int s_newI)=0;
    virtual double ObsFunc(int oI, int s_newI, int aI)=0;
    virtual double Reward(int sI, int aI)=0;
};
// PomdpInterface::PomdpInterface(/* args */){};
// PomdpInterface::~PomdpInterface(){};

#endif /* !_POMDPINTERFACE_H_ */