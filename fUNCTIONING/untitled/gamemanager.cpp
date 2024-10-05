#include "gamemanager.h"
#include "gamehandler.h"  // Make sure this is included for the full definition of GameHandler
#include <cstdlib>
#include <ctime>
#include <iterator>  // For std::next
#include <iostream>

GameManager::GameManager(int numPlayers)
    : currentPlayerIndex(0), diceRollResult(0) {
    std::srand(static_cast<unsigned>(time(nullptr)));  // Seed random generator

    for (int i = 0; i < numPlayers; ++i) {
        std::string playerName = "Player " + std::to_string(i + 1);
        Player* newPlayer = new Player(playerName, 1500, "Color" + std::to_string(i + 1)); // You can define player colors in some other way
        players.push_back(newPlayer);

        // Initialize player's starting position
        PointF goPosition = board.getBoard().front()->calculateRandomPoint();
        newPlayer->setPosition(goPosition);
    }

    gameHandler = new GameHandler(this);  // This now works since GameHandler is fully defined
}

GameManager::~GameManager() {
    delete gameHandler;
}

void GameManager::rollDice() {
    int die1 = std::rand() % 6 + 1;
    int die2 = std::rand() % 6 + 1;
    diceRollResult = die1 + die2;

    bool isDouble = (die1 == die2);
    Player* currentPlayer = getCurrentPlayer();

    currentPlayer->addRoll(isDouble);

    if (currentPlayer->hasRolledThreeDoubles()) {
        std::cout << "You rolled doubles three times in a row! Go to Jail.\n";
        gameHandler->handleGoToJail(currentPlayer);
    } else if (isDouble) {
        std::cout << "You rolled doubles! Roll again.\n";
    }
}
void GameManager::movePlayer(int diceRoll, bool wantsToBuy, bool wantsToPayForHouse) {
    Player* currentPlayer = getCurrentPlayer();

    // Calculate the new grid index
    int currentGridIndex = currentPlayer->getCurrentGridIndex();
    int newGridIndex = (currentGridIndex + diceRoll) % board.getBoard().size();
    currentPlayer->setCurrentGridIndex(newGridIndex);
    Grid* grid = getGridByIndex(newGridIndex);

    if (!grid) {
        std::cerr << "Error: grid is null!" << std::endl;
        return;
    }

    // Use handleLanding to process what happens when landing on a grid
    gameHandler->handleLanding(currentPlayer, grid, wantsToBuy, wantsToPayForHouse);  // Pass the argument for building payment
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();

}





Player* GameManager::getCurrentPlayer() const {
    return getPlayerByIndex(currentPlayerIndex);
}

int GameManager::getDiceRoll() const {
    return diceRollResult;
}
std::vector<Player*> GameManager::getPlayers() const {
    return players;
}

std::vector<Grid*> GameManager::getBoard() const {
    return board.getBoard();
}

Player* GameManager::getPlayerByIndex(int index) const {
    if (index < 0 || index >= players.size()) {
        std::cerr << "Error: Index out of bounds!" << std::endl;
        return nullptr;
    }
    return players[index];  // Direct access with vector
}

Grid* GameManager::getGridByIndex(int index) const {
    const auto& grids = board.getBoard();

    if (index < 0 || index >= grids.size()) {
        std::cerr << "Error: Index out of bounds!" << std::endl;
        return nullptr;  // Return nullptr if the index is invalid
    }

    return grids[index];  // Direct access with vector
}
