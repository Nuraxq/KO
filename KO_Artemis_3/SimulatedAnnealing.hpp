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


/**
 * Sucht eine Loesung des Binaeren Rucksackproblems mithilfe von Simulated Annealing
 * Generiert dafuer zufaellige Loesungen
 * Es koennen sowohl die Zeit als auch die Iterationsanzahl als Abbruchkriterium dienen.
 */
class SimulatedAnnealing {
public:
    /**
    *  Sucht eine moeglichst gute Loesung fuer das Binare Rucksackproblem
    * @param toSolve Instanz die geloest werden muss
    * @param timelimit Zeitlimit fuers berechnen
    * @param iterationlimit Iterationslimit
    * @param starttemperature Starttemperatur
    * @param factor Startfaktor
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

/**
 * Gibt einen zufaelligen Int aus im Intervall 0-x (inkl x)
 * @param x obere Intervallsgrenze
 * @return die generierte Zufallszahl
 */
int randomInt(int x);

/**
 * Gibt eine zufaellige Zahl im Intervall 0-1 aus
 * @return die generierte Zufallszahl
 */
double random01();
