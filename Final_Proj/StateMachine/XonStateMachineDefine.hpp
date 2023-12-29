#ifndef XonStateMachineDefine_HPP
#define XonStateMachineDefine_HPP

#include "../GameComponent/Chartlet.hpp"

class GameController;

enum Color
{
    NO_COLOR = 0,
    RED = 0,
    BLUE = 1,

    COLOR_NUM
};

class XonState
{
    public:
    Chartlet* p_chartlet;
    float x_velo_coe;
    float y_velo_coe;
    float impact_radius;

    XonState(Chartlet* _p_chartlet):p_chartlet(_p_chartlet){;}
    //The "=0" at the end means the function is purely virtual, that must not be defined in this class.
    virtual void Init(GameController* _FSM_Owner) = 0;
    virtual void Enter(GameController* _FSM_Owner) = 0;
    virtual void Execute(GameController* _FSM_Owner) = 0;
    virtual void Exit(GameController* _FSM_Owner) = 0;
    virtual void CalcXVeloCoe(GameController* _FSM_Owner, float _direct_angle) = 0;
    virtual void CalcYVeloCoe(GameController* _FSM_Owner, float _direct_angle) = 0;
};

class Xon
{
    public:
    //此处坐标不包含边框!!!
    int x_coor;
    int y_coor;
    Color color;

    protected:
    GameController* p_FSM_owner;
    XonState *p_current_state;
    
    public:
    Xon(GameController* _FSM_Owner, Color _color):p_FSM_owner(_FSM_Owner),color(_color),p_current_state(nullptr)
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
    void SetInitCoor(int _x_coor, int _y_coor)
    {
        x_coor = _x_coor;
        y_coor = _y_coor;
    }
    XonState* GetPCurrentState()
    {
        return p_current_state;
    }
    virtual void Init() {};            // Need implement
    virtual void HandleInput() {};     // Need implement
};

#endif