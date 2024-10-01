#ifndef FORM_H
#define FORM_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QVector>
#include "gamehandler.h"
#include "gamemanager.h"

namespace Ui {
class form;
}

class form : public QDialog
{
    Q_OBJECT

public:
    explicit form(QWidget *parent = nullptr, int numPlayers = 2);  // Constructor that takes the number of players
    ~form();  // Destructor
    QPointF convertToQPointF(const PointF& point) {
        return QPointF(point.x, point.y);
    }

private slots:
    void updateCurrentPlayerToken(Player* player);  // Add this in your private section
    void handlePlayerAction(PlayerAction action);

    void rollDice();  // Slot for when the roll dice button is pressed
    void updatePlayerInfo();  // Slot to update player info on the UI
    void showPlayerStatus();  // Slot to show player status in a message box
private:
    Ui::form *ui;  // UI object
    QGraphicsScene *scene;  // Graphics scene for the game board
    GameManager *gameManager;  // Pointer to the GameManager object

    QVector<QGraphicsEllipseItem*> playerTokens;  // Vector to store player tokens (graphical representations)

    void initializePlayerTokens(int numPlayers);  // Initializes player tokens on the board
    void updatePlayerTokens();  // Updates player tokens' positions after moves
};

#endif // FORM_H
