#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    size = 11;
    mazeMatrix = nullptr;
    Maze maze = Maze(size, size);
    maze.generateMaze();
    mazeMatrix = maze.generateGrid();
    displayMaze();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showOnEdit(){
    QString str="";
    int newRows = 2*size + 1;
    int newColumns = 2*size + 1;
    for(int i = 0; i < newRows; i++){
        for(int j = 0; j < newColumns; j++){
            if(mazeMatrix[i][j] == 1){
                str += "   ";
            } else {
               str += "#  ";
            }
        }
        str+="\n";
    }
}
void MainWindow::displayMaze(){
    mazeGrid = new QLabel**[2 * size + 1];
    QPixmap pass("://img/pass.png");
    QPixmap wall("://img/wall.png");
    for(int i =0; i<2 * size +1; i++){
        mazeGrid[i] = new QLabel*[2 * size +1];
    }

    gridLayout = new QGridLayout;
    for(int i =0; i< 2 * size + 1; i++){
        for(int j = 0; j<2 * size + 1; j++){
            mazeGrid[i][j] = new QLabel;
            //add image
            if(mazeMatrix[i][j] == 1){
                mazeGrid[i][j]->setPixmap(pass);
            } else {
                mazeGrid[i][j]->setPixmap(wall);
            }
            mazeGrid[i][j]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            gridLayout->addWidget(mazeGrid[i][j], i, j);
        }
    }
    centralWidget()->setLayout(gridLayout);
}
