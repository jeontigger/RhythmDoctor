#include "pch.h"
#include "CNormalBeat.h"

#include "CAnimator.h"
CNormalBeat::CNormalBeat()
{
	pAnimator = AddComponent<CAnimator>();
	/*pAtlas = CAssetMgr::GetInst()->LoadTexture(L"NormalBeat", L"texture\\NormalBeat.png");
	pAnimator->CreateAnimation(L"NormalBeat", pAtlas, Vec2(0, 0), Vec2(30, 40), Vec2(0, 0), 0.3f, 1);
	pAnimator->SaveAnimation(L"animdata");*/
	pAnimator->LoadAnimation(L"animdata\\NormalBeat.txt");
	pAnimator->Play(L"NormalBeat", true);
	this->Hide();
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
	if (m_Idx == -1) {
		return;
	}

	
	m_AccTime += _dt;
	m_ScaleAccTime += _dt;

	if (m_HideTime / 6 <= m_ScaleAccTime) {
		Animating(m_Idx);
		m_ScaleAccTime = 0;
		m_Idx++;
	}
	

	if (m_HideTime <= m_AccTime) {
		Hide();
		m_AccTime = 0;
	}

	if (6 <= m_Idx) {
		m_Idx = -1;
	}
}

void CNormalBeat::Play()
{
	pAnimator->Play(L"NormalBeat", false);
}

void CNormalBeat::Animating(int _idx)
{
	SetScale({ 30.f, 40.f * Magnificant[_idx] });
}