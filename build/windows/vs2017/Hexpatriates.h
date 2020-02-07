#pragma once

#ifndef __ORXSCROLL_H_
#define __ORXSCROLL_H_

//! Includes
// The following define skips compilation of ScrollEd (map editor) for now
#define __NO_SCROLLED__
#include "Scroll.h"
#include <vector>

namespace hexpatriates
{
    //! OrxScroll class
    class Hexpatriates : public Scroll<Hexpatriates>
    {
    private:
        //! Enforce finding of config files outside of .exe folder
        virtual orxSTATUS Bootstrap() const;
        //! Initialize the program
        virtual orxSTATUS Init();
        //! Bind our scroll objects
        virtual void BindObjects();
        //! Callback called every frame
        virtual orxSTATUS Run();
        //! Exit the program
        virtual void Exit();
    public:
        virtual orxSTATUS PauseGame(orxBOOL _bPause);
        void PauseAction(orxBOOL _bPause);
        float GetMaxMatchTime();
        float GetRemainingMatchTime();
        ScrollObject *GetArena();
        ScrollObject *GetArenaBounds();
        ScrollObject *GetPartition();
        ScrollObject *GetScenePilotSelect();
        ScrollObject *GetPilotByPlayerType(const std::string _str);
        ScrollObject *GetCrosshairsByPlayerType(const std::string _str);
        ScrollObject *GetNearestProjectileByPlayerType(const ScrollObject *_obj, const std::string _type);
        ScrollObject *GetMostPressingProjectileByPlayerType(const ScrollObject *_obj, const std::string _type, const std::string _otherType);
        std::vector<ScrollObject*> GetProjectilesByPlayerType(const std::string _type);
        std::vector<ScrollObject*> GetFamiliarsByPlayerType(const std::string _str);
    };
}

#endif // __ORXSCROLL_H_
