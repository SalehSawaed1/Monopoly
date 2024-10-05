#include "player.h"
#include "propertygrid.h"
#include "railroadgrid.h"
#include "utilitygrid.h"
#include <string>
#include "stdlib.h"
#include <list>

// Constructor
Player::Player(const std::string& name, int startingBalance, const std::string& color)
    : m_name(name), m_bankBalance(startingBalance), m_color(color),
    m_currentGridIndex(0), m_inJail(false), m_jailTurns(0), m_numHouses(0),
    m_numHotels(0), m_outOfJailCards(0) {}

// Getters and Setters
std::string Player::getName() const {
    return m_name;
}

std::string Player::getColor() const {
    return m_color;
}

PointF Player::getPosition() const {
    return m_position;
}

void Player::setPosition(const PointF& newPosition) {
    m_position = newPosition;
}

float Player::getBankBalance() const {
    return m_bankBalance;
}

void Player::updateBankBalance(float amount) {
    m_bankBalance += amount;  // Update balance by adding the amount (positive or negative)
}

std::string Player::getCurrentGrid() const {
    return m_currentGrid;
}

void Player::setCurrentGrid(const std::string& gridName) {
    m_currentGrid = gridName;
}

int Player::getCurrentGridIndex() const {
    return m_currentGridIndex;
}

void Player::setCurrentGridIndex(int index) {
    m_currentGridIndex = index;
}

// Jail Management
bool Player::isInJail() const {
    return m_inJail;
}

void Player::setInJail(bool inJail) {
    m_inJail = inJail;
    if (inJail) {
        m_jailTurns = 0;  // Reset jail turns when sent to jail
    }
}

int Player::getJailTurns() const {
    return m_jailTurns;
}

void Player::incrementJailTurn() {
    ++m_jailTurns;
}

void Player::resetJailTurns() {
    m_jailTurns = 0;
}

// Track if the player rolled doubles
void Player::addRoll(bool isDouble) {
    if (m_lastThreeRolls.size() == 3) {
        m_lastThreeRolls.erase(m_lastThreeRolls.begin());  // Remove the oldest roll (first element)
    }
    m_lastThreeRolls.push_back(isDouble);  // Add the new roll to the end
}


// Check if the player rolled doubles three times in a row
bool Player::hasRolledThreeDoubles() const {
    if (m_lastThreeRolls.size() != 3) {
        return false;
    }

    // Using an iterator to access the elements of the list
    auto it = m_lastThreeRolls.begin();
    bool first = *it;
    ++it;
    bool second = *it;
    ++it;
    bool third = *it;

    return first && second && third;
}


// Ownership Management
std::vector<PropertyGrid*> Player::getOwnedProperties() const {
    return m_ownedProperties;
}

std::vector<RailroadGrid*> Player::getOwnedRailroads() const {
    return m_ownedRailroads;
}

std::vector<UtilityGrid*> Player::getOwnedUtilities() const {
    return m_ownedUtilities;
}


void Player::addProperty(PropertyGrid* property) {
    m_ownedProperties.push_back(property);
    m_numHouses += property->getNumHouses();  // Update house count when a new property is added
    m_numHotels += property->getNumHotels();  // Update hotel count when a new property is added
}

void Player::addRailroad(RailroadGrid* railroad) {
    m_ownedRailroads.push_back(railroad);
}

void Player::addUtility(UtilityGrid* utility) {
    m_ownedUtilities.push_back(utility);
}

// Get total houses and hotels
int Player::getNumHouses() const {
    return m_numHouses;
}

int Player::getNumHotels() const {
    return m_numHotels;
}

// Get Out of Jail Card Management
int Player::getOutOfJailCards() const {
    return m_outOfJailCards;
}

void Player::setOutOfJailCards(int numCards) {
    m_outOfJailCards = numCards;
}

void Player::decrementOutOfJailCard() {
    if (m_outOfJailCards > 0) {
        --m_outOfJailCards;
    }
}
