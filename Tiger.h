/* This file has been written and/or modified by the following people:
 *
 * You Yang
 *
 * This PBVI program is used for solving POMDPs which An implementation of:
 * Joelle Pineau, Geoffrey Gordon, Sebastian Thrun. Point-based value
 * iteration: An anytime algorithm for POMDPs. In IJCAI, 2003.
 * (http://ri.cmu.edu/pub_files/pub4/pineau_joelle_2003_3/pineau_joelle_2003_3.pdf)
 */

/* Only include this header file once. */
#ifndef _TIGER_H_
#define _TIGER_H_1
#include "PomdpInterface.h"
class TigerPb: public PomdpInterface
{
private:
    int S_size = 2; // TLeft, Right 
    int A_size = 3; // Left, Right, Listen
    int Obs_size = 2; // HTLeft, HTRight
    std::vector<double> b0{0.5,0.5};
public:
    TigerPb(/* args */);
    ~TigerPb();

    int GetSizeOfS(){return this->S_size;};
    int GetSizeOfA(){return this->A_size;};
    int GetSizeOfObs(){return this->Obs_size;};
    std::vector<double> GetInitBelief(){return this->b0;};


    double TransFunc(int sI, int aI, int s_newI);
    double ObsFunc(int oI, int s_newI, int aI);
    double Reward(int sI, int aI);

};




#endif /* !_TIGER_H_ */