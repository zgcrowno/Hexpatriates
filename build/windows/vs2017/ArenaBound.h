#pragma once

#include "Hexpatriates.h"
#include "ScrollMod.h"

namespace hexpatriates
{
    /// <summary>Represents an arena in which two pilots battle.</summary>
    class ArenaBound : public ScrollMod
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
        ScrollObject *m_electricityIconP1;
        ScrollObject *m_electricityIconP2;
    };
}
