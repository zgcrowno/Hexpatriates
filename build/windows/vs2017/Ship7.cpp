#include "Ship7.h"

using namespace hexpatriates;

void Ship7::OnCreate()
{
    Ship::OnCreate();
}

void Ship7::OnDelete()
{
    Ship::OnDelete();
}

orxBOOL Ship7::OnCollide(
    ScrollObject *_poCollider,
    const orxSTRING _zPartName,
    const orxSTRING _zColliderPartName,
    const orxVECTOR &_rvPosition,
    const orxVECTOR &_rvNormal)
{
    Ship::OnCollide(
        _poCollider,
        _zPartName,
        _zColliderPartName,
        _rvPosition,
        _rvNormal);

    return true;
}

void Ship7::Update(const orxCLOCK_INFO &_rstInfo)
{
    Ship::Update(_rstInfo);
}

void Ship7::FireNeutral()
{
    for (int i = 0; i < m_waveSizeNeutral; i++)
    {
        m_neutralGun->SpawnAtSelf(m_enemyDirection);
    }
}

void Ship7::FireUpward()
{
    for (int i = 0; i < m_waveSizeUpward; i++)
    {
        m_upwardGun->SpawnAtSelf(-orxMATH_KF_PI_BY_8 - copysignf(1, cosf(m_enemyDirection)) * (i * orxMATH_KF_PI_BY_8));
    }
}

void Ship7::FireDownward()
{
    for (int i = 0; i < m_waveSizeDownward; i++)
    {
        m_downwardGun->SpawnAtSelf(orxMATH_KF_PI_BY_4);
    }
}

void Ship7::FireSuper()
{
    for (int i = 0; i < m_waveSizeSuper; i++)
    {
        m_superGun->SpawnAtSelf(m_enemyDirection);
    }
}
