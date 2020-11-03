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
#ifndef _PBVIPLANNER_H_
#define _PBVIPLANNER_H_1

#include "Utils.h"
#include <iostream>
#include "PomdpInterface.h"

class PbviPlanner
{
private:
    vector<Belief> BS; //Belief Set
    vector<AlphaVector> AlphaVecs; // Value Function (Alpha Vectors)
    vector<vector <double> > RewardVecs; // Reward vectors
    double err = __DBL_MIN__;
    double gamma;
    int MAX_BP; // Max Belief set size
    int MAX_ITER_GLOBAL; // Max iteration number in PBVI main alogrithm
    int MAX_ITER_IMP; // Max iteration number during improving process
    PomdpInterface *Pb;
public:
    PbviPlanner(double gamma, int MAX_BP, int MAX_ITER_GLOBAL, int MAX_ITER_IMP, PomdpInterface *Pb);
    ~PbviPlanner();
    vector<AlphaVector> BuildInitalV(double gamma, PomdpInterface *Pb);
    Belief UpdateForward(unsigned int oI, unsigned int aI, Belief& b, PomdpInterface *Pb);
    vector<Belief>& SampleBeliefPoints(int BS_size, int S_size, vector<Belief>& BPS);
    double Pr_oba(int oI, Belief& b, int aI, PomdpInterface *Pb);
    vector<Belief> successors_b(Belief& b, PomdpInterface* Pb);
    vector<Belief> Expand(vector<Belief>& BS, int MAX_BP, PomdpInterface* Pb);
    AlphaVector UpdateAlphaAO(unsigned int aI, AlphaVector alpha, unsigned oI, PomdpInterface* Pb);
    vector<vector <double> > BuildRewardVectors(PomdpInterface* Pb);
    vector< vector<vector<AlphaVector> > > ComputeAllAlphaAOValues(vector<AlphaVector>& alpha_vecs, PomdpInterface* Pb);
    AlphaVector UpdateAlphaAB(unsigned int aI, vector< vector<vector<AlphaVector> > >& AlphaAOVecs, Belief& b,  vector<vector <double> >& RewardVecs, double gamma, PomdpInterface* Pb);
    AlphaVector backup(vector<AlphaVector>& alpha_vecs, Belief& b,vector< vector<vector<AlphaVector> > >& AlphaAOVecs, vector<vector <double> >& RewardVecs, double gamma, PomdpInterface* Pb);
    void Improve(vector<AlphaVector>& alpha_vecs,vector<Belief>& BPS,vector<vector <double> >& RewardVecs, double gamma, int MAX_ITER_IMP ,PomdpInterface* Pb);
    void PrintRewardVecs(vector<vector <double> > & RVecs, PomdpInterface* Pb);
    void Plan(vector<AlphaVector>& alpha_vecs,vector<Belief>& BPS, int MAX_BP,vector<vector <double> >& RewardVecs, double gamma, int MAX_ITER_G, int MAX_ITER_I, double err ,PomdpInterface* Pb);
    void Plan();
    vector<AlphaVector> GetValueFunction();
};



#endif /* !_PBVIPLANNER_H_ */
