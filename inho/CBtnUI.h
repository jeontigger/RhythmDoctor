#pragma once
#include "CUI.h"

class CTexture;

typedef void(*BtnCallBack)(void);
typedef void(CEntity::* DelegateFunc)(void);

class CBtnUI :
    public CUI
{
    GENERATED_OBJECT(CUI);

private:
    CTexture* m_NormalImg;
    CTexture* m_HoverImg;
    CTexture* m_PressedImg;
    CTexture* m_CurImg;

    BtnCallBack m_CallBackFunc;

    CEntity* m_Inst;
    DelegateFunc m_Delegate;

public:
    void SetNormalImg(CTexture* _NormalImg) { m_NormalImg = _NormalImg; }
    void SetPressedImg(CTexture* _PressedImg) { m_PressedImg = _PressedImg; }
    void SetHoverImg(CTexture* _HoverImg) { m_CurImg = _HoverImg; }
    void SetCallBack(BtnCallBack _CallBackFunc) { m_CallBackFunc = _CallBackFunc; }
    void SetDelegate(CEntity* _Inst, DelegateFunc _Func) { m_Inst = _Inst; m_Delegate = _Func; }


public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    virtual void OnHovered(Vec2 _vMousePos) override;
    virtual void OnUnHovered(Vec2 _vMousePos) override;
    virtual void MouseOn(Vec2 _vMousePos) override;

    virtual void LBtnDown(Vec2 _vMousePos) override;
    virtual void LBtnUp(Vec2 _vMousePos) override;
    virtual void LBtnClicked(Vec2 _vMousePos) override;

public:
    CLONE(CBtnUI);
    CBtnUI();
    ~CBtnUI();

};

