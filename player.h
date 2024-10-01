#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Grid.h"
#include "propertygrid.h"
#include "railroadgrid.h"
#include "utilitygrid.h"
#include "PointF.h"  // Assuming you have a PointF class to replace QPoint

class Player {
public:
    // Constructor
    Player(const std::string& name, int startingBalance, const std::string& color);

    // Getters and Setters
    std::string getName() const;
    std::string getColor() const;

    PointF getPosition() const;
    void setPosition(const PointF& newPosition);

    float getBankBalance() const;
    void updateBankBalance(float amount);

    std::string getCurrentGrid() const;
    void setCurrentGrid(const std::string& gridName);

    int getCurrentGridIndex() const;
    void setCurrentGridIndex(int index);

    bool isInJail() const;
    void setInJail(bool inJail);
    int getJailTurns() const;
    void incrementJailTurn();
    void resetJailTurns();

    void addRoll(bool isDouble);
    bool hasRolledThreeDoubles();

    // Ownership management
    std::vector<PropertyGrid*> getOwnedProperties() const;
    std::vector<RailroadGrid*> getOwnedRailroads() const;
    std::vector<UtilityGrid*> getOwnedUtilities() const;

    void addProperty(PropertyGrid* property);
    void addRailroad(RailroadGrid* railroad);
    void addUtility(UtilityGrid* utility);

    // Get total houses and hotels owned
    int getNumHouses() const;
    int getNumHotels() const;

    // Jail card management
    int getOutOfJailCards() const;
    void setOutOfJailCards(int numCards);
    void decrementOutOfJailCard();
    bool isBankrupt() const;
    void declareBankruptcy();
    std::vector<PropertyGrid*> getPropertiesInColorGroup(const std::string& colorGroup) const;
    int m_numHouses =0;
    int m_numHotels=0;
    int m_outOfJailCards=0;
    std::vector<bool> m_lastThreeRolls;
    void declareBankruptcyToPlayer(Player* creditor);
    void declareBankruptcyToBank();

private:
    std::string m_name;
    PointF m_position;
    float m_bankBalance;
    std::string m_color;
    std::string m_currentGrid;
    int m_currentGridIndex;
    bool m_inJail;
    int m_jailTurns;
    bool m_bankrupt;  // New field to track if the player is bankrupt

    std::vector<PropertyGrid*> m_ownedProperties;
    std::vector<RailroadGrid*> m_ownedRailroads;
    std::vector<UtilityGrid*> m_ownedUtilities;

    // Number of "Get Out of Jail Free" cards
};

#endif // PLAYER_H
