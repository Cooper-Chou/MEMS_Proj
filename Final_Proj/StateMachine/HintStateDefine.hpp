#ifndef HintStateDefine_HPP
#define HintStateDefine_HPP

#include "../../C_FSM/State.hpp"
#include <stdint.h>
#include <wiringPi.h>
#include "../BSP/bsp.hpp"
#include "../BSP/Music.hpp"
#include "ElectronStateDefine.hpp"
#include "XonStateMachineDefine.hpp"

#define MAX_LED_BLINK_PERIOD 800 /* ms */
#define MIN_LED_BLINK_PERIOD 100 /* ms */
#define BEAT 300 /* ms */
#define LED_BLINK_PERIOD_LEVEL 5 //LED闪烁频率分成五个档次

class GameController;

void ledBlink(int _led_pin, int _blink_period, int _last_tick);

class PeaceState : public State<GameController>
{
    private:
        inline static PeaceState *m_pInstance;
    
    public:    
        Music *p_music;
        PeaceState()
        {
            m_pInstance = nullptr;
        }

        virtual void Init(GameController* _FSM_Owner);
        virtual void Enter(GameController* _FSM_Owner);
        virtual void Execute(GameController* _FSM_Owner);
        virtual void Exit(GameController* _FSM_Owner);

        static PeaceState* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new PeaceState();
            }
            return m_pInstance;
        }
};

class BattleState : public State<GameController>
{
    private:
        inline static BattleState *m_pInstance;
    
    public:    
        Music *p_music;
        BattleState()
        {
            m_pInstance = nullptr;
        }

        int led_blink_period;
        int last_led_tick;

        virtual void Init(GameController* _FSM_Owner);
        virtual void Enter(GameController* _FSM_Owner);
        virtual void Execute(GameController* _FSM_Owner);
        virtual void Exit(GameController* _FSM_Owner);

        static BattleState* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new BattleState();
            }
            return m_pInstance;
        }
};

class EndState : public State<GameController>
{
    private:
        inline static EndState *m_pInstance;

    public:
        Music *red_win_p_music;
        Music *blue_win_p_music;
        EndState()
        {
            m_pInstance = nullptr;
        }

        int led_blink_period;
        int last_led_tick_green;
        int last_led_tick_winner;

        virtual void Init(GameController* _FSM_Owner);
        virtual void Enter(GameController* _FSM_Owner);
        virtual void Execute(GameController* _FSM_Owner);
        virtual void Exit(GameController* _FSM_Owner);

        static EndState* GetInstance()
        {
            if(m_pInstance == nullptr)
            {
                m_pInstance = new EndState();
            }
            return m_pInstance;
        }
};

#endif
