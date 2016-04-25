#ifndef HEXAGONFIELD_H
#define HEXAGONFIELD_H

#include "hexagon.h"
#include <QVector>
#include <QGraphicsScene>
// Закомментрировать, если проверка выхода за границы не нужна
#define FIELD_RANGE_CHECK

class HexagonField
{
public:
    HexagonField(unsigned nLines = 1, unsigned nColumns = 1, QGraphicsScene* scene = 0);
    ~HexagonField ();
    // Стилизует поле
    void setStyle (const Hexagon& hexagon);
    // Возвращает тайл с данной позицией
    Hexagon* getHexagon (unsigned columnNo, unsigned lineNo);
    // Изменяет высоту
    void setNLines (unsigned nLines);
    // Изменяет длину
    void setNColumns (unsigned nColumns);
    // Изменяет все параметры
    void setSize (unsigned nLines, unsigned nColumns);
    // Возвращает длину
    unsigned getNColumns () const;
    void fill (const Hexagon &hexagon);
    // Возвращает высоту столбца с номером i
    unsigned getNLines (unsigned i) const;
    void rebuildGeometry ();
    // Извращенская функция, призванная улучшить производительность,
    // избегая использования цикла QGraphicsScene
    void changeAll (void (QGraphicsScene::*operation) (QGraphicsItem*));
private:
    // Высота (число шестиугольников в самом левом столбце)
    unsigned mNLines;
    // Ширина (число шестиугольников в горизонтальной змейке)
    unsigned mNColumns;
    // Храним все шестиугольнички в векторе, находим индексы по формулке
    QVector<Hexagon*> mHexagons;
    // Проверяет корректность координат
    bool isInRange(unsigned columnNo, unsigned lineNo) const;
    int calculateIndex (unsigned columnNo, unsigned lineNo) const;
    QGraphicsScene* mScene;
    void deleteField ();
};

#endif // HEXAGONFIELD_H
