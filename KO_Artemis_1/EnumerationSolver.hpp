#pragma once

#include "Instance.hpp"
#include "Solution.hpp"

#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

// TODO: comment this class with Doxygen (and delete this comment)
class EnumerationSolver {
    static std::vector<Solution> solutions_;
    static int numberOptimal_;
    static int optimalValue_;
    static int numberFeasible_;
public:
    static void backtrack(Solution& sol, int dep,int max);

    static vector<int> solve(Instance& toSolve);
};