#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>

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

    // Color Button
    QPalette pal;
    pal.setColor(QPalette::Button, QColor(255, 255, 0));
    ui->pushButton_4->setPalette(pal);
    pal.setColor(QPalette::Button, QColor(255, 0, 0));
    ui->pushButton_5->setPalette(pal);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// --------------------------
// ---------- Sort ----------
void MainWindow::simpleSort()
{
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

void MainWindow::heapSort()
{
    // Generate Heap
    for(int i=arraySize/2-1; i>=0; i--){
        // 子を持つ最小ノードからルートに向かってdownHeap
        downHeap(i, arraySize-1);
    }
    // Shift Up
    for(int i=arraySize-1; i>=1; i--){
        // ルートを一番後ろから詰めていく
        array.swapItemsAt(0, i);
        downHeap(0, i-1);
    }
    draw();
}
void MainWindow::downHeap(int parent, int last)
{
    while(true){
        int child = 2*parent + 1; // Left
        if(child > last) return;
        if(child!=last && array[child+1]>array[child]){
            child++; // Right
        }
        if(array[parent] >= array[child]) return;
        // Swap
        array.swapItemsAt(parent, child);
        parent = child;
        sleep();
        draw(parent, last);
    }
}

void MainWindow::merge(int size, QList<int> &from, QList<int> &into)
{
    int start = 0;
    while(start <= arraySize){
        // 位置を初期化
        int i = start, j = start+size, k = start;
        int iend = qMin(start+size-1, arraySize-1);
        int jend = qMin(start+2*size-1, arraySize-1);
        // 小さい方を入れていく
        while(i <= iend && j<= jend){
            if(from[i] <= from[j])
                put(i, k, from, into);
            else
                put(j, k, from, into);
        }
        // 先に後ろがなくなった場合
        while(i <= iend) put(i, k, from, into);
        // 先に前がなくなった場合
        while(j <= jend) put(j, k, from, into);
        start += 2*size;
    }
}
void MainWindow::put(int &inx, int &k, QList<int> &from, QList<int> &into)
{
    into[k] = from[inx];
    sleep();
    draw(k, inx);
    inx++;
    k++;
}

void MainWindow::sort3(int &w1, int &w2, int &w3)
{
    if(w1 > w2){
        qSwap(w1, w2);
    }
    if(w2 > w3){
        qSwap(w2, w3);
        if(w1 > w2){
             qSwap(w1, w2);
        }
    }
}
void MainWindow::mergeSort()
{
    QList<int> array2;
    for(int i=0; i<arraySize; i++) array2.append(0);

    int seqSize = 1;
    while(seqSize < arraySize){
        merge(seqSize, array, array2);
        merge(seqSize*2, array2, array);
        seqSize *= 4;
    }
    draw();
}

void MainWindow::quickSort()
{
    QPair<int, int> stack[40];
    int limit = 10, sp = 0;
    stack[0].first = 0;
    stack[0].second = arraySize-1;

    do{
        int left  = stack[sp].first;
        int right = stack[sp].second;
        sp--;

        while(right-left >= limit){
            int w1 = array[left];
            int w2 = array[right];
            int center = (left+right)/2;
            int w3 = array[center];
            sort3(w1, w2, w3);

            // サンプル値のMin,Maxは先に左右に置く
            array[left] = w1;
            array[right] = w3;
            // Medianは左から2つ目に置き、centerに元の値を置いておく
            array[center] = array[left+1];
            array[left+1] = w2;

            int pivot = w2;
            int i = qMin(left+2, arraySize-1);
            int j = qMax(right-1, 0);

            do{
                // 前からpivotに反する要素まで動かす
                while(array[i] < pivot) i++;
                // 後ろからpivotに反する要素まで動かす
                while(array[j] > pivot) j--;

                if(i < j) array.swapItemsAt(i, j);
                sleep();
                draw(i, j);
            }while(i < j);

            array.swapItemsAt(j, left+1);
            sleep();
            draw(j, left+1);

            // 狭い範囲を次に処理(広い方はスタックに入れる)
            sp++;
            if(j-left <= right-j){
                stack[sp].first  = j+1;
                stack[sp].second = right;
                right = j-1;    // 次に実行する
            }else{
                stack[sp].first = left;
                stack[sp].second = j-1;
                left = j+1;    // 次に実行する
            }
        }
    }while(sp>=0);

    insertionSort();
    draw();
}

// ---------- Sort ----------
// --------------------------

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

    if(ui->comboBox_3->currentText() == "Random")
        generateRandomSequence();
    if(ui->comboBox_3->currentText() == "Ascending")
        generateAscendingSequence();
    if(ui->comboBox_3->currentText() == "Descending")
        generateDescendingSequence();
}

void MainWindow::generateRandomSequence()
{
    generateAscendingSequence();
    for (int i=0;i<arraySize;i++){
        int j = qrand()%arraySize;
        array.swapItemsAt(i, j);
    }
}

void MainWindow::generateAscendingSequence()
{
    for (int i=0;i<arraySize;i++)
        array.append((i+1)*255/arraySize);
}

void MainWindow::generateDescendingSequence()
{
    for (int i=0;i<arraySize;i++)
        array.append(255 - i*255/arraySize);
}

void MainWindow::resetScene()
{
    delete(scene);
    scene = new GraphicsScene(itemMenu, this);
    view->setScene(scene);
}

void MainWindow::draw(int a, int b)
{
    scene->clear();

    for(int i=0; i<arraySize; i++){
        QColor color(startColor.red()   + diffColor.x()*array[i]/255,
                     startColor.green() + diffColor.y()*array[i]/255,
                     startColor.blue()  + diffColor.z()*array[i]/255);
        QBrush brush(color);
        if(i == a || i == b) brush.setColor(complementaryColor);
        scene->addRect(barWidth*i, 0, barWidth, -array[i], pen, brush);
    }
    view->fitInView(scene->sceneRect());
}

void MainWindow::updateColor()
{
    startColor = ui->pushButton_4->palette().color(QPalette::Button);
    endColor = ui->pushButton_5->palette().color(QPalette::Button);
    diffColor = QVector3D(endColor.red() - startColor.red(),
                          endColor.green() - startColor.green(),
                          endColor.blue() - startColor.blue());

    complementaryColor = QColor(255 - (startColor.red()   + diffColor.x()/2.0),
                                255 - (startColor.green() + diffColor.y()/2.0),
                                255 - (startColor.blue()  + diffColor.z()/2.0));
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "on_pushButton_clicked()";
    generate();
    updateColor();
    draw();
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "on_pushButton_2_clicked()";

    if(isSorted) generate();
    updateColor();

    isRunning = true;
    QString kind = ui->comboBox_2->currentText();
    if(kind == "Simple Sort")    simpleSort();
    if(kind == "Insertion Sort") insertionSort();
    if(kind == "Shell Sort")     shellSort();
    if(kind == "Bubble Sort")    bubbleSort();
    if(kind == "Selection Sort") selectionSort();
    if(kind == "Heap Sort") heapSort();
    if(kind == "Merge Sort") mergeSort();
    if(kind == "Quick Sort") quickSort();
    isSorted = true;
    isRunning = false;

    qDebug() << "Completed:" << kind;
}

void MainWindow::on_pushButton_3_clicked()
{
    qDebug() << "on_pushButton_3_clicked()";
    isRunning = !isRunning;
    while(!isRunning) sleep();
}

void MainWindow::on_pushButton_4_clicked()
{
    qDebug() << "on_pushButton_4_clicked()";
    QColor chosenColor = QColorDialog::getColor();
    if(chosenColor.isValid()){
        QPalette pal;
        pal.setColor(QPalette::Button, chosenColor);
        ui->pushButton_4->setPalette(pal);
        ui->pushButton_4->update();
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    qDebug() << "on_pushButton_5_clicked()";
    QColor chosenColor = QColorDialog::getColor();
    if(chosenColor.isValid()){
        QPalette pal;
        pal.setColor(QPalette::Button, chosenColor);
        ui->pushButton_5->setPalette(pal);
        ui->pushButton_5->update();
    }
}
