#include "pch.h"
#include "CWindowEvent.h"

#include "CEngine.h"
#include "Resource.h"

#include "CCamera.h"
#include "CPathMgr.h"

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
     m_vTarget = (m_vMonitorRes - m_vWinRes) * _target/100;

    if ((m_vTarget - GetPos()).Length() <= 1.f) {
        m_fSpeed = 0;
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
        pFunc = &CWindowEvent::LinearMove;
        break;

    case WindowEventType::CircleMove:
        pFunc = &CWindowEvent::CircleMove;
        break;

    case WindowEventType::Quake:
        m_vOrigin = m_vWinPos;
        if (m_IsFlash) {
            CCamera::GetInst()->BlinkIn(0.2f);
            m_IsFlash = false;
        }
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
        m_vOrigin = m_vWinPos * 100 / (m_vMonitorRes - m_vWinRes);
        SetTarget({ m_vOrigin.x, 200.f }, m_Duration);
        m_IsUp = false;
        pFunc = &CWindowEvent::Disappear;
        break;

    case WindowEventType::Wave:
        if (!m_IsPersist) {
            m_AccTime = 0;
            m_IsPersist = false;
        }
        pFunc = &CWindowEvent::Wave;
        break;
    case WindowEventType::PortalMove:
        pFunc = &CWindowEvent::Portal;
        break;

    case WindowEventType::END:
        pFunc = &CWindowEvent::Stop;
        break;

    default:
        break;
    }
}

void CWindowEvent::LinearMove(float _dt)
{
   
    if (m_fSpeed == 0) {
        if (m_IsFlash) {
            CCamera::GetInst()->BlinkIn(0.2f);
            m_IsFlash = false;
        }
        SetPos(m_vTarget);
        return;
    }

    Vec2 vPos = GetPos();
    if ((vPos - m_vTarget).Length() <= 10.f) {
        SetPos(m_vTarget);
        m_vTarget = GetPos();

        return;
    }
    

    Vec2 vDir = m_vTarget - vPos;
    vDir.Normalize();
    vPos += vDir * m_fSpeed * _dt;
    SetPos(vPos);

}

void CWindowEvent::CircleMove(float _dt)
{
    Vec2 vPos;

    m_Theta += m_fSpeed*_dt;
    if (m_bCW) {
        vPos.x = m_Radius * cosf(m_Theta) * m_vMonitorRes.y / 100;
    }
    else {
        vPos.x = -m_Radius * cosf(m_Theta) * m_vMonitorRes.y / 100;
    }
    
    vPos.y = m_Radius * sinf(m_Theta) * m_vMonitorRes.y / 100;

    vPos -= m_vWinRes / 2.f;

    SetPos(vPos + m_vMonitorRes/2.f);

    SetRadius(m_Radius - _dt * m_fRDecSpeed);
    if (m_Radius <= 1.f) {
        m_fRDecSpeed = 0;
    }
}

void CWindowEvent::WindowQuake(float _dt)
{
    Vec2 vPos = m_vOrigin;
    
    int x = rand() % m_QuakeAmount - m_QuakeAmount/2;
    int y = rand() % m_QuakeAmount - m_QuakeAmount / 2;

    vPos.x += x;
    vPos.y += y;

    SetPos(vPos);

}

void CWindowEvent::UpAndDown(float _dt)
{
    // 100 * m_vTarget  / (m_vMonitorRes - m_vWinRes) =  _target;
    Vec2 vPos = m_vTarget * 100 / (m_vMonitorRes - m_vWinRes);
    Vec2 vRes = m_vWinRes;
    m_AccTime += _dt;

    if (0.16f <= m_AccTime && m_curCount <= m_iUDCount) {
        SetTarget({ vPos.x , vPos.y + m_fUDSize },0.05f);
        m_fUDSize = -m_fUDSize;
        m_AccTime = 0;
        m_curCount++;
    }

    LinearMove(_dt);
}

void CWindowEvent::Jumping(float _dt)
{
    Vec2 vPos = m_vWinPos * 100 / (m_vMonitorRes - m_vWinRes);
    if (!m_IsUp) {
        SetTarget({ vPos.x, vPos.y - m_fUDSize }, m_Duration);
        m_vOrigin = vPos;
        m_IsUp = true;
        CCamera::GetInst()->BlinkIn(0.2f);
        m_IsFlash = true;
    }

    m_AccTime += _dt;

    if (m_Duration <= m_AccTime && !m_IsFall) {
        SetTarget(m_vOrigin, m_Duration);
        m_IsFall = true;
    }
    
    LinearMove(_dt);
}

void CWindowEvent::Disappear(float _dt)
{
    m_AccTime += _dt;
    if (m_DisappearDuration <= m_AccTime && !m_IsUp) {
        
        SetPos({ m_vWinPos.x + m_Distance * m_vMonitorRes.y / 100, m_vWinPos.y});
        SetTarget({ m_vOrigin.x + m_Distance, m_vOrigin.y }, m_Duration);
        m_AccTime = 0;
        m_IsUp = true;
    }
    LinearMove(_dt);
}

void CWindowEvent::Wave(float _dt)
{
    // y = asinbx
    // dy/dx = abcosbx
    float prevY = m_fUDSize * m_vMonitorRes.y / 1000 * sinf(m_AccTime / m_fFrequency);


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

void CWindowEvent::SetPortalDirection(Vec2 _dir)
{
    SetTarget(_dir);
}

void CWindowEvent::Stop(float _dt)
{
}

void CWindowEvent::LoadEventData(const wstring& _strRelativePath, list<WinInfo>& _out)
{
    wstring strFilePath = CPathMgr::GetContentPath();
    strFilePath += L"eventdata\\" + _strRelativePath;


    FILE* pFile = nullptr;

    _wfopen_s(&pFile, strFilePath.c_str(), L"r");

    _out.clear();

    if (nullptr == pFile) {

        LOG(ERR, L"이벤트 파일 열기 실패");
        return;
    }

    while (true) {

        wchar_t szRead[256] = {};
        if (EOF == fwscanf_s(pFile, L"%s", szRead, 256)) {
            break;
        }

        WinInfo info = {};

        if (!wcscmp(szRead, L"[LINEAR_MOVE]")) {
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[TYPE]")) {
                int type = 0;
                fwscanf_s(pFile, L"%d", &type);
                info.Type = (WindowEventType)type;
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[START_TIME]")) {
                fwscanf_s(pFile, L"%f", &info.StartTime);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[TARGET]")) {
                Vec2 target;
                fwscanf_s(pFile, L"%f", &target.x);
                fwscanf_s(pFile, L"%f", &target.y);
                info.Target = target;
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[SPEED]")) {
                fwscanf_s(pFile, L"%f", &info.Speed);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[FLASH]")) {
                fwscanf_s(pFile, L"%d", &info.Flash);
            }
            _out.push_back(info);
        }
        else if (!wcscmp(szRead, L"[CIRCLE_MOVE]")) {
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[TYPE]")) {
                int type = 0;
                fwscanf_s(pFile, L"%d", &type);
                info.Type = (WindowEventType)type;
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[START_TIME]")) {
                fwscanf_s(pFile, L"%f", &info.StartTime);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[THETA]")) {
                fwscanf_s(pFile, L"%f", &info.Theta);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[SPEED]")) {
                fwscanf_s(pFile, L"%f", &info.Speed);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[RADIUS]")) {
                fwscanf_s(pFile, L"%f", &info.Radius);
            }
            fwscanf_s(pFile, L"%s", szRead, 256); 
            if (!wcscmp(szRead, L"[CW]")) {
                fwscanf_s(pFile, L"%d", &info.CW);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[DECREASE]")) {
                fwscanf_s(pFile, L"%d", &info.Decrease);
            }
            _out.push_back(info);
        }
        else if (!wcscmp(szRead, L"[QUAKE_MOVE]")) {
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[TYPE]")) {
                int type = 0;
                fwscanf_s(pFile, L"%d", &type);
                info.Type = (WindowEventType)type;
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[START_TIME]")) {
                fwscanf_s(pFile, L"%f", &info.StartTime);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[QUAKE_AMOUNT]")) {
                fwscanf_s(pFile, L"%f", &info.QuakeAmount);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[FLASH]")) {
                fwscanf_s(pFile, L"%d", &info.Flash);
            }
            _out.push_back(info);
        }
        else if (!wcscmp(szRead, L"[UP_DOWN]")) {
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[TYPE]")) {
                int type = 0;
                fwscanf_s(pFile, L"%d", &type);
                info.Type = (WindowEventType)type;
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[START_TIME]")) {
                fwscanf_s(pFile, L"%f", &info.StartTime);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[TARGET]")) {
                Vec2 target;
                fwscanf_s(pFile, L"%f", &target.x);
                fwscanf_s(pFile, L"%f", &target.y);
                info.Target = target;
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[SPEED]")) {
                fwscanf_s(pFile, L"%f", &info.Speed);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[SIZE]")) {
                fwscanf_s(pFile, L"%f", &info.Size);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[COUNT]")) {
                fwscanf_s(pFile, L"%f", &info.Count);
            }
            _out.push_back(info);
        }
        else if (!wcscmp(szRead, L"[JUMPING]")) {
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[TYPE]")) {
                int type = 0;
                fwscanf_s(pFile, L"%d", &type);
                info.Type = (WindowEventType)type;
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[START_TIME]")) {
                fwscanf_s(pFile, L"%f", &info.StartTime);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[SIZE]")) {
                fwscanf_s(pFile, L"%f", &info.Size);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[SPEED]")) {
                fwscanf_s(pFile, L"%f", &info.Speed);
            }
            _out.push_back(info);
        }
        else if (!wcscmp(szRead, L"[DISAPPEAR]")) {
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[TYPE]")) {
                int type = 0;
                fwscanf_s(pFile, L"%d", &type);
                info.Type = (WindowEventType)type;
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[START_TIME]")) {
                fwscanf_s(pFile, L"%f", &info.StartTime);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[SIZE]")) {
                fwscanf_s(pFile, L"%f", &info.Size);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[SPEED]")) {
                 fwscanf_s(pFile, L"%f", &info.Speed);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[DURATION]")) {
                fwscanf_s(pFile, L"%f", &info.Duration);
            }
            _out.push_back(info);
        }
        else if (!wcscmp(szRead, L"[WAVE]")) {
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[TYPE]")) {
                int type = 0;
                fwscanf_s(pFile, L"%d", &type);
                info.Type = (WindowEventType)type;
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[START_TIME]")) {
                fwscanf_s(pFile, L"%f", &info.StartTime);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[SIZE]")) {
                fwscanf_s(pFile, L"%f", &info.Size);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[SPEED]")) {
                fwscanf_s(pFile, L"%f", &info.Speed);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[DURATION]")) {
                fwscanf_s(pFile, L"%f", &info.Duration);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[PERSIST]")) {
                fwscanf_s(pFile, L"%f", &info.CW);
            }
            _out.push_back(info);
            }
        else if (!wcscmp(szRead, L"[PORTAL]")) {
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[TYPE]")) {
                int type = 0;
                fwscanf_s(pFile, L"%d", &type);
                info.Type = (WindowEventType)type;
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[START_TIME]")) {
                fwscanf_s(pFile, L"%f", &info.StartTime);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[TARGET]")) {
                Vec2 target;
                fwscanf_s(pFile, L"%f", &target.x);
                fwscanf_s(pFile, L"%f", &target.y);
                info.Target = target;
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[SPEED]")) {
                fwscanf_s(pFile, L"%f", &info.Speed);
            }
            _out.push_back(info);
            }
        
    }
    
    fclose(pFile);

    return;
}
