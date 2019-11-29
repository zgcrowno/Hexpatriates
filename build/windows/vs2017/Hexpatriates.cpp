//! Includes
// The following define/undef is done only once in the project. It should be
// done before including the interface of the class deriving from
// Scroll (as follows).
#define __SCROLL_IMPL__
#include "Hexpatriates.h"
#include "Arena.h"
#include "Beam.h"
#include "Explosion.h"
#include "Familiar.h"
#include "Laser.h"
#include "LaserHeatseeking.h"
#include "LaserPortalEntrance.h"
#include "LaserWall.h"
#include "MainMenu.h"
#include "Menu.h"
#include "Orb.h"
#include "Pilot.h"
#include "PilotSelectMenu.h"
#include "Prism.h"
#include "Ship1.h"
#include "Ship2.h"
#include "Ship3.h"
#include "Ship4.h"
#include "Ship5.h"
#include "Ship6.h"
#include "Ship7.h"
#include "Ship8.h"
#include "Spawner.h"
#include "Turret.h"
#include "Zone.h"
#undef __SCROLL_IMPL__

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
    CreateObject("O-MainMenu");
    
    return result;
}

void Hexpatriates::BindObjects()
{
    ScrollBindObject<Arena>("O-Arena");
    ScrollBindObject<Beam>("O-Beam");
    ScrollBindObject<Explosion>("O-Explosion");
    ScrollBindObject<Familiar>("O-Familiar");
    ScrollBindObject<Spawner>("O-Spawner");
    ScrollBindObject<Laser>("O-Laser");
    ScrollBindObject<LaserHeatseeking>("O-LaserHeatseeking");
    ScrollBindObject<LaserPortalEntrance>("O-LaserPortalEntrance");
    ScrollBindObject<LaserWall>("O-LaserWall");
    ScrollBindObject<MainMenu>("O-MainMenu");
    ScrollBindObject<Menu>("O-Menu");
    ScrollBindObject<Orb>("O-Orb");
    ScrollBindObject<Pilot>("O-Pilot");
    ScrollBindObject<PilotSelectMenu>("O-PilotSelectMenu");
    ScrollBindObject<Prism>("O-Prism");
    ScrollBindObject<Ship1>("O-Ship1");
    ScrollBindObject<Ship2>("O-Ship2");
    ScrollBindObject<Ship3>("O-Ship3");
    ScrollBindObject<Ship4>("O-Ship4");
    ScrollBindObject<Ship5>("O-Ship5");
    ScrollBindObject<Ship6>("O-Ship6");
    ScrollBindObject<Ship7>("O-Ship7");
    ScrollBindObject<Ship8>("O-Ship8");
    ScrollBindObject<Turret>("O-Turret");
    ScrollBindObject<Zone>("O-Zone");
}

orxSTATUS Hexpatriates::Run()
{
    orxSTATUS result = orxSTATUS_SUCCESS;

    if (orxInput_HasBeenActivated("Quit"))
    {
        result = orxSTATUS_FAILURE;
    }

    return result;
}

void Hexpatriates::Exit()
{
}

ScrollObject *Hexpatriates::GetPilotByPlayerType(const orxCHAR *_str)
{
    for (Pilot *pilot = GetNextObject<Pilot>(); pilot != orxNULL; pilot = GetNextObject<Pilot>(pilot))
    {
        if (orxString_SearchString(pilot->GetModelName(), _str) != orxNULL)
        {
            return pilot;
        }
    }

    return orxNULL;
}

ScrollObject *Hexpatriates::GetFamiliarByPlayerType(const orxCHAR *_str)
{
    for (Familiar *familiar = GetNextObject<Familiar>(); familiar != orxNULL; familiar = GetNextObject<Familiar>(familiar))
    {
        if (orxString_SearchString(familiar->GetModelName(), _str) != orxNULL)
        {
            return familiar;
        }
    }

    return orxNULL;
}

int main(int argc, char **argv)
{
    // Executes game
    Hexpatriates::GetInstance().Execute(argc, argv);

    // Done!
    return EXIT_SUCCESS;
}
