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
    }

    void StateMachine::awaiting_charger_st()
    {
    }

    void StateMachine::charging_st()
    {
    }

    void StateMachine::state_control()
    {
      // Keep the State Machine Running Until commanded to stop.
      while(!stop_state_machine_)
      {
        // State Machine Flow.
      }

      // Stop State Work.

    }
    
    void StateMachine::stop_state_machine()
    {
      stop_state_machine_ = true;
    }

  } // namespace state_machine
} // namespace eVTOL_sim
