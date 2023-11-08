#pragma once
#include "CObj.h"

constexpr int StartPoint[6] = { 20, 40, 60, 80, 100, 120 };
constexpr int NoteSize = 15;

class CUnitBar :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:
    vector<class CJudgeBar*> m_vecBars;
    class CCharacter* m_Character;
    class CHeart* m_Heart;
    vector<class CNormalBeat*>m_NormalBeats;

public:
    void HideBar(int _idx, float _duration);
    void ShowNormalBeat(int _idx, float _duration);
public:
    virtual void begin() override;
    virtual void tick(float _dt) override;

public:
    CLONE_DISABLE(CUnitBar);
    CUnitBar();
    ~CUnitBar();

};

