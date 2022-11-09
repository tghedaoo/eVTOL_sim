/*
State Machine Class Header.
Tracks and Switches the state of the aircraft - flight, waiting, charging.
*/

#include <cstdint>
#include <chrono>
#include <thread>
#include <mutex>

#pragma once

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

      /// @brief Flight State.
      void flight_st();
      /// @brief Waiting for Charging.
      void awaiting_charger_st();
      /// @brief Charging State.
      void charging_st();
      /// @brief Stop State.
      void stop_st();
      
      /// @brief Aircraft State Control.
      void state_control();

      /// @brief Command Stop.
      void stop_state_machine();

      /// @brief Get time tracking results.
      /// @return Time tracking results.
      StateMachineTimeTrack get_time_track_results();

      /// maximum time an aircraft can fly on one charge.
      uint16_t max_time_per_flight_minutes_;   
      
    private:
      AircraftState current_state_;         /// Current State of the Aircraft.
      bool stop_state_machine_;             /// State Machine End Flag.
      StateMachineTimeTrack time_track_;    /// time tracking variables.
    };

  } // namespace state_machine
} // namespace eVTOL_sim
