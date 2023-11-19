#include "pch.h"
#include "CObjEvent.h"

#include "CPathMgr.h"

#include "CObj.h"

CObjEvent::CObjEvent()
{
}

CObjEvent::~CObjEvent()
{
}

void CObj::SetFadeAway(float _duration)
{
    m_AccTime = 0;
    m_Duration = _duration;
    pFunc = &CObj::FadeAway;
}
void CObj::FadeAway(float _dt)
{
    m_AccTime += _dt;
    if (m_AccTime <= m_Duration) {
        float alpha = m_InitAlpha - 255 * (m_AccTime / m_Duration);
        SetAlpha(alpha);
        if (alpha <= 3.f) {
            SetAlpha(0);
        }
    }
}

void CObj::SetMove(Vec2 _target, float _time)
{
    if (_time == 0) {
        pFunc = nullptr;
        SetPos(_target);
    }

    m_Target = _target;

    m_Speed = (m_Target - m_Pos).Length() / _time;
    pFunc = &CObj::Move;
}


void CObj::SetScaleMove(Vec2 _target, float _time)
{
    if (_time == 0) {
        pFunc = nullptr;
        SetPos(_target);
    }

    m_ScaleTarget = _target;

    m_ScaleSpeed = (m_ScaleTarget - m_Scale).Length() / _time;
}


void CObj::Move(float _dt)
{
    Vec2 vPos = m_Pos;
    if ((vPos - m_Target).Length() <= 1.f) {
        SetPos(m_Target);
        if (m_ScaleTarget.x != -1)
            SetScale(m_ScaleTarget);
        return;
    }

    Vec2 vDir = m_Target - vPos;
    vDir.Normalize();
    vPos += vDir * m_Speed * _dt;
    SetPos(vPos);


    Vec2 vScale = m_Scale;
    vDir = m_ScaleTarget - vScale;
    if (m_ScaleTarget.x == -1 || vDir.Length() <= 1.f)
        return;

    vDir.Normalize();
    vScale += vDir * m_ScaleSpeed * _dt;
    SetScale(vScale);
}

int CObjEvent::SelectObj(const wchar_t* szRead)
{
    int res = -1;
    if (!wcscmp(szRead, L"HAND")) {
        return (UINT)StageObj::Hand;
    }
    else if (!wcscmp(szRead, L"BAR")) {
        return (UINT)StageObj::Bar;
    }
    else if (!wcscmp(szRead, L"TING")) {
        return (UINT)StageObj::Ting;
    }
    else if (!wcscmp(szRead, L"COLE")) {
        return (UINT)StageObj::Cole;
    }
    else if (!wcscmp(szRead, L"BVEIL")) {
        return (UINT)StageObj::BVeil;
    }
    else if (!wcscmp(szRead, L"MVEIL")) {
        return (UINT)StageObj::MVeil;
    }
    else if (!wcscmp(szRead, L"TVEIL")) {
        return (UINT)StageObj::TVeil;
    }
    else if (!wcscmp(szRead, L"TINGBG")) {
        return (UINT)StageObj::TingBG;
    }
    else if (!wcscmp(szRead, L"COLEBG")) {
        return (UINT)StageObj::ColeBGFront;
    }
    else if (!wcscmp(szRead, L"BOSS")) {
        return (UINT)StageObj::Boss;
    }
    else if (!wcscmp(szRead, L"STAGE")) {
        return (UINT)StageObj::Stage;
    }
    else if (!wcscmp(szRead, L"TINGBGOPEN")) {
        return (UINT)StageObj::TingBGOpen;
    }
    else if (!wcscmp(szRead, L"NOISE")) {
        return (UINT)StageObj::Noise;
    }
    else if (!wcscmp(szRead, L"BLUESKY")) {
        return (UINT)StageObj::BlueSky;
    }
    else if (!wcscmp(szRead, L"GLITCH")) {
        return (UINT)StageObj::Glitch;
    }
    else if (!wcscmp(szRead, L"HOSPITAL")) {
        return (UINT)StageObj::Hospital;
    }
    return -1;
}

void CObjEvent::LoadEventData(const wstring& _strRelativePath, list<ObjInfo>& _out)
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

        ObjInfo info = {};

        
        if (!wcscmp(szRead, L"[MOVE]")) {
            info.Type = ObjEventType::Moving;
            fwscanf_s(pFile, L"%s", szRead, 256);
            info.Obj = (StageObj)SelectObj(szRead);

            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[START_TIME]")) {
                fwscanf_s(pFile, L"%f", &info.StartTime);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[TARGET]")) {
                Vec2 target;
                fwscanf_s(pFile, L"%f", &target.x);
                fwscanf_s(pFile, L"%f", &target.y);
                info.Pos = target;
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[SPEED]")) {
                fwscanf_s(pFile, L"%f", &info.Speed);
            }
            _out.push_back(info);
        }
        else if (!wcscmp(szRead, L"[SCALE]")) {
             info.Type = ObjEventType::Scale;
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"MVEIL")) {
                info.Obj = StageObj::MVeil;
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
                info.Scale = target;
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[SPEED]")) {
                fwscanf_s(pFile, L"%f", &info.Speed);
            }
            _out.push_back(info);
        }
        else if (!wcscmp(szRead, L"[BARMOVE]")) {
            info.Type = ObjEventType::BarMoving;
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[START_TIME]")) {
                fwscanf_s(pFile, L"%f", &info.StartTime);
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
        else if (!wcscmp(szRead, L"[SHOW]")) {
            info.Type = ObjEventType::Show;
            fwscanf_s(pFile, L"%s", szRead, 256);
            info.Obj = (StageObj)SelectObj(szRead);
            fwscanf_s(pFile, L"%d", &info.Show);
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[START_TIME]")) {
                fwscanf_s(pFile, L"%f", &info.StartTime);
            }
            _out.push_back(info);
        }
        else if (!wcscmp(szRead, L"[ANIM]")) {
            info.Type = ObjEventType::Animation;
            fwscanf_s(pFile, L"%s", szRead, 256);
            info.Obj = (StageObj)SelectObj(szRead);
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[START_TIME]")) {
                fwscanf_s(pFile, L"%f", &info.StartTime);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[NAME]")) {
                fwscanf_s(pFile, L"%s", szRead, 256);
                info.Str = szRead;
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[DURATION]")) {
                fwscanf_s(pFile, L"%f", &info.Duration);
            }
             _out.push_back(info);
        }
        else if (!wcscmp(szRead, L"[BLINK_OUT]")) {
            info.Type = ObjEventType::BlinkOut;
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[START_TIME]")) {
                fwscanf_s(pFile, L"%f", &info.StartTime);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[DURATION]")) {
                fwscanf_s(pFile, L"%f", &info.Duration);
            }
            _out.push_back(info);
        }
        else if (!wcscmp(szRead, L"[BLINK_IN]")) {
            info.Type = ObjEventType::BlinkIn;
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[START_TIME]")) {
                fwscanf_s(pFile, L"%f", &info.StartTime);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[DURATION]")) {
                fwscanf_s(pFile, L"%f", &info.Duration);
            }
            _out.push_back(info);
        }
        else if (!wcscmp(szRead, L"[FADE_OUT]")) {
            info.Type = ObjEventType::FadeOut;
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[START_TIME]")) {
                fwscanf_s(pFile, L"%f", &info.StartTime);
            }
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[DURATION]")) {
                fwscanf_s(pFile, L"%f", &info.Duration);
            }
            _out.push_back(info);
            }
    }

    fclose(pFile);

    return;

}

void CObjEvent::Play()
{
}

void CObjEvent::tick(float _dt)
{
}
