#pragma once

#include "Hexpatriates.h"
#include "MenuItem.h"
#include "Scene.h"
#include <vector>

namespace hexpatriates
{
    class SceneMenu : public Scene
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
        int m_selectedItemIndex;
        int m_selectedItemIndexP2;
        std::string m_transition = ""; // The scene transition object we'll use to jump from one SceneMenu to another scene.
        std::vector<MenuItem*> m_menuItems;
    };
}
