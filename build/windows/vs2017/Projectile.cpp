#include "Projectile.h"

using namespace hexpatriates;

void Projectile::OnCreate()
{
    m_tethered = GetBool("Tethered", GetModelName());
    m_speed = GetFloat("Speed", GetModelName());
    orxVECTOR speedRef = orxVECTOR_0;
    GetSpeed(speedRef, orxFALSE);
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
