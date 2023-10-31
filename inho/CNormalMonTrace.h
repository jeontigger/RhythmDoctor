#pragma once
#include "CState.h"

class CPlayer;

class CNormalMonTrace :
    public CState
{
private:
    CPlayer* m_pTarget;

public:
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CNormalMonTrace);
    CNormalMonTrace();
    ~CNormalMonTrace();
};

