#include "EnumerationSolver.hpp"


vector<int> EnumerationSolver::solve(Instance& toSolve){
    Solution loesung = Solution(toSolve);
    backtrack(loesung,0,toSolve.n());
    return vector<int> {amountFeasible_,amountOptimal_,optimalValue_};
}

void EnumerationSolver::backtrack( Solution &loesung,int depth,int max) {
    if (depth == max) {
        if(loesung.isFeasible()) {
            if(loesung.getValue() == optimalValue_) {
                amountOptimal_++;
            }
            if(loesung.getValue() > optimalValue_) {
                optimalValue_ = loesung.getValue();
                amountOptimal_ = 1;
            }
            amountFeasible_++;
        }
    }
    else {
        loesung.set(depth,0);
        backtrack(loesung,depth+1,max);
        loesung.set(depth,1);
        backtrack(loesung,depth+1,max);
    }
}
int EnumerationSolver::amountFeasible_ = 0;
int EnumerationSolver::amountOptimal_ = 0;
int EnumerationSolver::optimalValue_ = 0;
