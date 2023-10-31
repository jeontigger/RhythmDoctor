#include "pch.h"
#include "CUIMgr.h"

#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CUI.h"

#include "CLogMgr.h"

CUIMgr::CUIMgr():
	m_FocusedUI(nullptr)
{}

CUIMgr::~CUIMgr() {}

void CUIMgr::tick() {

	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	bool bLBtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnReleased = KEY_RELEASED(KEY::LBTN);


	CLevel* pLevel = CLevelMgr::GetInst()->GetCurLevel();
	if (nullptr == pLevel)
		return;

	CLayer* pUILayer = pLevel->GetLayer(LAYER::UI);
	vector<CObj*>& vecUI = pUILayer->m_vecObjects;
	vector<CObj*>::reverse_iterator iter = vecUI.rbegin();
	
	for (iter; iter != vecUI.rend(); ++iter) {
		CUI* pUI = dynamic_cast<CUI*>(*iter);
		if (nullptr == pUI)
		{
			LOG(ERR, L"UI Layer에 UI가 아닌 오브젝트가 들어있음");
			continue;
		}

		if (pUI->m_bMouseOn) {

			m_FocusedUI = pUI;
			pUI = GetPriorityCheck(pUI);

			if (pUI->m_bMouseOn_Prev != pUI->m_bMouseOn) {
				pUI->OnHovered(vMousePos);
			}
			else {
				pUI->MouseOn(vMousePos);
			}

			if (bLbtnReleased) {
				pUI->LBtnUp(vMousePos);

				if (pUI->m_bMouseLBtnDown) {
					pUI->LBtnClicked(vMousePos);
				}
			}

			if (bLBtnTap) {
				pUI->LBtnDown(vMousePos);
				pUI->m_bMouseLBtnDown = true;

				std::advance(iter, 1);
				vecUI.erase(iter.base());

				vecUI.push_back(m_FocusedUI);
			}

			if (bLbtnReleased) {
				pUI->m_bMouseLBtnDown = false;
			}

			break;
		}
		else {
			if (pUI->m_bMouseOn_Prev != pUI->m_bMouseOn) {
				pUI->OnUnHovered(vMousePos);
			}

			if (bLbtnReleased) {
				pUI->m_bMouseLBtnDown = false;
			}
		}
	}
}

CUI* CUIMgr::GetPriorityCheck(CUI* _ParentUI)
{
	CUI* pPriorityUI = nullptr;

	static list<CUI*> queue;
	queue.clear();

	queue.push_back(_ParentUI);


	while (!queue.empty()) {
		CUI* pUI = queue.front();
		queue.pop_front();

		for (size_t i = 0; i < pUI->m_vecChildUI.size(); ++i) {
			queue.push_back(pUI->m_vecChildUI[i]);
		}

		if (pUI->m_bMouseOn) {
			pPriorityUI = pUI;
		}
	}

	return pPriorityUI;
}
