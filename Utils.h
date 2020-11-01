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
#ifndef _UTILS_H_
#define _UTILS_H_1

#include <iostream>
#include <vector>
#include "Belief.h"
#include "AlphaVector.h"
using namespace std;

#define MIN_B_ACC 1e-3




double ComputeAvgL1Distance(Belief& b,vector<Belief>& bs, int NrB);
void ExpandBeliefSet(vector<Belief>& bs, vector<Belief>& temp_bs, int NrB );
double dot(Belief& b, AlphaVector& alpha);
double ComputeDistanceAlphas(AlphaVector& a, AlphaVector& b);
bool CheckConvergence(vector<AlphaVector>& a_vecs, vector<AlphaVector>& b_vecs, double err);
bool CheckAlphaExist(vector<AlphaVector>& a_vecs, AlphaVector& alpha);
void PrintBeliefSet(vector<Belief>& bs);
void PrintAlphaVectors(vector<AlphaVector>& a_vecs);
void PrintAllAlphaAOVecs(vector< vector<vector<AlphaVector>>>& a_ao_vecs);
#endif /* !_UTILS_H_ */