//! Includes
// The following define/undef is done only once in the project. It should be
// done before including the interface of the class deriving from
// Scroll (as follows).
#define __SCROLL_IMPL__
#include "Hexpatriates.h"
#include "ArenaBound.h"
#include "ArenaBounds.h"
#include "AudioManager.h"
#include "Beam.h"
#include "BeamPlacer.h"
#include "BeamSpouter.h"
#include "Crosshairs.h"
#include "Ember.h"
#include "Explosion.h"
#include "Familiar.h"
#include "Grenade.h"
#include "Laser.h"
#include "LaserGate.h"
#include "LaserHeatseeking.h"
#include "LaserPortalEntrance.h"
#include "LaserTeleportable.h"
#include "LaserWall.h"
#include "Legionnaire.h"
#include "MedussaHead.h"
#include "Missile.h"
#include "MissileShield.h"
#include "Orb.h"
#include "Pilot1.h"
#include "Pilot2.h"
#include "Pilot3.h"
#include "Pilot4.h"
#include "Pilot5.h"
#include "Pilot6.h"
#include "Pilot7.h"
#include "Pilot8.h"
#include "Prism.h"
#include "Scene.h"
#include "SceneArena.h"
#include "SceneMain.h"
#include "ScenePause.h"
#include "ScenePilotSelect.h"
#include "ScrollMod.h"
#include "Ship.h"
#include "Shrapnel.h"
#include "Shuttlecock.h"
#include "Spacer.h"
#include "Spawner.h"
#include "Turret.h"
#include "Zone.h"
#undef __SCROLL_IMPL__
#include <iostream>

using namespace hexpatriates;

orxSTATUS Hexpatriates::Bootstrap() const
{
    // Add "../data/config" to the list of locations from which config files can be loaded
    orxResource_AddStorage(orxCONFIG_KZ_RESOURCE_GROUP, "../data/config", orxFALSE);

    // Loads a specific config file
    orxConfig_Load("Hexpatriates.ini");

    return orxSTATUS_FAILURE;
}

orxSTATUS Hexpatriates::Init()
{
    orxSTATUS result = orxSTATUS_SUCCESS;

    // Instantiate game objects
    CreateObject("O-SceneMain");
    
    return result;
}

void Hexpatriates::BindObjects()
{
    ScrollBindObject<ArenaBound>("O-Wall");
    ScrollBindObject<ArenaBounds>("O-Walls");
    ScrollBindObject<Beam>("O-Beam");
    ScrollBindObject<BeamPlacer>("O-BeamPlacer");
    ScrollBindObject<BeamSpouter>("O-BeamSpouter");
    ScrollBindObject<Crosshairs>("O-Crosshairs");
    ScrollBindObject<Ember>("O-Ember");
    ScrollBindObject<Explosion>("O-Explosion");
    ScrollBindObject<Familiar>("O-Familiar");
    ScrollBindObject<Grenade>("O-Grenade");
    ScrollBindObject<Spawner>("O-Spawner");
    ScrollBindObject<Laser>("O-Laser");
    ScrollBindObject<LaserGate>("O-LaserGate");
    ScrollBindObject<LaserHeatseeking>("O-LaserHeatseeking");
    ScrollBindObject<LaserPortalEntrance>("O-LaserPortalEntrance");
    ScrollBindObject<LaserTeleportable>("O-LaserTeleportable");
    ScrollBindObject<LaserWall>("O-LaserWall");
    ScrollBindObject<Legionnaire>("O-Legionnaire");
    ScrollBindObject<MedussaHead>("O-MedussaHead");
    ScrollBindObject<Missile>("O-Missile");
    ScrollBindObject<MissileShield>("O-MissileShield");
    ScrollBindObject<Orb>("O-Orb");
    ScrollBindObject<Pilot1>("O-Pilot1");
    ScrollBindObject<Pilot2>("O-Pilot2");
    ScrollBindObject<Pilot3>("O-Pilot3");
    ScrollBindObject<Pilot4>("O-Pilot4");
    ScrollBindObject<Pilot5>("O-Pilot5");
    ScrollBindObject<Pilot6>("O-Pilot6");
    ScrollBindObject<Pilot7>("O-Pilot7");
    ScrollBindObject<Pilot8>("O-Pilot8");
    ScrollBindObject<Prism>("O-Prism");
    ScrollBindObject<Scene>("O-Scene");
    ScrollBindObject<SceneArena>("O-SceneArena");
    ScrollBindObject<SceneMain>("O-SceneMain");
    ScrollBindObject<ScenePause>("O-ScenePause");
    ScrollBindObject<ScenePilotSelect>("O-ScenePilotSelect");
    ScrollBindObject<ScrollMod>("O-ScrollMod");
    ScrollBindObject<Ship>("O-Ship");
    ScrollBindObject<Shrapnel>("O-Shrapnel");
    ScrollBindObject<Shuttlecock>("O-Shuttlecock");
    ScrollBindObject<Spacer>("O-Spacer");
    ScrollBindObject<Turret>("O-Turret");
    ScrollBindObject<Zone>("O-Zone");
}

orxSTATUS Hexpatriates::Run()
{
    return orxSTATUS_SUCCESS;
}

void Hexpatriates::Exit()
{
}

orxSTATUS Hexpatriates::PauseGame(orxBOOL _bPause)
{
    for (ScrollObject *poObject = GetNextObject(); poObject; poObject = GetNextObject(poObject))
    {
        if (poObject->TestFlags(ScrollObject::FlagPausable))
        {
            poObject->Pause(_bPause);
        }
    }
    orxPhysics_EnableSimulation(!_bPause);
    if (_bPause)
    {
        CreateObject("O-ToScenePause");
    }

    return orxSTATUS_SUCCESS;
}

ScrollObject *Hexpatriates::GetArena()
{
    return GetNextObject<SceneArena>();
}

ScrollObject *Hexpatriates::GetArenaBounds()
{
    return GetNextObject<ArenaBounds>();
}

ScrollObject *Hexpatriates::GetPilotByPlayerType(const std::string _str)
{
    // Doing it this way because I can't explicitly return a pointer to an abstract class (Pilot).
    for (Pilot1 *pilot = GetNextObject<Pilot1>(); pilot != orxNULL; pilot = GetNextObject<Pilot1>(pilot))
    {
        if (orxString_SearchString(pilot->GetModelName().c_str(), _str.c_str()) != orxNULL)
        {
            return pilot;
        }
    }
    for (Pilot2 *pilot = GetNextObject<Pilot2>(); pilot != orxNULL; pilot = GetNextObject<Pilot2>(pilot))
    {
        if (orxString_SearchString(pilot->GetModelName().c_str(), _str.c_str()) != orxNULL)
        {
            return pilot;
        }
    }
    for (Pilot3 *pilot = GetNextObject<Pilot3>(); pilot != orxNULL; pilot = GetNextObject<Pilot3>(pilot))
    {
        if (orxString_SearchString(pilot->GetModelName().c_str(), _str.c_str()) != orxNULL)
        {
            return pilot;
        }
    }
    for (Pilot4 *pilot = GetNextObject<Pilot4>(); pilot != orxNULL; pilot = GetNextObject<Pilot4>(pilot))
    {
        if (orxString_SearchString(pilot->GetModelName().c_str(), _str.c_str()) != orxNULL)
        {
            return pilot;
        }
    }
    for (Pilot5 *pilot = GetNextObject<Pilot5>(); pilot != orxNULL; pilot = GetNextObject<Pilot5>(pilot))
    {
        if (orxString_SearchString(pilot->GetModelName().c_str(), _str.c_str()) != orxNULL)
        {
            return pilot;
        }
    }
    for (Pilot6 *pilot = GetNextObject<Pilot6>(); pilot != orxNULL; pilot = GetNextObject<Pilot6>(pilot))
    {
        if (orxString_SearchString(pilot->GetModelName().c_str(), _str.c_str()) != orxNULL)
        {
            return pilot;
        }
    }
    for (Pilot7 *pilot = GetNextObject<Pilot7>(); pilot != orxNULL; pilot = GetNextObject<Pilot7>(pilot))
    {
        if (orxString_SearchString(pilot->GetModelName().c_str(), _str.c_str()) != orxNULL)
        {
            return pilot;
        }
    }
    for (Pilot8 *pilot = GetNextObject<Pilot8>(); pilot != orxNULL; pilot = GetNextObject<Pilot8>(pilot))
    {
        if (orxString_SearchString(pilot->GetModelName().c_str(), _str.c_str()) != orxNULL)
        {
            return pilot;
        }
    }

    return orxNULL;
}

ScrollObject *Hexpatriates::GetCrosshairsByPlayerType(const std::string _str)
{
    for (Crosshairs *crosshairs = GetNextObject<Crosshairs>(); crosshairs != nullptr; crosshairs = GetNextObject<Crosshairs>(crosshairs))
    {
        if (orxString_SearchString(crosshairs->GetModelName().c_str(), _str.c_str()) != nullptr)
        {
            return crosshairs;
        }
    }

    return nullptr;
}

std::vector<ScrollObject*> Hexpatriates::GetFamiliarsByPlayerType(const std::string _str)
{
    std::vector<ScrollObject*> retVal;

    for (Familiar *familiar = GetNextObject<Familiar>(); familiar != orxNULL; familiar = GetNextObject<Familiar>(familiar))
    {
        if (orxString_SearchString(familiar->GetModelName().c_str(), _str.c_str()) != orxNULL)
        {
            retVal.push_back(familiar);
        }
    }

    return retVal;
}

int main(int argc, char **argv)
{
    // Executes game
    Hexpatriates::GetInstance().Execute(argc, argv);

    // Done!
    return EXIT_SUCCESS;
}
