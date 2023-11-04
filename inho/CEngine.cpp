#include "pch.h"

#include "CEngine.h"

// Manager
#include "CPaletteMgr.h"
#include "CTimeMgr.h"
#include "CAssetMgr.h"
#include "CCamera.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CMonster.h"
#include "CPathMgr.h"
#include "CPlayer.h"
#include "CTaskMgr.h"

#include "CGCMgr.h"
#include "CUIMgr.h"
#include "CSoundMgr.h"

#include "CTexture.h"

CEngine::CEngine(): 
    m_hWnd(nullptr), 
    m_ptResolution{}, 
    m_dc(nullptr),
    m_bDebugRender(true) 

{}

CEngine::~CEngine() {
    ReleaseDC(m_hWnd, m_dc);
}

void CEngine::init(HWND _hWnd, POINT _ptResolution) {
    m_hWnd = _hWnd;
    ChangeWindowSize(_ptResolution, false);
    ShowWindow(m_hWnd, true);

    // DC : Device Context
    // pen : Black
    // brush : White
    // Bitmap(�׸� �׸� ��) : �ڵ鿡 �ش��ϴ�
    // ������ ��Ʈ��
    m_dc = GetDC(m_hWnd);

    m_SubTex = CAssetMgr::GetInst()->CreateTexture(L"SubTex", m_ptResolution.x, m_ptResolution.y);

    // Manager �ʱ�ȭ
    CTimeMgr::GetInst()->init();
    CPaletteMgr::GetInst()->init(m_SubTex->GetDC());
    CKeyMgr::GetInst()->init();
    CPathMgr::init();
    CSoundMgr::GetInst()->init();

    CLevelMgr::GetInst()->init();
}

void CEngine::tick() {
    // TimeMgr
    CTimeMgr::GetInst()->tick();
    CKeyMgr::GetInst()->tick();
    CCamera::GetInst()->tick();

    if (KEY_TAP(NUM8)) {
        m_bDebugRender = !m_bDebugRender;
    }

    CLevelMgr::GetInst()->tick();
    CCollisionMgr::GetInst()->tick();
    CUIMgr::GetInst()->tick();
    CLevelMgr::GetInst()->render(m_SubTex->GetDC());
    CCamera::GetInst()->render(m_SubTex->GetDC());

    BitBlt(CEngine::GetInst()->GetMainDC(),
        0, 0,
        m_ptResolution.x, m_ptResolution.y,
        m_SubTex->GetDC(),
        0, 0, SRCCOPY);

    CTaskMgr::GetInst()->tick();

    CGCMgr::GetInst()->tick();

    
}

HDC CEngine::GetSubDC()
{
     return m_SubTex->GetDC(); 
}

void CEngine::ChangeWindowSize(POINT _ptResolution, bool _bMenu)
{
    m_ptResolution = _ptResolution;

    RECT rt = { 0, 0, _ptResolution.x, _ptResolution.y };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
    int x = rt.right - rt.left;
    int y = rt.bottom - rt.top;
    SetWindowPos(m_hWnd, nullptr, 10, 10, (int)(rt.right - rt.left), (int)(rt.bottom - rt.top), 0);
}

