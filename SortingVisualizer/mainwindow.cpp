#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Sorting Visualizer"));
    setUnifiedTitleAndToolBarOnMac(true);

    // Setup GraphicsView
    scene = new GraphicsScene(itemMenu, this);
    view = new GraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setMinimumSize(500, 500);
    ui->gridLayout->addWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw(int a, int b)
{
    scene->clear();

    for(int i=0; i<arraySize; i++){
        QBrush brush = QBrush(QColor(255,255-array[i],0));
        if(i == a || i == b) brush.setColor(QColor(0, 0, 255));
        scene->addRect(barWidth*i, 0, barWidth, -array[i], pen, brush);
        view->fitInView(scene->sceneRect());
    }
}

// ----- Sort -----
void MainWindow::simpleSort()
{
    qDebug() << "simpleSort()";
    for(int i=0; i<arraySize; i++){
        for(int j=i+1;j<arraySize;j++){
            if(array[j] < array[i]){
                array.swapItemsAt(i, j);
            }
            sleep();
            draw(i, j);
        }
    }
    draw();
}

void MainWindow::insertionSort()
{
    qDebug() << "insertionSort()";
    for(int i=1; i<arraySize; i++){
        for(int j=i-1; j>=0; j--){
            if(array[j] > array[j+1]){
                array.swapItemsAt(j, j+1);
                sleep();
                draw(i, j);
            }else break;
        }
    }
    draw();
}

void MainWindow::shellSort()
{
    qDebug() << "shellSort()";
    int h = 1;
    while(h < arraySize) h = 3*h + 1;
    while(h > 1){
        h /= 3;
        for(int i=h; i<arraySize; i++){
            for(int j=i-h; j>=0; j-=h){
                if(array[j] > array[j+h]){
                    array.swapItemsAt(j, j+h);
                    sleep();
                    draw(j, j+h);
                }else break;
            }
        }
    }
    draw();
}

void MainWindow::bubbleSort()
{
    qDebug() << "bubbleSort()";
    for(int i=0; i<arraySize-1; i++){
        for(int j=arraySize-1; j>i; j--){
            if(array[j-1] > array[j]){
                array.swapItemsAt(j-1, j);
            }
            sleep();
            draw(i, j);
        }
    }
    draw();
}

void MainWindow::selectionSort()
{
    qDebug() << "selectionSort()";
    for(int i=0; i<arraySize; i++){
        int minPos = i;
        for(int j=i+1;j<arraySize;j++){
            if(array[j] < array[minPos]){
                minPos = j;
            }
            sleep();
            draw(i, j);
        }
        array.swapItemsAt(i, minPos);
    }
    draw();
}

void MainWindow::sleep()
{
    QEventLoop loop;
    QTimer::singleShot(1, &loop, SLOT(quit()));
    loop.exec();
}

void MainWindow::generate()
{
    resetScene();
    array.clear();
    isSorted = false;

    arraySize = ui->comboBox->currentText().toInt();
    if(ui->comboBox_3->currentText() == "Random"){
        for(int i=0; i<arraySize; i++){
            array.append(qrand()%255+1);
            QBrush brush = QBrush(QColor(255,255-array[i],0));
            scene->addRect(barWidth*i, 0, barWidth, -array[i], pen, brush);
        }
    }else if(ui->comboBox_3->currentText() == "Ascending"){
        for (int i=0;i<arraySize;i++) {
            array.append(i*255/arraySize);
            QBrush brush = QBrush(QColor(255,255-(array[i]),0));
            scene->addRect(barWidth*i, 0, barWidth, -array[i], pen, brush);
        }
    }else if(ui->comboBox_3->currentText() == "Descending"){
        for (int i=0;i<arraySize;i++) {
            array.append(255 - i*255/arraySize);
            QBrush brush = QBrush(QColor(255,255-array[i],0));
            scene->addRect(barWidth*i, 0, barWidth, -array[i], pen, brush);
        }
    }
    view->fitInView(scene->sceneRect());
}

void MainWindow::resetScene()
{
    delete(scene);
    scene = new GraphicsScene(itemMenu, this);
    view->setScene(scene);
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "on_pushButton_clicked()";
    generate();
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "on_pushButton_2_clicked()";

    if(isSorted) generate();

    isRunning = true;
    QString kind = ui->comboBox_2->currentText();
    if(kind == "Simple Sort")    simpleSort();
    if(kind == "Insertion Sort") insertionSort();
    if(kind == "Shell Sort")     shellSort();
    if(kind == "Bubble Sort")    bubbleSort();
    if(kind == "Selection Sort") selectionSort();
    isSorted = true;
    isRunning = false;
}

void MainWindow::on_pushButton_3_clicked()
{
    qDebug() << "on_pushButton_3_clicked()";
    isRunning = !isRunning;
    while(!isRunning) sleep();
}
