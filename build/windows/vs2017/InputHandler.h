#pragma once

#include "Hexpatriates.h"
#include "ScrollMod.h"

namespace hexpatriates
{
    // Using virtual inheritance for ScrollMod to prevent member ambiguity errors when other classes inherit from both ScrollMod and InputHandler.
    class InputHandler : public virtual ScrollMod
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
        bool m_bAllowMultiInput;

        virtual void HandleInput(const std::string &_playerType) = 0;
    };
}
