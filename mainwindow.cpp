/**
 * Name: Allison So
 * Description: mainwindow class file creates the main window where the game will be played,
 * and handles default game functionality (button click, handling neighbours and the hints displayed)
 * Date: 2/6/2025
 * */
#include "mainwindow.h"
#include "customButton.h"

/**
 * Name: mainwindow default constructor
 * Description: Default constructor for mainwindow, initializes the window with a parent widget.
 * Parameters: QWidget pointer called parent - the parent widget.
 * Return: None
 * */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setUp();
}

/**
 * Name: setUp
 * Description: Sets up the Minesweeper game board by creating a grid of buttons and placing mines randomly.
 * Parameters: None
 * Return: None
 * */
void MainWindow::setUp(){
    // Set up Main Window with minesweeper grid of buttons, randomizing mines whenever function called
    mines.clear();
    openCount = 0;
    // Create grid to store buttons
    board = new QGridLayout();
    board->setHorizontalSpacing(0);
    board->setVerticalSpacing(0);
    board->setContentsMargins(0, 0, 0, 0);

    // Generate random mines
    while (mines.size() < 99){
        // Generate random col between 0 and 29
        int col = QRandomGenerator::global()->bounded(30);
        // Generate random row between 0 and 15
        int row = QRandomGenerator::global()->bounded(16);

        QPoint mine(row, col);

        // Check if mine already exists at this location:
        if (!mines.contains(mine)){
            // Input location (row, col) in array
            mines.append(mine);
        } else {
            continue;
        }
    }

    // Set up buttons
    for (int rcount = 0; rcount < 16; rcount++){
        for (int ccount = 0; ccount < 30; ccount++){
            // for every space in the 30x16 grid
            // Create the button
            buttons[rcount][ccount] = new customButton(this);
            QIcon icon(":/icons/icons/0.svg.png");
            buttons[rcount][ccount]->setProperty("flag", "u");
            buttons[rcount][ccount]->setIcon(icon);
            buttons[rcount][ccount]->setIconSize(QSize(25,25));
            buttons[rcount][ccount]->setFixedSize(18,25);
            QSizePolicy policy = this->sizePolicy();
            policy.setRetainSizeWhenHidden(true);
            buttons[rcount][ccount]->setSizePolicy(policy);

            // Store row and col to check for mines later
            buttons[rcount][ccount]->setProperty("row", rcount);
            buttons[rcount][ccount]->setProperty("col", ccount);

            // Connect button signal to appropriate slot
            connect(buttons[rcount][ccount], &customButton::released, this, &MainWindow::handleButton);
            // Add button to grid
            board->addWidget(buttons[rcount][ccount], rcount, ccount);
        }
    }

    // Create platform for board layout
    QWidget *platform = new QWidget(this);
    platform->setLayout(board);
    setCentralWidget(platform);
}

/**
 * Name: handleButton
 * Description: Handles the click event on any button in the Minesweeper grid. Checks if the clicked button is a mine or not and reveals surrounding squares.
 * Parameters: None
 * Return: None
 * */
void MainWindow::handleButton()
{
    // Handles clicking any button in the Minesweeper grid
    // retrieve button clicked
    customButton* clicked = qobject_cast<customButton*>(sender());

    if (clicked){
        int row = clicked->property("row").toInt();
        int col = clicked->property("col").toInt();

        // Check if clicked button is sitting on a mine!
        QPoint isMine(row, col);
        if(mines.contains(isMine)){   // ITS A MINE, GAME OVER

            for (const QPoint& mine : mines){
                // show all mines on board
                buttons[mine.x()][mine.y()]->setVisible(true);
                QIcon icon(":/icons/icons/mine.png");
                buttons[mine.x()][mine.y()]->setIcon(icon);
            }

            // Game over pop up
            QMessageBox gameOver;
            QPixmap gameOverIcon(":/icons/icons/dead.png");
            gameOver.setIconPixmap(gameOverIcon);
            gameOver.setWindowTitle("Uh Oh!");
            gameOver.setText("You have hit a mine and exploded.");
            gameOver.setStandardButtons(QMessageBox::Retry | QMessageBox::Close);

            int btnClicked = gameOver.exec();
            if(btnClicked == QMessageBox::Retry){
                // Retry
                setUp();
            }else if(btnClicked == QMessageBox::Close){
                // Close
                QApplication::quit();
            }
        }else{                         // PHEW, NO MINE
            if (clicked->isVisible()){
                clicked->setVisible(false);
                openCount++;
            }

            // Prepare to provide hints in adjacent squares
            // for each neighbouring square, check it's neighbours for #mines nearby
            QVector<QPoint> neighbours = {
                QPoint(row, col-1), QPoint(row, col+1), QPoint(row-1, col),
                QPoint(row+1, col), QPoint(row-1, col-1), QPoint(row-1, col+1),
                QPoint(row+1, col-1), QPoint(row+1, col+1)
            };

            // for every neighbouring square, check the neighbours of that neighbour for mines
            for (const QPoint& neighbour:neighbours){
                // first, making sure neighbours are being accessed correctly
                if (neighbour.x()>=0 && neighbour.x()<16 && neighbour.y()>=0 && neighbour.y()<30){
                    int nRow = neighbour.x();
                    int nCol = neighbour.y();
                    customButton* nButton = buttons[nRow][nCol];

                    // count mines in neighbours of neighbour
                    int count = 0;
                    QVector<QPoint> nNeighbours = {
                        QPoint(nRow, nCol-1), QPoint(nRow, nCol+1), QPoint(nRow-1, nCol),
                        QPoint(nRow+1, nCol), QPoint(nRow-1, nCol-1), QPoint(nRow-1, nCol+1),
                        QPoint(nRow+1, nCol-1), QPoint(nRow+1, nCol+1)
                    };

                    for (const QPoint& nNeighbour:nNeighbours){
                        if (nNeighbour.x()>=0 && nNeighbour.x()<16 && nNeighbour.y()>=0 && nNeighbour.y()<30){
                            if (mines.contains(QPoint(nNeighbour.x(),nNeighbour.y()))){
                                count++;
                            }
                        }
                    }

                    if (count>0){
                        if (nButton->property("flag")=="u"){
                            // set neighbour icon to mine count if there are neighbouring mines
                            QIcon icon(":/icons/icons/"+QString::number(count)+".svg.png");
                            nButton->setIcon(icon);
                            nButton->setIconSize(QSize(25,25));
                        }
                    }
                    else{
                        // if no neighbouring mines, hide the neighbour
                        if (nButton->isVisible()){
                            nButton->setVisible(false);
                            openCount++;
                        }

                        bool isDone = false;
                        nRow = nButton->property("row").toInt();    //zero button: button with no neighbouring mines
                        nCol = nButton->property("col").toInt();

                        while (!isDone){
                            //if no neighbouring mines, check neighbours of zero btn for other zero btns
                            checkNeighbours(nRow, nCol);
                            isDone = true;
                        }
                    }
                }
            }

            // Check if user won!
            if (openCount==totalOpen) {
                QMessageBox youWon;
                QPixmap youWonIcon(":/icons/icons/alive.png");
                gameOver.setIconPixmap(youWonIcon);
                youWon.setWindowTitle("Hurray!");
                youWon.setText("Congratulations! You have won the game.");
                QPushButton *playAgain = youWon.addButton(tr("Play Again"), QMessageBox::AcceptRole);
                QPushButton *quitGame = youWon.addButton(QMessageBox::Close);

                youWon.exec();
                if(youWon.clickedButton() == playAgain){
                    // Play Again
                    setUp();
                }else if(youWon.clickedButton() == quitGame){
                    // Close
                    QApplication::quit();
                }
            }
        }
    }
}

/**
 * Name: checkNeighbours
 * Description: Recursively checks all adjacent "empty" buttons and opens them if they have no neighboring mines.
 * Parameters: int nRow - row of the current button to check, int nCol - column of the current button to check.
 * Return: None
 * */
void MainWindow::checkNeighbours(int nRow, int nCol)
{
    //recursive check for empty neighbours, opens all neighbouring zero buttons
    QVector<QPoint> cNeighbours = {
        QPoint(nRow, nCol-1), QPoint(nRow, nCol+1), QPoint(nRow-1, nCol),
        QPoint(nRow+1, nCol), QPoint(nRow-1, nCol-1), QPoint(nRow-1, nCol+1),
        QPoint(nRow+1, nCol-1), QPoint(nRow+1, nCol+1)
    };

    for (const QPoint& cNeighbour:cNeighbours){
        if (cNeighbour.x()>=0 && cNeighbour.x()<16 && cNeighbour.y()>=0 && cNeighbour.y()<30){
            //if valid neighbour btn, check if neighbour is zero btn
            int cRow = cNeighbour.x();  //get zero btn neighbour
            int cCol = cNeighbour.y();
            customButton* cButton = buttons[cRow][cCol];

            if (!cButton->isVisible()){
                continue;       //skip if already clicked
            }

            int cCount = 0;
            QVector<QPoint> zNeighbours = {
                QPoint(cRow, cCol-1), QPoint(cRow, cCol+1), QPoint(cRow-1, cCol),
                QPoint(cRow+1, cCol), QPoint(cRow-1, cCol-1), QPoint(cRow-1, cCol+1),
                QPoint(cRow+1, cCol-1), QPoint(cRow+1, cCol+1)
            };

            for (const QPoint& zNeighbour:zNeighbours){
                if (zNeighbour.x()>=0 && zNeighbour.x()<16 && zNeighbour.y()>=0 && zNeighbour.y()<30){
                    if (mines.contains(QPoint(zNeighbour.x(),zNeighbour.y()))){
                        cCount++;
                    }
                }
            }

            if (cCount==0) {
                cButton->setVisible(false);
                checkNeighbours(cRow, cCol);    // recursive to get rid of all empty squares nearby
            }
            else{
                if (cButton->property("flag")=="u"){
                    QIcon icon(":/icons/icons/"+QString::number(cCount)+".svg.png");
                    cButton->setIcon(icon);
                    cButton->setIconSize(QSize(25,25));
                }
            }
        }
    }
}

