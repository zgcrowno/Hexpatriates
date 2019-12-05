#pragma once

#include "Hexpatriates.h"
#include "Projectile.h"

namespace hexpatriates
{
    class Ember : public Projectile
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
        int m_possibleSwayDirections[2] = { 1, -1 };
        float m_fallSpeed;
        float m_swaySpeed;
        float m_swayTime;
        float m_maxSwayTime;
        orxVECTOR m_movementDirection;
    };
}

