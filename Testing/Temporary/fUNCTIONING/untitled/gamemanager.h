#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include "player.h"
#include "monopolyboard.h"

// Forward declaration to avoid circular dependency
class GameHandler;

class GameManager {
public:
    GameManager(int numPlayers);
    ~GameManager();

    void rollDice();
    void movePlayer(int diceRoll, bool wantsToBuy, bool wantsToPayForHouse);

    // Get the current player using an iterator
    Player* getCurrentPlayer() const;

    // Get the result of the dice roll
    int getDiceRoll() const;

    // Return the list of players
    std::vector<Player*> getPlayers() const;

    // Return the game board as a list
    std::vector<Grid*> getBoard() const;

private:
    int currentPlayerIndex;  // Tracks the current player's index
    int diceRollResult;  // Stores the result of the dice roll

    std::vector<Player*> players;  // Vector of players in the game
    MonopolyBoard board;  // The game board object
    GameHandler* gameHandler;  // Pointer to GameHandler

    // Helper function to get a player by index using an iterator
    Player* getPlayerByIndex(int index) const;

    // Helper function to get a grid by index using an iterator
    Grid* getGridByIndex(int index) const;
};

#endif // GAMEMANAGER_H
