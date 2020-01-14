#pragma once

#include "Hexpatriates.h"
#include "PlayerSpecific.h"
#include "ArenaBound.h"

namespace hexpatriates
{
    class Projectile : public PlayerSpecific
    {
    protected:
        //! Called on object creation
        virtual void OnCreate();
        //! Called on object deletion
        virtual void OnDelete() = 0;
        //! Called on object collision
        virtual orxBOOL OnCollide(
            ScrollObject *_poCollider,
            const orxSTRING _zPartName,
            const orxSTRING _zColliderPartName,
            const orxVECTOR &_rvPosition,
            const orxVECTOR &_rvNormal);
        //! Called on clock update
        virtual void Update(const orxCLOCK_INFO &_rstInfo);
        virtual void AttachToBound(const ArenaBound *_arenaBound, const orxVECTOR &_attachPosition, const orxVECTOR &_attachNormal);
    public:
        bool m_bIsBouncy;
        bool m_bRotateOnCollision;
        bool m_tethered;
        float m_parrySpeedModifier;
        float m_speed;
        orxOBJECT *m_parentGun;
        orxOBJECT *m_parentPilot;
    };
}
