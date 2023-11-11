#include "pch.h"
#include "CWindowEvent.h"

#include "CEngine.h"
#include "Resource.h"

#include "CCamera.h"

#include <time.h>

CWindowEvent::CWindowEvent():
    m_Radius(0.f),
    m_QuakeAmount(1)
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

    srand(time(NULL));
  
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

void CWindowEvent::SetTarget(Vec2 _target, float _time)
{
    m_bIsAlive = true;
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

    m_Duration = _time;

}

void CWindowEvent::SetPortalDirection(PortalDirection _dir)
{
    switch (_dir)
    {
    case PortalDirection::Left:
        SetTarget({ -m_vWinRes.x - 10.f, m_vWinPos.y });
        break;

    case PortalDirection::Top:
        SetTarget({ m_vWinPos.x, -m_vWinRes.y - 10.f });
        break;

    case PortalDirection::Right:
        SetTarget({ m_vMonitorRes.x + 10.f, m_vWinPos.y });
        break;

    case PortalDirection::Bottom:
        SetTarget({ m_vWinPos.x , m_vMonitorRes.y + 10.f});
        break;

    case PortalDirection::END:
        break;
    default:
        break;
    }
}

void CWindowEvent::SetMode(WindowEventType _type)
{
    switch (_type)
    {
    case WindowEventType::LinearMove:
        pFunc = &CWindowEvent::LinearMove;
        break;

    case WindowEventType::CircleMove:
        pFunc = &CWindowEvent::CircleMove;
        break;

    case WindowEventType::Quake:
        pFunc = &CWindowEvent::WindowQuake;
        break;

    case WindowEventType::UpAndDown:
        m_AccTime = 0;
        m_curCount = 0;
        pFunc = &CWindowEvent::UpAndDown;
        break;

    case WindowEventType::Jumping:
        m_IsUp = false;
        m_IsFall = false;
        m_AccTime = 0;
        pFunc = &CWindowEvent::Jumping;
        break;

    case WindowEventType::Disapear:
        m_AccTime = 0;
        m_vOrigin = m_vWinPos;
        SetTarget({ m_vWinPos.x, m_vMonitorRes.y + m_vWinRes.y }, m_Duration);
        m_IsUp = false;
        pFunc = &CWindowEvent::Disapear;
        break;

    case WindowEventType::Wave:
        m_AccTime = 0;
        pFunc = &CWindowEvent::Wave;
        break;
    case WindowEventType::PortalMove:
        pFunc = &CWindowEvent::Portal;
        break;

    case WindowEventType::END:
        break;
    default:
        break;
    }
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

void CWindowEvent::CircleMove(float _dt)
{
    Vec2 vPos;

    m_Theta += m_fSpeed*_dt;
    if (m_bCW) {
        vPos.x = m_Radius * cosf(m_Theta);
    }
    else {
        vPos.x = -m_Radius * cosf(m_Theta);
    }
    
    vPos.y = m_Radius * sinf(m_Theta);

    vPos -= m_vWinRes / 2.f;

    SetPos(vPos + m_vMonitorRes/2.f);

    SetRadius(m_Radius - _dt * m_fRDecSpeed);
    if (m_Radius <= 1.f) {
        m_fRDecSpeed = 0;
    }
}

void CWindowEvent::WindowQuake(float _dt)
{
    Vec2 vPos = GetPos();
    
    int x = rand() % m_QuakeAmount - m_QuakeAmount/2;
    int y = rand() % m_QuakeAmount - m_QuakeAmount / 2;

    vPos.x += x;
    vPos.y += y;

    SetPos(vPos);

}

void CWindowEvent::UpAndDown(float _dt)
{
    Vec2 vPos = m_vWinPos;
    Vec2 vRes = m_vWinRes;
    m_AccTime += _dt;

    if (m_Duration <= m_AccTime && m_curCount <= m_iUDCount) {
        SetTarget({ vPos.x, vRes.y + m_fUDSize },0.1f);
        m_fUDSize = -m_fUDSize;
        m_AccTime = 0;
        m_curCount++;
    }
    LinearMove(_dt);
}

void CWindowEvent::Jumping(float _dt)
{
    Vec2 vPos = m_vWinPos;
    if (!m_IsUp) {
        SetTarget({ vPos.x, vPos.y - m_fUDSize }, m_Duration);
        m_vOrigin = vPos;
        m_IsUp = true;
    }

    m_AccTime += _dt;
    if (m_Duration <= m_AccTime && !m_IsFall) {
        CCamera::GetInst()->BlinkIn(0.2f);
        SetTarget(m_vOrigin, m_Duration);
        m_IsFall = true;
    }
    
    LinearMove(_dt);
}

void CWindowEvent::Disapear(float _dt)
{
    m_AccTime += _dt;
    if (m_Duration <= m_AccTime && !m_IsUp) {
        
        SetPos({ m_vWinPos.x + m_Distance, m_vWinPos.y });
        SetTarget({ m_vWinPos.x, m_vOrigin.y }, m_Duration);
        m_AccTime = 0;
        m_IsUp = true;
    }
    LinearMove(_dt);
}

void CWindowEvent::Wave(float _dt)
{
    // y = asinbx
    // dy/dx = abcosbx
    float prevY = m_fUDSize * sinf(m_AccTime / m_fFrequency);


    m_AccTime += m_fSpeed * _dt;
    float x = m_AccTime;


    float y = m_fUDSize * sinf(x / m_fFrequency);
    float dy = y - prevY;
    //vPos += vDir * m_fSpeed * _dt;
    SetPos({ m_vWinPos.x + m_fSpeed *_dt, m_vWinPos.y + dy });
}

void CWindowEvent::Portal(float _dt)
{
    Vec2 vPos = m_vWinPos;

    if (m_vMonitorRes.x <= vPos.x) {
        SetPos({ 0 - m_vWinRes.x, vPos.y });
    }
    if (m_vMonitorRes.y <= vPos.y) {
        SetPos({ vPos.x, 0 - m_vWinRes.y });
    }

    if (vPos.x  <= - m_vWinRes.x) {
        SetPos({ m_vMonitorRes.x, m_vWinPos.y });
    }

    if (vPos.y <= -m_vWinRes.y) {
        SetPos({ m_vWinPos.x, m_vMonitorRes.y });
    }
    LinearMove(_dt);
}
