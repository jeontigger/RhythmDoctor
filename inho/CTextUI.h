#pragma once
#include "CUI.h"
class CTextUI :
    public CUI
{
    GENERATED_OBJECT(CUI);

private:
    wstring m_Text;
    float m_fShowTime;
    float m_fHideTime;

    float m_AccTime;

public:
    virtual void render(HDC _dc) override;
    virtual void finaltick(float _dt) override;
    void SetText(const wstring& _str) { m_Text = _str; }
    void SetBlink(float _showTime, float _hideTime) { m_fShowTime = _showTime; m_fHideTime = _hideTime; }

public:
    CLONE(CTextUI);
    CTextUI();
    CTextUI(const CTextUI& _Origin);
    ~CTextUI();


};

