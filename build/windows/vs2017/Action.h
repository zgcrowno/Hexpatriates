#pragma once

#include "Hexpatriates.h"
#include "ScrollMod.h"
#include <functional>
#include <vector>

namespace hexpatriates
{
    class Action : public virtual ScrollMod
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
        // Enum representing the various actions a pilot can take.
        enum ActionType
        {
            // Movement actions.
            MoveAggressively,
            MoveDefensively,
            DontMove,
            // Jump actions.
            Jump,
            DontJump,
            // Fall actions
            Fall,
            DontFall,
            // Other actions.
            DashAggressively,
            DashDefensively,
            Parry,
            Melee,
            Downstab,
            FireNeutral,
            FireUpward,
            FireDownward,
            FireSuper,
            DontAct
        };
        // Enum representing the various factors that go into scoring an action.
        enum Factor
        {
            NumLives,
            IFrames,
            ContaminationTimer,
            ConstructionTimer,
            NumProjectiles,
            PartitionDistanceX,
            MostPressingProjectileDistance,
            OpposingPilotDistance,
            OpposingPilotDistanceX,
            OpposingPilotDistanceY,
            NumOpposingProjectiles,
            RemainingMatchTime
        };

        // What type of action is this?
        ActionType m_actionType;
        // Number used to multiply function results in the Score method in order to guarantee greater differences in associated UBucket utilities.
        const int m_granularity = 100;
        // Generally speaking, how important is this action?
        float m_weight;
        // Generally speaking, how likely is an agent to deviate from this action once they're already engaged in it?
        float m_momentum;
        // The factors by which the action will be scored.
        std::vector<Factor> m_factors;
        // Map of the action's factors to their respective utility functions.
        std::map<Factor, std::function<int(float)>> m_utilityFunctionMap;

        // Returns the compensation value of the passed score (See David Mark's 2015 GDC talk).
        const float Compensate(const float &_score);
    };
}
