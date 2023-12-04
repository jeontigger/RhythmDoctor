#include "pch.h"

#include "CTimeMgr.h"

#include "CEngine.h"

// 제일 큰 자료형 기준으로 같은 공간을 지칭하는 DataType 선언 방식
union MousePos {
    struct {
        short High;
        short Low;
    };

    UINT value;
};

CTimeMgr::CTimeMgr() : m_Frequency{}, m_PrevCount{}, m_CurCount{} {}

CTimeMgr::~CTimeMgr() {}

void CTimeMgr::init() {
    // 초당 빈도
    QueryPerformanceFrequency(&m_Frequency);

    QueryPerformanceCounter(&m_PrevCount);
}

void CTimeMgr::tick() {
    QueryPerformanceCounter(&m_CurCount);

    m_DeltaTime = float(m_CurCount.QuadPart - m_PrevCount.QuadPart) /
                  float(m_Frequency.QuadPart);

    m_PrevCount = m_CurCount;

    if ((1.f / 60.f) < m_DeltaTime)
        m_DeltaTime = (1.f / 60.f);

    m_fTime += m_DeltaTime;
    if (1.f <= m_fTime) {
        wchar_t szText[50] = {};
        swprintf_s(szText, 50, L"FPS [%d]", m_iCall);
        SetWindowText(CEngine::GetInst()->GetMainWind(), szText);

        m_iCall = 0;
        m_fTime = 0;
    }

    ++m_iCall;
}