#include "pch.h"
#include "CNormalBeat.h"

#include "CTexture.h"

#include "CAssetMgr.h"
#include "CAnimator.h"
CNormalBeat::CNormalBeat():
	m_Idx(-1)
{
	pAnimator = AddComponent<CAnimator>();
	CTexture* pAtlas;
	pAtlas = CAssetMgr::GetInst()->LoadTexture(L"NormalBeat", L"texture\\NormalBeat.png");
	pAnimator->CreateAnimation(L"NormalBeat", pAtlas, Vec2(0, 0), Vec2(36, 41), Vec2(0, 0), 0.02f, 9);
	pAnimator->SaveAnimation(L"animdata");
	pAnimator->LoadAnimation(L"animdata\\NormalBeat.txt");


}

CNormalBeat::~CNormalBeat()
{
}



void CNormalBeat::Show(float _duration)
{
	// 하이드타임을 프레임으로 나눈게 스케일 프레임duration
	// idx를 가짐
	m_Idx = 0;
	m_AccTime = 0;
	m_ScaleAccTime = 0;
	m_HideTime = _duration;
	Play();
	CObj::Show();
}

void CNormalBeat::tick(float _dt)
{
	if (m_HideTime <= 0) {
		return;
	}

	m_AccTime += _dt;

	if (m_HideTime <= m_AccTime) {
		Hide();
		m_AccTime = 0;
		m_HideTime = 0;
	}

}

void CNormalBeat::Play()
{
	pAnimator->Play(L"NormalBeat", false);
}
