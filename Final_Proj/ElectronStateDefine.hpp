#ifndef ELectronStateDefine_HPP
#define ELectronStateDefine_HPP

#include <State.hpp>
#include "Chartlet.hpp"
#include <wiringPi.h>
#include "GameController.hpp"

#define EXCITED_STATE_LAST 7000 /* ms */


class ElectronState : public State
{
    
    public:    
        Chartlet chartlet;
        float x_velo_coe;
        float y_velo_coe;
        float impact_radius; //碰撞半径
};

class GroundState : public ElectronState
{
    private:
        static GroundState *m_pInstance;
    
    public:
        //如果要将父类的纯虚函数实现, 就要在实现的那一级声明!
        virtual void Init(GameController* _FSM_Owner){;}
        virtual void Enter(GameController* _FSM_Owner){;}
        virtual void Execute(GameController* _FSM_Owner){;}
        virtual void Exit(GameController* _FSM_Owner){;}

        // GetInstance() 必须要在子类里面定义, 如果在父类 State 中定义, 全场就只有一个 State 了!
        static GroundState* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new GroundState();
            }
            return m_pInstance;
        }
};

class ExcitedState : public ElectronState
{
    private:
        static ExcitedState *m_pInstance;
    
    public:
        unsigned int state_entering_tick;
        unsigned int state_remain_ms;
        //如果要将父类的纯虚函数实现, 就要在实现的那一级声明!
        virtual void Init(GameController* _FSM_Owner);
        virtual void Enter(GameController* _FSM_Owner);
        virtual void Execute(GameController* _FSM_Owner);
        virtual void Exit(GameController* _FSM_Owner);

        // GetInstance() 必须要在子类里面定义, 如果在父类 State 中定义, 全场就只有一个 State 了!
        static ExcitedState* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new ExcitedState();
            }
            return m_pInstance;
        }
};

#endif