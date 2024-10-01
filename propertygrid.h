#ifndef PROPERTYGRID_H
#define PROPERTYGRID_H

#include "Grid.h"
#include "PointF.h"
#include <string>
#include <vector>

class Player;  // Forward declaration of Player class

class PropertyGrid : public Grid {
public:
    // Constructor for PropertyGrid, initializing with grid corners, name, color group, price, and rent
    PropertyGrid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight,
                 const std::string& name, const std::string& colorGroup, float price, float rent);

    // Getters for property-specific data
    std::string getName() const override;
    std::string getColorGroup() const;
    float getPrice() const;
    float getRent() const;
    float getBaseRent() const;

    // House and hotel prices
    float getHousePrice() const;
    float getHotelPrice() const;

    // Methods for building houses and hotels
    bool canBuildHotel() const;
    void buildHotel();

    // Get number of houses and hotels (for status display purposes)
    int getNumHouses() const;
    bool hasHotel() const;
    int getNumHotels() const;  // Helper method to return the number of hotels (1 or 0)

    // Change from std::list to std::vector in the following methods
    bool canBuildHouse(const Player* player, const std::vector<PropertyGrid*>& propertiesInGroup) const;
    void buildHouse(const Player* player, const std::vector<PropertyGrid*>& propertiesInGroup);
    bool canBuildEvenly(const std::vector<PropertyGrid*>& propertiesInGroup) const;
    bool ownsAllInColorGroup(const Player* player, const std::vector<PropertyGrid*>& propertiesInGroup) const;

    int getTotalColorGroupSize() const {
        if (m_colorGroup == "Brown") {
            return 2; // Brown has 2 properties
        } else if (m_colorGroup == "Light Blue") {
            return 3;
        } else if (m_colorGroup == "Pink") {
            return 3;
        } else if (m_colorGroup == "Orange") {
            return 3;
        } else if (m_colorGroup == "Red") {
            return 3;
        } else if (m_colorGroup == "Yellow") {
            return 3;
        } else if (m_colorGroup == "Green") {
            return 3;
        } else if (m_colorGroup == "Dark Blue") {
            return 2; // Dark Blue has 2 properties
        }
        return 0;
    }

private:
    std::string m_name;
    std::string m_colorGroup;
    float m_price;
    float m_baseRent;
    float m_rent;

    // House and hotel management
    float m_housePrice = 100;
    float m_hotelPrice;
    int m_numHouses;
    bool m_hasHotel;
};

#endif // PROPERTYGRID_H
