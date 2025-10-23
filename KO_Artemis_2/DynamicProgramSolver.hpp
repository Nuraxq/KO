#pragma once

#include "Instance.hpp"
#include "Solution.hpp"

#include <vector>
#include <iostream>

using namespace std;

// TODO: comment this class with Doxygen (and delete this comment)
class DynamicProgramSolver {

public:
    static vector<int> solve(Instance& toSolve);
};