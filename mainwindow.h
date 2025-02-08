#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QRandomGenerator>
#include <QVector>
#include <QPoint>
#include <QMessageBox>
#include <QIcon>
#include <QApplication>
#include "customButton.h"
#include <QSizePolicy>
#include <QDebug>
#include <QPixmap>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    const int totalOpen = (30*16)-99;

private:
    customButton* buttons[16][30];
    QGridLayout *board;
    QVector<QPoint> mines;
    QVector<QPoint> neighbours;
    QVector<QPoint> nNeighbours;
    QMessageBox gameOver;
    int openCount;
    void handleButton();
    void checkNeighbours(int nRow, int nCol);
    void setUp();
};
#endif // MAINWINDOW_H
