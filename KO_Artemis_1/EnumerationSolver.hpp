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
public:


    // Todo: Funktion schneller machen, maybe call by reference anstatt Solution objekt zu Kopieren
    static void solve_helper(Solution loesung, const Instance& instanz, int depth);
    static vector<int> count_solution();

    static vector<int> solve(Instance& toSolve);
};