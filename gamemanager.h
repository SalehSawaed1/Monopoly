#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include "player.h"
#include "monopolyboard.h"
#include "playeraction.h"

// Forward declaration to avoid circular dependency
class GameHandler;
enum class WaitingResponseType {
    None,         // No waiting response
    UtilityRent,  // Waiting for dice roll to calculate utility rent
    RailroadRent  // Waiting for dice roll to calculate railroad rent
};

class GameManager {
public:
    GameManager(int numPlayers);
    ~GameManager();
    int getCurrentPlayerIndex() const {
        return currentPlayerIndex;
    }

    int rollDice(int die1, int die2);
    PlayerAction movePlayer(int die1, int die2, bool wantsToBuy, bool wantsToPayForHouse,
                            bool wantsToPayForJail, bool wantsToUseJailOutCard);

    // Get the current player using an iterator
    Player* getCurrentPlayer() const;

    int getDiceRoll() const;

    std::vector<Player*> getPlayers() const;
    Grid* getGridByIndex(int index) const;

    std::vector<Grid*> getBoard() const;
    int currentPlayerIndex;  // Tracks the current player's index

    Player* getPlayerByIndex(int index) const;

    bool checkWinner();            // Check if there's a winner
    Player* getWinner();

    GameHandler* gameHandler;  // Pointer to GameHandler
    bool waiting_response =false;
    WaitingResponseType waiting_response_type = WaitingResponseType::None;
    Player* currentPropertyOwner = nullptr;  // To store the owner of the property
    int rentMultiplier = 0;

private:

    int diceRollResult;  // Stores the result of the dice roll
    std::vector<Player*> players;  // Vector of players in the game
    MonopolyBoard board;  // The game board object

};

#endif // GAMEMANAGER_H
