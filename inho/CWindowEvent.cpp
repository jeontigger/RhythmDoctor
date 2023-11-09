#include "pch.h"
#include "CWindowEvent.h"

#include "CEngine.h"
#include "Resource.h"

CWindowEvent::CWindowEvent()
{
    m_hWnd = CEngine::GetInst()->GetMainWind();

    Vec2 _ptResolution = CEngine::GetInst()->GetResolution();
    RECT rt = { 0, 0, _ptResolution.x, _ptResolution.y };

    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
    int x = rt.right - rt.left;
    int y = rt.bottom - rt.top;
    m_vWinRes = { x, y };

    GetWindowRect(m_hWnd, &rt);
    x = rt.left;
    y = rt.top;
    m_vWinPos = { x, y };

    GetWindowRect(GetDesktopWindow(), &rt);
    x = rt.right - rt.left;
    y = rt.bottom - rt.top;
    m_vMonitorRes = { x, y };
  
}

CWindowEvent::~CWindowEvent()
{
}

void CWindowEvent::Play()
{
}

void CWindowEvent::tick(float _dt)
{
    if (pFunc == nullptr) {
        return;
    }

    (this->*pFunc)(_dt);
}

void CWindowEvent::LinearMove(float _dt)
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

void CWindowEvent::SetTarget(Vec2 _target, float _time)
{
    m_vTarget = _target;
    if ((m_vTarget - GetPos()).Length() <= 1.f) {
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

void CWindowEvent::SetMode(WindowEventType _type)
{
    switch (_type)
    {
    case WindowEventType::LinearMove:

        m_bIsAlive = true;
        pFunc = &CWindowEvent::LinearMove;
        break;
    case WindowEventType::END:
        break;
    default:
        break;
    }
}
