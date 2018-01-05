#include "qtitchessprite.h"

#include <QLoggingCategory>

#include <cmath>

namespace QtItches {
namespace Core {

namespace {
Q_LOGGING_CATEGORY(lcSprite, "qtitches.sprite")
}

void Sprite::setX(double x)
{
    setPosition({x, y()});
}

double Sprite::x() const
{
    return m_position.x();
}

void Sprite::setY(double y)
{
    setPosition({x(), y});
}

double Sprite::y() const
{
    return m_position.y();
}

void Sprite::setPosition(const QPointF &position)
{
    if (m_position == position)
        return;

    m_position = position;
    emit positionChanged(m_position);
}

QPointF Sprite::position() const
{
    return m_position;
}

void Sprite::setDirection(double direction)
{
    if (m_direction == direction)
        return;

    while (direction > 180)
        direction -= 360;
    while (direction < -180)
        direction += 360;

    m_direction = direction;
    emit directionChanged(m_direction);
}

double Sprite::direction() const
{
    return m_direction;
}

void Sprite::setCostumes(const QList<QUrl> &costumes)
{
    if (m_costumes == costumes)
        return;

    m_costumes = costumes;
    emit costumesChanged(m_costumes);
}

QList<QUrl> Sprite::costumes() const
{
    return m_costumes;
}

void Sprite::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

QString Sprite::name() const
{
    return m_name;
}

QString Sprite::saying() const
{
    return m_saying;
}

QString Sprite::thinking() const
{
    return m_thinking;
}

void Sprite::say(const QString &text)
{
    if (!text.isEmpty())
        qCInfo(lcSprite, "%ls says: `%ls'", qUtf16Printable(name()), qUtf16Printable(text));

    m_saying = text;
    emit said(m_saying); // really always emit
}

void Sprite::think(const QString &text)
{
    if (!text.isEmpty())
        qCInfo(lcSprite, "%ls thinks: `%ls'", qUtf16Printable(name()), qUtf16Printable(text));

    m_thinking = text;
    emit thought(m_thinking); // really always emit
}

void Sprite::goForward(int steps)
{
    if (steps > 0) {
        // MIT Scratch has a very special idea of basic trigonometry
        const auto dx = steps * cos(M_PI * (90 - direction()) / 180);
        const auto dy = steps * sin(M_PI * (90 - direction()) / 180);
        m_position += {dx, dy};
        emit positionChanged(m_position);
    }
}

} // namespace Core
} // namespace QtItches
