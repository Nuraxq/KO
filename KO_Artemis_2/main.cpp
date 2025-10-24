#include <iostream>
#include <vector>
#include <string>
#include <chrono>

#include "Instance.hpp"
#include "Reader.hpp"
#include "parameter_reader.hpp"
#include "DynamicProgramSolver.hpp"

using namespace std;

int main(int argc, char** argv) {

    vector<string> input_vector = input_to_vector(argc, argv);

    if(input_vector.size() < 3) {
        Reader::printUsageAndExit();
    }

    bool measureRuntime = (input_vector[1] == "t");

    // input via file
    if (input_vector[0] == "dat") {
        // Read insance from file, exit if error
        Instance instance = Reader::readInstanceFromFile(input_vector[2]);

        // Measure time and/or solve
        chrono::time_point<std::chrono::high_resolution_clock> start;
        chrono::time_point<std::chrono::high_resolution_clock> end;
        if(measureRuntime)
            start = chrono::high_resolution_clock::now();
        Solution result = DynamicProgramSolver::solve(instance);
        if(measureRuntime)
            end = chrono::high_resolution_clock::now();


        // extract instancename as only the substring after the last slash
        string instancename = input_vector[2];
        size_t pos = instancename.find_last_of('/');
        if (pos != std::string::npos)
            instancename = instancename.substr(pos + 1);

        // Print solution
        chrono::duration<double> duration; // runtime in seconds
        if (measureRuntime) {
            duration = end - start;
            cout << "Benoetigte Laufzeit fuers Loesen von " << instancename << ": " << duration.count() << " Sekunden\n";
        }
        cout << instancename << ": Optimaler Zielfunktionswert: " << result.getValue() << "\n";
	    cout << "Loesungsvektor: \n";
        for (int i = 0; i < instance.getNumberOfItems(); ++i) {
            cout << result.get(i) << " ";
        }
	    cout << "\n";

    }

    // input via command line arguments
    else if(input_vector[0] == "param") {
        // Read insance from command line args, exit if error
        Instance instance = Reader::readInstanceFromArgs(input_vector);

        // Solve the instance
        Solution result = DynamicProgramSolver::solve(instance);

        // Print solution
        cout << "Optimaler Zielfunktionswert: " << result.getValue() << "\n";
	    cout << "Loesungsvektor: \n";
        for (int i = 0; i < instance.getNumberOfItems(); ++i) {
            cout << result.get(i) << " ";
        }
	    cout << "\n";
    }

    // wrong input
    else {
        Reader::printUsageAndExit();
    }

}