#include "DynamicProgramSolver.hpp"
// wir gehen die matrix rückwärts durch und gucken ob wir ein Objekt eingepackt haben oder niicht
Solution DynamicProgramSolver::find_path(Instance& toSolve,vector<vector<int>>& matrix)
{
    Solution path = Solution(toSolve);
    int y = toSolve.n();
    int x = toSolve.getCapacity();

    for(int i = toSolve.n()-1; i >= 0; i--)
    {
        // Objekt nicht eingepackt
        if( matrix[y][x] == matrix[y-1][x])
        {
            y = y-1;
            path.set(i,0);
        }else // Objekt eingepackt
        {
            path.set(i,1);
            y = y-1;
            x = x-toSolve.getWeight(i);
        }
    }

    return path;
}

Solution DynamicProgramSolver::solve(Instance& toSolve) {
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
    return find_path(toSolve,matrix);
}