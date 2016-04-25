#include "hexagonscene.h"
#include <QDebug>

HexagonScene::HexagonScene(unsigned nLines, unsigned nColumns, float hexagonRadius, QObject * parent) :
    QGraphicsScene (parent), mHexagonRadius (hexagonRadius), mField (nLines, nColumns, this)
{
    Hexagon::setRadius(hexagonRadius);
    mField.rebuildGeometry();
    mField.changeAll(&QGraphicsScene::addItem);

}
