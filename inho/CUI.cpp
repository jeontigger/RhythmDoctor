﻿#include "pch.h"
#include "CUI.h"

#include "CKeyMgr.h"
#include "CTransform.h"

CUI::CUI():
	m_ParentUI(nullptr),
	m_bMouseOn(false),
	m_bMouseOn_Prev(false),
	m_bMouseLBtnDown(false)
{
	m_Transform = AddComponent<CTransform>(L"Transform");
}

CUI::CUI(const CUI& _Origin):
	CObj(_Origin),
	m_ParentUI(nullptr),
	m_bMouseOn(false),
	m_bMouseOn_Prev(false),
	m_bMouseLBtnDown(false)
{
	for (size_t i = 0; i < _Origin.m_vecChildUI.size(); ++i) {
		AddChildUI(_Origin.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	for (size_t i = 0; i < m_vecChildUI.size(); i++) {
		delete m_vecChildUI[i];
	}
}

void CUI::tick(float _DT)
{
	Super::tick(_DT);

	m_vFinalPos = GetPos();

	if (nullptr != m_ParentUI) {
		m_vFinalPos += m_ParentUI->GetFinalPos();
	}

	m_bMouseOn_Prev = m_bMouseOn;

	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + GetScale().x
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + GetScale().y) {
		m_bMouseOn = true;
	}
	else {
		m_bMouseOn = false;
	}

	for (size_t i = 0; i < m_vecChildUI.size(); i++) {
		m_vecChildUI[i]->tick(_DT);
	}
}

void CUI::render(HDC _dc)
{
	Super::render(_dc);

	for (size_t i = 0; i < m_vecChildUI.size(); i++) {
		m_vecChildUI[i]->render(_dc);
	}
}

void CUI::finaltick(float _dt)
{
	const vector<CComponent*> components = GetComponentAll();
	for (int i = 0; i < components.size(); i++) {
		components[i]->finaltick(_dt);
	}
	for (int i = 0; i < m_vecChildUI.size(); ++i) {
		m_vecChildUI[i]->finaltick(_dt);
	}
}

void CUI::begin()
{
	m_Transform->SetTargetPoint(GetPos());
}
