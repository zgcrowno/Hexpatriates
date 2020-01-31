#pragma once

#include "Hexpatriates.h"
#include "ScrollMod.h"
#include "RCurve.h"

namespace hexpatriates
{
    class Context : public virtual ScrollMod
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
        // A collection of all of the context's non-mutually-exclusive RCurves.
        std::vector<RCurve*> m_rCurves;
    };
}
