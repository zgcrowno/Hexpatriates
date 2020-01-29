#pragma once

#include "Hexpatriates.h"
#include "ScrollMod.h"
#include "RCurve.h"
#include <functional>
#include <vector>

namespace hexpatriates
{
    class Agent : public virtual ScrollMod
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
        virtual void SetActionMap();
    public:
        // A collection of all of the agent's non-mutually-exclusive RCurves.
        std::vector<RCurve*> m_rCurves;
        // A map of action types to actual actions/behaviors.
        std::map<Action::ActionType, std::function<void()>> m_actionMap;

        void CalculateUtilities();
        void Act();
        // Score the action by summing the scores of its associated considerations.
        int ScoreAction(Action *_action);
    };
}
