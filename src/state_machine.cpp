/*
State Machine Class Implementation.
*/

#include "../includes/state_machine.h"

namespace eVTOL_sim
{
  namespace state_machine
  {
    StateMachine::StateMachine() : current_state_(AircraftState::flight), stop_state_machine_(false)
    {
    }

    void StateMachine::flight_st()
    {
      current_state_ = AircraftState::flight;
    }

    void StateMachine::awaiting_charger_st()
    {
      current_state_ = AircraftState::awaiting_charger;
    }

    void StateMachine::charging_st()
    {
      current_state_ = AircraftState::charging;
    }

    void StateMachine::stop_st()
    {
      current_state_ = AircraftState::stop;
    }

    void StateMachine::state_control()
    {
      // Keep the State Machine Running Until commanded to stop.
      while(!stop_state_machine_)
      {
        // State Machine Flow.
      }
      // Stop operation.
      stop_st();
    }
    
    void StateMachine::stop_state_machine()
    {
      stop_state_machine_ = true;
    }

    

  } // namespace state_machine
} // namespace eVTOL_sim
