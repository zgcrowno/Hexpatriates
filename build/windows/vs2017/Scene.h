#pragma once

#include "Hexpatriates.h"
#include "ScrollMod.h"
#include <functional>

namespace hexpatriates
{
    class Scene : public ScrollMod
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
        static std::map<std::string, std::function<void()>> m_transitionBehaviorMap;

        static void TransitionToScene(const std::string &_toScene);
    };
}
