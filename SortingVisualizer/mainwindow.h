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
    void updateColor();

    // Sort
    void simpleSort();
    void insertionSort();
    void shellSort();
    void bubbleSort();
    void selectionSort();
    void heapSort();
    void downHeap(int parent, int size);
    void merge(int size, QList<int> &from, QList<int> &into);
    void mergeSort();
    void put(int &inx, int &k, QList<int> &from, QList<int> &into);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    QMenu *itemMenu;
    GraphicsScene *scene;
    GraphicsView *view;

    QPen pen = QPen(Qt::NoPen);
    QColor startColor;
    QColor endColor;
    QVector3D diffColor;

    QList<int> array;
    int arraySize;
    int barWidth = 5;
    bool isSorted = true;
    bool isRunning = false;
};

#endif // MAINWINDOW_H
