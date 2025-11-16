#include "SimulatedAnnealing.hpp"

void SimulatedAnnealing::solve(Instance& toSolve, int timelimit, int iterationlimit, double starttemperature, double factor) {


    const int IterToCooling = 10* toSolve.n();
    double temperatur = starttemperature;
    int totalIteration = 0;
    int currentIteration = 0;

    // Startloesung
    Solution loesung(toSolve);
    startSolution1(toSolve,loesung);
    int maxValue = loesung.getValue();
    Solution optimalSolution = loesung;
    printStart(loesung);

    chrono::time_point<std::chrono::high_resolution_clock> start = chrono::high_resolution_clock::now();
    chrono::time_point<std::chrono::high_resolution_clock> current;
    bool stopCriteriaTrue = false;

    while(!stopCriteriaTrue) {
        Solution randomSol = loesung;
        generateRandomSol(toSolve,loesung,randomSol);

        int valCurrent = loesung.getValue();
        int valRandom = randomSol.getValue();

        double temperatureWorth = exp(-(valRandom-valCurrent)/temperatur);

        // Wir gucken ob die zufaellige Loesung besser ist oder ob sie zufaellig genommen werden soll
        if(valRandom > valCurrent || random01() < temperatureWorth ) {
            loesung = randomSol;
            if(valRandom > maxValue) {
                optimalSolution = loesung;
                maxValue = valRandom;
            }
        }
        currentIteration += 1;
        totalIteration += 1;

        // Wir kuehlen ab nach einer bestimmten Anzahl iterationen
        if(currentIteration == IterToCooling) {
            currentIteration = 0;
            temperatur = temperatur * factor;
        }

        // Wir vergleichen ob die Zeit in Sekunden schon abgelaufen ist.
        auto timediff = std::chrono::high_resolution_clock::now() - start;


        if((iterationlimit > 0 && totalIteration >= iterationlimit) ||
                                (timelimit > 0 &&  timediff > std::chrono::seconds(timelimit))){
            stopCriteriaTrue = true;
        }

    }
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
    cout << "beste gefundene Loesung mit Zielfunktionswert " << solution.getValue() << ":\n (";
    for(int i = 0; i < solution.getInstance().n() -1; i++) {
        cout << solution.get(i) << " ";
    }
    cout << solution.get(solution.getInstance().n() -1);
    cout << ")\n";
}


// Wir holen uns eine Zufallszahl und flippen das entsprechende Bit.
// Wenn das Bit von 0 auf 1 geflippt wird, wird erst geguckt ob die Loesung zulaessig ist.
void SimulatedAnnealing::generateRandomSol(Instance& toSolve,Solution& solution, Solution& randomSol) {
    int index = randomInt(toSolve.n()-1);

    if(randomSol.get(index) == 1) {
        randomSol.set(index,0);
    }
    else {
        if(randomSol.getWeight() + toSolve.getWeight(index) <= toSolve.getCapacity()) {
            randomSol.set(index,1);
        }
    }
}


// Zufällige Zahl generieren
int randomInt(int x) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, x);
    return dist(gen);
}

// Zufallszahl zwischen 0 und 1
double random01() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dist(0.0, 1.0);
    return dist(gen);
}