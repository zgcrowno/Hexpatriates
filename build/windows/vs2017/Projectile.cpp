#include "Projectile.h"
#include "ArenaBound.h"
#include "SceneArena.h"

using namespace hexpatriates;

void Projectile::OnCreate()
{
    PlayerSpecific::OnCreate();

    m_bIsBouncy = GetBool("IsBouncy", GetModelName());
    m_tethered = GetBool("Tethered", GetModelName());
    m_speed = GetFloat("Speed", GetModelName());
    orxVECTOR speedRef = GetSpeed();
    SetSpeed({ speedRef.fX * m_speed, speedRef.fY * m_speed});

    //TODO: Instead of using joints, I may just adopt the projectile's parent's speed in the update function.
    if (m_tethered)
    {
        // Attach the Projectile and its associated gun together with a joint.
        m_parentGun = orxOBJECT(orxStructure_GetOwner(orxSPAWNER(orxObject_GetOwner(GetOrxObject()))));
        orxBODY *gunBody = (orxBODY*)_orxStructure_GetPointer(_orxObject_GetStructure(m_parentGun, orxSTRUCTURE_ID_BODY), orxSTRUCTURE_ID_BODY);
        orxBODY *projectileBody = (orxBODY*)GetStructure(orxSTRUCTURE_ID_BODY);
        orxBody_AddJointFromConfig(projectileBody, gunBody, "J-Weld");
    }
    //else
    //{
    //    // Setting parent to arena so the projectiles pause along with it.
    //    SceneArena *arena = static_cast<SceneArena*>(Hexpatriates::GetInstance().GetArena());
    //    SetOwner(arena);
    //}
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
        orxVECTOR reflectionVector = ReflectionVector(NormalizeVector(GetSpeed()), _rvNormal);
        SetSpeed({ reflectionVector.fX * m_speed, reflectionVector.fY * m_speed });
    }
    
    return orxTRUE;
}

void Projectile::Update(const orxCLOCK_INFO &_rstInfo)
{
    // If it's tethered, ensure that the Projectile is destroyed if its parent gun is disabled.
    if (m_tethered && !orxObject_IsEnabled(m_parentGun))
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
