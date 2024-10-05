#include "gamemanager.h"
#include "gamehandler.h"
#include "player.h"
#include <iostream>

// Function to print board grid names
void printBoardGrids(const GameManager& gameManager) {
    std::cout << "Monopoly Board Grids:" << std::endl;
    std::vector<Grid*> board = gameManager.getBoard();
    int index = 0;
    for (Grid* grid : board) {
        std::cout << "Grid " << index << ": " << grid->getName() << std::endl;
        index++;
    }
}

// Function to print player information
void printPlayerInfo(const GameManager& gameManager) {
    std::vector<Player*> players = gameManager.getPlayers();
    for (Player* player : players) {
        std::cout << "Player: " << player->getName() << std::endl;
        std::cout << "  Position: " << player->getCurrentGrid() << std::endl;
        std::cout << "  Bank Balance: $" << player->getBankBalance() << std::endl;
        std::cout << "  Houses: " << player->getNumHouses() << std::endl;
        std::cout << "  Hotels: " << player->getNumHotels() << std::endl;
        std::cout << "  Owned Properties: ";
        for (auto property : player->getOwnedProperties()) {
            std::cout << property->getName() << ", ";
        }
        std::cout << std::endl;
    }
}

// Test 1: Try to build a house without owning all properties of a color group
void testCannotBuildHouseWithoutFullColorGroup(GameManager& gameManager) {
    std::cout << "\n--- Test 1: Player cannot build a house without full color group ---\n";

    // Player 1 buys Mediterranean Avenue (Brown) but does not own Baltic Avenue
    gameManager.movePlayer(1, true, true);  // Player buys but does not build
    gameManager.movePlayer(10, true, true);  // Player buys but does not build
    gameManager.movePlayer(10, true, true);  // Player buys but does not build
    gameManager.movePlayer(10, true, true);  // Player buys but does not build
    gameManager.movePlayer(10, true, true);
    gameManager.movePlayer(10, true, true);  // Player buys but does not build
    gameManager.movePlayer(10, true, true);  // Player buys but does not build
    gameManager.movePlayer(10, true, true);  // Player buys but does not build
    gameManager.movePlayer(10, true, true);  // Player buys but does not build

    printPlayerInfo(gameManager);
}
void testCannotBuildHouseWithFullColorGroup(GameManager& gameManager) {
    std::cout << "\n--- Test 1: Player cannot build a house without full color group ---\n";

    // Player 1 buys Mediterranean Avenue (Brown) but does not own Baltic Avenue
    gameManager.movePlayer(1, true, true);  // Player buys but does not build
    gameManager.movePlayer(10, true, true);  // Player buys but does not build
    gameManager.movePlayer(2, true, true);  // Player buys but does not build
    gameManager.movePlayer(10, true, true);  // Player buys but does not build
    gameManager.movePlayer(8, true, true);  // Player buys but does not build
    gameManager.movePlayer(10, true, true);  // Player buys but does not build
    gameManager.movePlayer(10, true, true);  // Player buys but does not build
    gameManager.movePlayer(10, true, true);  // Player buys but does not build
    gameManager.movePlayer(10, true, true);  // Player buys but does not build
    gameManager.movePlayer(10, true, true);  // Player buys but does not build
    gameManager.movePlayer(10, true, true);  // Player buys but does not build


    printPlayerInfo(gameManager);
}

// Test 2: Build a house after acquiring all properties of a color group
void testBuildHouseAfterOwningFullColorGroup(GameManager& gameManager) {
    std::cout << "\n--- Test 2: Player can build a house after acquiring full color group ---\n";

    // Player 1 lands on Baltic Avenue and buys it, completing the color group
    gameManager.movePlayer(2, true, true);  // Player buys and builds

    printPlayerInfo(gameManager);
}

// Test 3: Try to build a house on a property that another player owns
void testCannotBuildHouseOnAnotherPlayersProperty(GameManager& gameManager) {
    std::cout << "\n--- Test 3: Player cannot build a house on another player's property ---\n";

    // Player 2 lands on Illinois Avenue (Red), but Player 1 tries to build a house (which they can't)
    gameManager.movePlayer(5, true, false);  // Player 2 buys Illinois Avenue
    gameManager.movePlayer(5, false, true);  // Player 1 tries to build a house on Player 2's property

    printPlayerInfo(gameManager);
}

// Test 4: Test full flow of house and hotel building after acquiring all properties in a color group
void testFullHouseAndHotelBuildingFlow(GameManager& gameManager) {
    std::cout << "\n--- Test 4: Full flow of house and hotel building ---\n";

    // Player 1 lands on Baltic Avenue (after acquiring Mediterranean Avenue) and builds houses
    gameManager.movePlayer(2, true, true);  // Player buys and builds

    // Player 1 moves and builds more houses until they can build a hotel
    gameManager.movePlayer(3, false, true);  // Player builds more houses

    // After building four houses, they can build a hotel
    gameManager.movePlayer(1, false, true);  // Player builds hotel

    printPlayerInfo(gameManager);
}

int main() {
    // Initialize Game Manager with 2 players
    GameManager gameManager1(2);
    // Print initialized board grids
    printBoardGrids(gameManager1);

    // Test 1: Try to build a house without owning all properties of a color group
    GameManager gameManager2(2);

    testCannotBuildHouseWithoutFullColorGroup(gameManager2);

    GameManager gameManager3(2);

    testCannotBuildHouseWithFullColorGroup(gameManager3);

    // Test 2: Build a house after acquiring all properties of a color group
    GameManager gameManager4(2);

    testBuildHouseAfterOwningFullColorGroup(gameManager4);

    // Test 3: Try to build a house on a property that another player owns
    GameManager gameManager5(2);

    testCannotBuildHouseOnAnotherPlayersProperty(gameManager5);

    // Test 4: Test full flow of house and hotel building after acquiring all properties in a color group
    GameManager gameManager6(2);

    testFullHouseAndHotelBuildingFlow(gameManager6);

    std::cout << "\nGame Test Completed!" << std::endl;
    return 0;
}
