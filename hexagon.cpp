#include "hexagon.h"
#include <QPainter>
#include <QFontMetrics>
#include <QDebug>

float Hexagon::mRadius = 20;
const double Hexagon::mSin60 = 0.8660254037844386;
float Hexagon::mHeight = Hexagon::mRadius * Hexagon::mSin60;
QRect Hexagon::mTextRect = QRect();

Hexagon::Hexagon(QColor color, QGraphicsItem *parent) :
    QGraphicsItem (parent), mColor (color), mFont ("Times", 3), mPercent (0), mPoints (100), mTextMode (Hexagon::POINTS)
{
    mFont.setBold(true);
    mText = "TEST";
}


Hexagon::Hexagon (const Hexagon &other, QGraphicsItem *parent) :
    Hexagon (other.getColor(), parent)
{
    mPercent = other.getPercent();
    mPoints = other.getPoints();
}

float Hexagon::getRadius()
{
    return mRadius;
}

QColor Hexagon::getColor() const
{
    return mColor;
}

void Hexagon::setRadius(float radius)
{
    mRadius = radius;
    mHeight = Hexagon::mSin60 * mRadius;
    mTextRect = QRect (-0.75 * mRadius, -mHeight / 2, 1.5 * mRadius, mHeight);
}

void Hexagon::updateText()
{
    switch (mTextMode)
    {
    case POINTS:
        mText = QString::number(mPoints, 'g', 2);
        break;
    case PERCENT:
        mText = QString::number(mPercent, 'g', 2);
        break;
    case NONE:
        mText = QString ();
        break;
    case BOTH:
        mText = QString::number(mPoints, 'g', 2);
        mText += "\n";
        mText += QString::number(mPercent, 'g', 2);
        break;
    };
}

Hexagon& Hexagon::operator = (const Hexagon& other)
{
    setStyle(other);
    setPoints(other.getPoints());
    setPercent(other.getPercent());

    return *this;
}

QRectF Hexagon::boundingRect() const
{
    qreal adjust = 2;

    return QRectF(- adjust - mRadius, - adjust - mHeight,
                  mRadius + adjust, mHeight + adjust);
}

void Hexagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
//   updateText();
   setTextColor();
   updateFontSize();

   painter->setRenderHint(QPainter::Antialiasing);
   painter->setPen(QPen (Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
   painter->setBrush(QBrush (mColor));

   QPainterPath path (QPointF(-mRadius,0));
   path.lineTo(-mRadius / 2, - mHeight);
   path.lineTo(mRadius / 2, - mHeight);
   path.lineTo(mRadius, 0);
   path.lineTo(mRadius / 2, mHeight);
   path.lineTo(-mRadius / 2, mHeight);
   path.lineTo(-mRadius, 0);
   painter->drawPath(path);
   painter->setPen(/*QColor ("orange")*/mTextColor);
   painter->setFont(mFont);
   painter->drawText(mTextRect, mText, QTextOption(Qt::AlignCenter));
}

float Hexagon::getHeight()
{
    return mHeight;
}

void Hexagon::setStyle(const Hexagon &other)
{
    mColor = other.getColor();
    mTextColor = other.getTextColor();
    mTextMode = other.getTextMode();
    mFont = other.getFont();
}

void Hexagon::setTextColor()
{
    qDebug () << mColor.toHsv();

//    mTextColor.setHsv(mColor.hsvHue() + 180, mColor.hsvSaturation(), mColor.value());
    qDebug () << mTextColor.hsvHue();
}

QColor Hexagon::getTextColor() const
{
    return mTextColor;
}

void Hexagon::updateFontSize()
{
    QFontMetrics metrics (mFont);
    qDebug() << "Done!";
    float factor = (float) mTextRect.width() / metrics.width(mText);
    if ((factor < 1) || (factor > 1.25))
    {
         mFont.setPointSizeF(mFont.pointSizeF()*factor);
    }
}

QFont Hexagon::getFont() const
{
    return mFont;
}

float Hexagon::getPoints() const
{
    return mPoints;
}

float Hexagon::getPercent() const
{
    return mPercent;
}

void Hexagon::setPoints(float points)
{
    mPoints = points;
}

void Hexagon::setPercent(float percent)
{
    if ((percent >= 0) && (percent <= 100))
        mPercent = percent;
    else
        qDebug() << "Hexagon: percent must be in [0; 100] interval!";
}

Hexagon::TextMode Hexagon::getTextMode() const
{
    return mTextMode;
}
