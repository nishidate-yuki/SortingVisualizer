#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setup GraphicsView
    scene = new GraphicsScene(itemMenu, this);
    view = new GraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
//    view->setStyleSheet("QGraphicsView { background-color : #ffffff; }");
    view->setMinimumSize(400, 400);
    view->setMaximumSize(400, 400);
    ui->gridLayout->addWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw()
{
    qDebug() << "draw()";
    scene->clear();

    for(int i=0; i<arraySize; i++){
        QBrush brush = QBrush(QColor(255,255-array[i],0));
        scene->addRect(/*x=*/ barWidth*i, /*y=*/0, /*w=*/barWidth, /*h=*/-array[i], pen, brush);
        view->fitInView(scene->sceneRect());
    }
}

void MainWindow::simpleSort()
{
    qDebug() << "simpleSort()";
    for(int i=0; i<arraySize; i++){
        for(int j=i+1;j<arraySize;j++){
            if(array[j] < array[i]){
                array.swapItemsAt(i, j);

                sleep();
                draw();
            }
        }
    }
    qDebug() << "Sorting Complete";
}

void MainWindow::insertionSort()
{
    for(int i=1; i<arraySize; i++){
        for(int j=i-1; j>=0; j--){
            if(array[j] > array[j+1]){
                array.swapItemsAt(j, j+1);
                sleep();
                draw();
            }else{
                break;
            }
        }
    }
}

void MainWindow::shellSort()
{
    int h = 1;
    while(h < arraySize) h = 3*h + 1;
    while(h > 1){
        h /= 3;
        for(int i=h; i<arraySize; i++){
            for(int j=i-h; j>=0; j-=h){
                if(array[j] > array[j+h]){
                    array.swapItemsAt(j, j+h);
                    sleep();
                    draw();
                }
                else break;
            }
        }
    }
}

void MainWindow::sleep()
{
    QEventLoop loop;
    QTimer::singleShot(5, &loop, SLOT(quit()));
    loop.exec();
}

void MainWindow::on_pushButton_clicked()
{
    arraySize = 64;

    for(int i=0; i<arraySize; i++){
        array.append(qrand()%256);
        QBrush brush = QBrush(QColor(255,255-array[i],0));
        scene->addRect(/*x=*/ barWidth*i, /*y=*/0, /*w=*/barWidth, /*h=*/-array[i], pen, brush);
        view->fitInView(scene->sceneRect());
    }

//    qDebug() << view->width() << view->height();
//    qDebug() << scene->sceneRect();
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "on_pushButton_2_clicked()";
//    simpleSort();
//    insertionSort();
    shellSort();
}