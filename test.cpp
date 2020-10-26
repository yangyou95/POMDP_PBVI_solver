# include "Utils.h"
#include <iostream>
#include "Tiger.h"
#include "time.h"
using namespace std;
const int NrB = 150;

Belief UpdateForward(unsigned int oI, unsigned int aI, Belief& b, PomdpInterface *Pb);
vector<Belief>& SampleBeliefPoints(int BS_size, int S_size, vector<Belief>& BPS);
double Pr_oba(int oI, Belief& b, int aI, PomdpInterface *Pb);
vector<Belief> successors_b(Belief& b, PomdpInterface* Pb);
vector<Belief> Expand(vector<Belief>& BS, int MAX_BP, PomdpInterface* Pb);
AlphaVector UpdateAlphaAO(unsigned int aI, AlphaVector alpha, unsigned oI, PomdpInterface* Pb);
vector<vector <double> > BuildRewardVectors(PomdpInterface* Pb);
vector< vector<vector<AlphaVector>>> ComputeAllAlphaAOValues(vector<AlphaVector>& alpha_vecs, PomdpInterface* Pb);
AlphaVector UpdateAlphaAB(unsigned int aI, vector< vector<vector<AlphaVector>>>& AlphaAOVecs, Belief& b,  vector<vector <double> >& RewardVecs, double gamma, PomdpInterface* Pb);
AlphaVector backup(vector<AlphaVector>& alpha_vecs, Belief& b,vector< vector<vector<AlphaVector>>>& AlphaAOVecs, vector<vector <double> >& RewardVecs, double gamma, PomdpInterface* Pb);
void Improve(vector<AlphaVector>& alpha_vecs,vector<Belief>& BPS,vector<vector <double> >& RewardVecs, double gamma, int MAX_ITER ,PomdpInterface* Pb);
void PrintRewardVecs(vector<vector <double> > & RVecs, PomdpInterface* Pb);
void PBVI_main(vector<AlphaVector>& alpha_vecs,vector<Belief>& BPS, int MAX_BP,vector<vector <double> >& RewardVecs, double gamma, int MAX_ITER, double err ,PomdpInterface* Pb);


const int a_left_I = 0;
const int a_right_I = 1;
const int a_listen_I = 2;



int main(){
    Belief b_0({0.5,0.5});
    // Belief b_1({0.45,0.55});
    // Belief b_2({0.1,0.9});

    // Belief b0({0.1,0.9});
    // Belief b1({0.2,0.8});
    // Belief b2({0.3,0.7});
    // Belief b3({0.4,0.6});



    // vector<Belief> bs{b0,b1,b2,b3};
    // vector<Belief> temp_bs{b_0,b_1,b_2};

    // cout << "Size before expansion: " << bs.size() << endl;
    // ExpandBeliefSet(bs, temp_bs, NrB);
    // cout << "Size after expansion: " << bs.size() << endl;


    PomdpInterface *Pb = new TigerPb();
   


    // cout << Pb.Reward(1,1) << endl;
    // cout << Pb.TransFunc(1,1,1) << endl;
    // cout << Pb.TransFunc(0,1,1) << endl;

    // cout << Pb->GetSizeOfS() << endl;
    clock_t start,end;
    start = clock();
    vector<Belief> BS{b_0};
    // vector<Belief> new_BS = Expand(BS,Pb);
    // vector<Belief> new2_BS = Expand(new_BS,Pb);
    // vector<Belief> new3_BS = Expand(new2_BS,Pb);
    // vector<Belief> new4_BS = Expand(new3_BS,Pb);

    // for (int i = 0; i < new4_BS.size(); i++){
    //     new4_BS[i].PrintBelief();
    // }
    // cout << "The process finished in "<< (double)(end-start)/CLOCKS_PER_SEC << " s" << endl;



    // test AlphaVector update
    vector<double> v_left{-100, -100};
    vector<double> v_right{-100, -100};
    vector<double> v_listen{-100, -100};
    AlphaVector alpha_left(v_left,a_left_I);
    AlphaVector alpha_right(v_right,a_right_I);
    AlphaVector alpha_listen(v_listen,a_listen_I);

    vector<AlphaVector> AlphaVecs{alpha_left, alpha_right, alpha_listen};



    // int oI = 1; //HTRight
    // AlphaVector updated_alpha = UpdateAlphaAO(1,alpha_left, oI, Pb);

    // cout << " --- Before update ---" << endl;
    // alpha_left.Print();
    // cout << " --- After update ---" << endl;
    // updated_alpha.Print();

    vector<vector <double> > RewardVecs = BuildRewardVectors(Pb);
    // PrintRewardVecs(RewardVecs, Pb);

    cout << " ----- Before Improved -----" << endl;
    for (int i = 0; i < AlphaVecs.size(); i++)
    {
        AlphaVecs[i].Print();
    }

    double err = -__DBL_MAX__;
    int MAX_BP = 100;
    PBVI_main(AlphaVecs, BS,MAX_BP,RewardVecs,0.95,100,err,Pb);

    cout << " ----- After Improved -----" << endl;
    for (int i = 0; i < AlphaVecs.size(); i++)
    {
        AlphaVecs[i].Print();
    }
    




    // int BS_size = 20;
    // int S_size = Pb->GetSizeOfS();

    // srand((unsigned)time(NULL));
    // clock_t start,end;
    // start = clock();
    // vector<Belief> inital_belief_set{PbGetInitBelief()};
    // SampleBeliefPoints(BS_size,S_size, inital_belief_set);
    // end = clock();
    // cout << " ---------- " << endl;
    // cout << "Belief points: " << BS_size << endl;
    // cout << "State Numbers: " << S_size << endl;
    // cout << "The sampling process finished in "<< (double)(end-start)/CLOCKS_PER_SEC << " s" << endl;
    return 0;

}



Belief UpdateForward(unsigned int oI, unsigned int aI, Belief& b, PomdpInterface *Pb){
    vector<double> b_aI_value(Pb->GetSizeOfS()); 
    double pr_oba = Pr_oba(oI,b,aI,Pb);
    if (pr_oba > 0){
        for (unsigned int s_newI = 0; s_newI < Pb->GetSizeOfS(); s_newI++){
            double p_s_newI = 0;
            for (unsigned int sI = 0; sI < Pb->GetSizeOfS(); sI++){
                p_s_newI += Pb->TransFunc(sI,aI,s_newI)*b[sI];
            }
            // cerr << "pr_oba:" << pr_oba << endl;
            // cerr << "something" << endl;
            double pr_snew_ao = (Pb->ObsFunc(oI,s_newI,aI)*p_s_newI)/pr_oba;
            // cerr << "bai_size: " << b_aI_value.size() <<" , snewI:" << s_newI << endl;
            b_aI_value[s_newI] = pr_snew_ao;
            // cerr << "something else" << endl;
        }
        
    }
    Belief b_ao(b_aI_value);

    return b_ao;

};


// This may be bad, in paper, the inital belief point set is expanded using the initial belief point
vector<Belief>& SampleBeliefPoints(int BS_size, int S_size, vector<Belief>& BPS){
    
    while (BPS.size()< BS_size)
    {
        vector<double> temp_b;
        double temp_sum = 0;
        bool check = true;
        for (unsigned int si = 0;si<S_size-1;si++){
            double random_p = static_cast <double> (rand()) / static_cast <double> (RAND_MAX); 
            temp_sum += random_p;
            temp_b.push_back(random_p);
            if (temp_sum>1){
                check = false;
                break;
            }
        }
        if(temp_sum<1 && check){
            temp_b.push_back(1-temp_sum);
            Belief b(temp_b);
            // b.PrintBelief();
            BPS.push_back(b);
        }
    }
    return BPS;
};


double Pr_oba(int oI, Belief& b, int aI, PomdpInterface *Pb)
{
    double p_oba = 0;
    for (unsigned int s_newI = 0; s_newI < Pb->GetSizeOfS(); s_newI++){
        double p_s_newI = 0;
        for (unsigned int sI = 0; sI < Pb->GetSizeOfS(); sI++){
            p_s_newI += Pb->TransFunc(sI,aI,s_newI)*Pb->ObsFunc(oI,s_newI,aI)*b[sI];
        }
        p_oba+=p_s_newI;
    }
    return p_oba;
}


// Can be optimized
vector<Belief> successors_b(Belief& b, PomdpInterface* Pb){
    vector<Belief> succ_b;
    for (int aI = 0; aI<Pb->GetSizeOfA();aI++){
        for (int oI = 0; oI<Pb->GetSizeOfObs();oI++){
            // cout << " ------" << endl;
            // cout <<"oI:"<<oI <<", aI:"<<aI << endl;
            Belief b_ao = UpdateForward(oI,aI,b,Pb);
            // b_ao.PrintBelief();
            succ_b.push_back(b_ao);
        }
    }
    return succ_b;
}


vector<Belief> Expand(vector<Belief>& BS, int MAX_BP, PomdpInterface* Pb){
    int NrB = BS.size();
    // For each belief point in BS
    if (BS.size() < MAX_BP){
        for (int i = 0; i<NrB;i++){
            vector<Belief> succ_b = successors_b(BS[i],Pb);
            ExpandBeliefSet(BS, succ_b,NrB);
        }
        return BS;
    }else{
        return BS;
    }

}

// Dont use & alpha, becuase currently dont update the alpha vectors in V
AlphaVector UpdateAlphaAO(unsigned int aI, AlphaVector alpha, unsigned oI, PomdpInterface* Pb){
    vector<int> temp(alpha.GetSize());
    for (unsigned int sI = 0; sI < alpha.GetSize(); sI++){
        double pr_sn = 0;
        for (unsigned int s_newI = 0; s_newI < alpha.GetSize(); s_newI++){
            pr_sn += alpha[s_newI]*Pb->ObsFunc(oI,s_newI,aI)*Pb->TransFunc(sI,aI,s_newI);
        }
        temp[sI] = pr_sn;
    }
    for (unsigned int sI = 0; sI < alpha.GetSize(); sI++){
        alpha.ChangeValue(sI, temp[sI]);
    }
    return alpha;
}

AlphaVector UpdateAlphaAB(unsigned int aI, vector< vector<vector<AlphaVector>>>& AlphaAOVecs, Belief& b,  vector<vector <double> >& RewardVecs, double gamma, PomdpInterface* Pb){
    // reward vector for an action a
    vector<double> rewards = RewardVecs[aI];
    vector<double> values(Pb->GetSizeOfS());
    // Find different alphavecs (diff aI, same oI), which can have max b*alpha_a_o
    for (unsigned int oI = 0; oI <Pb->GetSizeOfObs(); oI++){
        // Update alpha vec according to oI and find argmax b*alpha_a_o
        double max_res = -__DBL_MAX__;
        int selected_aI = 0;
        // For each alpha vector (alpha_a_o)
        for (unsigned int i= 0; i < Pb->GetSizeOfA(); i++){
            if (dot(b,AlphaAOVecs[aI][i][oI]) > max_res){
                max_res = dot(b,AlphaAOVecs[aI][i][oI]);
                selected_aI = i;
            } 
        }
        
        // update value for each sI
        for (unsigned int sI = 0;sI<Pb->GetSizeOfS(); sI++){
            values[sI] = rewards[sI] + gamma*AlphaAOVecs[aI][selected_aI][oI][sI];
        } 
    }
    AlphaVector alpha_a_b(values,aI);
    return alpha_a_b;

}


// Checked
vector<vector <double> > BuildRewardVectors(PomdpInterface* Pb){
    vector<vector <double> > RewardVecs(Pb->GetSizeOfA());
    for (unsigned int aI= 0; aI < Pb->GetSizeOfA(); aI++){
        vector<double> rewards_aI(Pb->GetSizeOfS());
        for (unsigned int sI = 0; sI < Pb->GetSizeOfS(); sI++){
            rewards_aI[sI] = Pb->Reward(sI,aI);
        }
        RewardVecs[aI] = rewards_aI;
    }
    return RewardVecs;
}

// Just for testing the RewardVecs
void PrintRewardVecs(vector<vector <double> > & RVecs, PomdpInterface* Pb){
    for (unsigned int aI= 0; aI < Pb->GetSizeOfA(); aI++){
        for (unsigned int sI = 0; sI < Pb->GetSizeOfS(); sI++){
            cout <<"aI: "<<aI << ", sI:"<<sI<<", Reward:"<<RVecs[aI][sI]<<endl;
        }
    }
}

// Compute all the alpha_a_o values and store them to use in different belief point
vector< vector<vector<AlphaVector>>> ComputeAllAlphaAOValues(vector<AlphaVector>& alpha_vecs, PomdpInterface* Pb){
    vector< vector<vector<AlphaVector>>> AlphaAOVecs(Pb->GetSizeOfA(),vector<vector<AlphaVector>>(Pb->GetSizeOfA(),vector<AlphaVector>(Pb->GetSizeOfObs())));
    // For all the action index in alpha_a_b
    for (unsigned int i = 0; i<Pb->GetSizeOfA();i++){
        // For all the alpha vector 
        for(unsigned int j = 0; j<alpha_vecs.size(); j++){
            // For all the observation
            for (unsigned int oI = 0; oI<Pb->GetSizeOfObs();oI++){
                AlphaAOVecs[i][j][oI] = UpdateAlphaAO(i,alpha_vecs[j],oI,Pb);
            }
        }
    }
    return AlphaAOVecs;
}

AlphaVector backup(vector<AlphaVector>& alpha_vecs, Belief& b,vector< vector<vector<AlphaVector>>>& AlphaAOVecs, vector<vector <double> >& RewardVecs, double gamma, PomdpInterface* Pb){
    double res = -__DBL_MAX__;
    int selected_I = -1;
    vector<AlphaVector> vec_alpha(Pb->GetSizeOfA());
    for (int aI = 0; aI < Pb->GetSizeOfA(); aI++)
    {
        vec_alpha[aI] = UpdateAlphaAB(aI, AlphaAOVecs, b, RewardVecs, gamma,Pb);
        double temp = dot(b,vec_alpha[aI]);
        if(temp>res){
            res = temp;
            selected_I = aI;
        }
    }
    return vec_alpha[selected_I];
}

void Improve(vector<AlphaVector>& alpha_vecs,vector<Belief>& BPS,vector<vector <double> >& RewardVecs, double gamma, int MAX_ITER ,PomdpInterface* Pb){
    double err = __DBL_MIN__;
    for (int i = 0; i < MAX_ITER; i++)
    {
        vector<AlphaVector> temp_vecs = alpha_vecs;
        // Compute a vector to store alpha_a_o values
        vector< vector<vector<AlphaVector>>> AlphaAOVecs = ComputeAllAlphaAOValues(alpha_vecs,Pb);
        for (int bI = 0; bI < BPS.size(); bI++){
            AlphaVector alpha = backup(alpha_vecs,BPS[bI],AlphaAOVecs,RewardVecs,gamma,Pb);
            alpha_vecs[alpha.GetActionIndex()] = alpha;

        }
        // Check converged or not
        if (CheckConvergence(temp_vecs, alpha_vecs, err)){
            cerr << "Coverged in improvement at iteration:"<<i << endl;
            return;
        }
    }
    
};

void PBVI_main(vector<AlphaVector>& alpha_vecs,vector<Belief>& BPS, int MAX_BP,vector<vector <double> >& RewardVecs, double gamma, int MAX_ITER, double err ,PomdpInterface* Pb){
    for (int i = 0; i< MAX_ITER; i++){
        vector<AlphaVector> temp_vecs = alpha_vecs;
        Improve(alpha_vecs,BPS,RewardVecs,gamma,MAX_ITER,Pb);
        Expand(BPS,MAX_BP,Pb);
        if (CheckConvergence(temp_vecs, alpha_vecs, err)){
            cerr << "Coverged at iteration:"<<i << endl;
            return;
        }
    }
}