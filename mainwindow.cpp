#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QDialog>
#include <QPointF>
#include <QString>
#include <QMainWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set up the spin box for player selection (2 to 8 players)
    ui->startButton_2->setRange(2, 8);
    ui->startButton_2->setValue(2); // Default value

    // Enable the start button initially
    ui->startButton->setEnabled(true);

    // Connect spinBox valueChanged signal to enable/disable the start button
    connect(ui->startButton_2, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value) {
        ui->startButton->setEnabled(value >= 2 && value <= 8);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    int numPlayers = ui->startButton_2->value();

    // Create the game form and pass the number of players
    formWindow = new form(nullptr, numPlayers);  // Pass numPlayers here
    formWindow->show();

    this->close(); // Close the start window
}
