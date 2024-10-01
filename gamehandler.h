#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <vector>
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
#include "playeraction.h"
#include <string>
class GameManager;

class GameHandler {
public:
    GameHandler(GameManager* manager);

    PlayerAction handleLanding(Player* player, Grid* grid, bool wantsToBuy, bool wantsToPayForHouse, int diceRoll);
    PlayerAction handleProperty(Player* player, PropertyGrid* property, bool wantsToBuy, bool wantsToPayForHouse);
    PlayerAction handleRailroad(Player* player, RailroadGrid* railroad);
    PlayerAction handleUtility(Player* player, UtilityGrid* utility, int diceRoll);


    // Handle the surprise grid and return both the player action and the type of surprise card
    PlayerAction handleSurprise(Player* player, SurpriseGrid* surprise);

    PlayerAction handleTax(Player* player, TaxGrid* tax);
    PlayerAction handleFreeParking(Player* player);
    PlayerAction handleGoToJail(Player* currentPlayer, bool wantsToPayForJail,bool wantsToUseJailOutCard);

    Player* findOwner_Property(PropertyGrid* property, const std::vector<Player*>& players);
    Player* findOwner_Railroad(RailroadGrid* railroad, const std::vector<Player*>& players);
    Player* findOwner_Utility(UtilityGrid* utility, const std::vector<Player*>& players);

    void handleBuilding(Player* player, PropertyGrid* property, bool wantsToPayForHouse);


    // Find the grid index by its name (e.g., Illinois Ave, Boardwalk)
    int findGridIndexByName(const std::string& name) const;

    // Find the index of the nearest utility grid from the player's current position
    int findNearestUtility(int currentIndex) const;

    // Find the index of the nearest railroad grid from the player's current position
    int findNearestRailroad(int currentIndex) const;

    std::vector<PropertyGrid*> getAllPropertiesOnBoard() const;


private:

    GameManager* m_gameManager;

    void buildHousePrompt(Player* player, PropertyGrid* property, const std::vector<PropertyGrid*>& propertiesInColorGroup);
    void buildHotelPrompt(Player* player, PropertyGrid* property);
};

#endif // GAMEHANDLER_H
