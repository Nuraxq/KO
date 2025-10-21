#pragma once

#include "Instance.hpp"
#include "Solution.hpp"

#include <vector>
#include <cmath>


using namespace std;

/**
 *
 * Solves the Knapsack Problem by Enumeration every Solution with Backtracking
 *
 */
class EnumerationSolver {
private:

    /// Number of Optimal Solutions found
    static int amountOptimal_;


    /// The Value of the Optimal Solution(s)
    static int optimalValue_;

    /// Number of Feasible Solutions found
    static int amountFeasible_;

public:
    /**
     * Backtrack through every possible solution
     *
     * @param sol The solution object
     * @param depth The current depth of the recursive call chain
     * @param max The depth limit at which a Solution is Found (the number of items in the instance)
     */
    static void backtrack(Solution& sol, int depth,int max);

    /**
     * Solves the given Instance using the backtrack function
     *
     * @param toSolve The instance to solve
     * @return Solution of the instance:  { amount Feasible, amount Optimal, Optimal Value }
     */
    static vector<int> solve(Instance& toSolve);
};