#include "DynamicProgramSolver.hpp"



vector<int> DynamicProgramSolver::solve(Instance& toSolve) {
    // Initialisiere Vektor in n * W größe, mit Standartwert -1 (kein Gewinn)

    // Rows and Cols have 0 Included
    const int kRows = toSolve.n()+1;
    const int kCols = toSolve.getCapacity() +1;
    vector<vector<int>> matrix(kRows,vector<int>(kCols,0));

    for(int i = 1; i < kRows; i++)
    {
        for (int j = 1; j < kCols; j++)
        {
            // Objekt nicht nehmen
            int optimal = matrix[i-1][j];

            int current_weight = toSolve.getWeight(i-1);
            int current_val = toSolve.getValue(i-1);

            // Test ob Objektgewicht nicht zu groß ist, sowie ob Objekt neues Maximum ermöglicht für Gewicht genau W
            if(j - current_weight >= 0 && (matrix[i-1][j- current_weight] + current_val > optimal))
            {
                // Objekt mitzunehmen wäre Optimal
                optimal = matrix[i-1][j- current_weight ] + current_val;
            }
            matrix[i][j] = optimal;
        }
    }
    return vector<int> {};
}