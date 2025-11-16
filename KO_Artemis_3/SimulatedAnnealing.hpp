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
 * Idee: 2 Funktionen um Startlösung zu generieren -> z.b.
 * Greedy und einfach Random oder einf die ersten Elemente nehmen bis nix geht
 *  Dann: zufällige nachbarschaftslösung nehmen und erzeugen, indem 1 Bit geflippt wird.
 *
 */



// TODO: comment this class with Doxygen (and delete this comment)
class SimulatedAnnealing {

    public:
        static void solve(Instance& toSolve, int timelimit, int iterationlimit, double starttemperature, double factor);
        static void startSolution1(Instance& toSolve,Solution& solution);
        static void startSolution2(Instance& toSokve,Solution& solution);
        static void printStart(Solution& loesung);
        static void printBest(Solution& loesung);
        static void generateRandomSol(Instance& toSolve,Solution& solution);

};