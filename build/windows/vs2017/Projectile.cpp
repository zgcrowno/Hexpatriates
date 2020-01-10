#include "Projectile.h"
#include "ArenaBound.h"
#include "SceneArena.h"

using namespace hexpatriates;

void Projectile::OnCreate()
{
    PlayerSpecific::OnCreate();

    m_bIsBouncy = GetBool("IsBouncy", GetModelName());
    m_bRotateOnCollision = GetBool("RotateOnCollision", GetModelName());
    m_tethered = GetBool("Tethered", GetModelName());
    m_speed = GetFloat("FSpeed", GetModelName());
    orxVECTOR speedRef = GetSpeed();
    SetSpeed({ speedRef.fX * m_speed, speedRef.fY * m_speed});

    if (m_tethered)
    {
        m_parentGun = orxOBJECT(orxStructure_GetOwner(orxSPAWNER(orxObject_GetOwner(GetOrxObject()))));
        m_parentPilot = orxOBJECT(orxObject_GetParent(orxOBJECT(orxObject_GetParent(m_parentGun))));
    }
}

void Projectile::OnDelete()
{

}

orxBOOL Projectile::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    // Bounce off of bounds, if appropriate.
    if (m_bIsBouncy && dynamic_cast<ArenaBound*>(_poCollider) != NULL)
    {
        orxVECTOR normalizedSpeed = NormalizeVector(GetSpeed());
        orxVECTOR reflectionVector = ReflectionVector(normalizedSpeed, _rvNormal);
        SetSpeed({ reflectionVector.fX * m_speed, reflectionVector.fY * m_speed });
        if (m_bRotateOnCollision)
        {
            float angleDifference = AngleBetweenVectors(normalizedSpeed, reflectionVector);
            SetRotation(GetRotation() + angleDifference);
        }
    }
    
    return orxTRUE;
}

void Projectile::Update(const orxCLOCK_INFO &_rstInfo)
{
    // If it's tethered, ensure that the Projectile is destroyed if its parent gun is disabled.
    if (m_tethered)
    {
        if (!orxObject_IsEnabled(m_parentGun))
        {
            Destroy();
        }
        else
        {
            orxVECTOR parentCurPos = orxVECTOR_0;
            orxObject_GetWorldPosition(m_parentGun, &parentCurPos);
            orxVECTOR parentCurSpeed = orxVECTOR_0;
            // Check for null pointer just in case the spawning gun isn't attached to a ship.
            if (m_parentPilot != nullptr)
            {
                // Getting speed of pilot, since speed of gun and ship register as 0.
                orxObject_GetSpeed(m_parentPilot, &parentCurSpeed);
                orxVECTOR parentPosNextFrame = { parentCurPos.fX + parentCurSpeed.fX *_rstInfo.fDT, parentCurPos.fY + parentCurSpeed.fY * _rstInfo.fDT, parentCurPos.fZ + parentCurSpeed.fZ * _rstInfo.fDT };

                SetPosition(parentPosNextFrame, true);
            }
        }
    }
    // Destroy any projectile which exits the bounds of the screen.
    if (IsOffCamera("MainCamera"))
    {
        Destroy();
    }
}

// TODO: Keep an eye on this, because once I have final sprites, I'll probably have to change whether I use scaledSize.fY or scaledSize.fX.
void Projectile::AttachToBound(const ArenaBound *_arenaBound, const orxVECTOR &_attachPosition, const orxVECTOR &_attachNormal)
{
    orxVECTOR scaledSize = GetScaledSize();
    std::string boundName = _arenaBound->GetModelName();
    orxVECTOR boundPos = _arenaBound->GetPosition();
    orxVECTOR boundScaledSize = _arenaBound->GetScaledSize();
    if (orxString_SearchString(boundName.c_str(), "Left") != nullptr)
    {
        SetPosition({ boundPos.fX + boundScaledSize.fX / 2 + scaledSize.fY / 2, _attachPosition.fY });
    }
    else if (orxString_SearchString(boundName.c_str(), "Right") != nullptr)
    {
        SetPosition({ boundPos.fX - boundScaledSize.fX / 2 - scaledSize.fY / 2, _attachPosition.fY });
    }
    else if (orxString_SearchString(boundName.c_str(), "Ceiling") != nullptr)
    {
        SetPosition({ _attachPosition.fX, boundPos.fY + boundScaledSize.fY / 2 + scaledSize.fY / 2 });
    }
    else // orxString_SearchString(boundName.c_str(), "Floor") != nullptr
    {
        SetPosition({ _attachPosition.fX, boundPos.fY - boundScaledSize.fY / 2 - scaledSize.fY / 2 });
    }
}
