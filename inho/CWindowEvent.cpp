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
}
