#pragma once

#include "Hexpatriates.h"
#include "ScrollMod.h"
#include "InputHandler.h"

namespace hexpatriates
{
    // Using virtual inheritance for ScrollMod to prevent member ambiguity errors when also inheriting from InputHandler.
    class MenuItem : public virtual ScrollMod, public InputHandler
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
        // Represents whether the menu item is actually interactable or just potentially informative window dressing.
        bool m_bIsInteractable;
        bool m_bIsSelected;
        bool m_bIsSelectedP2;

        virtual void Select(const bool _p1);
        virtual void Deselect(const bool _p1);
        virtual void HandleInput(const std::string &_playerType);
    };
}
