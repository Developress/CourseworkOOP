#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QMessageBox>

#include "maze.h"

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
    void selectTheme();
    void selectDifficulty();
    void startGame();
private:
    enum {COUNT=3}; // The count of themes and difficulties
    enum {PINK, BLUE, GREEN}; // The enum with themes values, 0 - pink, 1 - blue, 2 - green
    enum {LOW, MEDIUM, HIGH}; // The enum with difficulty values, 0 - low, 1 - medium, 2 - high
    enum {MAZE_IMAGE_WIDTH = 500, MAZE_IMAGE_HEIGHT = 250}; // The enum with maze image dimentions
    enum {TEXT_WIDTH = 400, TEXT_HEIGHT = 150}; // The enum with text dimentions
    enum {BUTTON_WIDTH = 200, BUTTON_HEIGHT = 70}; // The enum with button dimentions
    enum {THEMES_BUTTON_SIZE = 150}; // The enum with themes button size
    enum {LOW_SIZE = 11, MEDIUM_SIZE = 15, HIGH_SIZE = 19}; // The enum with sizes of maze
    enum {WIDGET_WIDTH = 1000, WIDGET_HEIGHT = 800}; // The enum with widget dimentions
    enum {EXTRA_WIDTH = 1050, EXTRA_HEIGH = 950}; // The enum with extra width and height

    int size; // The size of the maze
    int currentRow; // The current row, where the player is situated
    int currentColumn; // The current column, where the player is situated
    int selectedTheme; // The theme, selected by player
    int selectedDifficulty; // The difficulty, selected by player
    int **mazeGrid; // The double pointer to the maze grid, created after the maze is generated, consists of 0 and 1, 0 - represent walls, 1 - the cell which can be passed

    static QString gradients[COUNT]; // The static array with gradient values for background for different themes
    static QString difficultyValues[COUNT]; // The static array with difficulty values

    Maze maze; // The maze object

    QVBoxLayout *mainLayout; // The layout used for arranging the elements on start, select theme and select difficulty pages
    QLabel *mazeImage; // The label with image on the start page
    QLabel *text; // The text label on start, select theme ans select difficulty pages
    QPushButton *button; // The start game button

    QPushButton *themes[COUNT]; // The array with buttons to select the theme
    QHBoxLayout *themesLayout; // The layout for themes buttons
    QWidget *themesWidget; // The widget for themes layout

    QPushButton *difficulties[COUNT]; // The array with buttons to select the difficulty

    QGridLayout *gridLayout; // The grid layout to display the maze
    QLabel ***mazeLabels; // The 2 dimentional array with pointers to labels representing walls or cells to be passed

    Ui::MainWindow *ui; // The pointer to the ui

    void startScreen();
    void selectThemeScreen();
    void selectDifficultyScreen();
    void displayMaze();
    void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
