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
#ifndef _BELIEF_H_
#define _BELIEF_H_1

#include <iostream>
#include <vector>

class Belief
{
private:
    std::vector<double> pb_states;
public:
    Belief(const std::vector<double> b);
    void PrintBelief();
    ~Belief();

    // Saw in MADP, they used two const, one in front, one in the end
    const std::vector<double> GetBelief() const;
    Belief& operator=(const Belief& o);
    double operator[](int i);
    bool operator==(Belief& o);
    unsigned long GetSize() const;

};



#endif /* !_BELIEF_H_ */
