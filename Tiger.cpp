#include "Tiger.h"

double TigerPb::TransFunc(int sI, int aI, int s_newI){
    if (sI< this->Obs_size){
        if (s_newI < this->S_size){
             // Open Left action or Right action
            if(aI == 0 || aI == 1) {
                return 0.5;
            } else if (aI == 2) {
                if (s_newI==0 && sI == 0){
                    return 1;
                } else if(s_newI==1 && sI == 1)
                {
                    return 1;
                } else
                {
                    return 0;
                }
            } else {
                throw "Wrong input action index for TransFunc!";
            }
        }else
        {
            throw "Wrong input state_new index for TranFunc!";
        }
    }else{
        throw "Wrong input state index for TransFunc!";
    }

};

double TigerPb::ObsFunc(int oI, int s_newI, int aI){
    if (oI< this->Obs_size){
        if (s_newI < this->S_size){
            // Open Left action or Right action
            if(aI == 0 || aI == 1) {
                return 0.5;
            }else if (aI == 2) // Listen
            {
                if (s_newI==0 && oI == 0){
                    return 0.85;
                } else if(s_newI==1 && oI == 1)
                {
                    return 0.85;
                } else
                {
                    return 0.15;
                }
            }else {
                throw "Wrong input action index for ObsFunc!";
            }
        }else
        {
            throw "Wrong input state index for ObsFunc!";
        }
    }else{
        throw "Wrong input observation index for ObsFunc!";
    }
};


double TigerPb::Reward(int sI, int aI){
    if (sI < this->S_size){
        // listen 
        if (aI == 2){
            return -1;
        }else if (aI == 0 || aI == 1)
        {
            if (sI==0 && aI == 0){
                return -100;
            } else if(sI==1 && aI == 1)
            {
                return -100;
            } else
            {
                return 10;
            }
        }else {
            throw "Wrong input action index for RewardFunc!";
        }
    }else
    {
        throw "Wrong input state index for RewardFunc!";
    }
    


    
};

TigerPb::TigerPb(/* args */)
{
}

TigerPb::~TigerPb()
{
}