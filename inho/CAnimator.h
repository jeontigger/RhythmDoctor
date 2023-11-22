#pragma once
#include "CComponent.h"

class CAnim;
class CTexture;

class CAnimator :
    public CComponent
{
private:
    map<wstring, CAnim*> m_mapAnim;

    CAnim* m_CurAnim;

    bool  m_bRepeat;

    float m_AccTime;
    float m_Duration;
    wstring m_WaitName;
    bool m_WaitRepeat;

public:
    void WaitPlay(const wstring& _strName, bool _b, float _time) { m_WaitName = _strName; m_WaitRepeat = _b; m_AccTime = 0; m_Duration = _time; }
    void Play(const wstring& _strName, bool _bRepeat);
    void Stop();

    CAnim* FindAnim(const wstring& _strName);
    void CreateAnimation(const wstring& _strName, CTexture* _Altas, Vec2 _vLeftTop, Vec2 _vCutSize,
        Vec2 _vOffset, float _duration, int _MaxFrm);

    void SaveAnimation(const wstring& _strRelativePath);
    void LoadAnimation(const wstring& _strRelativePath);


public:
    virtual void finaltick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CAnimator);
    CAnimator(CObj* _Owner);
    CAnimator(const CAnimator& _Origin);
    ~CAnimator();

    friend class CHeart;
    friend class CNormalBeat;
};

