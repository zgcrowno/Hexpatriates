#pragma once

#include "Hexpatriates.h"
#include "ScrollMod.h"
#include "Action.h"

namespace hexpatriates
{
    class UBucket : public virtual ScrollMod
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
        // The actual size (width) of the UBucket.
        int m_size;
        // The inclusive upper bound of the UBucket.
        int m_edge;
        // The action tied to this UBucket.
        Action *m_action;
    };
}
