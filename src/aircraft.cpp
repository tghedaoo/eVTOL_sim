/*
Aircraft Class Implementation.
*/

#include "../includes/aircraft.h"

namespace eVTOL_sim
{
  namespace aircraft
  {
    void Aircraft::init_aircraft(AircraftParams& params, AircraftType type, state_machine::StateMachine& state_machine_obj)
    {
      // Initialize all aircraft parameters.
      aircraft_parameters_.cruise_speed = params.cruise_speed;
      aircraft_parameters_.battery_capacity = params.battery_capacity;
      aircraft_parameters_.time_2_charge_minutes = params.time_2_charge_minutes;
      aircraft_parameters_.energy_use = params.energy_use;
      aircraft_parameters_.passenger_count = params.passenger_count;
      aircraft_parameters_.fault_probability = params.fault_probability;
      // Type.
      aircraft_type_ = type;
      // State Machine.
      state_machine_obj_ = state_machine_obj;
    }

    bool Aircraft::start_sim()
    { 
      // Start the state machine thread.
      return true;
    }

    void Aircraft::stop_sim()
    {
      state_machine_obj_.stop_state_machine();
    }

    AircraftType Aircraft::get_type()
    {
      return aircraft_type_;
    }

    SimRes Aircraft::sim_results()
    {
      SimRes results = {0};
      // Check Stop.
      // Get all results 
      return results;
    }
  } // namespace aircraft
} // namespace eVTOL_sim
