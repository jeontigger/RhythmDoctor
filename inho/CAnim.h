#pragma once
#include "CEntity.h"

class CTexture;
class CAnimator;

struct FFrame {
    Vec2 vLeftTop;
    Vec2 vCutSize;
    Vec2 vOffset;
    float Duration;
};


class CAnim :
    public CEntity
{
private:
    CAnimator* m_pAnimator;

    vector<FFrame> m_vecFrm;
    CTexture* m_Atlas;
    int m_iCurFrm;

    float m_AccTime;
    bool m_bFinish;

public:
    void finaltick();
    void render(HDC _dc);

public:
    void Create(const wstring& _strName, CTexture* _Atlas
        , Vec2 _vLeftTop, Vec2 _vCutSize, Vec2 _vOffset,  float _Duration, int _MaxFrm);

    bool IsFinish() { return m_bFinish; }

    void Reset() {
        m_AccTime = 0.f;
        m_iCurFrm = 0;
        m_bFinish = false;
    }

    bool Save(const wstring& _FilePath);
    bool Load(const wstring& _FilePath);

public:
    CLONE(CAnim);

    CAnim();
    ~CAnim();

    friend class CAnimator;
};

