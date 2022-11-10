/*
State Machine Class.
----------------
Tracks and Switches the state of the aircraft - flight, waiting, charging.
*/
#pragma once

#include <iostream>
#include <cstdint>
#include <chrono>
#include <ctime>
#include <thread>
#include <mutex>
#include <string>

namespace eVTOL_sim
{
  namespace state_machine
  {
    enum class AircraftState : uint8_t
    {
      flight = 0,
      awaiting_charger,
      charging,
    };

    struct StateTimeTrack
    {
      bool started;
      std::clock_t start_time;
    };

    struct StateMachineTimeTrack
    {
      uint16_t total_flight_time_minutes;   /// Total Flight time in minutes.
      uint16_t total_charging_time_minutes; /// Total Charging time in minutes.
      uint16_t total_wait_time_minutes;     /// Total Waiting time in minutes.
    };

    class StateMachine
    {
    public:
      StateMachine();
      ~StateMachine() = default;

      /// @brief Aircraft State Control.
      void state_control();

      /// TODO: Encapsulate the flow of time track in a function as its common across states.

      /// @brief Flight State.
      void flight_st();
      /// @brief Charging State.
      void charging_st();
      /// @brief Waiting for Charging.
      void awaiting_charger_st();
      /// @brief Stop State.
      void stop_st();

      /// @brief Check Charger Availability and take a note of it.
      /// @return True if charger obtained.
      bool check_charger_availability();

      /// @brief Command Stop.
      void stop_state_machine();

      /// @brief Get time tracking results.
      /// @return Time tracking results.
      StateMachineTimeTrack get_time_track_results();

      /// TODO: Add an init method to update the following 3 variables and make them private.
      uint8_t aircraft_id;              /// aircraft id number. Just for logging purposes.
      uint16_t time_per_flight_minutes; /// maximum time an aircraft can fly on one charge.
      uint16_t time_to_charge_minutes;  /// time to charge.

    private:
      AircraftState current_state_; /// Current State of the Aircraft.
      bool stop_state_machine_;     /// State Machine End Flag.

      /// Tracking the charger obtained by the aircraft.
      std::mutex *obtained_charger_;

      /// Total time per state.
      StateMachineTimeTrack time_track_;
      /// Instantaneous State Time Trackers.
      StateTimeTrack flight_time_track_;
      StateTimeTrack charging_time_track_;
      StateTimeTrack waiting_time_track_;
    };

  } // namespace state_machine
} // namespace eVTOL_sim
