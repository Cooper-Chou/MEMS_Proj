#ifndef Controller_HPP
#define Controller_HPP

#include <stdint.h>

class Controller
{
    public:
    Controller *m_pInstance;
    
    virtual void HandleInput() = 0;
    virtual void Init() = 0;
    virtual void Update() = 0;
};

#endif