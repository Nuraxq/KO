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
    static int count_max;
    static int max_value;
    static int count_feas;
public:


    // Todo: Funktion schneller machen, maybe call by reference anstatt Solution objekt zu Kopieren
    static void solve_helper(Solution loesung, const Instance& instanz, int depth);
    static vector<int> count_solution();
    static void fast_helper(Solution& sol, int dep,int max);

    static vector<int> solve(Instance& toSolve);
};