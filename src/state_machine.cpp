/*
State Machine Class Implementation.
*/

#include "../includes/state_machine.h"

namespace eVTOL_sim
{
  namespace state_machine
  {
    // Initializing state tio flight as per the problem statement.
    StateMachine::StateMachine() : current_state_(AircraftState::flight), stop_state_machine_(false), time_track_({0})
    {
    }

    void StateMachine::state_control()
    {
      // Keep the State Machine Running Until commanded to stop.
      while (!stop_state_machine_)
      {
        switch (current_state_)
        {
        case AircraftState::flight:
          flight_st();
          break;
        case AircraftState::charging:
          charging_st();
          break;
        case AircraftState::awaiting_charger:
          awaiting_charger_st();
          break;
        }
      }
      // Stop operation.
      stop_st();
    }

    void StateMachine::flight_st()
    {
      // Check if already flying.
      if (!flight_time_track_.started)
      {
        flight_time_track_.start_time = std::clock();
        flight_time_track_.started = true;
      }

      // Track for flight time.
      double flight_duration = time_per_flight_minutes; // Max duration of flight in full charge.
      if (((std::clock() - flight_time_track_.start_time) / (double)CLOCKS_PER_SEC) < flight_duration)
      {
        return;
      }

      // Update total time of flight since beginning.
      time_track_.total_flight_time_minutes += flight_duration;

      // Try to find a charger.
      if (check_charger_availability())
      {
        current_state_ = AircraftState::charging;
      }
      else
      {
        current_state_ = AircraftState::awaiting_charger;
      }

      // end current tracking.
      flight_time_track_.started = false;
    }

    void StateMachine::awaiting_charger_st()
    {
      // Check if already waiting.
      if (!waiting_time_track_.started)
      {
        waiting_time_track_.start_time = std::clock();
        waiting_time_track_.started = true;
      }

      // Try to find a charger.
      if (check_charger_availability())
      {
        current_state_ = AircraftState::charging;
        // Update total time of waiting since beginning.
        double waiting_duration = ((std::clock() - waiting_time_track_.start_time) / (double)CLOCKS_PER_SEC);
        time_track_.total_wait_time_minutes += waiting_duration;
        waiting_time_track_.started = false;
      }

    }

    void StateMachine::charging_st()
    {      
      // Check if already charging.
      if (!charging_time_track_.started)
      {
        charging_time_track_.start_time = std::clock();
        charging_time_track_.started = true;
      }

      // Track for flight time.
      double charge_duration = time_to_charge_minutes; // Max duration for full charge.
      if (((std::clock() - charging_time_track_.start_time) / (double)CLOCKS_PER_SEC) < charge_duration)
      {
        return;
      }
      
      // Update total time of charging since beginning.
      time_track_.total_charging_time_minutes += charge_duration;

      // TODO: release obtained charger.

      // end current tracking.
      charging_time_track_.started = false;
      current_state_ = AircraftState::flight;
    }

    void StateMachine::stop_st()
    {
      // check current state and complete time tracking.
      switch(current_state_)
      {
        case AircraftState::flight:
          time_track_.total_flight_time_minutes += ((std::clock() - flight_time_track_.start_time) / (double)CLOCKS_PER_SEC);
          break;
        case AircraftState::charging:
          time_track_.total_charging_time_minutes += ((std::clock() - charging_time_track_.start_time) / (double)CLOCKS_PER_SEC);
          break;
        case AircraftState::awaiting_charger:
          time_track_.total_wait_time_minutes += ((std::clock() - waiting_time_track_.start_time) / (double)CLOCKS_PER_SEC);
          break;
      }
    }

    bool StateMachine::check_charger_availability()
    {
      return true;
    }

    void StateMachine::stop_state_machine()
    {
      stop_state_machine_ = true;
    }

    StateMachineTimeTrack StateMachine::get_time_track_results()
    {
      return time_track_;
    }

  } // namespace state_machine
} // namespace eVTOL_sim
