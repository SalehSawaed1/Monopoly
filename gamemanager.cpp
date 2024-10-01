#include "gamemanager.h"
#include "gamehandler.h"  // Make sure this is included for the full definition of GameHandler
#include <cstdlib>
#include <ctime>
#include <iterator>  // For std::next
#include <iostream>
#include <QMessageBox>

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

int GameManager::rollDice(int die1, int die2) {
    //    int die1 = std::rand() % 6 + 1;
    //    int die2 = std::rand() % 6 + 1;
    diceRollResult = die1 + die2;

    bool isDouble = (die1 == die2);
    Player* currentPlayer = getCurrentPlayer();

    currentPlayer->addRoll(isDouble);
    if(currentPlayer->isInJail()==true
        && isDouble){
        return -2;
    }
    if (currentPlayer->hasRolledThreeDoubles()) {
        std::cout << "You rolled doubles three times in a row! Go to Jail.\n";
        return -1;
        // if it return -1 this means current player had rolled 3 times doubles, and goes to jail
    }
    return diceRollResult;
    //Everything fine, get the result and call moveplayer
}

PlayerAction GameManager::movePlayer(int die1, int die2, bool wantsToBuy, bool wantsToPayForHouse,
                                     bool wantsToPayForJail, bool wantsToUseJailOutCard) {
    Player* currentPlayer = getCurrentPlayer();
    int diceRollResult = rollDice(die1, die2);

    // Check if the player rolled three doubles and went to jail
    if (diceRollResult == -1) {
        std::cout << currentPlayer->getName() << " rolled three doubles and is going to jail!\n";
        currentPlayer->setInJail(true);
        currentPlayer->setCurrentGridIndex(10);
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        return PlayerAction::GoToJail;
    }
    //PLAYER IS IN JAIL, AND ROLLED DOUBLE

    if (diceRollResult == -2) {
        std::cout << currentPlayer->getName() << " rolled three doubles and is going to jail!\n";
        currentPlayer->setInJail(false);
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        return PlayerAction::OutOfJail;
    }

    //PLAYER ROLLED DUBLE THREE TIMES, GO TO JAIL

    // If the player is in jail, handle the jail logic first
    if (currentPlayer->isInJail()) {
        currentPlayer->incrementJailTurn();
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        return  gameHandler->handleGoToJail(currentPlayer, wantsToPayForJail, wantsToUseJailOutCard);
    }
    //PLAYER IS IN JAIL, AND NO DOUBLES WERE ROLLED


    // Normal movement if not in jail or just got out of jail
    // Calculate the new grid index
    int currentGridIndex = currentPlayer->getCurrentGridIndex();
    int newGridIndex = (currentGridIndex + diceRollResult) % board.getBoard().size();
    currentPlayer->setCurrentGridIndex(newGridIndex);

    // If the player passes 'Go', they collect $200
    if (newGridIndex <= currentGridIndex) {
        std::cout << currentPlayer->getName() << " passed 'Go' and collected $200.\n";
        currentPlayer->updateBankBalance(200);
    }

    // Check if the player lands on the 'Go to Jail' grid
    if (GoToJailGrid* goToJail = dynamic_cast<GoToJailGrid*>(getGridByIndex(newGridIndex))) {
        std::cout << currentPlayer->getName() << " landed on 'Go to Jail' and is going to jail!\n";
        currentPlayer->setInJail(true);
        currentPlayer->setCurrentGridIndex(10);
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();

        return PlayerAction::GoToJail;
    }


    // Get the grid the player lands on
    Grid* grid = getGridByIndex(newGridIndex);
    if (!grid) {
        std::cerr << "Error: grid is null!" << std::endl;
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        return PlayerAction::NoAction;
    }

    // Process the landing on the new grid using the GameHandler
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    return gameHandler->handleLanding(currentPlayer, grid, wantsToBuy, wantsToPayForHouse,diceRollResult);

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

std::vector<PropertyGrid*> GameHandler::getAllPropertiesOnBoard() const {
    std::vector<PropertyGrid*> properties;
    const auto& board = m_gameManager->getBoard();  // Assuming the board is a vector of Grid* in GameManager
    for (Grid* grid : board) {
        if (PropertyGrid* property = dynamic_cast<PropertyGrid*>(grid)) {
            properties.push_back(property);
        }
    }
    return properties;
}


bool GameManager::checkWinner() {
    for (Player* player : players) {
        if (!player->isBankrupt() && player->getBankBalance() >= 4000) {
            return true;  // This player wins by having 4000 or more currency
        }
    }

    int nonBankruptPlayers = 0;
    for (Player* player : players) {
        if (!player->isBankrupt()) {
            nonBankruptPlayers++;
        }
    }

    // If only one non-bankrupt player is left, they win
    if (nonBankruptPlayers == 1) {
        return true;
    }

    return false;
}

Player* GameManager::getWinner()  {
    for (Player* player : players) {
        if (!player->isBankrupt() && player->getBankBalance() >= 4000) {
            return player;
        }
    }

    for (Player* player : players) {
        if (!player->isBankrupt()) {
            return player;  // The only non-bankrupt player is the winner
        }
    }

    return nullptr;  // No winner found
}

