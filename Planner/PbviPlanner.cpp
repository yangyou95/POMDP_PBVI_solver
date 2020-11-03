#include "../Include/PbviPlanner.h"

vector<AlphaVector> PbviPlanner::BuildInitalV(double gamma, PomdpInterface *Pb){
    double R_min = __DBL_MAX__;
    vector<AlphaVector> V;
    //Fixed default action index 0
    int aI = 0;
    vector<double> alpha_values(Pb->GetSizeOfS());
    for (int sI = 0; sI < Pb->GetSizeOfS(); sI++){
        for (int aI = 0; aI < Pb->GetSizeOfA(); aI++){
            if (Pb->Reward(sI,aI) < R_min){
                R_min = Pb->Reward(sI,aI);
            }
        }
        alpha_values[sI] = R_min/(1-gamma);
    }
    AlphaVector alpha_min(alpha_values, aI);
    V.push_back(alpha_min);
    return V;
}


Belief PbviPlanner::UpdateForward(unsigned int oI, unsigned int aI, Belief& b, PomdpInterface *Pb){
    vector<double> b_aI_value(Pb->GetSizeOfS()); 
    double pr_oba = Pr_oba(oI,b,aI,Pb);
    if (pr_oba > 0){
        for (unsigned int s_newI = 0; s_newI < Pb->GetSizeOfS(); s_newI++){
            double p_s_newI = 0;
            for (unsigned int sI = 0; sI < Pb->GetSizeOfS(); sI++){
                p_s_newI += Pb->TransFunc(sI,aI,s_newI)*b[sI];
            }
            double pr_snew_ao = (Pb->ObsFunc(oI,s_newI,aI)*p_s_newI)/pr_oba;
            b_aI_value[s_newI] = pr_snew_ao;
        }
        
    }
    Belief b_ao(b_aI_value);

    return b_ao;

};


// This may be bad, in paper, the inital belief point set is expanded using the initial belief point
vector<Belief>& PbviPlanner::SampleBeliefPoints(int BS_size, int S_size, vector<Belief>& BPS){
    
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


double PbviPlanner::Pr_oba(int oI, Belief& b, int aI, PomdpInterface *Pb)
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
vector<Belief> PbviPlanner::successors_b(Belief& b, PomdpInterface* Pb){
    vector<Belief> succ_b;
    for (int aI = 0; aI<Pb->GetSizeOfA();aI++){
        for (int oI = 0; oI<Pb->GetSizeOfObs();oI++){
            Belief b_ao = UpdateForward(oI,aI,b,Pb);
            succ_b.push_back(b_ao);
        }
    }
    return succ_b;
}


vector<Belief> PbviPlanner::Expand(vector<Belief>& BS, int MAX_BP, PomdpInterface* Pb){
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
AlphaVector PbviPlanner::UpdateAlphaAO(unsigned int aI, AlphaVector alpha, unsigned oI, PomdpInterface* Pb){

    vector<double> temp(alpha.GetSize());
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

AlphaVector PbviPlanner::UpdateAlphaAB(unsigned int aI, vector< vector<vector<AlphaVector>>>& AlphaAOVecs, Belief& b,  vector<vector <double> >& RewardVecs, double gamma, PomdpInterface* Pb){
    // reward vector for an action a
    vector<double> rewards = RewardVecs[aI];
    vector<double> values(Pb->GetSizeOfS());
    // Find different alpha vecs (diff aI, same oI), which can have max b*alpha_a_o
    for (unsigned int oI = 0; oI <Pb->GetSizeOfObs(); oI++){
        // Update alpha vec according to oI and find argmax b*alpha_a_o
        double max_res = -__DBL_MAX__;
        int selected_I = 0;
        // For each alpha vector (alpha_a_o)， select a best alpha idx
        for (unsigned int i= 0; i < AlphaAOVecs[aI][oI].size(); i++){
            if (dot(b,AlphaAOVecs[aI][oI][i]) > max_res){
                max_res = dot(b,AlphaAOVecs[aI][oI][i]);
                selected_I = i;
            } 
        }
        
        // Sum of argmax b*alpha_a_o
        for (unsigned int sI = 0;sI<Pb->GetSizeOfS(); sI++){
            values[sI] += AlphaAOVecs[aI][oI][selected_I][sI];
        } 
    }
    for (unsigned int sI = 0;sI<Pb->GetSizeOfS(); sI++){
        values[sI] = rewards[sI] + gamma*values[sI];
    } 
    AlphaVector alpha_a_b(values,aI);
    return alpha_a_b;

}


// Checked
vector<vector <double> > PbviPlanner::BuildRewardVectors(PomdpInterface* Pb){
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
void PbviPlanner::PrintRewardVecs(vector<vector <double> > & RVecs, PomdpInterface* Pb){
    for (unsigned int aI= 0; aI < Pb->GetSizeOfA(); aI++){
        for (unsigned int sI = 0; sI < Pb->GetSizeOfS(); sI++){
            cout <<"aI: "<<aI << ", sI:"<<sI<<", Reward:"<<RVecs[aI][sI]<<endl;
        }
    }
}

// Compute all the alpha_a_o values and store them to use in different belief point
vector< vector<vector<AlphaVector>>> PbviPlanner::ComputeAllAlphaAOValues(vector<AlphaVector>& alpha_vecs, PomdpInterface* Pb){
    vector< vector<vector<AlphaVector>>> AlphaAOVecs(Pb->GetSizeOfA(),vector<vector<AlphaVector>>(Pb->GetSizeOfObs(),vector<AlphaVector>(alpha_vecs.size())));
    // For all the action index in alpha_a_b
    for (unsigned int aI = 0; aI<Pb->GetSizeOfA();aI++){
        // For all the alpha vector 
        for(unsigned int alpha_idx = 0; alpha_idx<alpha_vecs.size(); alpha_idx++){
            // For all the observation
            for (unsigned int oI = 0; oI<Pb->GetSizeOfObs();oI++){
                AlphaAOVecs[aI][oI][alpha_idx] = UpdateAlphaAO(aI,alpha_vecs[alpha_idx],oI,Pb);
            }
        }
    }
    return AlphaAOVecs;
}


AlphaVector PbviPlanner::backup(vector<AlphaVector>& alpha_vecs, Belief& b,vector< vector<vector<AlphaVector>>>& AlphaAOVecs, vector<vector <double> >& RewardVecs, double gamma, PomdpInterface* Pb){
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

void PbviPlanner::Improve(vector<AlphaVector>& alpha_vecs,vector<Belief>& BPS,vector<vector <double> >& RewardVecs, double gamma, int MAX_ITER_IMP ,PomdpInterface* Pb){
    double err = __DBL_MIN__;
    vector<AlphaVector> temp_vecs = alpha_vecs;
    alpha_vecs.clear();
    for (int i = 0; i < MAX_ITER_IMP; i++)
    {

        // Compute a vector to store alpha_a_o values
        vector< vector<vector<AlphaVector>>> AlphaAOVecs = ComputeAllAlphaAOValues(temp_vecs,Pb);
        for (int bI = 0; bI < BPS.size(); bI++){
            AlphaVector alpha = backup(temp_vecs,BPS[bI],AlphaAOVecs,RewardVecs,gamma,Pb);
            if (!CheckAlphaExist(alpha_vecs, alpha)){
                alpha_vecs.push_back(alpha); 
            }
        }

        // Check converged or not 
        if (CheckConvergence(temp_vecs, alpha_vecs, err)){
            cerr << "Coverged in improvement at iteration:"<<i << endl;
            return;
        }else
        {
            temp_vecs = alpha_vecs;
        }
        
    }

};

// Main Solving Process 
void PbviPlanner::Plan(vector<AlphaVector>& alpha_vecs,vector<Belief>& BPS, int MAX_BP,vector<vector <double> >& RewardVecs, double gamma, int MAX_ITER_G, int MAX_ITER_I, double err ,PomdpInterface* Pb){
    for (int i = 0; i< MAX_ITER_G; i++){
        vector<AlphaVector> temp_vecs = alpha_vecs;
        Improve(alpha_vecs,BPS,RewardVecs,gamma,MAX_ITER_I,Pb);
        Expand(BPS,MAX_BP,Pb);
        if (CheckConvergence(temp_vecs, alpha_vecs, err)){
            cerr << "Coverged at iteration:"<<i << endl;
            return;
        }
    }
}

void PbviPlanner::Plan(){
    Plan(this->AlphaVecs,this->BS,this->MAX_BP,this->RewardVecs,this->gamma,this->MAX_ITER_GLOBAL, this->MAX_ITER_IMP, this->err, this->Pb);
};


vector<AlphaVector> PbviPlanner::GetValueFunction(){
    return this->AlphaVecs;
}

PbviPlanner::PbviPlanner(double gamma, int MAX_BP, int MAX_ITER_GLOBAL, int MAX_ITER_IMP,PomdpInterface *Pb){
    this->gamma = gamma;
    this->MAX_BP = MAX_BP;
    this->MAX_ITER_GLOBAL = MAX_ITER_GLOBAL;
    this->MAX_ITER_IMP = MAX_ITER_IMP;
    this->Pb = Pb;
    this->AlphaVecs = BuildInitalV(gamma, this->Pb);
    this->RewardVecs = BuildRewardVectors(this->Pb);
    this->BS = {this->Pb->GetInitBelief()};
};
PbviPlanner:: ~PbviPlanner(){};

