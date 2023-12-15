#ifndef PhotonStateDefine_HPP
#define PhotonStateDefine_HPP

#include <State.hpp>
#include "GameController.hpp"


class PhotonState : public State
{
    public:
    int existence;
};

class ExistState : public PhotonState
{
    private:
        static ExistState *m_pInstance;
    
    public:
        //如果要将父类的纯虚函数实现, 就要在实现的那一级声明!
        virtual void Init(GameController* _FSM_Owner){;}
        virtual void Enter(GameController* _FSM_Owner){;}
        virtual void Execute(GameController* _FSM_Owner){;}
        virtual void Exit(GameController* _FSM_Owner){;}

        // GetInstance() 必须要在子类里面定义, 如果在父类 State 中定义, 全场就只有一个 State 了!
        static ExistState* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new ExistState();
            }
            return m_pInstance;
        }
};

class GoneState : public PhotonState
{
    private:
        static GoneState *m_pInstance;
    
    public:
        //如果要将父类的纯虚函数实现, 就要在实现的那一级声明!
        virtual void Init(GameController* _FSM_Owner){;}
        virtual void Enter(GameController* _FSM_Owner){;}
        virtual void Execute(GameController* _FSM_Owner){;}
        virtual void Exit(GameController* _FSM_Owner){;}

        // GetInstance() 必须要在子类里面定义, 如果在父类 State 中定义, 全场就只有一个 State 了!
        static GoneState* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new GoneState();
            }
            return m_pInstance;
        }
};

#endif