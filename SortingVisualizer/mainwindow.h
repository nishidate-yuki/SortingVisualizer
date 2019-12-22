#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QRandomGenerator>
#include <QDebug>
#include "graphicsscene.h"
#include "graphicsview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void draw(int a=-1, int b=-1);
    void sleep();
    void generate();
    void resetScene();

    // Sort
    void simpleSort();
    void insertionSort();
    void shellSort();
    void bubbleSort();
    void selectionSort();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QMenu *itemMenu;
    GraphicsScene *scene;
    GraphicsView *view;

    QPen pen = QPen(Qt::NoPen);

    QList<int> array;
    int arraySize;
    int barWidth = 5;
    bool isSorted = true;
    bool isRunning = false;
};

#endif // MAINWINDOW_H
