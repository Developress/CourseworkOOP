#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

QString MainWindow::gradients[COUNT] = {"background-color: qlineargradient(spread:pad, x1:0.507, y1:1, x2:0.498, y2:0, stop:0 rgba(161, 140, 209, 255), stop:1 rgba(251, 194, 235, 255));",
                                        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(79, 172, 254, 255), stop:1 rgba(0, 242, 254, 255));",
                                        "background-color: qlineargradient(spread:pad, x1:0.517413, y1:1, x2:0.453, y2:0, stop:0 rgba(155, 225, 93, 255), stop:1 rgba(0, 227, 174, 255));"};

QString MainWindow::difficultyValues[COUNT] = {"Low", "Medium", "High"};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Maze Game");
    button = new QPushButton;
    layout = new QVBoxLayout;
    mazeImage = new QLabel;
    text = new QLabel;
    for(int i = 0; i < COUNT; i++){
        themes[i] = new QPushButton;
        connect(themes[i], SIGNAL(clicked()), this, SLOT(themeSelected()));
        difficulties[i] = new QPushButton;
        connect(difficulties[i], SIGNAL(clicked()), this, SLOT(playGame()));
    }
    themesLayout = new QHBoxLayout;
    themesWidget = new QWidget;
    connect(button, SIGNAL(clicked()), this, SLOT(onButtonClick()));
    startScreen();
    mazeMatrix = nullptr;
    //displayMaze();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButtonClick(){
    QPushButton *button = (QPushButton*) sender();
    if(button->text() == "START"){
        chooseTheme();
    }
}

void MainWindow::themeSelected(){
    QPushButton *button = (QPushButton*) sender();
    if(button == themes[PINK]){
        selectedTheme = PINK;
    }
    if(button == themes[BLUE]){
        selectedTheme = BLUE;
    }
    if(button == themes[GREEN]){
        selectedTheme = GREEN;
    }
    chooseDifficulty();
}

void MainWindow::playGame(){
    QPushButton *button = (QPushButton*) sender();
    if(button == difficulties[LOW]){
        selectedDifficulty = LOW;
        size = 11;
    }
    if(button == difficulties[MEDIUM]){
        selectedDifficulty = MEDIUM;
        size = 15;
    }
    if(button == difficulties[HIGH]){
        selectedDifficulty = HIGH;
        size = 19;
    }
    maze = Maze(size, size);
    mazeMatrix = maze.generateMaze(selectedDifficulty);
    displayMaze();
}

void MainWindow::startScreen(){
    mazeImage->setFixedSize(500, 250);
    QPixmap pixmap("://img/maze.png");
    mazeImage->setPixmap(pixmap.scaled(mazeImage->width(),mazeImage->height(),Qt::IgnoreAspectRatio));
    layout->addWidget(mazeImage);
    layout->setAlignment(mazeImage, Qt::AlignHCenter);

    text->setFixedSize(400, 150);
    text->setAlignment(Qt::AlignCenter);
    text->setText("MAZE GAME");
    text->setStyleSheet("color: qlineargradient(spread:pad, x1:0.507, y1:1, x2:0.498, y2:0, stop:0 rgba(161, 140, 209, 255), stop:1 rgba(251, 194, 235, 255));"
                            "font: 87 30pt \"Lato Black\";");
    layout->addWidget(text);
    layout->setAlignment(text, Qt::AlignHCenter);

    button->setText("START");
    button->setStyleSheet("border-radius: 20px;"
                         "border-style: solid;"
                         "border-width: 0px;"
                         "color: rgb(255, 255, 255);"
                         "font: 87 15pt \"Lato Black\";"
                         "background-color: qlineargradient(spread:pad, x1:0.507, y1:1, x2:0.498, y2:0, stop:0 rgba(161, 140, 209, 255), stop:1 rgba(251, 194, 235, 255));");
    button->setFixedSize(200, 70);
    layout->addWidget(button);
    layout->setAlignment(button, Qt::AlignHCenter);
    ui->centralwidget->setLayout(layout);
}

void MainWindow::chooseTheme(){
    layout->removeWidget(mazeImage);
    layout->removeWidget(button);
    mazeImage->hide();
    button->hide();
    text->setText("Choose Theme:");
    for(int i = 0; i < COUNT; i++){
        themes[i]->setFixedSize(150, 150);
        themes[i]->setStyleSheet("border-radius: 75px;"
                                 "border-style:solid;"
                                 "border-width:0px;" + gradients[i]);
        themesLayout->addWidget(themes[i]);
        themesLayout->setAlignment(themes[i], Qt::AlignCenter);
    }
    themesWidget->setLayout(themesLayout);
    layout->addWidget(themesWidget);
    layout->setAlignment(themesLayout, Qt::AlignCenter);
}

void MainWindow::chooseDifficulty(){
    layout->removeWidget(themesWidget);
    themesWidget->hide();
    text->setText("Choose difficulty:");
    for(int i = 0; i < COUNT; i++){
        difficulties[i]->setText(difficultyValues[i]);
        difficulties[i]->setStyleSheet("border-radius: 20px;"
                             "border-style: solid;"
                             "border-width: 0px;"
                             "color: rgb(255, 255, 255);"
                             "font: 87 15pt \"Lato Black\";"
                             "background-color: qlineargradient(spread:pad, x1:0.507, y1:1, x2:0.498, y2:0, stop:0 rgba(161, 140, 209, 255), stop:1 rgba(251, 194, 235, 255));");
        difficulties[i]->setFixedSize(200, 70);
        layout->addWidget(difficulties[i]);
        layout->setAlignment(difficulties[i], Qt::AlignHCenter);
    }
}
void MainWindow::displayMaze(){
    text->hide();
    for(int i = 0; i < COUNT; i++){
        difficulties[i]->hide();
    }
    centralWidget()->setStyleSheet(gradients[selectedTheme]);
    delete layout;
    mazeGrid = new QLabel**[2 * size + 1];
    QPixmap pass("://img/pass.png");
    QPixmap enter("://img/enter.png");
    for(int i =0; i<2 * size +1; i++){
        mazeGrid[i] = new QLabel*[2 * size +1];
    }
    mazeMatrix[1][0] = 1;
    mazeMatrix[2*size-1][2*size] = 1;
    gridLayout = new QGridLayout;
    gridLayout->setMargin(0);
    gridLayout->setSpacing(0);
    for(int i =0; i< 2 * size + 1; i++){
        for(int j = 0; j<2 * size + 1; j++){
            mazeGrid[i][j] = new QLabel;
            //add image
            if(mazeMatrix[i][j] == 1){
                mazeGrid[i][j]->setPixmap(pass);
            } else {
                mazeGrid[i][j]->setStyleSheet("background: transparent;");
            }
            gridLayout->addWidget(mazeGrid[i][j], i, j);
        }
    }
    mazeGrid[1][0]->setPixmap(enter);
    mazeGrid[2*size-1][2*size]->setPixmap(enter);
    centralWidget()->setFixedSize(1000, 800);
    centralWidget()->setLayout(gridLayout);
}
