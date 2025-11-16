#include "SimulatedAnnealing.hpp"

void SimulatedAnnealing::solve(Instance& toSolve, int timelimit, int iterationlimit, double starttemperature, double factor) {

    const int IterationLimit = 10* toSolve.n();
    double temperatur = starttemperature;
    Solution loesung(toSolve);
    startSolution1(toSolve,loesung);
    printStart(loesung);
    int max_value = loesung.getValue();
    int iteration = 0;




}

// Wir gehen einmal durch und nehmen das Objekt wenn es noch reinpasst
void SimulatedAnnealing::startSolution1(Instance& toSolve, Solution& solution) {
    for(int i = 0; i < toSolve.n(); i++) {
        if(toSolve.getWeight(i) <= (toSolve.getCapacity() - solution.getWeight())) {
            solution.set(i,1);
        }
    }
}


// Wir nehmen nach Greedy Wahl die Objekte
void SimulatedAnnealing::startSolution2(Instance& toSolve,Solution& solution) {
    for(int i = 0; i < toSolve.n(); i++) {
        double highest = 0.0;
        int index_highest = -1;
        for(int j = 0; j < toSolve.n(); j++) {
            // wir berechnen den Value pro Gewicht
            double value = static_cast<float>(toSolve.getValue(j)) / static_cast<float>(toSolve.getWeight(j));

            // Wir nehmen ein Objekt wenn es
            // 1. Noch nicht drin ist, 2. Größeren Val/Gewicht hat. 3.den Rucksack nicht überfüllt
            if(solution.get(j) == false && value  > highest && (toSolve.getCapacity() - solution.getWeight() >=  toSolve.getValue(j))) {
                highest = value;
                index_highest = j;
            }
        }
        // Wenn der index -1 ist kann nichts mehr gewählt werden, wir sind fertig
        if(index_highest == -1){return;}
        solution.set(index_highest,1);
    }
}

void SimulatedAnnealing::printStart(Solution& solution) {
    cout << "Startloesung mit Zielfunktionswert " << solution.getValue() << ":\n (";
    for(int i = 0; i < solution.getInstance().n() -1; i++) {
        cout << solution.get(i) << " ";
    }
    cout << solution.get(solution.getInstance().n() -1);
    cout << ")\n";
}

void SimulatedAnnealing::printBest(Solution& solution) {
    cout << "Startloesung mit Zielfunktionswert " << solution.getValue() << ":\n (";
    for(int i = 0; i < solution.getInstance().n() -1; i++) {
        cout << solution.get(i) << " ";
    }
    cout << solution.get(solution.getInstance().n() -1);
    cout << ")\n";
}
