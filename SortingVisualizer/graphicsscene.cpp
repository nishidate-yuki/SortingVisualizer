#include "graphicsscene.h"

GraphicsScene::GraphicsScene(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent)
{
    pen = QPen(Qt::black, 5);
    brush = QBrush(Qt::black);
}

void GraphicsScene::draw(QList<int> array)
{
    qDebug() << "draw()" << sceneRect().width() << sceneRect().height();
    for(int i=0; i<array.size(); i++){
        addRect(0, 0, 400, 400, pen, brush);
    }

//    QGraphicsRectItem *bar = new QGraphicsRectItem(0, 0, 10, 100);
//    bar->setBrush(brush);
//    addItem(bar);

}
