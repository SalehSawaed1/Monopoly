#include "gamehandler.h"
#include "player.h"
#include "propertygrid.h"
#include "railroadgrid.h"
#include "utilitygrid.h"
#include "surprisegrid.h"
#include "taxgrid.h"
#include "freeparkinggrid.h"
#include "gotojailgrid.h"
#include "jailgrid.h"
#include "gamemanager.h"
#include <iostream>

GameHandler::GameHandler(GameManager* manager) : m_gameManager(manager) {}

void GameHandler::handleBuilding(Player* player, PropertyGrid* property, bool wantsToPayForHouse) {
    std::vector<PropertyGrid*> propertiesInColorGroup = player->getPropertiesInColorGroup(property->getColorGroup());

    // Check if the player owns all properties in the color group
    if (propertiesInColorGroup.size() == property->getTotalColorGroupSize()) {
        std::cout << "You own all properties in this color group.\n";

        // Check if the player wants to pay for building a house and can afford it
        if (wantsToPayForHouse) {
            if (property->getNumHouses() < 4 && !property->hasHotel()) {
                buildHousePrompt(player, property, propertiesInColorGroup);
            } else if (property->getNumHouses() == 4) {
                buildHotelPrompt(player, property);
            }
        } else {
            std::cout << "Player chose not to build houses yet.\n";
        }
    } else {
        std::cout << "You do not own all properties in this color group yet.\n";
    }
}


void GameHandler::buildHousePrompt(Player* player, PropertyGrid* property, const std::vector<PropertyGrid*>& propertiesInColorGroup) {
    if (property->canBuildHouse(player, propertiesInColorGroup)) {
        if (player->getBankBalance() >= property->getHousePrice()) {
            player->updateBankBalance(-property->getHousePrice());
            property->buildHouse(player, propertiesInColorGroup);
            std::cout << "House built successfully on " << property->getName() << "!\n";
        } else {
            std::cout << "Player cannot afford to build a house on " << property->getName() << ".\n";
        }
    } else {
        std::cout << "You must evenly distribute houses across the color group.\n";
    }
}

void GameHandler::buildHotelPrompt(Player* player, PropertyGrid* property) {
    int hotelPrice = property->getHousePrice() * 4 + 100;
    if (player->getBankBalance() >= hotelPrice) {
        player->updateBankBalance(-hotelPrice);
        property->buildHotel();
        std::cout << "Hotel built successfully on " << property->getName() << "!\n";
    } else {
        std::cout << "Player cannot afford to build a hotel on " << property->getName() << ".\n";
    }
}

void GameHandler::handleProperty(Player* player, PropertyGrid* property, bool wantsToBuy, bool wantsToPayForHouse) {
    // Get the vector of players from the game manager
    std::vector<Player*> players = m_gameManager->getPlayers();
    Player* owner = findOwner(property, players);

    if (owner == nullptr) {  // Property is unowned
        if (wantsToBuy) {  // If player decided to buy
            if (player->getBankBalance() >= property->getPrice()) {
                player->updateBankBalance(-property->getPrice());
                player->addProperty(property);
                std::cout << "Player purchased " << property->getName() << ".\n";
            } else {
                std::cout << "Player cannot afford to purchase " << property->getName() << ".\n";
            }
        } else {
            std::cout << "Player chose not to purchase " << property->getName() << ".\n";
        }
    } else if (owner != player) {  // Someone else owns the property
        float rent = property->getRent();
        player->updateBankBalance(-rent);
        owner->updateBankBalance(rent);
        std::cout << "Player paid $" << rent << " rent to " << owner->getName() << ".\n";
    } else {  // Player already owns the property
        handleBuilding(player, property, wantsToPayForHouse);  // Pass the argument to handle building
    }
}


void GameHandler::handleRailroad(Player* player, RailroadGrid* railroad) {
    std::cout << "Player landed on a railroad.\n";
}

void GameHandler::handleUtility(Player* player, UtilityGrid* utility) {
    std::cout << "Player landed on a utility.\n";
}

void GameHandler::handleSurprise(Player* player, SurpriseGrid* surprise) {
    std::cout << "Player landed on a surprise.\n";
}

void GameHandler::handleTax(Player* player, TaxGrid* tax) {
    std::cout << "Player landed on a tax grid.\n";
    player->updateBankBalance(-100);  // Apply tax amount
}

void GameHandler::handleFreeParking(Player* player) {
    std::cout << "Player landed on free parking.\n";
}

void GameHandler::handleGoToJail(Player* player) {
    std::cout << "Player is going to jail.\n";
    player->setInJail(true);
    player->resetJailTurns();
    player->setCurrentGrid("Jail");
    player->setCurrentGridIndex(10);
    player->setPosition(PointF(10, 10));  // Example coordinates for jail
}

void GameHandler::handleJail(Player* player) {
    if (player->getOutOfJailCards() > 0) {
        player->decrementOutOfJailCard();
        player->setInJail(false);
        player->resetJailTurns();
        std::cout << "Player used a 'Get Out of Jail Free' card.\n";
        return;
    }

    if (player->getBankBalance() >= 50) {
        player->updateBankBalance(-50);
        player->setInJail(false);
        player->resetJailTurns();
        std::cout << "Player paid $50 to get out of jail.\n";
        return;
    }

    if (player->getJailTurns() < 3) {
        player->incrementJailTurn();
        std::cout << "Player is still in jail, needs to roll doubles.\n";
    } else {
        player->updateBankBalance(-50);
        player->setInJail(false);
        player->resetJailTurns();
        std::cout << "Player paid $50 to get out of jail after 3 turns.\n";
    }
}

void GameHandler::handleLanding(Player* player, Grid* grid, bool wantsToBuy, bool wantsToPayForHouse) {
    // Use dynamic_cast to determine the actual type of grid and handle accordingly
    if (PropertyGrid* property = dynamic_cast<PropertyGrid*>(grid)) {
        std::cout << "Landed on a Property: " << property->getName() << std::endl;
        player->setCurrentGrid(property->getName());  // Set grid name from PropertyGrid
        handleProperty(player, property, wantsToBuy, wantsToPayForHouse);  // Pass the new argument to handle house building
    } else if (RailroadGrid* railroad = dynamic_cast<RailroadGrid*>(grid)) {
        std::cout << "Landed on a Railroad: " << railroad->getName() << std::endl;
        player->setCurrentGrid(railroad->getName());  // Set grid name from RailroadGrid
        handleRailroad(player, railroad);  // Handle railroad-specific behavior
    } else if (UtilityGrid* utility = dynamic_cast<UtilityGrid*>(grid)) {
        std::cout << "Landed on a Utility: " << utility->getName() << std::endl;
        player->setCurrentGrid(utility->getName());  // Set grid name from UtilityGrid
        handleUtility(player, utility);  // Handle utility-specific behavior
    } else if (TaxGrid* tax = dynamic_cast<TaxGrid*>(grid)) {
        std::cout << "Landed on a Tax Grid: " << tax->getName() << std::endl;
        player->setCurrentGrid(tax->getName());  // Set grid name from TaxGrid
        handleTax(player, tax);  // Handle tax-specific behavior
    } else if (JailGrid* jail = dynamic_cast<JailGrid*>(grid)) {
        std::cout << "Landed on Jail: " << jail->getName() << std::endl;
        player->setCurrentGrid(jail->getName());  // Set grid name from JailGrid
        handleJail(player);  // Handle landing in jail
    } else if (GoToJailGrid* goToJail = dynamic_cast<GoToJailGrid*>(grid)) {
        std::cout << "Landed on Go To Jail: " << goToJail->getName() << std::endl;
        player->setCurrentGrid(goToJail->getName());  // Set grid name from GoToJailGrid
        handleGoToJail(player);  // Handle sending player to jail
    } else if (FreeParkingGrid* freeParking = dynamic_cast<FreeParkingGrid*>(grid)) {
        std::cout << "Landed on Free Parking: " << freeParking->getName() << std::endl;
        player->setCurrentGrid(freeParking->getName());  // Set grid name from FreeParkingGrid
        handleFreeParking(player);  // Handle free parking behavior
    } else if (SurpriseGrid* surprise = dynamic_cast<SurpriseGrid*>(grid)) {
        std::cout << "Landed on a Surprise Grid: " << surprise->getName() << std::endl;
        player->setCurrentGrid(surprise->getName());  // Set grid name from SurpriseGrid
        handleSurprise(player, surprise);  // Handle surprise card or effect
    } else {
        // Fallback for any unrecognized grid types
        std::cerr << "Landed on an unrecognized grid. Something went wrong." << std::endl;
        player->setCurrentGrid("Unrecognized Grid");  // Set to a generic grid name for safety
    }
}

Player* GameHandler::findOwner(PropertyGrid* property, const std::vector<Player*>& players) {
    // Loop through all players
    for (Player* player : players) {
        // Loop through each property owned by the player
        for (PropertyGrid* ownedProperty : player->getOwnedProperties()) {
            // Compare the name or unique identifier of the property
            if (ownedProperty->getName() == property->getName()) {
                return player;  // Return the owner if found
            }
        }
    }
    return nullptr;  // Return nullptr if no owner is found
}
