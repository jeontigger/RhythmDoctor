#pragma once
#include "CLevel.h"

constexpr int Stage_YPosValue = 260;
class CStageSelectLevel : public CLevel {

private:
    class CAnimUI* m_StageArrow;
    vector<class CStage*> m_vecStages;
    

private:
    int m_cursorIdx;
    void StageCursorNext();
    void StageCursorPrev();

  public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;

public:
    CStageSelectLevel();
    ~CStageSelectLevel();
};
