#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

#include "form.h"  // Include the next form header

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked(); // Slot for handling start button click

private:
    Ui::MainWindow *ui;
    form *formWindow; // Pointer to the next form (game window)
};

#endif // MAINWINDOW_H
