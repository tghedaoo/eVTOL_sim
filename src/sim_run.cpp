/* 
eVTOL Simulator.
----------------
Spawns 20 aircrafts, runs simulation for 3 minutes, produces simulations results.
The number of aircrafts are generated randomly.
The aircraft parameters are given and therefore hardcoded for our purposes.
The aircraft uses a state machine to track its states and timings. 
*/

#include "..\includes\state_machine.h"

#include <iostream>

int main(int argc, char **argv)
{
  std::cout << " **** eVTOL SIMULATION **** " << std::endl;
  std::cout << "eVTOL sim: Initializing ..." << std::endl;
  // Random number generator
  // Get 20 vehicles (of 5 types in random numbers)
  // Get 3 charger mutexes.
  // init all at once? 20 threads.
  std::cout << "eVTOL sim: Initialization COMPLETE." << std::endl;
  std::cout << "eVTOL sim: Simualtion Beginning ... " << std::endl;
  // Start a 3 minute timer.
  // Stop sim
  std::cout << "eVTOL sim: Simulation COMPLETE." << std::endl;
  std::cout << "eVTOL sim: Calculations Beginning ... " << std::endl;
  // Get all calculations.
  // populate xls or print results?
  // Destructor call  
  std::cout << "eVTOL sim: Calculations COMPLETE." << std::endl;
  return 0;
}