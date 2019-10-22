#pragma once

#include "ScrollMod.h"

namespace hexpatriates
{
    class Spawner : public ScrollMod
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
        float m_fireRate;
        float m_maxFiringTime;
        float m_firingTime;
        orxSPAWNER *m_spawner;

        void Spawn(const float _rotation);
    };
}
