/*
eVTOL Simulator.
----------------
Spawns 20 aircrafts, runs simulation for 3 minutes, produces simulations results.
The number of aircrafts are generated randomly.
The charging stations are 3 mutexes and only one aircraft state machine thread can grab it at a time.
The aircraft parameters are given and therefore hardcoded for our purposes.
The aircraft uses a state machine to track its states and timings.
*/

#include "../includes/state_machine.h"
#include "../includes/aircraft.h"

#include <vector>
#include <cstdlib>

// TODO: add this function as a part of the util class.
// Aircraft Parameters
std::vector<eVTOL_sim::aircraft::AircraftParams> get_aircraft_params()
{
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
  return param_list;
}

// TODO: add this function as a part of the util class.
// Calculate the max flight time per charge in minutes.
uint16_t calculate_max_flight_time_per_charge(eVTOL_sim::aircraft::AircraftParams params)
{
  // Float utilization as calculation just happening once.
  float range = (float)(params.battery_capacity * 1000) / (params.energy_use);
  float time_mins = (range / params.cruise_speed) * 60;
  // Also minute calculation accuracy is subject to float conversions.
  return static_cast<uint16_t>(time_mins);
}

// TODO: add this function as a part of the util class.
// Generate random numbers of aircrafts.
std::vector<int> random_number_of_aircrafts(int num_aircrafts)
{
  std::vector<int> num_aircrafts_per_type;

  // Providing a seed value
  srand((unsigned)time(NULL));

  int range = 0, current_type_numbers = 0;

  // Since there are 5 types, the worst case would be 1 each of 4 types and rest of 1 type.
  // loop hardcoded for 5 types as per our use case.
  for (int type = 4; type >= 0; type--)
  {
    range = num_aircrafts - type;
    current_type_numbers = (rand() % range) + 1;
    num_aircrafts_per_type.push_back(current_type_numbers);
    num_aircrafts -= current_type_numbers;
  }

  return num_aircrafts_per_type;
}

int main()
{
  std::cout << " **** eVTOL SIMULATION **** " << std::endl;
  std::cout << "eVTOL sim: Initializing ..." << std::endl;

  // Aircraft paramters.
  auto param_list = get_aircraft_params();

  // max flight time per charge in minutes
  std::vector<uint16_t> max_flight_time_per_charge_minutes;
  for (int iter = 0; iter < 5; iter++)
  {
    max_flight_time_per_charge_minutes.push_back(calculate_max_flight_time_per_charge(param_list[iter]));
    std::cout << max_flight_time_per_charge_minutes[iter] << " ";
  }
  std::cout << "<-- Aircraft max flight times in minutes." << std::endl;

  // Random number generator
  auto aircraft_count = random_number_of_aircrafts(20);
  for (auto value : aircraft_count)
  {
    std::cout << value << " ";
  }
  std::cout << "<-- Aircraft counts." << std::endl;

  // Get 20 vehicles (of 5 types in random numbers)
  // TODO: Create an infra to spawn as per random number of aircrafts.

  eVTOL_sim::state_machine::StateMachine state_machine1;
  eVTOL_sim::aircraft::Aircraft aircraft1;

  aircraft1.init_aircraft(0,
                          param_list[0],
                          eVTOL_sim::aircraft::AircraftType::Alpha,
                          state_machine1,
                          max_flight_time_per_charge_minutes[0]);

  eVTOL_sim::state_machine::StateMachine state_machine2;
  eVTOL_sim::aircraft::Aircraft aircraft2;
  aircraft2.init_aircraft(1,
                          param_list[1],
                          eVTOL_sim::aircraft::AircraftType::Beta,
                          state_machine2,
                          max_flight_time_per_charge_minutes[1]);

  eVTOL_sim::state_machine::StateMachine state_machine3;
  eVTOL_sim::aircraft::Aircraft aircraft3;
  aircraft3.init_aircraft(2,
                          param_list[2],
                          eVTOL_sim::aircraft::AircraftType::Charlie,
                          state_machine3,
                          max_flight_time_per_charge_minutes[2]);

  eVTOL_sim::state_machine::StateMachine state_machine4;
  eVTOL_sim::aircraft::Aircraft aircraft4;
  aircraft4.init_aircraft(3,
                          param_list[3],
                          eVTOL_sim::aircraft::AircraftType::Delta,
                          state_machine4,
                          max_flight_time_per_charge_minutes[3]);

  eVTOL_sim::state_machine::StateMachine state_machine5;
  eVTOL_sim::aircraft::Aircraft aircraft5;
  aircraft5.init_aircraft(4,
                          param_list[4],
                          eVTOL_sim::aircraft::AircraftType::Echo,
                          state_machine5,
                          max_flight_time_per_charge_minutes[4]);

  std::cout << "eVTOL sim: Initialization COMPLETE." << std::endl;

  // Begin Simulator.
  std::cout << "eVTOL sim: Simualtion Beginning ... " << std::endl;
  // TODO: Spawn 20 aircrafts.
  aircraft1.start_sim();
  aircraft2.start_sim();
  aircraft3.start_sim();
  aircraft4.start_sim();
  aircraft5.start_sim();

  // Start simulator time tracking.
  // 180 sec - 3 minutes ~ 3 hours of simulation.
  // TODO: Explore timer interrupt setup to avoid busy wait.
  // TODO: timing cleanups. Times in uint16_t roundup to 1 less minute depending upon the time of thread termination.
  std::clock_t start;
  start = std::clock();
  double sim_end_duration = 180;
  while (((std::clock() - start) / (double)CLOCKS_PER_SEC) < sim_end_duration)
    ;

  // Stop sim after 3 minutes.
  // TODO: Stop 20 spawned aircrafts.
  aircraft1.stop_sim();
  aircraft2.stop_sim();
  aircraft3.stop_sim();
  aircraft4.stop_sim();
  aircraft5.stop_sim();

  std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Just to let the all threads complete.
  std::cout << "eVTOL sim: Simulation COMPLETE." << std::endl;

  // Get all calculations.
  std::cout << "eVTOL sim: Calculations Beginning ... " << std::endl;
  std::vector<eVTOL_sim::aircraft::SimRes> results;

  // TODO: Get 20 aircraft results.
  results.push_back(aircraft1.sim_results());
  results.push_back(aircraft2.sim_results());
  results.push_back(aircraft3.sim_results());
  results.push_back(aircraft4.sim_results());
  results.push_back(aircraft5.sim_results());

  std::cout << "eVTOL sim: Calculations COMPLETE." << std::endl;

  std::cout << "------------------" << std::endl;
  std::cout << "PER AIRCRAFT RESULTS" << std::endl;
  std::cout << "------------------" << std::endl;
  // TODO: populate a file (maybe .xls) with the results.
  for (uint8_t iter = 0; iter < results.size(); iter++)
  {
    std::cout << "Aircraft id [" << std::to_string(iter) << "]" << std::endl;
    // std::cout << "Aircraft company [" << eVTOL_sim::aircraft::AircraftTypeEnums[(uint8_t)aircraft[iter].get_type()] << "]" << std::endl;

    std::cout << "avg_flight_time_minutes = " << results[iter].avg_flight_time_minutes << std::endl;
    std::cout << "avg_time_charging_minutes = " << results[iter].avg_time_charging_minutes << std::endl;
    std::cout << "avg_time_waiting_minutes = " << results[iter].avg_time_waiting_minutes << std::endl;
    std::cout << "max_numb_faults = " << results[iter].max_numb_faults << std::endl;
    std::cout << "passenger_miles = " << results[iter].passenger_miles << std::endl;

    std::cout << "------------------" << std::endl;
  }

  return EXIT_SUCCESS;
}