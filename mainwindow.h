#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "maze.h"
#include <QLabel>
#include <QMainWindow>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGridLayout *gridLayout;
    QLabel ***mazeGrid;
    int size;
    void displayMaze();
    int **mazeMatrix;
    void showOnEdit();
};
#endif // MAINWINDOW_H
