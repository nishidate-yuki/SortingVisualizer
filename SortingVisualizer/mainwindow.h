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

    void draw();
    void sleep();
    void generate();

    // Sort
    void simpleSort();
    void insertionSort();
    void shellSort();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QMenu *itemMenu;
    GraphicsScene *scene;
    GraphicsView *view;

    QPen pen = QPen(Qt::NoPen);

    QList<int> array;
    int arraySize;
    int barWidth = 5;
    bool isSorted = false;
};

#endif // MAINWINDOW_H
