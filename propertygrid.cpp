#include "propertygrid.h"
#include "player.h"
#include <cmath>
#include <algorithm>
#include<iostream>
using namespace std;

// Constructor
PropertyGrid::PropertyGrid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight,
                           const std::string& name, const std::string& colorGroup, float price, float baseRent)
    : Grid(topLeft, topRight, bottomLeft, bottomRight),
    m_name(name), m_colorGroup(colorGroup), m_price(price), m_baseRent(baseRent),
    m_numHouses(0), m_hasHotel(false), m_housePrice(100), m_hotelPrice(500) {}

// Getters
std::string PropertyGrid::getName() const {
    return m_name;
}

std::string PropertyGrid::getColorGroup() const {
    return m_colorGroup;
}

float PropertyGrid::getPrice() const {
    return m_price;
}

// Rent is calculated based on the number of houses or presence of a hotel
float PropertyGrid::getRent() const {
    if (m_hasHotel) {
        return m_hotelPrice;  // Rent with a hotel
    }
    if (m_numHouses > 0) {
        return m_baseRent * std::pow(2, m_numHouses - 1);  // Rent increases exponentially with houses
    }
    return m_baseRent;  // Base rent if no houses or hotels
}

float PropertyGrid::getBaseRent() const {
    return m_baseRent;
}

// House and hotel prices
float PropertyGrid::getHousePrice() const {
    return m_housePrice;
}

float PropertyGrid::getHotelPrice() const {
    return m_hotelPrice;
}

// Building methods
bool PropertyGrid::canBuildHouse(const Player* player, const std::vector<PropertyGrid*>& propertiesInGroup) const {
    return ownsAllInColorGroup(player, propertiesInGroup) && canBuildEvenly(propertiesInGroup) && m_numHouses < 4 && !m_hasHotel;
}

void PropertyGrid::buildHouse(const Player* player, const std::vector<PropertyGrid*>& propertiesInGroup) {
    if (canBuildHouse(player, propertiesInGroup)) {
        m_numHouses++;
    }
}

bool PropertyGrid::canBuildHotel() const {
    return m_numHouses == 4 && !m_hasHotel;  // Can build hotel if 4 houses exist
}

void PropertyGrid::buildHotel() {
    if (canBuildHotel()) {
        m_hasHotel = true;
        m_numHouses = 0;  // Building a hotel replaces houses
    }
}

// Get the number of houses
int PropertyGrid::getNumHouses() const {
    return m_numHouses;
}

// Check if the property has a hotel
bool PropertyGrid::hasHotel() const {
    return m_hasHotel;
}

// Return 1 if there is a hotel, otherwise 0
int PropertyGrid::getNumHotels() const {
    return m_hasHotel ? 1 : 0;
}

// Ensure that all properties in the color group have the same number of houses
bool PropertyGrid::canBuildEvenly(const std::vector<PropertyGrid*>& propertiesInGroup) const {
    for (const PropertyGrid* property : propertiesInGroup) {
        if (property->getNumHouses() < m_numHouses) {
            return false;  // Can't build if any property in the group has fewer houses
        }
    }
    return true;
}
bool PropertyGrid::ownsAllInColorGroup(const Player* player, const std::vector<PropertyGrid*>& allProperties) const {
    // Step 1: Collect all properties in the same color group
    std::vector<PropertyGrid*> colorGroupProperties;
    for (PropertyGrid* property : allProperties) {
        cout<<"name is: "<<property->getName()<<property->getColorGroup()<<endl;
        if (property->getColorGroup() == m_colorGroup) {
            cout<<"this is good property with"<<m_colorGroup<<property->getName()<<endl;
            colorGroupProperties.push_back(property);
        }
    }

    // Step 2: Print all properties in the color group
    std::cout << "Properties in color group (" << m_colorGroup << "):" << std::endl;
    for (PropertyGrid* property : colorGroupProperties) {
        std::cout << "here are all extracted group " << property->getName() << std::endl;
    }
    std::cout << player->getName() << "'s owned properties:" << std::endl;
    for (const PropertyGrid* ownedProperty : player->getOwnedProperties()) {
        std::cout << "- " << ownedProperty->getName() << std::endl;
    }

    std::cout << "Checking ownership of properties in the color group..." << std::endl;
    for (PropertyGrid* colorGroupProperty : colorGroupProperties) {
        bool found = false;

        // Loop through player's owned properties and check if the player owns the current property in the color group
        for (PropertyGrid* ownedProperty : player->getOwnedProperties()) {
            if (colorGroupProperty == ownedProperty) {
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << player->getName() << " does not own " << colorGroupProperty->getName() << std::endl;
            return false;  // The player doesn't own this property, so they don't own all in the group
        }
    }

    // Step 4: If the loop completes, the player owns all properties
    std::cout << player->getName() << " owns all properties in the color group." << std::endl;
    return true;
}
