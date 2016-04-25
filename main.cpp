#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "hexagonscene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HexagonScene scene (2,5, 30);
    QGraphicsView view (&scene);

    view.show();

    return a.exec();
}
