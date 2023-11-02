#pragma once
#include "CComponent.h"
class CTransform :
    public CComponent
{
private:
    Vec2 m_Point;
    float m_Speed;

public:
    virtual void finaltick(float _DT) override;
    void MoveTo(Vec2 _Point, float _duration);
    void SetTargetPoint(Vec2 _point) { m_Point = _point; }


public:
    CLONE(CTransform);
    CTransform(CObj* _Owner);
    ~CTransform();
};

