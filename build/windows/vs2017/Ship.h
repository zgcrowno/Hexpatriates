#pragma once

#include "Hexpatriates.h"
#include "PlayerSpecific.h"
#include "Spawner.h"

namespace hexpatriates
{
    /// <summary>Represents a vessel which is operated by a Pilot.</summary>
    class Ship : public PlayerSpecific
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
        //! Called on object separation
        virtual orxBOOL OnSeparate(ScrollObject *_poCollider);
        //! Called on clock update
        virtual void Update(const orxCLOCK_INFO &_rstInfo);
    public:
        bool m_bIsAgainstFloor;
        Spawner *m_neutralGun;
        Spawner *m_upwardGun;
        Spawner *m_downwardGun;
        Spawner *m_superGun;
    };
}
