#pragma once

#include "Instance.hpp"
#include "Solution.hpp"

#include <vector>
#include <iostream>

using namespace std;

/**
 * Klasse die das binäre Rucksackproblem mittels Dynamischer Programmierung löst
 */
class DynamicProgramSolver {

public:
    /**
     * Löst das binäre Rucksackproblem exakt mittels Dynamischer Programmierung
     * @param toSolve Instanz die zu lösen ist
     * @return ein Solution Objekt mit einer Optimalen Lösung
     */
    static Solution solve(Instance& toSolve);


    /**
     * Findet welche Items bei der Optimalen Lösung des Rucksackproblems gewählt wurden
     * @param toSolve Instanz die gelöst werden muss
     * @param matrix Bereits ausgefüllte Matrix [i][w] mit i = Objekte und w = Gewicht
     * @return Lösungsobjekt mit Optimaler Lösung 
     */
    static Solution find_path(Instance& toSolve,vector<vector<int>>& matrix);
};