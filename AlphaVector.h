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
#ifndef _ALPHAVECTOR_H_
#define _ALPHAVECTOR_H_ 1

#include <iostream>
#include <vector>

using namespace std;

class AlphaVector
{
private:
    std::vector<double> values;
    unsigned int action_Index;
    /* data */
public:
    AlphaVector(){};
    AlphaVector(std::vector<double> V, const unsigned int aI);
    unsigned int GetSize() const;
    unsigned int GetActionIndex() const;
    double operator[](unsigned int i);
    void ChangeValue(unsigned int sI, double v);
    void Print();
    ~AlphaVector();
};



#endif /* !_ALPHAVECTOR_H_ */
