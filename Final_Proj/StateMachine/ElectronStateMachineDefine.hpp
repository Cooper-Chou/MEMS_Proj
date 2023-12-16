#ifndef ElectronStateMachineDefine_HPP
#define ElectronStateMachineDefine_HPP

#include "GameController.hpp"
#include "ElectronStateDefine.hpp"
#include "../GameComponent/Chartlet.hpp"


class Xon
{
    public:
    long x_coor;
    long y_coor;
    float impact_radius;
    Color color;

    protected:
    GameController* p_FSM_owner;
    ElectronState *p_current_state;
    
    public:
    Xon(GameController* _FSM_Owner, Color _color):color(_color)
    {;}

    void setCurrentState(ElectronState *p_state)
	{
		p_current_state = p_state;
		p_current_state->Enter(p_FSM_owner);
	}
    void Update()
    {
        if(p_current_state != nullptr)
        {
            p_current_state->Execute(p_FSM_owner);
        }
    }
    void ChangeState(ElectronState *p_next_state)
    {
        if(p_next_state != nullptr && p_current_state != p_next_state)
        {
            p_current_state->Exit(p_FSM_owner);
            p_current_state = p_next_state;
            p_current_state->Enter(p_FSM_owner);
        }
    }
    
    virtual void Init();
    virtual void HandleInput();

    void SetInitCoor(long _x_coor, long _y_coor)
    {
        x_coor = _x_coor;
        y_coor = _y_coor;
    }
};

#endif