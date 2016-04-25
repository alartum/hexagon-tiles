#include "hexagonfield.h"
#include <QDebug>

HexagonField::HexagonField(unsigned nLines, unsigned nColumns, QGraphicsScene *scene) :
    mScene (scene)
{
    setSize(nLines, nColumns);
}

void HexagonField::setNLines(unsigned linesNo)
{
    setSize(linesNo, mNColumns);
}

void HexagonField::setNColumns(unsigned columnNo)
{
    setSize(mNLines, columnNo);
}

unsigned HexagonField::getNColumns() const
{
    return mNColumns;
}

Hexagon *HexagonField::getHexagon(unsigned columnNo, unsigned lineNo)
{
#ifdef FIELD_RANGE_CHECK
    if (!isInRange(columnNo, lineNo))
        return NULL;
#endif
    int i = calculateIndex(columnNo, lineNo);

    return mHexagons[i];
}

void HexagonField::fill (const Hexagon& hexagon)
{
    foreach (Hexagon* element, mHexagons)
       *element = hexagon;
}

void HexagonField::setSize(unsigned linesNo, unsigned columnNo)
{
    mNLines = linesNo;
    mNColumns = columnNo;

    deleteField();

    int nElements = (columnNo + 1) / 2 * linesNo + columnNo / 2 * (linesNo + 1);

    mHexagons.resize(nElements);
    for (int i = 0; i < mHexagons.size(); i ++)
       mHexagons[i] = new Hexagon;
}

bool HexagonField::isInRange(unsigned columnNo, unsigned lineNo) const
{
    bool isOk = false;

    // Если x не вылезает за границы ширины
    if (columnNo < mNColumns)
    {
        // Если имеем дело с чётным по счёту столбиком
        if (columnNo % 2 == 0)
        {
            if (lineNo < mNLines)
                isOk = true;
        }
        // Если с нечётным
        else
        {
            if (lineNo < mNLines + 1)
                isOk = true;
        }
    }
    if (isOk)
        return true;
    else
    {
        qDebug () << "HexagonField: index out of range!";
        return false;
    }
}

void HexagonField::rebuildGeometry()
{
    float height = Hexagon::getHeight();
    float radius = Hexagon::getRadius();

    for (unsigned i = 0; i < mNColumns; i += 2)
        for (unsigned j = 0; j < mNLines; j ++)
            getHexagon(i, j)->setPos(3 * radius * i / 2, 2 * height * (j + 1));

    for (unsigned i = 1; i < mNColumns; i += 2)
        for (unsigned j = 0; j < mNLines + 1; j ++)
            getHexagon(i, j)->setPos((i / 2 * 3 + 1.5) * radius, height * (2 * j + 1));
}

 unsigned HexagonField::getNLines (unsigned i) const
 {
    if (i % 2 == 0)
        return mNLines;
    else
        return mNLines + 1;
 }

 int HexagonField::calculateIndex(unsigned columnNo, unsigned lineNo) const
 {
     return (columnNo + 1) / 2 * mNLines + columnNo / 2* (mNLines + 1) + lineNo;
 }

 void HexagonField::setStyle(const Hexagon &hexagon)
 {
     foreach (Hexagon* element, mHexagons)
        element->setStyle(hexagon);
 }

 void HexagonField::deleteField()
 {
     qDeleteAll (mHexagons);
     mHexagons.clear();
 }

 HexagonField::~HexagonField ()
 {
     deleteField();
 }

 void HexagonField::changeAll(void (QGraphicsScene::*operation)(QGraphicsItem *))
 {
     for (int i = 0; i < mHexagons.size(); i ++)
        (mScene->*operation) (mHexagons[i]);
 }
