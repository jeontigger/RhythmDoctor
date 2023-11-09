#include "pch.h"
#include "CWindowMove.h"

CWindowMove::CWindowMove():
    m_vTarget{0,0},
    m_fSpeed(0.f),
    m_bIsAlive(false)
{
}

CWindowMove::~CWindowMove()
{
}

void CWindowMove::tick(float _dt)
{
    if (!m_bIsAlive) {
        return;
    }

    if (m_fSpeed == 0) {
        SetPos(m_vTarget);
        m_bIsAlive = false;
        return;
    }

    Vec2 vPos = GetPos();

    Vec2 vDir = m_vTarget - vPos;
    vDir.Normalize();
    vPos += vDir * m_fSpeed * _dt;
    SetPos(vPos);

    if ((vPos - m_vTarget).Length() <= 3.f) {
        m_bIsAlive = false;
        SetPos(m_vTarget);
    }
}

void CWindowMove::SetTarget(Vec2 _target, float _time)
{
    m_vTarget = _target; 
    if ((m_vTarget-GetPos()).Length() <= 1.f) {
        m_fSpeed = 0;
        m_bIsAlive = false;
        return;
    }

    if (_time == 0) {
        m_fSpeed = 0;
        return;
    }

    Vec2 vDir = m_vTarget - GetPos();
    float len = vDir.Length();

    m_fSpeed = len / _time;

}

void CWindowMove::Play()
{
    m_bIsAlive = true;
}
