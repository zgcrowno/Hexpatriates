#pragma once

#include "Hexpatriates.h"
#include "Projectile.h"
#include "Laser.h"

namespace hexpatriates
{
    class LaserGate : public Projectile
    {
    private:
        //! Called on object creation
        virtual void OnCreate();
        //! Called on object deletion
        virtual void OnDelete();
        //! Called on object collision
        virtual orxBOOL OnCollide(
            ScrollObject *_poCollider,
            const orxSTRING _zPartName,
            const orxSTRING _zColliderPartName,
            const orxVECTOR &_rvPosition,
            const orxVECTOR &_rvNormal);
        //! Called on clock update
        virtual void Update(const orxCLOCK_INFO &_rstInfo);
    public:
        enum Placement
        {
            Left,
            Right,
            Top,
            Bottom
        };

        static constexpr float MinLaserGateLaserYScale = 0.2f;

        Placement m_placement;
        bool m_bIsAttached;
        bool m_bExpandingNear;
        float m_movementDirection;
        float m_openingSize;
        float m_laserExpansionSpeed;
        Laser *m_laserNear;
        Laser *m_laserFar;
    };
}
