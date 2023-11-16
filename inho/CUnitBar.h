﻿#pragma once
#include "CObj.h"

constexpr int StartPoint[9] = { 6, 23, 40, 57, 74, 91, 120, 130, 145 };
constexpr int NoteSize = 15;
enum class BeatPoint {
    one,
    two,
    three,
    four,
    five,
    six,
    Left,
    Correct,
    Right,
};
enum class JudgeBeatType {
    Left,
    Right,
    Correct,
    Miss
};
class CUnitBar :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:
    vector<class CJudgeBar*> m_vecBars;
    class CCharacter* m_Character;
    class CHeart* m_Heart;
    vector<class CNormalBeat*> m_NormalBeats;
    vector<class CNormalBeat*> m_IncorrectBeats;
    class CNormalBeat* m_CorrectBeat;

    class CGetSetBeat* m_GetSetBeat;

    class CCharacter* m_SpaceBarSprite;

    bool m_IsStart;
    bool m_IsMoving;
    float m_fSpeed;
    float m_fDuration;
    float m_AccTime;
    float m_fQuakeDuration;

    bool m_IsShow;

public:
    class CCharacter* GetSpaceBarSprite() { return m_SpaceBarSprite; }

public:
    void Start(bool _b) { m_IsStart = _b; }

    void SetMovingSpeed(float _speed) { m_fSpeed = _speed; }
    void SetMoving(bool _b) { m_IsMoving = _b; }
    void SetMovingDuration(float _duration) { m_fDuration = _duration; }

    void HideBar(int _idx, float _duration);
    void ShowNormalBeat(int _idx, float _duration);

public:
    void StayGetSetBeat();
    void GoGetSetBeat(float _speed);
    void HideAll();
    void ShowAll();
    bool IsShow() { return m_IsShow; }
    void ShowCharacter();
    void Incorrect(JudgeBeatType _type);
    void Correct();

public:
    virtual void begin() override;
    virtual void tick(float _dt) override;

public:
    CLONE_DISABLE(CUnitBar);
    CUnitBar();
    ~CUnitBar();

    friend class CGetSetBeat;

};

