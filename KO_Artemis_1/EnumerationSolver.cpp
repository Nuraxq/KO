#include "EnumerationSolver.hpp"


vector<int> EnumerationSolver::solve(Instance& toSolve){
    Solution loesung = Solution(toSolve);
    backtrack(loesung,0,toSolve.n());
    return vector<int> {numberFeasible_,numberOptimal_,optimalValue_};
}

void EnumerationSolver::backtrack( Solution &loesung,int depth,int max) {
    if (depth == max) {
        if(loesung.isFeasible()) {
            if(loesung.getValue() == optimalValue_) {
                numberOptimal_++;
            }
            if(loesung.getValue() > optimalValue_) {
                optimalValue_ = loesung.getValue();
                numberOptimal_ = 1;
            }
            numberFeasible_++;
        }
    }
    else {
        loesung.set(depth,0);
        backtrack(loesung,depth+1,max);
        loesung.set(depth,1);
        backtrack(loesung,depth+1,max);
    }
}


/*
vector<int> EnumerationSolver::count_solution()
{
    vector<int> sol;
    sol.push_back(solutions_.size());
    int count = 0;
    int max = 0;
    if(solutions_.size() >0)
    {
        count = 1;
        max = solutions_[0].getValue();
        for(int i = 1; i < solutions_.size(); i++)
        {
            if(solutions_[i].getValue() > max)
            {
                count = 1;
                max = solutions_[i].getValue();
            }
            else if(solutions_[i].getValue() == max)
            {
                count++;
            }
        }
    }
    sol.push_back(count);
    sol.push_back(max);
    return sol;
}


void EnumerationSolver::solve_helper(Solution loesung, const Instance& instanz, int depth)
{
    {
        if(depth == instanz.getNumberOfItems())
        {
            if (loesung.isFeasible())
            {
                solutions_.push_back(loesung);
            }
        }
        else
        {
            Solution temp = loesung;
            loesung.set(depth,1);
            solve_helper(loesung,instanz,depth+1); // nehmen
            temp.set(depth,0);
            solve_helper(temp,instanz,depth+1); // nicht nehmen
        }
    }
}
*/
int EnumerationSolver::numberFeasible_ = 0;
int EnumerationSolver::numberOptimal_ = 0;
int EnumerationSolver::optimalValue_ = 0;
