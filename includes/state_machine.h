/*
State Machine Class Header.
Tracks and Switches the state of the aircraft - flight, waiting, charging.
*/

#include <cstdint>
#include <chrono>
#include <thread>

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
      stop,
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
      

    private:
      AircraftState current_state_;
      bool stop_state_machine_;
    };

  } // namespace state_machine
} // namespace eVTOL_sim
