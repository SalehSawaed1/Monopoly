#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <vector>  // Use vector instead of list
#include "player.h"
#include "Grid.h"
#include "propertygrid.h"
#include "railroadgrid.h"
#include "utilitygrid.h"
#include "surprisegrid.h"
#include "taxgrid.h"
#include "freeparkinggrid.h"
#include "gotojailgrid.h"
#include "jailgrid.h"

class GameManager;  // Proper forward declaration

class GameHandler {
public:
    GameHandler(GameManager* manager);

    // Handle various landings
    void handleLanding(Player* player, Grid* grid,bool wantsToBuy, bool wantsToPayForHouse);
    void handleProperty(Player* player, PropertyGrid* property, bool wantsToBuy, bool wantsToPayForHouse);
    void handleRailroad(Player* player, RailroadGrid* railroad);
    void handleUtility(Player* player, UtilityGrid* utility);
    void handleSurprise(Player* player, SurpriseGrid* surprise);
    void handleTax(Player* player, TaxGrid* tax);
    void handleFreeParking(Player* player);
    void handleGoToJail(Player* player);
    void handleJail(Player* player);

    // Updated to use vector instead of list
    Player* findOwner(PropertyGrid* property, const std::vector<Player*>& players);
    void handleBuilding(Player* player, PropertyGrid* property, bool wantsToPayForHouse);

private:
    GameManager* m_gameManager;

    // Updated to use vector instead of list
    void buildHousePrompt(Player* player, PropertyGrid* property, const std::vector<PropertyGrid*>& propertiesInColorGroup);
    void buildHotelPrompt(Player* player, PropertyGrid* property);
};

#endif // GAMEHANDLER_H
