#include "pch.h"

#include "CLevelMgr.h"

#include "CCamera.h"
#include "CEngine.h"

#include "CLevel.h"
#include "CPlayLevel.h"
#include "CStartLevel.h"
#include "CEditorLevel.h"

#include "CMonster.h"
#include "CPaletteMgr.h"
#include "CPlayer.h"
#include "CLogMgr.h"
#include "CCollisionMgr.h"

#include "CPlatform.h"

CLevelMgr::CLevelMgr():m_pCurLevel(nullptr) {}
CLevelMgr::~CLevelMgr() {
    for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; i++) {
        if (nullptr != m_arrLevels[i]) {
            delete m_arrLevels[i];
        }
    }
};


void CLevelMgr::init() {

    m_arrLevels[(UINT)LEVEL_TYPE::START_LEVEL] = new CStartLevel;
    m_arrLevels[(UINT)LEVEL_TYPE::EDITOR_LEVEL] = new CEditorLevel;
    m_arrLevels[(UINT)LEVEL_TYPE::PLAY_LEVEL] = new CPlayLevel;

    for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; i++) {
        m_arrLevels[i]->init();
    }

    ::ChangeLevel(LEVEL_TYPE::PLAY_LEVEL);

}

void CLevelMgr::tick() { 

    if (nullptr != m_pCurLevel) {
        m_pCurLevel->tick();
    }
}

void CLevelMgr::render(HDC _dc) {

    if (nullptr == m_pCurLevel)
        return;

    POINT ptResolution = CEngine::GetInst()->GetResolution();
    Rectangle(_dc, -1, -1, ptResolution.x, ptResolution.y);

    m_pCurLevel->render(_dc);
    CPaletteMgr::GetInst()->SelectBrush(CPaletteMgr::BrushColor::BWHITE);

    CLogMgr::GetInst()->tick(_dc);
}
void CLevelMgr::ChangeLevel(LEVEL_TYPE _Type)
{
    if (m_pCurLevel == m_arrLevels[(UINT)_Type])
        return;

    if (nullptr != m_pCurLevel)
        m_pCurLevel->exit();

    m_pCurLevel = m_arrLevels[(UINT)_Type];

    m_pCurLevel->enter();

    m_pCurLevel->begin();
}