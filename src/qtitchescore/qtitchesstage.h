#ifndef QTITCHESSTAGE_H
#define QTITCHESSTAGE_H

#include <QQmlListProperty>

namespace QtItches {

class Actor;

class Stage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<QtItches::Actor> actors READ actors CONSTANT FINAL)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_CLASSINFO("DefaultProperty", "actors")

public:
    Stage(QObject *parent = {});
    ~Stage();

    QQmlListProperty<Actor> actors();

    void setName(const QString &name);
    QString name() const;

signals:
    void nameChanged(const QString &name);

private:
    class Private;
    Private *const d;
};

} // namespace QtItches

#endif // QTITCHESSTAGE_H