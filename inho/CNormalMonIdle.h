#pragma once
#include "CState.h"

class CPlayer;

class CNormalMonIdle :
    public CState
{
private:
    CPlayer* m_pTarget;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CNormalMonIdle);
    CNormalMonIdle();
    ~CNormalMonIdle();
};

