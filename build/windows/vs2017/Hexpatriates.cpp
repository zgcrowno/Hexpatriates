//! Includes
// The following define/undef is done only once in the project. It should be
// done before including the interface of the class deriving from
// Scroll (as follows).
#define __SCROLL_IMPL__
#include "Hexpatriates.h"
#include "Arena.h"
#include "Laser.h"
#include "LaserWall.h"
#include "MainMenu.h"
#include "Menu.h"
#include "Orb.h"
#include "Pilot.h"
#include "PilotSelectMenu.h"
#include "Ship1.h"
#include "Ship2.h"
#include "Ship3.h"
#include "Ship4.h"
#include "Ship5.h"
#include "Ship6.h"
#include "Ship7.h"
#include "Ship8.h"
#include "Spawner.h"
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
    // CreateObject("O-Arena");
    
    return result;
}

void Hexpatriates::BindObjects()
{
    ScrollBindObject<Arena>("O-Arena");
    ScrollBindObject<Spawner>("O-Spawner");
    ScrollBindObject<Laser>("O-Laser");
    ScrollBindObject<LaserWall>("O-LaserWall");
    ScrollBindObject<MainMenu>("O-MainMenu");
    ScrollBindObject<Menu>("O-Menu");
    ScrollBindObject<Orb>("O-Orb");
    ScrollBindObject<Pilot>("O-Pilot");
    ScrollBindObject<PilotSelectMenu>("O-PilotSelectMenu");
    ScrollBindObject<Ship1>("O-Ship1");
    ScrollBindObject<Ship2>("O-Ship2");
    ScrollBindObject<Ship3>("O-Ship3");
    ScrollBindObject<Ship4>("O-Ship4");
    ScrollBindObject<Ship5>("O-Ship5");
    ScrollBindObject<Ship6>("O-Ship6");
    ScrollBindObject<Ship7>("O-Ship7");
    ScrollBindObject<Ship8>("O-Ship8");
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

int main(int argc, char **argv)
{
    // Executes game
    Hexpatriates::GetInstance().Execute(argc, argv);

    // Done!
    return EXIT_SUCCESS;
}
