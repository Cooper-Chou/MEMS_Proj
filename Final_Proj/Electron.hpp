#ifndef Electron_HPP
#define Electron_HPP

#include "ElectronStateDefine.hpp"
#include "Chartlet.hpp"

#define X_DEFAULT_VELOCITY 8.0f;
#define Y_DEFAULT_VELOCITY 4.0f;

#define EXCITED_STATE_LAST 7000 /* ms */

class ElectronState
{
    public:
        Chartlet chartlet;
        float x_velo_coe;
        float y_velo_coe;
        float impact_radius; //碰撞半径
};

enum Color
{
    NULL = 0,
    RED = 1,
    BLUE = 2
};

class Electron 
{
    public:
    ElectronState gnd_state;
    ElectronState exc_state;
    int x_coor;
    int y_coor;
    Color color;
};

#endif