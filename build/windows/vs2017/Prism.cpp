#include "Prism.h"
#include "Laser.h"

using namespace hexpatriates;

void Prism::OnCreate()
{
    Projectile::OnCreate();

    m_waveSize = GetFloat("WaveSize", GetModelName());

    orxCHAR gunText[512] = "O-PrismGun";
    m_gun = ScrollCast<Spawner*>(GetChildByName(gunText + m_typeName));
}

void Prism::OnDelete()
{
    Projectile::OnDelete();
}

orxBOOL Prism::OnCollide(
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
    
    if (dynamic_cast<Laser*>(_poCollider) != NULL)
    {
        FireWave();
    }

    return orxTRUE;
}

void Prism::Update(const orxCLOCK_INFO &_rstInfo)
{
    Projectile::Update(_rstInfo);
}

void Prism::FireWave()
{
    for (int i = 0; i < m_waveSize; i++)
    {
        m_gun->SpawnAtSelf(GetRotation() + (i * (orxMATH_KF_2_PI / m_waveSize)));
    }
}
