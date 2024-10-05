#include "form.h"
#include "ui_form.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QMessageBox>
#include <QVBoxLayout>
#include "gamemanager.h"
#include "gamehandler.h"
#include <iostream>
using namespace std;

form::form(QWidget *parent, int numPlayers)
    : QDialog(parent)
    , ui(new Ui::form)
    , scene(new QGraphicsScene(this))  // Initialize the scene here
    , gameManager(new GameManager(numPlayers))  // Initialize the GameManager without GUI elements
{
    ui->setupUi(this);

    // Set the fixed size of the window
    this->setFixedSize(940, 800);

    // Load the board image
    QPixmap boardImage("C:/Users/saleh/Downloads/board.jpeg"); // Your board image path
    if (boardImage.isNull()) {
        qDebug() << "Failed to load image!";
        return;
    }

    // Resize the image to fit the scene
    QPixmap scaledBoardImage = boardImage.scaled(750, 750, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    scene->setSceneRect(0, 0, scaledBoardImage.width(), scaledBoardImage.height());
    scene->addPixmap(scaledBoardImage);  // Add the image to the scene

    // Set the scene to the graphics view
    ui->graphicsView->setScene(scene);

    // Initialize player tokens and place them on the board
    initializePlayerTokens(numPlayers);

    // Create the layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(ui->graphicsView);
    layout->addWidget(ui->diceResultLabel);
    layout->addWidget(ui->playerInfoLabel);
    layout->addWidget(ui->rollDiceButton);

    // Add the Player Status button
    QPushButton* playerStatusButton = new QPushButton("Player Status", this);
    layout->addWidget(playerStatusButton);
    setLayout(layout);

    // Connect buttons to their respective slots
    connect(ui->rollDiceButton, &QPushButton::clicked, this, &form::rollDice);
    connect(playerStatusButton, &QPushButton::clicked, this, &form::showPlayerStatus);

    // Initialize player info
    updatePlayerInfo();
}

// Destructor to clean up dynamically allocated memory
form::~form() {
    delete ui;
    delete gameManager;  // Ensure we delete the GameManager object
}

// Method to initialize player tokens on the board
void form::initializePlayerTokens(int numPlayers) {
    // Define colors for players
    QColor playerColors[] = {Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::cyan, Qt::magenta, Qt::gray, Qt::darkRed};

    // For each player, create a token and place them on the starting grid
    for (int i = 0; i < numPlayers; ++i) {
        Player* player = gameManager->getPlayerByIndex(i);

        // Create a graphical token for each player
        QGraphicsEllipseItem* playerToken = new QGraphicsEllipseItem(0, 0, 10, 10);  // Set player marker size
        playerToken->setBrush(QBrush(playerColors[i % 8]));  // Set player color
        scene->addItem(playerToken);  // Add player token to the scene

        // Place the token on the "Go" grid initially
        QPointF goPosition = convertToQPointF(gameManager->getGridByIndex(0)->calculateRandomPoint());  // Use Grid's random point calculation
        playerToken->setPos(goPosition.x(), goPosition.y());

        // Store the player token in a list for future updates
        playerTokens.append(playerToken);
    }
}

// Method to update the current player's token after movement
void form::updateCurrentPlayerToken(Player* player) {
    Grid* currentGrid = gameManager->getGridByIndex(player->getCurrentGridIndex());

    // Calculate a random point on the current grid and update player's position
    QPointF newPosition = convertToQPointF(currentGrid->calculateRandomPoint());
    player->setPosition(PointF(newPosition.x(), newPosition.y()));  // Set the player's position with PointF

    // Get the current player's index from the player list
    int currentPlayerIndex = gameManager->getCurrentPlayerIndex();

    // Update the current player's token position on the board
    playerTokens[currentPlayerIndex]->setPos(newPosition);

    if(gameManager->ISdoubleRolled==false)
        gameManager->currentPlayerIndex = ( gameManager->currentPlayerIndex + 1) %  gameManager->getPlayers().size();

}

// Method to roll dice and move the current player
void form::rollDice() {
    if (gameManager->waiting_response) {
        // Roll the dice for rent calculation when waiting for response
        int die1 = (rand() % 6) + 1;
        int die2 = (rand() % 6) + 1;
        int totalDice = die1 + die2;

        Player* currentPlayer = gameManager->getCurrentPlayer();
        Player* owner = gameManager->currentPropertyOwner;

        if (gameManager->waiting_response_type == WaitingResponseType::UtilityRent) {
            int rentAmount = totalDice * gameManager->rentMultiplier;

            if (currentPlayer->getBankBalance() >= rentAmount) {
                currentPlayer->updateBankBalance(-rentAmount);
                owner->updateBankBalance(rentAmount);

                QMessageBox::information(this, "Rent Paid", "You rolled a " + QString::number(totalDice) +
                                                                " and paid $" + QString::number(rentAmount) + " rent to " +
                                                                QString::fromStdString(owner->getName()) + ".");
            } else {
                QMessageBox::warning(this, "Cannot Afford Rent", "You don't have enough money to pay the rent.");
            }
        } else if (gameManager->waiting_response_type == WaitingResponseType::RailroadRent) {
            int rentAmount = gameManager->rentMultiplier * totalDice;

            if (currentPlayer->getBankBalance() >= rentAmount) {
                currentPlayer->updateBankBalance(-rentAmount);
                owner->updateBankBalance(rentAmount);

                QMessageBox::information(this, "Rent Paid", "You rolled a " + QString::number(totalDice) +
                                                                " and paid $" + QString::number(rentAmount) + " rent to " +
                                                                QString::fromStdString(owner->getName()) + ".");
            }
        }
        gameManager->waiting_response = false;
        updateCurrentPlayerToken(currentPlayer);
    }
    else {
        if (gameManager->checkWinner() == true) {
            // Get the winner
            Player* winner = gameManager->getWinner();

            // Display a message box to announce the winner
            QMessageBox::information(this, "Game Over", "Congratulations! The winner is " +
                                                            QString::fromStdString(winner->getName()) +
                                                            " with a balance of $" + QString::number(winner->getBankBalance()) + ".");

            // Close the form after the message is shown
            this->close();
        }


        int die1 = (rand() % 6) + 1;
        int die2 = (rand() % 6) + 1;
        Player* currentPlayer = gameManager->getCurrentPlayer();
        bool wantsToPayForJail = false;
        bool wantsToUseJailOutCard = false;

        // Reset the decision flags before any player actions are taken
        bool wantsToBuy = false;
        bool wantsToPayForHouse = false;

        int new_grid_index = die1 + die2;  // Calculate the new grid index

        // Get the current grid and check its type
        Grid* currentGrid = gameManager->getGridByIndex(new_grid_index);
        GameHandler* gameHandler = gameManager->gameHandler;  // Access GameHandler from GameManager

        // Reset decisions at the beginning of each turn
        wantsToBuy = false;
        wantsToPayForHouse = false;


        // Call the movePlayer function with the user's decision
        PlayerAction result = gameManager->movePlayer(die1, die2, wantsToBuy, wantsToPayForHouse, wantsToPayForJail, wantsToUseJailOutCard);

        // Update the current player's token position on the GUI after the move
        updateCurrentPlayerToken(currentPlayer);

        // Handle actions based on the result from GameManager
        handlePlayerAction(result);


        // Update the UI with the dice roll result
        ui->diceResultLabel->setText("You rolled a " + QString::number(die1) + " and " + QString::number(die2));
        updatePlayerInfo();


    }


}




// Handle the outcome of the player's action based on the enum
void form::handlePlayerAction(PlayerAction action) {
    switch (action) {
    case PlayerAction::BuyProperty:
        QMessageBox::information(this, "Property Purchased", "You successfully bought the property.");
        break;
    case PlayerAction::CannotAffordProperty:
        QMessageBox::warning(this, "Cannot Buy Property", "You don't have enough money to buy this property.");
        break;
    case PlayerAction::PaidRent:
        QMessageBox::information(this, "Rent Paid", "You paid rent to the property owner.");
        break;
    case PlayerAction::CannotAffordRent:
        QMessageBox::warning(this, "Cannot Pay Rent", "You don't have enough money to pay the rent.");
        break;
    case PlayerAction::BuildHouse:
        QMessageBox::information(this, "House Built", "You successfully built a house.");
        break;
    case PlayerAction::CannotBuildHouse:
        QMessageBox::warning(this, "Cannot Build House", "You cannot build a house at this time.");
        break;
    case PlayerAction::BuildHotel:
        QMessageBox::information(this, "Hotel Built", "You successfully built a hotel.");
        break;
    case PlayerAction::CannotBuildHotel:
        QMessageBox::warning(this, "Cannot Build Hotel", "You cannot build a hotel at this time.");
        break;
    case PlayerAction::GoToJail:
        QMessageBox::information(this, "Go to Jail", "You are going to jail!");
        break;
    case PlayerAction::FreeParking:
        QMessageBox::information(this, "Free Parking", "You landed on Free Parking. Take a break.");
        break;
    case PlayerAction::SurpriseCardAdvanceToGo:
    case PlayerAction::SurpriseCardDividend:
    case PlayerAction::SurpriseCardGoBack3Spaces:
    case PlayerAction::SurpriseCardGoToJail:
        QMessageBox::information(this, "Surprise Card", "You picked a surprise card.");
        break;
    case PlayerAction::TaxPaid:
        QMessageBox::information(this, "Tax Paid", "You paid the tax.");
        break;
    case PlayerAction::OutOfJail:
        QMessageBox::information(this, "Out of Jail", "You are out of jail!");
        break;
    case PlayerAction::JailTurn:
        QMessageBox::warning(this, "In Jail", "You are still in jail.");
        break;
    case PlayerAction::NoAction:
    default:
        // No action is required
        break;
    }
}

// Method to update the player info in the UI
void form::updatePlayerInfo() {
    Player* currentPlayer = gameManager->getCurrentPlayer();
    QString playerInfo = "Player: " + QString::fromStdString(currentPlayer->getName()) +
                         "\nBalance: $" + QString::number(currentPlayer->getBankBalance()) +
                         "\nPosition: " + QString::fromStdString(currentPlayer->getCurrentGrid());

    ui->playerInfoLabel->setText(playerInfo);  // Display player info in the UI
}

// Method to display detailed player status in a message box
void form::showPlayerStatus() {
    Player* currentPlayer = gameManager->getCurrentPlayer();

    QString playerStatus = "Player: " + QString::fromStdString(currentPlayer->getName()) + "\n";
    playerStatus += "Balance: $" + QString::number(currentPlayer->getBankBalance()) + "\n";
    playerStatus += "Position: " + QString::fromStdString(currentPlayer->getCurrentGrid()) + "\n";
    playerStatus += "Houses: " + QString::number(currentPlayer->getNumHouses()) + "\n";
    playerStatus += "Hotels: " + QString::number(currentPlayer->getNumHotels()) + "\n";
    playerStatus += "Get Out of Jail Cards: " + QString::number(currentPlayer->getOutOfJailCards()) + "\n";

    // Display owned properties
    playerStatus += "Properties:\n";
    std::vector<PropertyGrid*> properties = currentPlayer->getOwnedProperties();
    if (!properties.empty()) {
        for (PropertyGrid* property : properties) {
            playerStatus += "  - " + QString::fromStdString(property->getName()) +
                            " (Rent: $" + QString::number(property->getRent()) + ")\n";
        }
    } else {
        playerStatus += "  None\n";
    }

    // Show the player's status in a message box
    QMessageBox::information(this, "Player Status", playerStatus);
}
