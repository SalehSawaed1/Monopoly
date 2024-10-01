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
#include <QMessageBox>
#include <QVBoxLayout>
using namespace std;


GameHandler::GameHandler(GameManager* manager) : m_gameManager(manager) {}

// Handling Property landing
PlayerAction GameHandler::handleProperty(Player* player, PropertyGrid* property, bool wantsToBuy, bool wantsToPayForHouse) {
    Player* owner = findOwner_Property(property, m_gameManager->getPlayers());

    if (owner == nullptr) {
        // No owner, the player can buy the property
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Buy Property",
                                      "Do you want to buy " + QString::fromStdString(property->getName()) +
                                          " for $" + QString::number(property->getPrice()) + "?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            if (player->getBankBalance() >= property->getPrice()) {
                player->updateBankBalance(-property->getPrice());
                player->addProperty(property);
                return PlayerAction::BuyProperty;
            } else {
                return PlayerAction::CannotAffordProperty;
            }
        }

    } else if (owner != player) {
        // The property is owned by someone else, pay rent
        float rent = property->getRent();
        if (player->getBankBalance() >= rent) {
            player->updateBankBalance(-rent);
            owner->updateBankBalance(rent);
            QMessageBox::information(nullptr, "Rent Paid",
                                     "You paid rent to " + QString::fromStdString(owner->getName()) +
                                         " for $" + QString::number(rent) + ".");
            return PlayerAction::PaidRent;
        } else {
            return PlayerAction::CannotAffordRent;
        }
    }

    // Player already owns this property, check if they want to build a house
    if (owner == player) {
        cout<<"gG"<<endl;
        std::vector<PropertyGrid*> propertiesInGroup = player->getPropertiesInColorGroup(property->getColorGroup());

        cout<<"start"<<endl;
        cout<<property->getColorGroup()<<endl;
        cout<<player->getName()<<endl;
        for(auto propertyc: propertiesInGroup){
            cout<<propertyc->getName()<<endl;
        }
        cout<<"end"<<endl;


        // Check if the player owns all properties in the color group and can build evenly
        if (property->ownsAllInColorGroup(player,getAllPropertiesOnBoard() ) && property->canBuildEvenly(propertiesInGroup)) {
            // Check if they can build a house
            if (property->canBuildHouse(player, propertiesInGroup)) {
                QMessageBox::StandardButton buildHouseReply;
                buildHouseReply = QMessageBox::question(
                    nullptr,
                    "Build House",
                    "Do you want to build a house on " + QString::fromStdString(property->getName()) +
                        " for $" + QString::number(property->getHousePrice()) + "?",
                    QMessageBox::Yes | QMessageBox::No
                    );

                if (buildHouseReply == QMessageBox::Yes) {
                    buildHousePrompt(player, property, propertiesInGroup);
                    QMessageBox::information(
                        nullptr,
                        "House Built",
                        "You have built a house on " + QString::fromStdString(property->getName()) + "."
                        );
                    return PlayerAction::BuildHouse;
                }

                // Check if they can build a hotel
            } else if (property->getNumHouses() == 4 && player->getBankBalance() >= property->getHousePrice() * 4) {
                QMessageBox::StandardButton buildHotelReply;
                buildHotelReply = QMessageBox::question(
                    nullptr,
                    "Build Hotel",
                    "Do you want to build a hotel on " + QString::fromStdString(property->getName()) +
                        " for $" + QString::number(property->getHousePrice() * 4) + "?",
                    QMessageBox::Yes | QMessageBox::No
                    );

                if (buildHotelReply == QMessageBox::Yes) {
                    buildHotelPrompt(player, property);
                    QMessageBox::information(
                        nullptr,
                        "Hotel Built",
                        "You have built a hotel on " + QString::fromStdString(property->getName()) + "."
                        );
                    return PlayerAction::BuildHotel;
                }

            } else {
                // Inform the player why they cannot build
                QString reason;
                if (property->getNumHouses() >= 4 && player->getBankBalance() < property->getHousePrice() * 4) {
                    reason = "You have already built 4 houses and do not have enough money to build a hotel.";
                } else if (property->getNumHouses() >= 4) {
                    reason = "You have already built the maximum number of houses on this property.";
                } else {
                    reason = "You do not have enough money to build a house.";
                }
                QMessageBox::information(
                    nullptr,
                    "Cannot Build",
                    reason
                    );
                return PlayerAction::CannotBuildHouse;
            }
        } else {
            // Inform the player they cannot build because they don't own all properties or can't build evenly
            QString reason;
            if (!property->ownsAllInColorGroup(player, propertiesInGroup)) {
                reason = "You do not own all properties in the color group.";
            } else if (!property->canBuildEvenly(propertiesInGroup)) {
                reason = "You must build evenly across all properties in this color group.";
            }
            QMessageBox::information(nullptr, "Cannot Build", reason);
            return PlayerAction::CannotBuildHouse;
        }
    }

    return PlayerAction::NoAction;
}


// Helper method to build a house
void GameHandler::buildHousePrompt(Player* player, PropertyGrid* property, const std::vector<PropertyGrid*>& propertiesInColorGroup) {
    if (property->canBuildHouse(player, propertiesInColorGroup)) {
        player->updateBankBalance(-property->getHousePrice());
        property->buildHouse(player, propertiesInColorGroup);
        player->m_numHouses++;
    }
}

// Helper method to build a hotel
void GameHandler::buildHotelPrompt(Player* player, PropertyGrid* property) {
    player->updateBankBalance(-property->getHousePrice() * 4);
    property->buildHotel();
    player->m_numHotels++;
}

// Handling Railroad landing
PlayerAction GameHandler::handleRailroad(Player* player, RailroadGrid* railroad) {
    Player* owner = findOwner_Railroad(railroad, m_gameManager->getPlayers());

    // If no one owns the railroad, the player can buy it
    if (owner == nullptr) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Buy Railroad",
                                      "Do you want to buy " + QString::fromStdString(railroad->getName()) +
                                          " for $" + QString::number(railroad->getPrice()) + "?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            if (player->getBankBalance() >= railroad->getPrice()) {
                player->updateBankBalance(-railroad->getPrice());
                player->addRailroad(railroad);
                QMessageBox::information(nullptr, "Purchase Successful", "You successfully bought the railroad.");
                return PlayerAction::BuyProperty;
            } else {
                QMessageBox::warning(nullptr, "Cannot Afford", "You cannot afford this railroad.");
                return PlayerAction::CannotAffordProperty;
            }
        }
    }
    // If the player lands on another player's railroad, they must pay rent
    else if (owner != player) {
        int rent = railroad->getRent(owner->getOwnedRailroads().size());

        if (player->getBankBalance() >= rent) {
            player->updateBankBalance(-rent);
            owner->updateBankBalance(rent);
            QMessageBox::information(nullptr, "Rent Paid",
                                     "You paid $" + QString::number(rent) + " rent to " +
                                         QString::fromStdString(owner->getName()) + ".");
            return PlayerAction::PaidRent;
        } else {
            QMessageBox::warning(nullptr, "Cannot Afford Rent",
                                 "You cannot afford the rent of $" + QString::number(rent) +
                                     " for landing on " + QString::fromStdString(railroad->getName()) +
                                     " owned by " + QString::fromStdString(owner->getName()) + ".");
            player->declareBankruptcyToPlayer(owner);
            return PlayerAction::DeclareBankruptcyToPlayer;
        }
    }

    return PlayerAction::NoAction;
}

// Handling Utility landing
PlayerAction GameHandler::handleUtility(Player* player, UtilityGrid* utility, int diceRoll) {
    Player* owner = findOwner_Utility(utility, m_gameManager->getPlayers());

    // Check if the utility is unowned
    if (owner == nullptr) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Buy Utility",
                                      "Do you want to buy " + QString::fromStdString(utility->getName()) +
                                          " for $150?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            if (player->getBankBalance() >= 150) {
                player->updateBankBalance(-150);
                player->addUtility(utility);
                QMessageBox::information(nullptr, "Purchase Successful", "You successfully bought the utility.");
                return PlayerAction::BuyProperty;
            } else {
                QMessageBox::warning(nullptr, "Cannot Afford", "You cannot afford this utility.");
                return PlayerAction::CannotAffordProperty;
            }
        }
    }
    // If the utility is owned by another player, pay rent
    else if (owner != player) {
        int rent = diceRoll * 10;  // Rent is 10 times the dice roll result
        if (player->getBankBalance() >= rent) {
            player->updateBankBalance(-rent);
            owner->updateBankBalance(rent);
            QMessageBox::information(nullptr, "Rent Paid",
                                     "You paid $" + QString::number(rent) + " rent to " +
                                         QString::fromStdString(owner->getName()) + ".");
            return PlayerAction::PaidRent;
        } else {
            QMessageBox::warning(nullptr, "Cannot Afford Rent",
                                 "You cannot afford the rent of $" + QString::number(rent) +
                                     " for landing on " + QString::fromStdString(utility->getName()) +
                                     " owned by " + QString::fromStdString(owner->getName()) + ".");
            return PlayerAction::CannotAffordRent;
        }
    }

    return PlayerAction::NoAction;
}

// Method to find the nearest utility



int GameHandler::findGridIndexByName(const std::string& name) const {
    for (int i = 0; i <m_gameManager->getBoard().size(); ++i) {
        if (m_gameManager->getBoard()[i]->getName() == name) {
            return i;
        }
    }
    return -1;  // If the grid is not found
}

int GameHandler::findNearestUtility(int currentIndex) const {
    const auto& grids = m_gameManager->getBoard();
    for (int i = currentIndex + 1; i < grids.size(); ++i) {
        if (dynamic_cast<UtilityGrid*>(grids[i])) {
            return i;
        }
    }
    return -1;  // If no utility is found
}

int GameHandler::findNearestRailroad(int currentIndex) const {
    const auto& grids = m_gameManager->getBoard();
    for (int i = currentIndex + 1; i < grids.size(); ++i) {
        if (dynamic_cast<RailroadGrid*>(grids[i])) {
            return i;
        }
    }
    return -1;  // If no railroad is found
}


PlayerAction GameHandler::handleSurprise(Player* player, SurpriseGrid* surprise) {
    // Retrieve a random surprise from the SurpriseGrid
    // This is a mock result for now
    std::string surpriseResult = "Go back 3 spaces";

    QMessageBox::information(nullptr, "Surprise Card", "You picked a surprise card: " + QString::fromStdString(surpriseResult));

    if (surpriseResult == "Advance to Go (Collect $200)") {
        player->setCurrentGridIndex(0);  // Move player to "Go"
        player->updateBankBalance(200);  // Collect $200
        QMessageBox::information(nullptr, "Advance to Go", "You advanced to Go and collected $200.");
        return PlayerAction::SurpriseCardAdvanceToGo;

    } else if (surpriseResult == "Bank pays you dividend of $50") {
        player->updateBankBalance(50);
        QMessageBox::information(nullptr, "Dividend", "You received a dividend of $50.");
        return PlayerAction::SurpriseCardDividend;

    } else if (surpriseResult == "Go back 3 spaces") {
        int newGridIndex = player->getCurrentGridIndex() - 3;
        cout<<newGridIndex<<endl;
        if (newGridIndex < 0) newGridIndex += m_gameManager->getBoard().size();  // Wrap around if negative
        player->setCurrentGridIndex(newGridIndex);
        QMessageBox::information(nullptr, "Go Back", "You moved back 3 spaces.");
        return PlayerAction::SurpriseCardGoBack3Spaces;

    } else if (surpriseResult == "Go directly to Jail – do not pass Go, do not collect $200") {
        player->setInJail(true);
        player->setCurrentGridIndex(10);
        QMessageBox::warning(nullptr, "Go to Jail", "You are sent to Jail. Do not pass Go, do not collect $200.");
        return PlayerAction::SurpriseCardGoToJail;

    } else if (surpriseResult == "Make general repairs on all your property – For each house pay $25 – For each hotel $100") {
        int totalCost = (player->getNumHouses() * 25) + (player->getNumHotels() * 100);
        player->updateBankBalance(-totalCost);
        QMessageBox::information(nullptr, "Repairs", "You paid $" + QString::number(totalCost) + " for property repairs.");
        return PlayerAction::SurpriseCardRepairs;

    } else if (surpriseResult == "Pay poor tax of $15") {
        player->updateBankBalance(-15);
        QMessageBox::information(nullptr, "Poor Tax", "You paid a poor tax of $15.");
        return PlayerAction::SurpriseCardPayPoorTax;

    } else if (surpriseResult == "Take a trip to Reading Railroad – If you pass Go collect $200") {
        int readingRailroadIndex = findGridIndexByName("Reading Railroad"); // Get the actual index for Reading Railroad
        if (player->getCurrentGridIndex() > readingRailroadIndex) {
            player->updateBankBalance(200);  // Collect $200 if passing Go
            QMessageBox::information(nullptr, "Passed Go", "You passed Go and collected $200.");
        }
        player->setCurrentGridIndex(readingRailroadIndex);
        QMessageBox::information(nullptr, "Reading Railroad", "You moved to Reading Railroad.");
        return PlayerAction::SurpriseCardTripToRailroad;

    } else if (surpriseResult == "Take a walk on the Boardwalk – Advance token to Boardwalk") {
        int boardwalkIndex = findGridIndexByName("Boardwalk");  // Get the actual index for Boardwalk
        player->setCurrentGridIndex(boardwalkIndex);
        QMessageBox::information(nullptr, "Boardwalk", "You advanced to Boardwalk.");
        return PlayerAction::SurpriseCardWalkOnBoardwalk;

    } else if (surpriseResult == "You have been elected Chairman of the Board – Pay each player $50") {
        for (Player* otherPlayer : m_gameManager->getPlayers()) {
            if (otherPlayer != player) {
                player->updateBankBalance(-50);
                otherPlayer->updateBankBalance(50);
            }
        }
        QMessageBox::information(nullptr, "Chairman Elected", "You have been elected Chairman and paid $50 to each player.");
        return PlayerAction::SurpriseCardElectedChairman;

    } else if (surpriseResult == "Your building loan matures – Collect $150") {
        player->updateBankBalance(150);
        QMessageBox::information(nullptr, "Building Loan Matures", "Your building loan has matured and you collected $150.");
        return PlayerAction::SurpriseCardBuildingLoanMatures;

    } else if (surpriseResult == "Get out of Jail Free – This card may be kept until needed or traded") {
        player->setOutOfJailCards(player->getOutOfJailCards() + 1);
        QMessageBox::information(nullptr, "Get Out of Jail Free", "You received a 'Get Out of Jail Free' card.");
        return PlayerAction::SurpriseCardGetOutOfJailFree;

    } else if (surpriseResult == "Advance to Illinois Ave. – If you pass Go, collect $200") {
        int illinoisAveIndex = findGridIndexByName("Illinois Ave");  // Get the actual index for Illinois Ave
        if (player->getCurrentGridIndex() > illinoisAveIndex) {
            player->updateBankBalance(200);            // Collect $200 if passing Go
            QMessageBox::information(nullptr, "Passed Go", "You passed Go and collected $200.");
        }
        cout<<illinoisAveIndex<<endl;
        player->setCurrentGridIndex(illinoisAveIndex);
        QMessageBox::information(nullptr, "Illinois Avenue", "You advanced to Illinois Avenue.");
        return PlayerAction::SurpriseCardAdvanceToIllinois;

    } else if (surpriseResult == "Advance to St. Charles Place – If you pass Go, collect $200") {
        int stCharlesIndex = findGridIndexByName("St. Charles Place");  // Get the actual index for St. Charles Place
        if (player->getCurrentGridIndex() > stCharlesIndex) {
            player->updateBankBalance(200);  // Collect $200 if passing Go
            QMessageBox::information(nullptr, "Passed Go", "You passed Go and collected $200.");
        }
        player->setCurrentGridIndex(stCharlesIndex);
        QMessageBox::information(nullptr, "St. Charles Place", "You advanced to St. Charles Place.");
        return PlayerAction::SurpriseCardAdvanceToStCharles;

    } else if (surpriseResult == "You are assessed for street repairs – $40 per house, $115 per hotel") {
        int totalCost = (player->getNumHouses() * 40) + (player->getNumHotels() * 115);
        player->updateBankBalance(-totalCost);
        QMessageBox::information(nullptr, "Street Repairs", "You paid $" + QString::number(totalCost) + " for street repairs.");
        return PlayerAction::SurpriseCardStreetRepairs;

    } else if (surpriseResult == "Advance to nearest Utility – If unowned you may buy it from the Bank. If owned, throw dice and pay owner a total ten times the amount thrown.") {
            int utilityIndex = findNearestUtility(player->getCurrentGridIndex());
            player->setCurrentGridIndex(utilityIndex);

            UtilityGrid* utility = dynamic_cast<UtilityGrid*>(m_gameManager->getGridByIndex(utilityIndex));
            Player* owner = findOwner_Utility(utility, m_gameManager->getPlayers());

            if (owner == nullptr) {
                // No owner, player may buy
                QMessageBox::information(nullptr, "Nearest Utility", "You advanced to the nearest utility and may buy it from the bank.");


                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(nullptr, "Buy Utility",
                                              "Do you want to buy " + QString::fromStdString(utility->getName()) +
                                                  " for $150?",
                                              QMessageBox::Yes | QMessageBox::No);

                if (reply == QMessageBox::Yes) {
                    if (player->getBankBalance() >= 150) {
                        player->updateBankBalance(-150);
                        player->addUtility(utility);
                        QMessageBox::information(nullptr, "Purchase Successful", "You successfully bought the utility.");
                        return PlayerAction::BuyProperty;
                    } else {
                        QMessageBox::warning(nullptr, "Cannot Afford", "You cannot afford this utility.");
                        return PlayerAction::CannotAffordProperty;
                    }
                }
                return PlayerAction::SurpriseCardNearestUtility;
            } else if (owner != player) {
                // Utility is owned by another player: Rent = 10 times the dice roll
                m_gameManager->waiting_response = true;
                m_gameManager->waiting_response_type = WaitingResponseType::UtilityRent;
                m_gameManager->rentMultiplier = 10;  // Rent for utilities is 10x the dice roll
                m_gameManager->currentPropertyOwner = owner;

                QMessageBox::information(nullptr, "Utility Owned", "This utility is owned by " + QString::fromStdString(owner->getName()) +
                                                                       ". Roll the dice and pay 10 times the amount rolled.");
                return PlayerAction::NoAction;  // Await dice roll input from the player
            }
        }
    else if (surpriseResult == "Advance to nearest Railroad. If unowned, you may buy it from the Bank. If owned, pay owner twice the rental to which they are otherwise entitled.") {
        int railroadIndex = findNearestRailroad(player->getCurrentGridIndex());
        player->setCurrentGridIndex(railroadIndex);

        RailroadGrid* railroad = dynamic_cast<RailroadGrid*>(m_gameManager->getGridByIndex(railroadIndex));
        Player* owner = findOwner_Railroad(railroad, m_gameManager->getPlayers());

        if (owner == nullptr) {
            // No owner, player may buy
            QMessageBox::information(nullptr, "Nearest Railroad", "You advanced to the nearest railroad and may buy it from the bank.");


            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(nullptr, "Buy Railroad",
                                          "Do you want to buy " + QString::fromStdString(railroad->getName()) +
                                              " for $" + QString::number(railroad->getPrice()) + "?",
                                          QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                if (player->getBankBalance() >= railroad->getPrice()) {
                    player->updateBankBalance(-railroad->getPrice());
                    player->addRailroad(railroad);
                    QMessageBox::information(nullptr, "Purchase Successful", "You successfully bought the railroad.");
                    return PlayerAction::BuyProperty;
                } else {
                    QMessageBox::warning(nullptr, "Cannot Afford", "You cannot afford this railroad.");
                    return PlayerAction::CannotAffordProperty;
                }
            }



            return PlayerAction::SurpriseCardNearestRailroad;
        } else if (owner != player) {
            // Railroad is owned by another player: Rent = double the normal rent
            m_gameManager->waiting_response = true;
            m_gameManager->waiting_response_type = WaitingResponseType::RailroadRent;
            m_gameManager->rentMultiplier = 2;  // Rent for railroads is double
            m_gameManager->currentPropertyOwner = owner;

            QMessageBox::information(nullptr, "Railroad Owned", "This railroad is owned by " + QString::fromStdString(owner->getName()) +
                                                                    ". Roll the dice and pay twice the normal rent.");
            return PlayerAction::NoAction;  // Await dice roll input from the player
        }
    }

    return PlayerAction::NoAction;  // Default case if no condition matches
}

// Handling Tax landing
PlayerAction GameHandler::handleTax(Player* player, TaxGrid* tax) {
    player->updateBankBalance(-tax->getTaxAmount());
    QMessageBox::information(nullptr, "Tax Paid", "You paid tax of $" + QString::number(tax->getTaxAmount()) + ".");
    return PlayerAction::TaxPaid;
}


PlayerAction GameHandler::handleGoToJail(Player* currentPlayer, bool wantsToPayForJail, bool wantsToUseJailOutCard) {
    // Ask the player if they want to use a "Get Out of Jail Free" card if they have one
    if (currentPlayer->getOutOfJailCards() > 0) {
        QMessageBox::StandardButton cardChoice;
        cardChoice = QMessageBox::question(nullptr, "Get Out of Jail Free",
                                           QString::fromStdString(currentPlayer->getName()) +
                                               " has a 'Get Out of Jail Free' card. Would you like to use it?",
                                           QMessageBox::Yes | QMessageBox::No);
        if (cardChoice == QMessageBox::Yes) {
            currentPlayer->decrementOutOfJailCard();
            currentPlayer->setInJail(false);

            // Inform the player that they've used the card
            QMessageBox::information(nullptr, "Out of Jail",
                                     QString::fromStdString(currentPlayer->getName()) +
                                         " used a 'Get Out of Jail Free' card.");
            return PlayerAction::OutOfJail;
        }
    }

    // Ask the player if they want to pay $50 to get out of jail
    if (currentPlayer->getBankBalance() >= 50) {
        QMessageBox::StandardButton payChoice;
        payChoice = QMessageBox::question(nullptr, "Pay Fine",
                                          QString::fromStdString(currentPlayer->getName()) +
                                              " can pay $50 to get out of jail. Would you like to pay?",
                                          QMessageBox::Yes | QMessageBox::No);
        if (payChoice == QMessageBox::Yes) {
            currentPlayer->updateBankBalance(-50);
            currentPlayer->setInJail(false);

            // Inform the player that they've paid to get out of jail
            QMessageBox::information(nullptr, "Out of Jail",
                                     QString::fromStdString(currentPlayer->getName()) +
                                         " paid the $50 fine to get out of jail.");
            return PlayerAction::OutOfJail;
        }
    }

    // If the player does not pay or use a card, check if they've been in jail for 3 turns
    if (currentPlayer->getJailTurns() >= 3) {
        if (currentPlayer->getBankBalance() >= 50) {
            currentPlayer->updateBankBalance(-50);
            currentPlayer->setInJail(false);
            currentPlayer->resetJailTurns();

            // Inform the player that they have to pay the fine after 3 turns
            QMessageBox::information(nullptr, "Out of Jail",
                                     QString::fromStdString(currentPlayer->getName()) +
                                         " paid $50 after 3 turns to get out of jail.");
            return PlayerAction::OutOfJail;
        } else {
            // Declare bankruptcy to the bank if they cannot pay
            currentPlayer->declareBankruptcyToBank();

            // Inform the player that they've declared bankruptcy
            QMessageBox::information(nullptr, "Bankruptcy",
                                     QString::fromStdString(currentPlayer->getName()) +
                                         " has declared bankruptcy due to inability to pay the fine.");
            return PlayerAction::DeclareBankruptcyToBank;
        }
    }

    // If no action is taken, the player stays in jail
    QMessageBox::information(nullptr, "Stay in Jail",
                             QString::fromStdString(currentPlayer->getName()) +
                                 " stays in jail for this turn.");
    return PlayerAction::JailTurn;  // Player remains in jail for this turn
}


// Handling Free Parking
PlayerAction GameHandler::handleFreeParking(Player* player) {
    return PlayerAction::FreeParking;
}

// Handling Jail
//PlayerAction GameHandler::handleJail(Player* player) {
//    if (player->getOutOfJailCards() > 0) {
//        player->getOutOfJailCards();
//        return PlayerAction::OutOfJail;
//    } else {
//        return PlayerAction::JailTurn;
//    }
//}

// Handling overall landing logic
PlayerAction GameHandler::handleLanding(Player* player, Grid* grid, bool wantsToBuy, bool wantsToPayForHouse, int diceRoll) {
    if (PropertyGrid* property = dynamic_cast<PropertyGrid*>(grid)) {
        return handleProperty(player, property, wantsToBuy, wantsToPayForHouse);
    } else if (RailroadGrid* railroad = dynamic_cast<RailroadGrid*>(grid)) {
        return handleRailroad(player, railroad);
    } else if (UtilityGrid* utility = dynamic_cast<UtilityGrid*>(grid)) {
        return handleUtility(player, utility,diceRoll);
    } else if (TaxGrid* tax = dynamic_cast<TaxGrid*>(grid)) {
        return handleTax(player, tax);
        //    } else if (JailGrid* jail = dynamic_cast<JailGrid*>(grid)) {
        //        return handleJail(player);
        //    } else if (GoToJailGrid* goToJail = dynamic_cast<GoToJailGrid*>(grid)) {
        //        return handleGoToJail(player);
    } else if (FreeParkingGrid* freeParking = dynamic_cast<FreeParkingGrid*>(grid)) {
        return handleFreeParking(player);
    } else if (SurpriseGrid* surprise = dynamic_cast<SurpriseGrid*>(grid)) {
        return handleSurprise(player, surprise);
    }
    return PlayerAction::NoAction;
}

// Methods to find the owner of properties, railroads, utilities
Player* GameHandler::findOwner_Property(PropertyGrid* property, const std::vector<Player*>& players) {
    for (Player* player : players) {
        for (PropertyGrid* ownedProperty : player->getOwnedProperties()) {
            if (ownedProperty->getName() == property->getName()) {
                return player;
            }
        }
    }
    return nullptr;
}

Player* GameHandler::findOwner_Railroad(RailroadGrid* railroad, const std::vector<Player*>& players) {
    for (Player* player : players) {
        for (RailroadGrid* ownedRailroad : player->getOwnedRailroads()) {
            if (ownedRailroad->getName() == railroad->getName()) {
                return player;
            }
        }
    }
    return nullptr;
}

Player* GameHandler::findOwner_Utility(UtilityGrid* utility, const std::vector<Player*>& players) {
    for (Player* player : players) {
        for (UtilityGrid* ownedUtility : player->getOwnedUtilities()) {
            if (ownedUtility->getName() == utility->getName()) {
                return player;
            }
        }
    }
    return nullptr;
}
