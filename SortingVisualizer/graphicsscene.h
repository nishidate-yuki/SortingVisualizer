#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H
#include <QGraphicsScene>
#include <QtWidgets>

class GraphicsScene : public QGraphicsScene
{
public:
    GraphicsScene(QMenu *itemMenu, QObject *parent = 0);
};

#endif // GRAPHICSSCENE_H
