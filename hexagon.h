#ifndef HEXAGON_H
#define HEXAGON_H

#include <QGraphicsItem>
#include <QRect>
#include <QFont>
#include <QString>
#include <QPoint>

class Hexagon : public QGraphicsItem
{
public:
    // Режим отображения текста
    enum TextMode {PERCENT, POINTS, BOTH, NONE};

    Hexagon(QColor color = QColor ("orange"), QGraphicsItem * parent = 0);
    Hexagon (const Hexagon& other, QGraphicsItem* parent = 0);
    Hexagon& operator = (const Hexagon& other);
    // Устанавливает стиль тайла на данный
    void setStyle (const Hexagon& other);
    static void setRadius (float radius);
    void setPoints (float points);
    void setPercent (float percent);
    Hexagon::TextMode getTextMode () const;
    float getPoints () const;
    float getPercent () const;
    static float getHeight ();
    static float getRadius ();
    QColor getColor () const;
    QColor getTextColor () const;
    QFont getFont () const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
private:
    //***************************************
    // СТИЛЬ
    //***************************************
    TextMode mTextMode;
    // Цвет фона
    QColor mColor;
    // Цвет текста
    QColor mTextColor;
    // Шрифт
    QFont mFont;
    //****************************************
    // ОТОБРАЖЕНИЕ
    //****************************************
    // Прямоугольник, в котором отображается текст
    static QRect mTextRect;
    // Текст
    QString mText;
    // Высота шестиугольника, чтобы каждый раз не вычислять
    static float mHeight;
    // Длина радиуса описанной окружности, она же - длина стороны
    static float mRadius;
    // Численное значение √3/2
    static const double mSin60;
    //***************************************
    // ЛОГИКА
    //***************************************
    // Очки
    float mPoints;
    // Процент
    float mPercent;

    void setTextColor ();
    void updateText ();
    void updateFontSize ();
};

#endif // HEXAGON_H
