#include "LaserGate.h"

using namespace hexpatriates;

void LaserGate::OnCreate()
{
    Projectile::OnCreate();

    m_openingSize = GetFloat("OpeningSize", GetModelName());
    m_laserExpansionSpeed = GetFloat("LaserExpansionSpeed", GetModelName());
    m_laserNear = ScrollCast<Laser*>(CreateObject("O-LaserGateLaserNear" + m_typeName));
    m_laserFar = ScrollCast<Laser*>(CreateObject("O-LaserGateLaserFar" + m_typeName));
    m_laserNear->Enable(false);
    m_laserFar->Enable(false);
}

void LaserGate::OnDelete()
{
    Projectile::OnDelete();

    m_laserNear->Destroy();
    m_laserFar->Destroy();
}

orxBOOL LaserGate::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    Projectile::OnCollide(
        _poCollider,
        _zPartName,
        _zColliderPartName,
        _rvPosition,
        _rvNormal);

    // Wall collisions
    ArenaBound *arenaBound = dynamic_cast<ArenaBound*>(_poCollider);
    if (arenaBound != orxNULL)
    {
        if (m_bIsAttached)
        {
            m_movementDirection += orxMATH_KF_PI;
            SetSpeed({ orxMath_Cos(m_movementDirection) * m_speed, orxMath_Sin(m_movementDirection) * m_speed });
        }
        else
        {
            AttachToBound(arenaBound, _rvPosition, _rvNormal);
        }
    }

    return orxTRUE;
}

void LaserGate::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);

    // Handle laser positioning
    switch (m_placement)
    {
    case Placement::Left:
        m_laserNear->SetPosition({ GetPosition().fX + (GetScaledSize().fX / 2), GetPositionNextFrame(_rstInfo.fDT).fY });
        m_laserFar->SetPosition({ m_laserNear->GetPosition().fX + m_laserNear->GetScaledSize().fY + m_laserFar->GetScaledSize().fY + m_openingSize, m_laserNear->GetPosition().fY });
        break;
    case Placement::Right:
        m_laserNear->SetPosition({ GetPosition().fX - (GetScaledSize().fX / 2), GetPositionNextFrame(_rstInfo.fDT).fY });
        m_laserFar->SetPosition({ m_laserNear->GetPosition().fX - m_laserNear->GetScaledSize().fY - m_laserFar->GetScaledSize().fY - m_openingSize, m_laserNear->GetPosition().fY });
        break;
    case Placement::Top:
        m_laserNear->SetPosition({ GetPositionNextFrame(_rstInfo.fDT).fX, GetPosition().fY + (GetScaledSize().fY / 2) });
        m_laserFar->SetPosition({ m_laserNear->GetPosition().fX, m_laserNear->GetPosition().fY + m_laserNear->GetScaledSize().fY + m_laserFar->GetScaledSize().fY + m_openingSize });
        break;
    case Placement::Bottom:
        m_laserNear->SetPosition({ GetPositionNextFrame(_rstInfo.fDT).fX, GetPosition().fY - (GetScaledSize().fY / 2) });
        m_laserFar->SetPosition({ m_laserNear->GetPosition().fX, m_laserNear->GetPosition().fY - m_laserNear->GetScaledSize().fY - m_laserFar->GetScaledSize().fY - m_openingSize });
        break;
    }

    // Handle laser scaling
    if (m_bIsAttached)
    {
        if (m_bExpandingNear)
        {
            m_laserNear->SetScale({ m_laserNear->GetScale().fX, orxCLAMP(m_laserNear->GetScale().fY + (m_laserExpansionSpeed * _rstInfo.fDT), MinLaserGateLaserYScale, 10000.0f) });
            m_laserFar->SetScale({ m_laserFar->GetScale().fX, orxCLAMP(m_laserFar->GetScale().fY - (m_laserExpansionSpeed * _rstInfo.fDT), MinLaserGateLaserYScale, 10000.0f) });
            
            if (m_laserNear->GetScale().fY > MinLaserGateLaserYScale)
            {
                m_laserNear->Enable(true);
            }
            if (m_laserFar->GetScale().fY <= MinLaserGateLaserYScale)
            {
                m_laserFar->Enable(false);
                m_bExpandingNear = false;
            }
        }
        else
        {
            m_laserFar->SetScale({ m_laserFar->GetScale().fX, orxCLAMP(m_laserFar->GetScale().fY + (m_laserExpansionSpeed * _rstInfo.fDT), MinLaserGateLaserYScale, 10000.0f) });
            m_laserNear->SetScale({ m_laserNear->GetScale().fX, orxCLAMP(m_laserNear->GetScale().fY - (m_laserExpansionSpeed * _rstInfo.fDT), MinLaserGateLaserYScale, 10000.0f) });

            if (m_laserFar->GetScale().fY > MinLaserGateLaserYScale)
            {
                m_laserFar->Enable(true);
            }
            if (m_laserNear->GetScale().fY <= MinLaserGateLaserYScale)
            {
                m_laserNear->Enable(false);
                m_bExpandingNear = true;
            }
        }
    }
}

void LaserGate::AttachToBound(const ArenaBound *_arenaBound, const orxVECTOR &_attachPosition, const orxVECTOR &_attachNormal)
{
    Projectile::AttachToBound(_arenaBound, _attachPosition, _attachNormal);

    m_bIsAttached = true;
    float normalDirection = orxMath_ATan(_attachNormal.fY, _attachNormal.fX);
    m_movementDirection = normalDirection - orxMATH_KF_PI_BY_2;
    SetRotation(normalDirection + orxMATH_KF_PI_BY_2);
    SetSpeed({ orxMath_Cos(m_movementDirection) * m_speed, orxMath_Sin(m_movementDirection) * m_speed });
    m_laserNear->Enable(true);
    m_laserFar->Enable(true);
    m_laserNear->SetRotation(GetRotation());
    m_laserFar->SetRotation(GetRotation());

    if (orxString_Compare(_arenaBound->GetModelName().c_str(), "O-WallLeftWall") == 0)
    {
        m_laserNear->SetRotation(orxMATH_KF_PI_BY_2);
        m_laserFar->SetRotation(orxMATH_KF_PI_BY_2);
        m_placement = Placement::Left;
    }
    else if (orxString_Compare(_arenaBound->GetModelName().c_str(), "O-WallRightWall") == 0)
    {
        m_laserNear->SetRotation(-orxMATH_KF_PI_BY_2);
        m_laserFar->SetRotation(-orxMATH_KF_PI_BY_2);
        m_placement = Placement::Right;
    }
    else if (orxString_Compare(_arenaBound->GetModelName().c_str(), "O-WallCeiling") == 0)
    {
        m_laserNear->SetRotation(orxMATH_KF_PI);
        m_laserFar->SetRotation(orxMATH_KF_PI);
        m_placement = Placement::Top;
    }
    else //orxString_Compare(_poCollider->GetModelName(), "O-WallFloor" == 0)
    {
        m_placement = Placement::Bottom;
    }
}
