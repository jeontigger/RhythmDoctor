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
        float alpha = 150 - 255 * (m_AccTime / m_Duration);
        SetAlpha(alpha);
        if (alpha <= 3.f) {
            SetAlpha(0);
        }
    }
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

        if (!wcscmp(szRead, L"[BAR]")) { 
            fwscanf_s(pFile, L"%s", szRead, 256);
            if (!wcscmp(szRead, L"[TYPE]")) {
                int type = 0;
                fwscanf_s(pFile, L"%d", &type);
                info.Type = (StageObj)type;
            }
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
