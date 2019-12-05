#pragma once

#include "Hexpatriates.h"
#include "ScrollMod.h"
#include "Spawner.h"

namespace hexpatriates
{
    /// <summary>Represents a vessel which is operated by a Pilot.</summary>
    class Ship : public ScrollMod
    {
    protected:
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
        Spawner *m_neutralGun;
        Spawner *m_upwardGun;
        Spawner *m_downwardGun;
        Spawner *m_superGun;
    };
}
