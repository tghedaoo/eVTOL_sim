/*
Aircraft Class Implementation.
*/

#include "../includes/aircraft.h"

#include <iostream>

namespace eVTOL_sim
{
  namespace aircraft
  {
    void Aircraft::init_aircraft(AircraftParams &params,
                                 AircraftType type, 
                                 state_machine::StateMachine &state_machine_obj,
                                 uint16_t max_time_per_flight_minutes)
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
      state_machine_obj_.max_time_per_flight_minutes_ = max_time_per_flight_minutes;
    }

    void Aircraft::start_sim()
    {
      state_machine_thread_ = std::thread(&state_machine::StateMachine::state_control, &state_machine_obj_);
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
      // Just to let the corresponding thread complete stop state calculations.
      std::this_thread::sleep_for(std::chrono::milliseconds(100));

      // Check if state machine thread ended already, if not close it now.
      if (state_machine_thread_.joinable())
      {
        state_machine_thread_.join();
      }

      // Get all results.
      SimRes results = {0};  
      auto time_res = state_machine_obj_.get_time_track_results();
      
      // Timings.
      results.avg_flight_time_minutes = time_res.total_flight_time_minutes;
      results.avg_time_charging_minutes = time_res.total_charging_time_minutes;
      results.avg_time_waiting_minutes = time_res.total_wait_time_minutes;
      // Analysis.
      results.max_numb_faults = (time_res.total_flight_time_minutes * (float)aircraft_parameters_.fault_probability) / (60 * 100);
      results.passenger_miles = ((float)time_res.total_flight_time_minutes / 60) * aircraft_parameters_.cruise_speed * aircraft_parameters_.passenger_count;

      return results;
    }
  } // namespace aircraft
} // namespace eVTOL_sim
