#include <iostream>
#include "PbviPlanner.h"
#include "Tiger.h"
#include "time.h"
using namespace std;



int main(){
    clock_t start,end;
    start=clock();

    PomdpInterface *Pb = new TigerPb();
    PbviPlanner pbvi_planner(0.95,100,100,50,Pb);

    cout << " ----- Initial Value Function -----" << endl;
    for (int i = 0; i < pbvi_planner.GetValueFunction().size(); i++)
    {
        pbvi_planner.GetValueFunction()[i].Print();
    }

    pbvi_planner.Plan();

    cout << " ----- Result Value Function -----" << endl;
    for (int i = 0; i < pbvi_planner.GetValueFunction().size(); i++)
    {
        pbvi_planner.GetValueFunction()[i].Print();
    }
    
    end=clock();
    cout <<" ------ End ----- "<< endl;
    cout<<"运行时间"<<(double)(end-start)/CLOCKS_PER_SEC<< "s" <<endl;
    return 0;

}

