﻿#include "pch.h"

#include "CCamera.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAssetMgr.h"
#include "CTexture.h"

CCamera::CCamera():
    m_Veil(nullptr),
    m_BlinkAlpha(0.f),
    m_VeilAlpha(0.f)
{
    Vec2 vResol = CEngine::GetInst()->GetResolution();
    m_Veil = CAssetMgr::GetInst()->CreateTexture(L"VeilTex", vResol.x, vResol.y);
    m_Blink = CAssetMgr::GetInst()->LoadTexture(L"BlinkTex", L"texture\\Blink.png");
}

CCamera::~CCamera() {}

void CCamera::tick() {

    float m_Speed = 400.f;

    if (m_bUseCamera) {
        if (KEY_PRESSED(LEFT)) {
            m_vLookAt.x -= m_Speed * DT;
        }

        if (KEY_PRESSED(RIGHT)) {
            m_vLookAt.x += m_Speed * DT;
        }

        if (KEY_PRESSED(UP)) {
            m_vLookAt.y -= m_Speed * DT;
        }

        if (KEY_PRESSED(DOWN)) {
            m_vLookAt.y += m_Speed * DT;
        }
    }
    
    if (KEY_TAP(_8)) {
        m_bUseCamera = !m_bUseCamera;
    }
    

    Vec2 vDir = m_TargetAt - m_vLookAt;
    if (vDir.Length() <= 5.f) {
        m_vLookAt = m_TargetAt;
   
    }
    else {
        vDir.Normalize();

        m_vLookAt += vDir * m_LinearSpeed * DT;
    }

    


    Vec2 vResolution = CEngine::GetInst()->GetResolution();
    Vec2 vCenter = vResolution / 2.f;

    m_vDiff = m_vLookAt - vCenter;

    if (m_EventList.empty())
        return;

    FCamEvent& evnt = m_EventList.front();

    if (evnt.type == CAM_EFFECT::FADE_IN) {

        evnt.AccTime += DT;

        if (evnt.Duration <= evnt.AccTime) {
            m_VeilAlpha = 0;
            m_EventList.pop_front();
        }
        else {
            float fRatio = evnt.AccTime / evnt.Duration;
            float alpha = 1.f - fRatio;
            m_VeilAlpha = (UINT)(alpha * 255);
        }
    }

    else if (evnt.type == CAM_EFFECT::FADE_OUT) {

        evnt.AccTime += DT;

        if (evnt.Duration <= evnt.AccTime) {
            m_EventList.pop_front();
            m_VeilAlpha = 255;
        }
        else {
            float fRatio = evnt.AccTime / evnt.Duration;
            float alpha = fRatio;
            m_VeilAlpha = (UINT)(alpha * 255);
        }
    }

    else if (evnt.type == CAM_EFFECT::BLINK_IN) {

        evnt.AccTime += DT;

        if (evnt.Duration <= evnt.AccTime) {
            m_BlinkAlpha = 0;
            m_EventList.pop_front();
        }
        else {
            float fRatio = evnt.AccTime / evnt.Duration;
            float alpha = 1.f - fRatio;
            m_BlinkAlpha = (UINT)(alpha * 255);
        }
    }
    else if (evnt.type == CAM_EFFECT::BLINK_OUT) {

        evnt.AccTime += DT;

        if (evnt.Duration <= evnt.AccTime) {
            m_EventList.pop_front();
            m_BlinkAlpha = 255;
        }
        else {
            float fRatio = evnt.AccTime / evnt.Duration;
            float alpha = fRatio;
            m_BlinkAlpha = (UINT)(alpha * 255);
        }
    }
}

void CCamera::render(HDC _dc)
{
    if (0 == m_VeilAlpha && 0 == m_BlinkAlpha)
        return;

    BLENDFUNCTION blend = {};
    blend.BlendOp = AC_SRC_OVER;
    blend.BlendFlags = 0;
    blend.SourceConstantAlpha = m_VeilAlpha;
    blend.AlphaFormat = 0;

    /*AlphaBlend(_dc
        , 0, 0, m_Veil->GetWidth(), m_Veil->GetHeight()
        , m_Veil->GetDC()
        , 0, 0
        , m_Veil->GetWidth(), m_Veil->GetHeight()
        , blend);*/

    blend.SourceConstantAlpha = m_BlinkAlpha;

    AlphaBlend(_dc
        , 0, 0,CEngine::GetInst()->GetResolution().x, CEngine::GetInst()->GetResolution().y
        , m_Blink->GetDC()
        , 0, 0
        , m_Blink->GetWidth(), m_Blink->GetHeight()
        , blend);
}

void CCamera::SetLinearLookAt(Vec2 _vLookAt, float _time)
{
    m_TargetAt = _vLookAt;
    m_LinearSpeed = (m_vLookAt - m_TargetAt).Length() / _time;
}
