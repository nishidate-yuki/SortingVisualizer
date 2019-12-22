#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H
#include <QGraphicsView>
#include "graphicsscene.h"

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(GraphicsScene *scene);
};

#endif // GRAPHICSVIEW_H
