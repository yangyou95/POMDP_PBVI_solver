POMDP PBVI Solver
====

POMDP PBVI Solver 是C++实现的 **Point Based Value Iteration** 算法[1].  PBVI是一种**offline**算法，其求解的是决策Horizon趋近于Infinite情况下，收敛得到的Value Function，以**Alpha-Vectors**的形式输出。PBVI的中文讲解 https://zhuanlan.zhihu.com/p/272867881 。

POMDP PBVI Solver is an C++ implementation of the Point Based Value Iteration algorithm [1]. PBVI is an offline algorithm. It aims to resolve the problem at infinite horizons. The result is the converged value function which is represented by the alpha-vectors.

## Installation

Tested systems:

* Linux
* Mac OS X

Dependencies:

* cmake >= 2.8

C++ 11 is required

Once you have all required dependencies, you can simply execute the following commands from the project's main folder:

```
cmake ./
make
```



The executable file is will be generated called "PBVI", to run the program, just type:
```
./PBVI your_file_path
```


A cleaning shell is written for cleaning the CMake compiling generated files, just run：

```
sh cleanCMAKE.sh
```

## Modify the planning parameters
You can change the global iteration max number, improving iteration max number, err and max belief points number setting in the solver program. This wil be soon changed to give parameters when execute the program.

## Current Parser
Right now the parser is able to parser .pomdp(.POMDP) files. There is a detailed explaination for this format http://www.pomdp.org/code/pomdp-file-spec.html .

You can also create POMDPs in Cpp codes, in the Problem folder, an example TigerProblem cpp file is provided.

### Create New Problems in Cpp

To create a new problem in C++, you need to extend the Model interface (Include/PomdpInterface.h). The following functions are needed to be customized:

* int GetSizeOfS();
* int GetSizeOfA();
* int GetSizeOfObs();
* vector<double> GetInitBelief();
* double TransFunc(int sI, int aI, int s_newI);
* double ObsFunc(int oI, int s_newI, int aI);
* double Reward(int sI, int aI).

## Future Improvement
* Parsing PGMX files
* Optimizing performance by multi-threads

## Refs

> [1]. Joelle Pineau, Geoff Gordon, and Sebastian Thrun. 2003. Point-based value iteration: an anytime algorithm for POMDPs. In <i>Proceedings of the 18th international joint conference on Artificial intelligence</i> (<i>IJCAI'03</i>). Morgan Kaufmann Publishers Inc., San Francisco, CA, USA, 1025–1030.

