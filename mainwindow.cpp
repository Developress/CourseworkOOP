#include "mainwindow.h"
#include "ui_mainwindow.h"

// The initialisation of array with gradient values for background for different themes
QString MainWindow::gradients[COUNT] = {"background-color: qlineargradient(spread:pad, x1:0.507, y1:1, x2:0.498, y2:0, stop:0 rgba(161, 140, 209, 255), stop:1 rgba(251, 194, 235, 255));",
                                        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(79, 172, 254, 255), stop:1 rgba(0, 242, 254, 255));",
                                        "background-color: qlineargradient(spread:pad, x1:0.517413, y1:1, x2:0.453, y2:0, stop:0 rgba(155, 225, 93, 255), stop:1 rgba(0, 227, 174, 255));"};

// The initialisation of array with difficulty values
QString MainWindow::difficultyValues[COUNT] = {"Low", "Medium", "High"};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // The constructor of MainWindow class. Initializes the fields with initial values.

    ui->setupUi(this);
    setWindowTitle("Maze Game");

    size = 0;
    currentRow = 0;
    currentColumn = 0;
    selectedTheme = 0;
    selectedDifficulty = 0;
    mazeGrid = nullptr;

    mainLayout = nullptr;
    mazeImage = nullptr;
    text = nullptr;
    button = nullptr;

    for(int i = 0; i < COUNT; i++){
        themes[i] = nullptr;
        difficulties[i] = nullptr;
    }

    themesLayout = nullptr;
    themesWidget = nullptr;

    gridLayout = nullptr;
    mazeLabels = nullptr;

    // Display the start screen
    startScreen();
}

MainWindow::~MainWindow()
{
    // Free the memory
    delete ui;

    if(mazeLabels){
        for(int i = 0; i < 2*size + 1; i++){
            for(int j = 0; j < 2*size + 1; j++){
                delete mazeLabels[i][j];
            }
        }

        for(int i = 0; i < 2*size + 1; i++){
            delete [] mazeLabels[i];
        }

        delete [] mazeLabels;
    }

    if(gridLayout){
        delete gridLayout;
    }
}

void MainWindow::startScreen(){
    // This method is called when the start screen is displayed
    // Alloc the memory for layout and its items
    mainLayout = new QVBoxLayout;
    mazeImage = new QLabel;
    text = new QLabel;
    button = new QPushButton;

    // Set the maze image
    mazeImage->setFixedSize(MAZE_IMAGE_WIDTH, MAZE_IMAGE_HEIGHT);
    QPixmap pixmap("://img/maze.png");
    mazeImage->setPixmap(pixmap.scaled(mazeImage->width(), mazeImage->height(), Qt::IgnoreAspectRatio));
    mainLayout->addWidget(mazeImage);
    mainLayout->setAlignment(mazeImage, Qt::AlignHCenter);

    // Set the text label
    text->setFixedSize(TEXT_WIDTH, TEXT_HEIGHT);
    text->setAlignment(Qt::AlignCenter);
    text->setText("MAZE GAME");
    text->setStyleSheet("color: qlineargradient(spread:pad, x1:0.507, y1:1, x2:0.498, y2:0, stop:0 rgba(161, 140, 209, 255), stop:1 rgba(251, 194, 235, 255));"
                            "font: 87 30pt \"Lato Black\";");
    mainLayout->addWidget(text);
    mainLayout->setAlignment(text, Qt::AlignHCenter);

    // Set the button to start
    button->setText("START");
    button->setStyleSheet("border-radius: 20px;"
                         "border-style: solid;"
                         "border-width: 0px;"
                         "color: rgb(255, 255, 255);"
                         "font: 87 15pt \"Lato Black\";"
                         "background-color: qlineargradient(spread:pad, x1:0.507, y1:1, x2:0.498, y2:0, stop:0 rgba(161, 140, 209, 255), stop:1 rgba(251, 194, 235, 255));");
    button->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    mainLayout->addWidget(button);
    mainLayout->setAlignment(button, Qt::AlignHCenter);
    connect(button, SIGNAL(clicked()), this, SLOT(selectTheme()));

    // Set the layout
    ui->centralwidget->setLayout(mainLayout);
}

void MainWindow::selectTheme(){
    // This method is called when the start button is pressed
    selectThemeScreen();
}

void MainWindow::selectThemeScreen(){
    // This method is called when the select theme screen is displayed
    // Free the memory of widgets that are not needed anymore
    mainLayout->removeWidget(mazeImage);
    delete mazeImage;
    mainLayout->removeWidget(button);
    delete button;

    // Alloc the memory for themes layout, widget and buttons
    themesLayout = new QHBoxLayout;
    themesWidget = new QWidget;

    for(int i = 0; i < COUNT; i++){
        themes[i] = new QPushButton;
        connect(themes[i], SIGNAL(clicked()), this, SLOT(selectDifficulty()));
    }

    // Set the text label
    text->setText("Choose Theme:");

    // Set the themes buttons
    for(int i = 0; i < COUNT; i++){
        themes[i]->setFixedSize(THEMES_BUTTON_SIZE, THEMES_BUTTON_SIZE);
        themes[i]->setStyleSheet("border-radius: 75px;"
                                 "border-style:solid;"
                                 "border-width:0px;" + gradients[i]);
        themesLayout->addWidget(themes[i]);
        themesLayout->setAlignment(themes[i], Qt::AlignCenter);
    }

    // set the themes layout, widget and alignment
    themesWidget->setLayout(themesLayout);
    mainLayout->addWidget(themesWidget);
    mainLayout->setAlignment(themesLayout, Qt::AlignCenter);
}

void MainWindow::selectDifficulty(){
    // This method is called when the theme is selected
    // Determine the theme button that sent a signal
    QPushButton *button = (QPushButton*) sender();

    // Set the selected theme value
    if(button == themes[PINK]){
        selectedTheme = PINK;
    }
    if(button == themes[BLUE]){
        selectedTheme = BLUE;
    }
    if(button == themes[GREEN]){
        selectedTheme = GREEN;
    }

    // display the next screen
    selectDifficultyScreen();
}

void MainWindow::selectDifficultyScreen(){
    // This method is called when the select difficulty screen is displayed
    // Free the memory of widgets that are not needed anymore
    mainLayout->removeWidget(themesWidget);

    for(int i = 0; i < COUNT; i++){
        delete themes[i];
    }

    delete themesLayout;
    delete themesWidget;

    // Alloc the memory for difficulties buttons
    for(int i = 0; i < COUNT; i++){
        difficulties[i] = new QPushButton;
        connect(difficulties[i], SIGNAL(clicked()), this, SLOT(startGame()));
    }

    // Set text label
    text->setText("Choose difficulty:");

    // Set the difficulties buttons
    for(int i = 0; i < COUNT; i++){
        difficulties[i]->setText(difficultyValues[i]);
        difficulties[i]->setStyleSheet("border-radius: 20px;"
                             "border-style: solid;"
                             "border-width: 0px;"
                             "color: rgb(255, 255, 255);"
                             "font: 87 15pt \"Lato Black\";"
                             "background-color: qlineargradient(spread:pad, x1:0.507, y1:1, x2:0.498, y2:0, stop:0 rgba(161, 140, 209, 255), stop:1 rgba(251, 194, 235, 255));");
        difficulties[i]->setFixedSize(200, 70);
        mainLayout->addWidget(difficulties[i]);
        mainLayout->setAlignment(difficulties[i], Qt::AlignHCenter);
    }
}

void MainWindow::startGame(){
    // This method is called when the difficulty is selected
    // Determine the difficulty button that sent a signal
    QPushButton *button = (QPushButton*) sender();

    // Set the selected difficulty value
    if(button == difficulties[LOW]){
        selectedDifficulty = LOW;
        size = LOW_SIZE;
    }
    if(button == difficulties[MEDIUM]){
        selectedDifficulty = MEDIUM;
        size = MEDIUM_SIZE;
    }
    if(button == difficulties[HIGH]){
        selectedDifficulty = HIGH;
        size = HIGH_SIZE;
    }

    // Create the maze and generate the maze grid
    maze = Maze(size);
    mazeGrid = maze.generateMaze(selectedDifficulty);

    // Display the maze
    displayMaze();
}


void MainWindow::displayMaze(){
    // This method is called after the game is started
    // Free the memory of widgets that are not needed anymore
    mainLayout->removeWidget(text);
    delete text;

    for(int i = 0; i < COUNT; i++){
        mainLayout->removeWidget(difficulties[i]);
        delete difficulties[i];
    }

    // Set the background that corresponds to chosen theme
    centralWidget()->setStyleSheet(gradients[selectedTheme]);

    // Delete the main layout, because the layout with maze grid will be specified
    delete mainLayout;

    // Initialize the pixmap which will be set to cells that can be passed
    QPixmap pass("://img/pass.png");

    // Alloc memory for maze labels
    mazeLabels = new QLabel**[2*size + 1];

    for(int i =0; i<2 * size +1; i++){
        mazeLabels[i] = new QLabel*[2*size +1];
    }

    // Specify the enter and exit
    mazeGrid[1][0] = 1;
    mazeGrid[2*size-1][2*size] = 1;

    // Alloc memory for grid layout and set margin and spacing to 0
    gridLayout = new QGridLayout;
    gridLayout->setMargin(0);
    gridLayout->setSpacing(0);

    for(int i = 0; i < 2*size + 1; i++){
        for(int j = 0; j < 2*size + 1; j++){
            // Alloc memory for maze labels and set the appropriate image if the cell can be passed and transparent background otherwise
            mazeLabels[i][j] = new QLabel;
            if(mazeGrid[i][j] == 1){
                mazeLabels[i][j]->setPixmap(pass);
            } else {
                mazeLabels[i][j]->setStyleSheet("background: transparent;");
            }
            gridLayout->addWidget(mazeLabels[i][j], i, j);
        }
    }

    // Fix the position of a player
    currentRow = 1;
    currentColumn = 0;

    // Initialize the pixmaps with player and exit
    QPixmap hamster("://img/hamster.png");
    QPixmap exit("://img/cheese.png");

    centralWidget()->setFixedSize(WIDGET_WIDTH, WIDGET_HEIGHT);

    // Set the pixmaps with player and exit
    mazeLabels[1][0]->setPixmap(hamster.scaled(EXTRA_WIDTH/gridLayout->columnCount(), EXTRA_HEIGH/gridLayout->columnCount(), Qt::IgnoreAspectRatio));
    mazeLabels[2*size-1][2*size]->setPixmap(exit.scaled(WIDGET_WIDTH/gridLayout->columnCount(), WIDGET_WIDTH/gridLayout->columnCount(), Qt::IgnoreAspectRatio));

    // Set the layout
    centralWidget()->setLayout(gridLayout);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    // This method is called when the key is pressed
    // Initialize the pixmaps with player and pass
    QPixmap hamster("://img/hamster.png");
    QPixmap pass("://img/pass.png");

    // Get the pressed key
    Qt::Key keyPressed = (Qt::Key)event->key();

    // Declare the pointers to current and next cells
    QLabel *next = nullptr;
    QLabel *current = mazeLabels[currentRow][currentColumn];

    if(keyPressed == Qt::Key_W){
        if(currentRow - 1 > 0){
            // if top neighbour can be visited, then visit it
            if(mazeGrid[currentRow - 1][currentColumn] == 1){
                next = mazeLabels[currentRow - 1][currentColumn];
                currentRow -= 1;
            }
        }
    }

    if(keyPressed == Qt::Key_D){
        if(currentColumn + 1 < 2*size+1){
            // if right neighbour can be visited, then visit it
            if(mazeGrid[currentRow][currentColumn + 1] == 1){
                next = mazeLabels[currentRow][currentColumn + 1];
                currentColumn += 1;
            }
        }
    }

    if(keyPressed == Qt::Key_S){
        if(currentRow + 1 < 2*size + 1){
            // if bottom neighbour can be visited, then visit it
            if(mazeGrid[currentRow + 1][currentColumn] == 1){
                next = mazeLabels[currentRow + 1][currentColumn];
                currentRow += 1;
            }
        }
    }

    if(keyPressed == Qt::Key_A){
        if(currentColumn - 1 > 0){
            // if left neighbour can be visited, then visit it
            if(mazeGrid[currentRow][currentColumn - 1] == 1){
                next = mazeLabels[currentRow][currentColumn - 1];
                currentColumn -= 1;
            }
        }
    }

    // if next cell is visited, then set the appropriate pixmaps
    if(next != nullptr){
        next->setPixmap(hamster.scaled(EXTRA_WIDTH/gridLayout->columnCount(), EXTRA_HEIGH/gridLayout->columnCount(), Qt::IgnoreAspectRatio));
        current->setPixmap(pass);
    }

    // if user has gone to the end, then display the message about victory and close the app
    if(currentRow == 2*size - 1 && currentColumn == 2*size){
        QMessageBox::information(this, tr("You won!"),
                                 tr("Congratulations! You won!!!"));
        close();
    }
}
