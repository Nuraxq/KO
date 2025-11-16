#include "SimulatedAnnealing.hpp"

// TODO: Code verschnellern, -> bei n = 5000 Arsch langsam
// TODO: Funktionalitäten kontrollieren (ist alles da?)
// TODO: Instanzen Testen und eingeben
// TODO: Kuehlugsweise ueberarbeiten (passt die Iterationenzahl und -> welche 2 Arten sind gewollt?)
// TODO: Testen + bei Artemis hochladen
// TODO: gucken ob bei Printbest -1 noetig



void SimulatedAnnealing::solve(Instance& toSolve, int timelimit, int iterationlimit, double starttemperature, double factor) {

    // iterationen bis gekuehlt wird
    const int IterToCooling = 10* toSolve.n();
    double temperatur = starttemperature;
    // Wir setzen currentIterationen nach dem Kuehlen zurueck
    int totalIteration = 0;
    int currentIteration = 0;

    // Startloesung
    Solution loesung(toSolve);


    // Auskommentiert lassen falls mit 0 Vektor gestartet werden soll
    //Funktion würde sonst mit Greedy Loesung starten

    //-----> startSolution(toSolve,loesung);

    // Wir speichern die beste gesehene Loesung
    int maxValue = loesung.getValue();
    Solution optimalSolution = loesung;

    printStart(loesung);

    chrono::time_point<std::chrono::high_resolution_clock> start = chrono::high_resolution_clock::now();
    bool stopCriteriaTrue = false;

    while(!stopCriteriaTrue) {
        // Wir generieren eine Random Loesung der Nachbarschaft
        Solution randomSol = loesung;
        generateRandomSol(toSolve,randomSol);

        int valCurrent = loesung.getValue();
        int valRandom = randomSol.getValue();

        double chance = exp(-(valRandom-valCurrent)/temperatur);

        // Wir gucken ob die zufaellige Loesung besser ist oder ob sie zufaellig genommen werden soll
        if(valRandom > valCurrent || random01() < chance ) {
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
        // wir gucken ob die Abbruchkriterien erfuellt sind
        if((iterationlimit > 0 && totalIteration >= iterationlimit) ||
                                (timelimit > 0 &&  timediff > std::chrono::seconds(timelimit))){
            stopCriteriaTrue = true;
        }
    }
    printBest(optimalSolution);
}



// Wir nehmen nach Greedy Wahl die Objekte
void SimulatedAnnealing::startSolution(Instance& toSolve,Solution& solution) {
    for(int i = 0; i < toSolve.n(); i++) {
        double highest = 0.0;
        int indexHighest = -1;
        for(int j = 0; j < toSolve.n(); j++) {
            // wir berechnen den Value pro Gewicht
            double value = static_cast<float>(toSolve.getValue(j)) / static_cast<float>(toSolve.getWeight(j));

            // Wir nehmen ein Objekt wenn es
            // 1. Noch nicht drin ist && 2. Größeren Val/Gewicht hat && 3.den Rucksack nicht überfüllt
            if(solution.get(j) == false && value  > highest && (toSolve.getCapacity() - solution.getWeight() >=  toSolve.getValue(j))) {
                highest = value;
                indexHighest = j;
            }
        }
        // Wenn der index -1 ist kann nichts mehr gewählt werden, wir sind fertig
        if(indexHighest == -1){return;}
        solution.set(indexHighest,1);
    }
}


// Startloesung ausgeben im angegebenen Format
void SimulatedAnnealing::printStart(Solution& solution) {
    cout << "Startloesung mit Zielfunktionswert " << solution.getValue() << ":\n (";
    for(int i = 0; i < solution.getInstance().n() -1; i++) {
        cout << solution.get(i) << " ";
    }
    cout << solution.get(solution.getInstance().n() -1);
    cout << ")\n";
}

// Beste Loesung ausgeben im angegebenen Format
void SimulatedAnnealing::printBest(Solution& solution) {
    cout << "beste gefundene Loesung mit Zielfunktionswert " << solution.getValue() << ":\n (";
    for(int i = 0; i < solution.getInstance().n()-1; i++) {
        cout << solution.get(i) << " ";
    }
    cout << solution.get(solution.getInstance().n() -1);
    cout << ")\n";
}


// Wir holen uns eine Zufallszahl und flippen das entsprechende Bit.
// Wenn das Bit von 0 auf 1 geflippt wird, wird erst geguckt ob die Loesung zulaessig ist.
void SimulatedAnnealing::generateRandomSol(Instance& toSolve, Solution& randomSol) {
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


// Zufaellige Zahl generieren
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