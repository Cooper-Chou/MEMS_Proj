#ifndef GameController_HPP
#define GameController_HPP

#include "../../C_FSM/State.hpp"
#include "../../C_FSM/StateMachine.hpp"
#include "../BSP/bsp.hpp"
#include "../../C_FSM/Controller.hpp"
#include <stdint.h>
#include <stdio.h>

#include "ElectronStateDefine.hpp"
#include "HintStateDefine.hpp"
#include "PhotonStateDefine.hpp"

#include "../GameComponent/Chartlet.hpp"
#include "../GameComponent/Shader.hpp"
#include "XonStateMachineDefine.hpp"
#include <cmath>

//此处的速度只是一个相对值，没有单位，只能 大了调小 小了调大 这样子
#define X_DEFAULT_VELOCITY (100.0f / (float)REFRESH_PERIOD)
#define Y_DEFAULT_VELOCITY (50.0f / (float)REFRESH_PERIOD)

#define PHOTON_NUM 1

enum GameState { PEACE = 0, BATTLE = 1, END = 2 };
class GameController;

// class GameController;//先声明防止报错

class RedElectron : public Xon {
public:
  ElectronGroundState ground_state;
  ElectronExcitedState excited_state;

public:
  RedElectron(GameController *_FSM_Owner)
      : Xon(_FSM_Owner, Color::RED), //子类构造函数必须要调用父类构造函数
        ground_state(p_gnd_aprnc_1), excited_state(p_exc_aprnc_1) {}

  void Init();
  void HandleInput();
};

class BlueElectron : public Xon {
public:
  ElectronGroundState ground_state;
  ElectronExcitedState excited_state;

public:
  BlueElectron(GameController *_FSM_Owner)
      : Xon(_FSM_Owner, Color::BLUE), //子类构造函数必须要调用父类构造函数
        ground_state(p_gnd_aprnc_2), excited_state(p_exc_aprnc_2) {}

  void Init() override;
  void HandleInput() override; // is this a leaf or inner node
};

class HintStateMachine : public StateMachine<GameController> {
public:
  HintStateMachine(GameController *_FSM_Owner)
      : StateMachine(_FSM_Owner) //子类构造函数必须要调用父类构造函数
  {
    this->Init();
  }

  virtual void Init();
  virtual void HandleInput();
};

class Photon : public Xon {
public:
  PhotonExistState exist_state;
  PhotonGoneState gone_state;

public:
  Photon(GameController *_FSM_Owner)
      : Xon(_FSM_Owner, Color::NO_COLOR), //子类构造函数必须要调用父类构造函数
        exist_state(p_photon_aprnc_exist), gone_state(p_photon_aprnc_gone) {
  } //光子类不能算作电子，只有电子才具有颜色属性，所以要给它赋予空颜色！

  void Init();
  void HandleInput();
};

// GameController是单例
class GameController : public Controller {
private:
  inline static GameController *m_pInstance;

public:
  int last_tick;
  int battle_state_entering_tick;
  int battle_state_remain_ms;
  int photon_absorbed_flag;

  HintStateMachine hint_state_machine;
  Photon photon;
  RedElectron red_electron;
  BlueElectron blue_electron;
  Xon *electron_p_list[Color::COLOR_NUM];
  Xon *shading_xon_p_list[Color::COLOR_NUM + PHOTON_NUM];
  GameState game_state;
  Shader shader;

  /*--------------------------------------*/
  Color game_state_color;
  //如果处于PEACE状态，这个变量没有意义，应该为NO_COLOR
  //如果处于BATTLE状态，这个变量表示进攻方
  //如果处于END状态，这个变量表示胜利方
  /*--------------------------------------*/

  GameController()
      : hint_state_machine(this), photon(this), game_state(GameState::PEACE),
        red_electron(this), blue_electron(this), Controller(),
        photon_absorbed_flag(0) {
    this->Init();
  }

  void Init() override;
  void Update() override;

  static GameController *GetInstance() {
    if (m_pInstance == nullptr) {
      m_pInstance = new GameController();
    }
    return m_pInstance;
  }
};

bool ImpactOverlap(Xon *_A_xon, Xon *_B_xon);

extern int battle_hint_Xofst[][2];

extern int battle_hint_Yofst[][2];

extern char battle_hint_aprnc[];

// TODO:速度重分配，计算碰撞，动量守恒，如果有条件就做碰撞！没有就算了！
// void VeloRedistribute();

#endif
