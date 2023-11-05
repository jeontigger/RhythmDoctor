#pragma once
#include "CUI.h"

typedef void(*BtnCallBack)(void);
class CTextUI :
    public CUI
{
    GENERATED_OBJECT(CUI);

private:
    wstring m_Text;
    float m_fShowTime;
    float m_fHideTime;

    float m_AccTime;

    BtnCallBack m_CallBackFunc;
    struct fRGB {
        int r;
        int g;
        int b;
    };
    fRGB m_Color;

public:
    virtual void render(HDC _dc) override;
    virtual void finaltick(float _dt) override;
    void SetText(const wstring& _str) { m_Text = _str; }
    void SetBlink(float _showTime, float _hideTime) { m_fShowTime = _showTime; m_fHideTime = _hideTime; }

    void SetCallBack(BtnCallBack _CallBackFunc) { m_CallBackFunc = _CallBackFunc; }
    virtual void LBtnClicked(Vec2 _vMousePos) override;

public:
    void SetColor(int _r, int _g, int _b) { m_Color.r = _r; m_Color.g = _g; m_Color.b = _b; }

public:
    CLONE(CTextUI);
    CTextUI();
    CTextUI(const CTextUI& _Origin);
    ~CTextUI();


};

