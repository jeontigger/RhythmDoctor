#pragma once
#include "CWindowEvent.h"

class CWindowMove :
    public CWindowEvent
{
    GENERATED_OBJECT(CWindowMove);

private:
    
    Vec2 m_vTarget;
    float m_fSpeed;
    bool m_bIsAlive;

public:
    void SetTarget(Vec2 _target, float _time = 0);

public:
    virtual void Play() override;
    virtual void tick(float _dt) override;

public:
    CWindowMove();
    ~CWindowMove();
};

