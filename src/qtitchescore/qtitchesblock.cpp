#include "qtitchesblock.h"

#include "qtitchesparameter.h"
#include "qtitchesscript.h"

#include <QMetaMethod>

namespace QtItches {
namespace Core {

class Block::Private
{
public:
    Category m_category = UnknownCategory;
    Connectors m_connectors = TopConnector | BottomConnector;
    Shape m_shape = StackShape;

    QList<QObject *> m_data;
    QList<Parameter *> m_parameters;
};

Block::Block(QObject *parent)
    : QObject{parent}
    , d{new Private}
{}

Block::~Block()
{
    delete d;
}

Actor *Block::actor() const
{
    if (const auto s = script())
        return s->actor();

    return {};
}

Script *Block::script() const
{
    if (const auto b = dynamic_cast<Block *>(parent()))
        return b->script();

    return dynamic_cast<Script *>(parent());
}

Stage *Block::stage() const
{
    if (const auto s = script())
        return s->stage();

    return {};
}

void Block::setCategory(Block::Category category)
{
    if (d->m_category == category)
        return;

    d->m_category = category;
    emit categoryChanged(d->m_category);
}

Block::Category Block::category() const
{
    return d->m_category;
}

void Block::setConnectors(Connectors connectors)
{
    if (d->m_connectors == connectors)
        return;

    d->m_connectors = connectors;
    emit categoryChanged(d->m_connectors);
}

Block::Connectors Block::connectors() const
{
    return d->m_connectors;
}

void Block::setShape(Block::Shape shape)
{
    if (d->m_shape == shape)
        return;

    d->m_shape = shape;
    emit shapeChanged(d->m_shape);
}

Block::Shape Block::shape() const
{
    return d->m_shape;
}

QQmlListProperty<QObject> Block::data()
{
    return {this, d->m_data};
}

QQmlListProperty<Parameter> Block::parameters()
{
    return {this, d->m_parameters};
}

Parameter *Block::parameter(int index) const
{
    return d->m_parameters.at(index);
}

void Block::classBegin()
{
}

void Block::componentComplete()
{
    for (const auto object: qAsConst(d->m_data)) {
        if (const auto parameter = dynamic_cast<Parameter *>(object))
            d->m_parameters.append(parameter);
    }
}

void Block::run()
{
}

void Block::stop()
{
    emit finished();
}

} // namespace Core
} // namespace QtItches
