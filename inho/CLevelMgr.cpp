#include "pch.h"

#include "CLevelMgr.h"

#include "CCamera.h"
#include "CEngine.h"

#include "CLevel.h"
#include "CStageSelectLevel.h"
#include "CStagePlayLevel.h"
#include "CStartMenuLevel.h"
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

    m_arrLevels[(UINT)LEVEL_TYPE::START_MENU_LEVEL] = new CStartMenuLevel;
    m_arrLevels[(UINT)LEVEL_TYPE::EDITOR_LEVEL] = new CEditorLevel;
    m_arrLevels[(UINT)LEVEL_TYPE::STAGE_SELECT_LEVEL] = new CStageSelectLevel;
    m_arrLevels[(UINT)LEVEL_TYPE::STAGE_PLAY_LEVEL] = new CStagePlayLevel;

    for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; i++) {
        m_arrLevels[i]->init();
    }

    ::ChangeLevel(LEVEL_TYPE::STAGE_PLAY_LEVEL);

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
    CPaletteMgr::GetInst()->SelectBrush(CPaletteMgr::BrushColor::BBLACK);
    Rectangle(_dc, -1, -1, ptResolution.x+1, ptResolution.y+1);

    m_pCurLevel->render(_dc);
    

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