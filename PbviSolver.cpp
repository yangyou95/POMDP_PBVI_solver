#include <iostream>
#include "Include/PbviPlanner.h"
#include "Include/Parser.h"



#include "time.h"
using namespace std;




int main(int argc, char* argv[]){

    clock_t start,end;
    start=clock();

    string filename;
    if (argc!=2){
        cout << "Argument Error!" << endl;
        return -1;
    }else{
        filename = argv[1];
    }

    PomdpInterface *Pb = new ParsedPOMDP(filename);
    PbviPlanner pbvi_planner(0.95,50,200,50,Pb);

    cout << " ----- Initial Value Function -----" << endl;
    for (int i = 0; i < pbvi_planner.GetValueFunction().size(); i++)
    {
        pbvi_planner.GetValueFunction()[i].Print();
    }

    pbvi_planner.Plan();

    cout << " ----- Result Value Function -----" << endl;
    cout << " ----- "<<pbvi_planner.GetValueFunction().size()<<" alpha vectors in Res  -----" << endl;
    for (int i = 0; i < pbvi_planner.GetValueFunction().size(); i++)
    {
        pbvi_planner.GetValueFunction()[i].Print();
    }
    
    end=clock();
    cout <<" ------ End ------ "<< endl;
    cout<<"运行时间"<<(double)(end-start)/CLOCKS_PER_SEC<< "s" <<endl;
    return 0;

}



