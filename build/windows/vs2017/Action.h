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

        //The returned y-value of the logit function is 0 at x = 0.5, so we want logitX to always be equal to at least 0.5.
        static float M_LogitXMin;

        static const float Compensate(const float &_score, const int _numFactors);

        // What type of action is this?
        ActionType m_actionType;
        // Number used to multiply function results in the Score method in order to guarantee greater differences in associated UBucket utilities.
        const int m_granularity = 100;
        // Generally speaking, how important is this action?
        float m_weight;
        // Generally speaking, how likely is an agent to deviate from this action once they're already engaged in it?
        float m_momentum;
        // The function to which we feed the action's normalized utility at the end of an agent's ScoreAction method.
        std::function<int(float)> m_function;
    };
}
