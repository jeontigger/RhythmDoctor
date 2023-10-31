#include "pch.h"

#include "CGuidedProjectile.h"
#include "CLevel.h"
#include "CLevelMgr.h"
#include "CMonster.h"
#include "CTimeMgr.h"

#include "CCollider.h"

CGuidedProjectile::CGuidedProjectile()
    : target(nullptr), m_fMass(1.f), m_fRotateSpeed(PI) {}

CGuidedProjectile::CGuidedProjectile(const CGuidedProjectile& _Origin) :
    target(nullptr),
    m_fMass(_Origin.m_fMass),
    m_vAccel(_Origin.m_vAccel),
    m_vVelocity(_Origin.m_vVelocity),
    m_vForce(_Origin.m_vForce),
    m_vDir(_Origin.m_vDir),
    m_fRotateSpeed(_Origin.m_fRotateSpeed)
{
}

CGuidedProjectile::~CGuidedProjectile() {}

void CGuidedProjectile::begin() {
    Super::begin();
    GetCollider()->SetScale(GetScale());
}

void CGuidedProjectile::tick(float _dt) {
    Super::tick(_dt);
    if (!IsValid(target)) {
        FindTarget();
    }
    if (!IsValid(target)) {
        Vec2 vPos = GetPos();

        vPos.x += m_vDir.x * GetSpeed() * DT;
        vPos.y += m_vDir.y * GetSpeed() * DT;

        SetPos(vPos);
    } else {
        // Update_1();
        // Update_2();
        Update_3();
    }
}

void CGuidedProjectile::FindTarget() {

    CLevel*              pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
    const vector<CObj*>& vecMon = pCurLevel->GetObjects(LAYER::MONSTER);

    if (vecMon.empty()) {
        return;
    } else if (vecMon.size() == 1) {
        target = dynamic_cast<CMonster*>(vecMon.front());

        assert(target);
    } else {
        float fMax = 2000.f;

        for (size_t i = 0; i < vecMon.size(); ++i) {
            float fDistance = GetPos().Distance(vecMon[i]->GetPos());
            if (fMax > fDistance) {
                fMax = fDistance;

                target = dynamic_cast<CMonster*>(vecMon[i]);
                assert(target);
            }
        }
    }
}

void CGuidedProjectile::Update_1() {
    Vec2 vPos = GetPos();
    Vec2 vDir = target->GetPos() - vPos;
    vDir.Normalize();

    vPos.x += vDir.x * GetSpeed() * DT;
    vPos.y += vDir.y * GetSpeed() * DT;

    SetPos(vPos);
}

void CGuidedProjectile::Update_2() {
    float Force = 1000.f;
    Vec2  vForce = target->GetPos() - GetPos();
    vForce.Normalize() *= Force;

    m_vAccel = vForce / m_fMass;

    m_vVelocity += m_vAccel * DT;

    Vec2 vPos = GetPos();
    vPos += m_vVelocity * DT;

    SetPos(vPos);
}

void CGuidedProjectile::Update_3() {

    m_vDir.Normalize();

    // 목적지를 향하는 방향벡터
    Vec2 vDest = target->GetPos() - GetPos();
    vDest.Normalize();

    // 현재 진행 방향과 목적지를 향하는 방향을 내적해서 둘 사이의 각도를 구한다.
    // m_vDir 과 vDest 를 내적, vA ● vB == |vA| * |vB| * cos(@)
    float fDot = m_vDir.x * vDest.x + m_vDir.y * vDest.y;
    float fAngle = acosf(fDot);
    float pi = PI;
    float diff = (PI / 90.f);
    // 진행 방향과 목적지를 향하는 방향이 각도 1도 이내에 들어오면 더이상
    // 진행방향을 회전하지 않는다.
    if (fAngle > diff) {
        // 타겟을 향해서 방향을 회전한다.
        if (GetRotateClock(m_vDir, vDest)) {
            m_vDir = Rotate(m_vDir, m_fRotateSpeed * DT);
        } else {
            m_vDir = Rotate(m_vDir, -m_fRotateSpeed * DT);
        }
    } else {
        int a = 0;
    }

    // 현재 방향을 향해서 이동한다.
    float fSpeed = GetSpeed();
    m_vVelocity = m_vDir * fSpeed;

    Vec2 vPos = GetPos();
    vPos += m_vVelocity * DT;
    SetPos(vPos);
}

void CGuidedProjectile::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
    if (dynamic_cast<CMonster*> (_OtherObj)) {
        Destroy();
    }
}