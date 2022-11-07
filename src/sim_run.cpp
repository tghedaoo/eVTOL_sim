/*
eVTOL Simulator.
----------------
Spawns 20 aircrafts, runs simulation for 3 minutes, produces simulations results.
The number of aircrafts are generated randomly.
The aircraft parameters are given and therefore hardcoded for our purposes.
The aircraft uses a state machine to track its states and timings.
*/

#include "../includes/state_machine.h"
#include "../includes/aircraft.h"

#include <iostream>
#include <vector>

int main()
{
  std::cout << " **** eVTOL SIMULATION **** " << std::endl;
  std::cout << "eVTOL sim: Initializing ..." << std::endl;
  
  // Aircraft paramters.
  // TODO: parse this from a config file using util class. 
  std::vector<eVTOL_sim::aircraft::AircraftParams> param_list;
  // Alpha Company
  param_list.push_back({120, 320, 36, 1600, 4, 25});
  // Beta Company    
  param_list.push_back({100, 100, 12, 1500, 5, 10});    
  // Charlie Company
  param_list.push_back({160, 220, 48, 2200, 3, 5});
  // Delta Company [time in minutes = 37.2 but rounded off]
  param_list.push_back({90, 120, 37, 800, 2, 22});
  // Echo Company
  param_list.push_back({30, 150, 18, 5800, 2, 61});

  // Random number generator
  
  // Get 20 vehicles (of 5 types in random numbers)
  eVTOL_sim::aircraft::Aircraft aircraft1;
  eVTOL_sim::state_machine::StateMachine state_machine1;

  // Get 3 charger mutexes.
  // init all at once? 20 threads.
  aircraft1.init_aircraft(param_list[0], eVTOL_sim::aircraft::AircraftType::Alpha, state_machine1);
  std::cout << "eVTOL sim: Initialization COMPLETE." << std::endl;
  
  // Begin Simulator.
  std::cout << "eVTOL sim: Simualtion Beginning ... " << std::endl;
  aircraft1.start_sim();

  std::this_thread::sleep_for (std::chrono::seconds(3));
  // Stop sim after 3 minutes.
  aircraft1.stop_sim();
  std::cout << "eVTOL sim: Simulation COMPLETE." << std::endl;
  
  // Get all calculations.
  std::cout << "eVTOL sim: Calculations Beginning ... " << std::endl;
  std::vector<eVTOL_sim::aircraft::SimRes> results;
  results.push_back(aircraft1.sim_results());
  std::cout << "eVTOL sim: Calculations COMPLETE." << std::endl;

  std::cout << "------------------" << std::endl;
  std::cout << "PER AIRCRAFT RESULTS" << std::endl;
  std::cout << "------------------" << std::endl;
  // TODO: populate a file (maybe .xls) with the results.
  for (uint8_t iter = 0; iter < results.size(); iter++)
  {
    std::cout << "Aircraft id [" << std::to_string(iter) << "]" << std::endl;
    std::cout << "Aircraft company [" << eVTOL_sim::aircraft::AircraftTypeEnums[(uint8_t)aircraft1.get_type()] << "]" << std::endl;
    
    std::cout << "avg_flight_time_minutes = " << results[iter].avg_flight_time_minutes << std::endl;
    std::cout << "avg_time_charging_minutes = " << results[iter].avg_time_charging_minutes << std::endl;
    std::cout << "avg_time_waiting_minutes = " << results[iter].avg_time_waiting_minutes << std::endl;
    std::cout << "max_numb_faults = " << results[iter].max_numb_faults << std::endl;
    std::cout << "passenger_miles = " << results[iter].passenger_miles << std::endl;

    std::cout << "------------------" << std::endl;
  }

  return EXIT_SUCCESS;
}