#ifndef HEXAGONSCENE_H
#define HEXAGONSCENE_H

#include <QGraphicsScene>
#include "hexagonfield.h"

class HexagonScene : public QGraphicsScene
{
public:
    HexagonScene(unsigned nLines = 1, unsigned nColumns = 1, float hexagonRadius = 20, QObject * parent = 0);
private:
    float mHexagonRadius;
    HexagonField mField;

    void rebuildField ();
    // Строит mField заново, добавляя шестиугольники на сцену
    void buildField (unsigned nLines = 1, unsigned nColumns = 1);
    void deleteField ();

};

#endif // HEXAGONSCENE_H
