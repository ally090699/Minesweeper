#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.setWindowTitle("Minesweeper");   // added window title
    app.setWindowIcon(QIcon(":/icons/icons/alive.png"));    // added app icon
    mainWindow.resize(440, 150);    //resized window for game
    mainWindow.show();
    return app.exec();
}
