#pragma once

#include "Hexpatriates.h"
#include "Pilot.h"
#include "Scene.h"
#include "ArenaBounds.h"

namespace hexpatriates
{
    /// <summary>Represents an arena in which two pilots battle.</summary>
    class SceneArena : public Scene
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

        void SetTimerText();
        void CreateMeterBorder(const std::string _meterName, const ScrollMod *_meter, const int &_clipSize);
    public:
        bool m_bIsPausedForContraction;
        //! The amount of time, in seconds, remaining until the round automatically ends.
        float m_timer;
        float m_matchTime;
        float m_contractionSpeed;
        //! The scale of the arena, to be determined by match time.
        orxVECTOR m_targetScalePilotP1;
        orxVECTOR m_targetScalePilotP2;
        orxVECTOR m_targetScale1PilotP1;
        orxVECTOR m_targetScale2PilotP1;
        orxVECTOR m_targetScale3PilotP1;
        orxVECTOR m_targetScale1PilotP2;
        orxVECTOR m_targetScale2PilotP2;
        orxVECTOR m_targetScale3PilotP2;
        ArenaBounds *m_bounds;
        Pilot *m_pilotP1;
        Pilot *m_pilotP2;
        ScrollMod *m_livesMeterP1;
        ScrollMod *m_superMeterP1;
        ScrollMod *m_livesMeterP2;
        ScrollMod *m_superMeterP2;
        ScrollMod *m_timerText;
        //! Associated UI elements' default scales
        // TODO: At least for these default scales, I should probably put together a UI manager to handle data like this. OR, make fully fleshed out classes for these UI elements.
        orxVECTOR m_defaultScaleLives;
        orxVECTOR m_defaultScaleSuper;

        void PauseForContraction(bool _pause);
        void CreateMeterBorders();
    };
}
