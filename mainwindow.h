#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "maze.h"
#include <QLabel>
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onButtonClick();
    void themeSelected();
    void playGame();
private:
    enum {COUNT=3};
    enum {PINK, BLUE, GREEN};
    enum {LOW, MEDIUM, HIGH};
    Ui::MainWindow *ui;
    QGridLayout *gridLayout;
    QLabel ***mazeGrid;
    int size;
    void displayMaze();
    int **mazeMatrix;
    void showOnEdit();
    void startScreen();
    QPushButton *button;
    QVBoxLayout *layout;
    QLabel *mazeImage;
    QLabel *text;
    QWidget *themesWidget;
    int selectedTheme;
    QPushButton *themes[COUNT];
    static QString gradients[COUNT];
    static QString difficultyValues[COUNT];
    QHBoxLayout *themesLayout;
    QPushButton *difficulties[COUNT];
    int selectedDifficulty;
    Maze maze;
    void chooseTheme();
    void chooseDifficulty();
};
#endif // MAINWINDOW_H
