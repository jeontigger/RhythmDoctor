#pragma once
#include "CNote.h"
class CBeatNote :
    public CNote
{
    GENERATED_OBJECT(CNote);

private:
    int m_loopCount;
    int m_curCount;
    float m_AccLoopTime;
    float m_LoopDuration;

public:
    void SetLoopDuration(float _duration) { m_LoopDuration = _duration; }
    void SetLoopCount(int _cnt) { m_loopCount = _cnt; }

public:
    virtual void Play() override;
    virtual void tick(float _dt) override;

public:
    CLONE(CBeatNote);
    CBeatNote();
    ~CBeatNote();
};

