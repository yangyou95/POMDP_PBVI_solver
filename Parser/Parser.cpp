#include "../Include/Parser.h"


ParsedPOMDP::ParsedPOMDP(const string filename)
{
    ifstream infile;
    infile.open(filename);
    if (!infile.is_open())
		cout << "open file failure" << endl;
        
    string temp;


	bool ReadStart = false; // end at here
    // First Get discount and all the state, action and observation space
    while(getline(infile, temp) && !ReadStart)
	{   
        istringstream is(temp);
        string s;
        int temp_num = 0;
		bool ReadDiscount = false;
		bool ReadStates = false;
		bool ReadActions = false;
		bool ReadObservations = false;
        while(is>>s)
        {
			if (s == "discount:")
			{
				ReadDiscount = true;
			}else if (s == "states:")
			{
				ReadStates = true;
			}else if (s == "actions:")
			{
				ReadActions = true;
			}else if (s == "observations:")
			{
				ReadObservations = true;
			}else if (s == "start:")
			{
				ReadStart = true;
			}
			
            // Get discount factor
            if (ReadDiscount && temp_num == 1)
            {
                this->discount = stod(s);
            }
            // Get all the States
            if (ReadStates && temp_num >0)
            {
                this->States.push_back(s);
            }
            // Get all actions
            if (ReadActions && temp_num >0)
            {
                this->Actions.push_back(s);
            }
            // Get all observations
            if (ReadObservations && temp_num >0)
            {
                this->Observations.push_back(s);
            }
            // Get intial belief
            if (ReadStart && temp_num >0)
            {
                b0.push_back(stod(s));
            }      
            temp_num +=1;

        }

	}
    infile.close();


    vector< vector< vector<double> > > T(Actions.size(), vector<vector<double> >(States.size(), vector<double>(States.size()) ));
    // double T[actions.size()][States.size()][States.size()];
    vector< vector< vector<double> > > O(Actions.size(), vector<vector<double> >(States.size(), vector<double>(Observations.size()) ));
    vector< vector<double> > R(Actions.size(), vector<double>(States.size()));
    infile.open(filename);
    // Get T,O and R
    while (getline(infile, temp))
    {
        // cout << temp << endl;
        istringstream is(temp);
        string s;
        int temp_num = 0;
        bool buildTrans = false;
        bool buildObs = false;
        bool buildReward = false;
        int aI, sI, oI, snewI = 0;
        double pb = 0;
        while(is>>s){
             // Get Transition Function
            if (s == "T:"){
                buildTrans = true;
            }else if (s == "O:")
            {
                buildObs = true;
            }else if (s == "R:")
            {
                buildReward = true;
            }
            
            


            if (temp_num == 1)
            {
                if (buildTrans || buildObs || buildReward){
                    aI = stoi(s);
                }
            }else if (temp_num == 3)
            {
                if (buildTrans || buildObs || buildReward){
                    sI = stoi(s);
                }
            }else if (temp_num == 5)
            {
                if (buildTrans){
                    snewI = stoi(s);
                }
                if (buildObs){
                    oI = stoi(s);
                }
            }else if (temp_num == 6)
            {
                    
                // build T now
                if (buildTrans){
                    pb = stod(s);
                    T[aI][sI][snewI] = pb;
                }
                if (buildObs){
                    pb = stod(s);
                    O[aI][sI][oI] = pb;
                }
            }else if (temp_num == 8)
            {
                if(buildReward){
                    pb = stod(s);
                    R[aI][sI] = pb;
                }
            }
                
            
            temp_num +=1;
        }
    }
    


	infile.close();


    this->TransFuncVecs = T;
    this->ObsFuncVecs = O;
    this->RewardFuncVecs = R;
    this->S_size = this->States.size();
    this->Obs_size = this->Observations.size();
    this->A_size = this->Actions.size();

}

double ParsedPOMDP::GetDiscount(){
    return this->discount;
};
int ParsedPOMDP::GetSizeOfS(){return this->S_size;};
int ParsedPOMDP::GetSizeOfA(){return this->A_size;};
int ParsedPOMDP::GetSizeOfObs(){return this->Obs_size;};
std::vector<double> ParsedPOMDP::GetInitBelief(){return this->b0;};
double ParsedPOMDP::TransFunc(int sI, int aI, int s_newI){
    return this->TransFuncVecs[aI][sI][s_newI];
};
double ParsedPOMDP::ObsFunc(int oI, int s_newI, int aI){
    return this->ObsFuncVecs[aI][s_newI][oI];
};
double ParsedPOMDP::Reward(int sI, int aI){
    return this->RewardFuncVecs[aI][sI];
};




ParsedPOMDP::~ParsedPOMDP()
{
}


