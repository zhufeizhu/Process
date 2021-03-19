#include "Simulation.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]){
	if(argc < 2){
		std::cout << "Usage: " << argv[0] << " <file name>" << endl;
	} else {
		std::cout << "Simulation begins...\n";
		Simulation* sim = new Simulation();
		sim->runSimulation(argv[1]);
		std::cout << "\n...All Processes complete.  Final Summary:\n\n";
		sim->summary();
		std::cout << "\nEnd of processing.\n";
		return 0;
	}
}// main
