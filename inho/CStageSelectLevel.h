#pragma once
#include "CLevel.h"

constexpr int Stage_YPosValue = 260;

class CStageSelectLevel : public CLevel {

private:
    class CAnimUI* m_StageArrow;
    class CAnimUI* m_arrow[2];
    vector<class CStage*> m_vecStages;
    bool m_isSelect;
    class CBackground* m_Veil;

    Vec2 SpotlightPos;
    

private:
    int m_cursorIdx;
    void StageCursorNext();
    void StageCursorPrev();
    void StageSelect();
    void StageSelectCancel();

  public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;

public:
    CStageSelectLevel();
    ~CStageSelectLevel();
};
