#include "Utils.h"


// For state and action index, unsigned int
// For belief point index, unsigned long


double ComputeAvgL1Distance(Belief& b,vector<Belief>& bs, int NrB){
    // double res;
    double res = 0;
    vector<double> b_value = b.GetBelief();
    // Loop for each belief point in the belief set bs
    for (unsigned long i=0;i<NrB;i++){
        vector<double> b_temp = bs[i].GetBelief();
        double temp_sum = 0;
        for (unsigned int j=0;j<b_value.size();j++){
            temp_sum += abs(b_value[j] - b_temp[j]);
        }
        // If temp_sum is 0, it means b already in bs, return = 0 directly
        if (temp_sum< MIN_B_ACC) return 0;

        res += temp_sum;
    }
    return res/bs.size();
};

// Find the most far distance belief point in temp_bs, then add it tp the bs
void ExpandBeliefSet(vector<Belief>& bs, vector<Belief>& temp_bs, int NrB ){
    if (bs.size() >= NrB){
        int select_i = -1;
        double dis = 0;
        for (unsigned long i = 0;i < temp_bs.size();i++){
            double temp_dis = ComputeAvgL1Distance(temp_bs[i], bs, NrB);

            if (temp_dis > dis) {
                dis = temp_dis;
                select_i = i;
            }
        }


        if(dis> MIN_B_ACC && select_i > -1){
            bs.push_back(temp_bs[select_i]);
        }
    }else
    {
        cerr << "The bs size and given number of belief point dont match!" << endl;
    }


    
}

double dot(Belief& b, AlphaVector& alpha){
    // First, check the dimension equality
    if (b.GetSize()!=alpha.GetSize()){
        cerr << "b_size:"<<b.GetSize() <<", alpha_size:"<<alpha.GetSize() << ". Dimension not equal!" << endl;
        throw("Dimension not equal");
    } 
    double res = 0;
    for (unsigned int i = 0; i < b.GetSize();i++){
        res += b[i]*alpha[i];
    }
    return res;
}

double ComputeDistanceAlphas(AlphaVector& a, AlphaVector& b){
    double res = 0;
    // Check dimension equal
    if (a.GetSize()!=b.GetSize()){
        cerr << "sizes of two alphas are not equal!" << endl;
        throw("");
    }else
    {
        for (int i = 0; i<a.GetSize();i++){
            res += abs(a[i] - b[i]);
        }
    }
    return res;
    
}

bool CheckConvergence(vector<AlphaVector>& a_vecs, vector<AlphaVector>& b_vecs, double err){
    // Check dimension equal
    if (a_vecs.size()!=b_vecs.size()){
        return false;
    }else{
        for (int i = 0; i<a_vecs.size();i++){
            if (ComputeDistanceAlphas(a_vecs[i], b_vecs[i]) > err){
                return false;
            }
        }
    }
    return true;
}

bool CheckAlphaExist(vector<AlphaVector>& a_vecs, AlphaVector& alpha){
    if (a_vecs.size()==0) return false;
    for (int i = 0; i<a_vecs.size();i++){
        if (a_vecs[i]==alpha){
            return true;
        }
    }
    return false;
}

void PrintBeliefSet(vector<Belief>& bs){
    for (int i = 0;i <bs.size();i++){
        bs[i].PrintBelief();
    }
}

void PrintAlphaVectors(vector<AlphaVector>& a_vecs){
    for (int i = 0; i <a_vecs.size(); i++){
        a_vecs[i].Print();
    }
};

void PrintAllAlphaAOVecs(vector< vector<vector<AlphaVector>>>& a_ao_vecs){
    // For all the action index in alpha_a_b
    for (unsigned int aI = 0; aI<a_ao_vecs.size();aI++){
        // cout << " ---- aI:"<<aI;
        // For all the oI 
        for (unsigned int oI = 0; oI<a_ao_vecs[aI].size();oI++){
            // cout << ", oI:"<<oI <<" ---- " << endl;
            // For all alpha idx
            for (int idx = 0; idx<a_ao_vecs[aI][oI].size();idx++){
                cout << " ---- aI:"<<aI <<", oI:"<<oI  << ", alpha_idx:"<<idx << " -----" << endl;
                a_ao_vecs[aI][oI][idx].Print();
            }
        }
    }
};

