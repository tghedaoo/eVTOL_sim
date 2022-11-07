/*
Aircraft Class
Contains technical specifications - cruise speed, battery capacity, time to charge, energy use at cruise, passenger count, fault probability.
Runs State machine class object to track the state of the aircraft - flight, waiting, charging.
Calculates simulations results.
*/

#include "state_machine.h"

#include <string>

#pragma once

namespace eVTOL_sim
{
  namespace aircraft
  {
    /// @brief Aircraft Type.
    enum class AircraftType : uint8_t
    {
      Alpha = 0,
      Beta,
      Charlie,
      Delta,
      Echo,
    };

    /// @brief Aircraft Type Strings.
    static const std::string AircraftTypeEnums[] = {"Alpha", "Beta", "Charlie", "Delta", "Echo"};

    /// @brief Aircraft Parameters Struture.
    /// @note time is in minutes
    /// @note energy_use is in Wh/mile.
    /// @note fault_probability is in percentage.
    struct AircraftParams
    {
      uint16_t cruise_speed;
      uint16_t battery_capacity;
      uint16_t time_2_charge_minutes;
      uint16_t energy_use;
      uint16_t passenger_count;
      uint16_t fault_probability;
    };

    /// @brief Simulation Result Structure.
    struct SimRes
    {
      uint16_t avg_flight_time_minutes;
      uint16_t avg_time_charging_minutes;
      uint16_t avg_time_waiting_minutes;
      uint16_t max_numb_faults;
      uint16_t passenger_miles;
    };

    class Aircraft
    {
    public:
      Aircraft() = default;
      ~Aircraft() = default;

      /// @brief Initialize aircraft with parameters.
      /// @param params Parameters for this specific aircraft.
      /// @param type aircraft type as in company of origin.
      /// @param state_machine_obj state machine governing the aircraft.
      void init_aircraft(AircraftParams &params, AircraftType type, state_machine::StateMachine& state_machine_obj);

      /// @brief Start aircraft i.e. start the state machine.
      void start_sim();

      /// @brief Stop aircraft i.e. stop the state machine.
      void stop_sim();

      /// @brief Type of aircraft
      /// @return aircraft type enum.
      AircraftType get_type();

      /// @brief Simulation Results.
      /// @return simulation results from the aircraft.
      SimRes sim_results();

    private:
      AircraftParams aircraft_parameters_;            /// Current Aircraft Parameters.
      AircraftType aircraft_type_;                    /// Current Aircraft Type.
      state_machine::StateMachine state_machine_obj_; /// State Machine governing the current aircraft.
      std::thread state_machine_thread_;              /// State Machine Thread.
    };

  } // namespace aircraft
} // namespace eVTOL_sim