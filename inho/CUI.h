﻿#pragma once
#include "CObj.h"
class CUI :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    vector<CUI*> m_vecChildUI;
    CUI* m_ParentUI;
    Vec2 m_vFinalPos;

    class CTransform* m_Transform;

    bool m_bMouseOn;
    bool m_bMouseOn_Prev;

    bool m_bMouseLBtnDown;

public:
    void AddChildUI(CUI* _ChildUI) {
        m_vecChildUI.push_back(_ChildUI);
        _ChildUI->m_ParentUI = this;
    }

public:
    virtual Vec2 GetRenderPos() { return CCamera::GetInst()->GetRenderPos(m_vFinalPos); }
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;
    virtual void finaltick(float _dt) override;
    virtual void begin() override;

    virtual void OnHovered(Vec2 _vMousePos) {}
    virtual void MouseOn(Vec2 _vMousePos) {}
    virtual void OnUnHovered(Vec2 _MousePos) {}

    virtual void LBtnDown(Vec2 _vMousePos) {}
    virtual void LBtnUp(Vec2 _vMousePos) {}
    virtual void LBtnClicked(Vec2 _vMousePos) {}

public:
    Vec2 GetFinalPos() { return m_vFinalPos; }
    bool IsLBtnDown() { return m_bMouseLBtnDown; }

public:
    void MoveTo(Vec2 _point, float _time = 0) { m_Transform->MoveTo(_point, _time); }

public:
    virtual CUI* Clone() = 0;
    CUI();
    CUI(const CUI& _Origin);
    ~CUI();

    friend class CUIMgr;
};

