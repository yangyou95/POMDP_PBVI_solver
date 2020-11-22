
// /* Only include this header file once. */
// #ifndef _NODE_H_
// #define _NODE_H_ 1

// /* the include directives */
// #include <iostream>
// #include "../Include/Belief.h"
// #include "../Include/AlphaVector.h"

// #define WHEREAMI std::cerr << __FILE__ << ":" << __func__ << ":" << __LINE__ << std::endl;
// #define ARGH(x) { WHEREAMI; std::cerr << "MSG: " << x << std::endl; exit(1); }

// using namespace std;

// class node {

//   size_t alphav;
//   size_t action;
//   JointBeliefSparse belief;
//   vector<size_t> transitions; // vector/array of alphavs (ordered by associated observation number), -1 if impossible observation
//   ValueFunctionPOMDPDiscrete alpha_vecs;

//  public:
//   node(size_t _alphav, size_t _action, ValueFunctionPOMDPDiscrete _alpha_vecs);

//   void addTransition(size_t z, size_t alphav);

//   void addTransitions(vector<size_t> _transitions);

//   size_t getAction();

//   size_t getAlphav();

//   vector<size_t> getTransitions();

//   void print();
// };

// #endif
