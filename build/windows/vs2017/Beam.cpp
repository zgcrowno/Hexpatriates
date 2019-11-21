#include "Beam.h"
#include <iostream>

using namespace hexpatriates;

void Beam::OnCreate()
{
    Projectile::OnCreate();

    // Attach the Beam and its associated gun together with a joint.
    m_parentGun = orxOBJECT(orxStructure_GetOwner(orxSPAWNER(orxObject_GetOwner(GetOrxObject()))));
    orxBODY *gunBody = (orxBODY*)_orxStructure_GetPointer(_orxObject_GetStructure(m_parentGun, orxSTRUCTURE_ID_BODY), orxSTRUCTURE_ID_BODY);
    orxBODY *projectileBody = (orxBODY*)GetStructure(orxSTRUCTURE_ID_BODY);
    orxBody_AddJointFromConfig(projectileBody, gunBody, "J-Weld");
}

void Beam::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL Beam::OnCollide(
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

    return orxTRUE;
}

void Beam::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);

    // Ensure that the Beam is destroyed if its parent gun is disabled.
    if (!orxObject_IsEnabled(m_parentGun))
    {
        Destroy();
    }
}
