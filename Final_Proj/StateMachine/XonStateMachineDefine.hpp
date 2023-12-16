#ifndef XonStateMachineDefine_HPP
#define XonStateMachineDefine_HPP

#include "GameController.hpp"
#include "../GameComponent/Chartlet.hpp"

class XonState
{
    public:    
    Chartlet chartlet;
    float x_velo_coe;
    float y_velo_coe;
    float impact_radius; //碰撞半径
    XonState(Chartlet* _chartlet):chartlet(*_chartlet){;};
    //The "=0" at the end means the function is purely virtual, that must not be defined in this class.
    virtual void Init(GameController* _FSM_Owner) = 0;
    virtual void Enter(GameController* _FSM_Owner) = 0;
    virtual void Execute(GameController* _FSM_Owner) = 0;
    virtual void Exit(GameController* _FSM_Owner) = 0;

    XonState* GetPInstance()
    {
        return this;
    }
};

class Xon
{
    public:
    long x_coor;
    long y_coor;
    Color color;

    protected:
    GameController* p_FSM_owner;
    XonState *p_current_state;
    
    public:
    Xon(GameController* _FSM_Owner, Color _color):color(_color)
    {;}

    void setCurrentState(XonState *p_state)
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
    void ChangeState(XonState *p_next_state)
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

    XonState* GetPCurrentState()
    {
        return p_current_state;
    }
};

#endif