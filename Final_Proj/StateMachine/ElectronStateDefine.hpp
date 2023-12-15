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



class RedGroundState : public ElectronState
{
    private:
        static RedGroundState *m_pInstance;
    
    public:
        //如果要将父类的纯虚函数实现, 就要在实现的那一级声明成虚函数!
        virtual void Init(GameController* _FSM_Owner){;}
        virtual void Enter(GameController* _FSM_Owner){;}
        virtual void Execute(GameController* _FSM_Owner){;}
        virtual void Exit(GameController* _FSM_Owner){;}

        // GetInstance() 必须要在子类里面定义, 如果在父类 State 中定义, 全场就只有一个 State 了!
        static RedGroundState* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new RedGroundState();
            }
            return m_pInstance;
        }
};

class RedExcitedState : public ElectronState
{
    private:
        static RedExcitedState *m_pInstance;
    
    public:
        unsigned int state_entering_tick;
        unsigned int state_remain_ms;
        //如果要将父类的纯虚函数实现, 就要在实现的那一级声明成虚函数!
        virtual void Init(GameController* _FSM_Owner);
        virtual void Enter(GameController* _FSM_Owner);
        virtual void Execute(GameController* _FSM_Owner);
        virtual void Exit(GameController* _FSM_Owner);

        // GetInstance() 必须要在子类里面定义, 如果在父类 State 中定义, 全场就只有一个 State 了!
        static RedExcitedState* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new RedExcitedState();
            }
            return m_pInstance;
        }
};

class BlueGroundState : public ElectronState
{
    private:
        static BlueGroundState *m_pInstance;
    
    public:
        //如果要将父类的纯虚函数实现, 就要在实现的那一级声明成虚函数!
        virtual void Init(GameController* _FSM_Owner){;}
        virtual void Enter(GameController* _FSM_Owner){;}
        virtual void Execute(GameController* _FSM_Owner){;}
        virtual void Exit(GameController* _FSM_Owner){;}

        // GetInstance() 必须要在子类里面定义, 如果在父类 State 中定义, 全场就只有一个 State 了!
        static BlueGroundState* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new BlueGroundState();
            }
            return m_pInstance;
        }
};

class BlueExcitedState : public ElectronState
{
    private:
        static BlueExcitedState *m_pInstance;
    
    public:
        unsigned int state_entering_tick;
        unsigned int state_remain_ms;
        //如果要将父类的纯虚函数实现, 就要在实现的那一级声明成虚函数!
        virtual void Init(GameController* _FSM_Owner);
        virtual void Enter(GameController* _FSM_Owner);
        virtual void Execute(GameController* _FSM_Owner);
        virtual void Exit(GameController* _FSM_Owner);

        // GetInstance() 必须要在子类里面定义, 如果在父类 State 中定义, 全场就只有一个 State 了!
        static BlueExcitedState* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new BlueExcitedState();
            }
            return m_pInstance;
        }
};

#endif