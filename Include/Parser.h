#ifndef _PARSER_H_
#define _PARSER_H_ 1

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>    
#include "PomdpInterface.h"
using namespace std;

class ParsedPOMDP: public PomdpInterface
{
private:
    vector<string> States;
    vector<string> Actions;
    vector<string> Observations;
    int S_size; 
    int A_size; 
    int Obs_size;
    vector<double> b0;
    vector<vector<vector<double>>> TransFuncVecs;
    vector<vector<vector<double>>> ObsFuncVecs;
    vector<vector<double>> RewardFuncVecs;
    double discount;

public:
    ParsedPOMDP(const string filename);
    ~ParsedPOMDP();
    double GetDiscount();
    int GetSizeOfS();
    int GetSizeOfA();
    int GetSizeOfObs();
    std::vector<double> GetInitBelief();
    double TransFunc(int sI, int aI, int s_newI);
    double ObsFunc(int oI, int s_newI, int aI);
    double Reward(int sI, int aI);
};



#endif

