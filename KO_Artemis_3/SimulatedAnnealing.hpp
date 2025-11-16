#pragma once

#include "Instance.hpp"
#include "Solution.hpp"

#include <vector>
#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;

/*
 * Idee: 2 Funktionen um Startloesung zu generieren -> z.b.
 * Greedy und einfach Random oder einf die ersten Elemente nehmen bis nix geht
 *  Dann: zufaellige Nachbarschaftsloesung nehmen und erzeugen, indem 1 Bit geflippt wird.
 *
 */


// TODO: comment this class with Doxygen (and delete this comment)
class SimulatedAnnealing {
public:
    /**
    *
    * @param toSolve
    * @param timelimit
    * @param iterationlimit
    * @param starttemperature
    * @param factor
    */
    static void solve(Instance &toSolve, int timelimit, int iterationlimit, double starttemperature, double factor);

    /**
    * Erstellt eine Startloesung mithilfe eines Greedy Verfahrens
    * @param toSolve Instanz die geloest wird
    * @param solution Objekt in der die Loesung gespeichert wird
    */
    static void startSolution(Instance &toSolve, Solution &solution);

    /**
    * Gibt Loesung aus mit "Startloesung" Ausgabe
    * @param loesung Loesungsinstanz die ausgegeben wird
    */
    static void printStart(Solution &loesung);

    /**
    * Gibt Loesug aus mit "Beste Loesung" Ausgabe
    * @param loesung Loesungsinstanz die ausgegeben wird
    */
    static void printBest(Solution &loesung);

    /**
     * Generiert eine zufaellige zulaessige Loesung aus der Nachbarschaft
     * der Loesung (Die Nachbarschaft ist durch einen Bitflip definiert)
     * @param toSolve Instanz des Problems
     * @param randomSol Loesung die Modifiziert wird
     */
    static void generateRandomSol(Instance &toSolve, Solution &randomSol);
};

int randomInt(int x);

double random01();
