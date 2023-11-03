#pragma once
#include "CLevel.h"
class CStageSelectLevel : public CLevel {

private:
    class CBackground* m_BG;

  public:
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};
