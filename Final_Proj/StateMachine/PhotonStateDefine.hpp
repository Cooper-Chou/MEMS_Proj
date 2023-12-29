#ifndef PhotonStateDefine_HPP
#define PhotonStateDefine_HPP

#include "XonStateMachineDefine.hpp"
#include "../GameComponent/Chartlet.hpp"

#define PHOTON_LAST_MS 5000 /* ms */
#define PHOTON_INTERVAL_MS 1000 /* ms */
#define PHOTON_GONE_MS 4000 /* ms */

#define PHOTON_IMPACT_RADIUS 1.0f
class GameController;

class PhotonExistState : public XonState
{
    public:
    int state_entering_tick;
    int state_remaining_ms;
    PhotonExistState(Chartlet *_chartlet):XonState(_chartlet)
    {
        x_velo_coe = 0.0f;
        y_velo_coe = 0.0f;
    }
    //如果要将父类的纯虚函数实现, 就要在实现的那一级声明!
    void Init(GameController* _FSM_Owner) override;
    void Enter(GameController* _FSM_Owner) override;
    void Execute(GameController* _FSM_Owner) override;
    void Exit(GameController* _FSM_Owner) override;
    void CalcXVeloCoe(GameController* _FSM_Owner, float _direct_angle) override {;}
    void CalcYVeloCoe(GameController* _FSM_Owner, float _direct_angle) override {;}
};

class PhotonGoneState : public XonState
{
    public:
    int state_entering_tick;
    int state_remaining_ms;
    PhotonGoneState(Chartlet *_chartlet);
    //如果要将父类的纯虚函数实现, 就要在实现的那一级声明!
    void Init(GameController* _FSM_Owner) override;
    void Enter(GameController* _FSM_Owner) override;
    void Execute(GameController* _FSM_Owner) override;
    void Exit(GameController* _FSM_Owner) override;
    void CalcXVeloCoe(GameController* _FSM_Owner, float _direct_angle) override {;}
    void CalcYVeloCoe(GameController* _FSM_Owner, float _direct_angle) override {;}
};

#endif