#pragma once

#include "Hexpatriates.h"
#include "ScrollMod.h"
#include <vector>
#include <map>

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
            Move,
            Jump,
            Fall,
            Dash,
            Parry,
            Melee,
            Downstab,
            FireNeutral,
            FireUpward,
            FireDownward,
            FireSuper
        };

        // TODO: This is used purely for my own bookkeeping at this point. Remove this enum once I'm finished using it.
        // Enum representing the various considerations that inform an action's utility score.
        enum ConsiderationType
        {
            Position,
            Trajectory,
            ZoneInhabited,
            NumLives,
            DashAvailable,
            ParryAvailable,
            MeleeAvailable,
            IFramesStatus,
            ContaminationStatus,
            ConstructionStatus,
            ShipStatus,
            GroundedStatus,
            WallTouchStatus,
            NeutralAvailable,
            UpwardAvailable,
            DownwardAvailable,
            SuperAvailable,
            LeftWallProximity,
            RightWallProximity,
            CeilingProximity,
            FloorProximity,
            ArenaElectrificationStatus,
            OpposingProjectileTrajectories,
            OpposingProjectilePositions,
            OpposingPilotTrajectory,
            OpposingPilotPosition
        };

        static std::map<std::string, ActionType> M_ActionSerializationMap;
        // TODO: This is used purely for my own bookkeeping at this point. Remove this map once I'm finished using it.
        static std::map<ActionType, std::vector<ConsiderationType>> M_ConsiderationMap;

        // What type of action is this?
        ActionType m_actionType;
        // Number used to multiply function results in the Score method in order to guarantee greater differences in associated UBucket utilities.
        int m_granularity;
        //The returned y-value of the logit function is 0 at x = 0.5, so we want logitX to always be equal to at least 0.5.
        const float m_logitXMin = 0.5f;
        // Generally speaking, how important is this action?
        float m_weight;
        // Generally speaking, how likely is an agent to deviate from this action once they're already engaged in it?
        float m_momentum;
        // What considerations inform the importance of this action?
        std::vector<ConsiderationType> m_considerations;
    };
}
