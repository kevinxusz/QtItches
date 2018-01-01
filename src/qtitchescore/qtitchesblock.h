#ifndef QTITCHESBLOCK_H
#define QTITCHESBLOCK_H

#include <QQmlListProperty>
#include <QQmlParserStatus>

namespace QtItches {

class Actor;
class Parameter;
class Script;
class Stage;

class Block : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_CLASSINFO("DefaultProperty", "data")
    Q_INTERFACES(QQmlParserStatus)

    Q_PROPERTY(QtItches::Actor *actor READ actor CONSTANT FINAL)
    Q_PROPERTY(QtItches::Script *script READ script CONSTANT FINAL)
    Q_PROPERTY(QtItches::Stage *stage READ stage CONSTANT FINAL)

    Q_PROPERTY(int category READ category WRITE setCategory NOTIFY categoryChanged FINAL)
    Q_PROPERTY(int connectors READ connectors WRITE setConnectors NOTIFY connectorsChanged FINAL)
    Q_PROPERTY(int shape READ shape WRITE setShape NOTIFY shapeChanged FINAL)

    Q_PROPERTY(QQmlListProperty<QObject> data READ data CONSTANT FINAL)
    Q_PROPERTY(QQmlListProperty<QtItches::Parameter> parameters READ parameters CONSTANT FINAL)

public:
    enum Category {
        UnknownCategory = 0,
        ControlCategory = 1,
        EventsCategory,
        ListsCategory,
        LooksCategory,
        MotionsCategory,
        OperatorsCategory,
        SensingCategory,
        SoundsCategory,
        VariablesCategory,
    };

    Q_ENUM(Category)

    enum Connector {
        TopConnector = 1,
        BottomConnector = 2,
    };

    Q_FLAG(Connector)
    Q_DECLARE_FLAGS(Connectors, Connector)

    enum Shape {
        BooleanShape,
        ReporterShape,
        StackShape,
    };

    Q_ENUM(Shape)

    explicit Block(QObject *parent = {});
    ~Block();

    Actor *actor() const;
    Script *script() const;
    Stage *stage() const;

    void setCategory(Category category);
    Category category() const;

    void setConnectors(Connectors connectors);
    Connectors connectors() const;

    void setShape(Shape shape);
    Shape shape() const;

    QQmlListProperty<QObject> data();
    QQmlListProperty<Parameter> parameters();

    // QQmlParserStatus interface
    void classBegin() override;
    void componentComplete() override;

public slots:
    virtual void run();
    virtual void stop();

signals:
    void categoryChanged(int category);
    void connectorsChanged(int connectors);
    void shapeChanged(int shape);
    void finished();

protected:
    Parameter *parameter(int index) const;
    template<class T> T *parameter(int index) const { return dynamic_cast<T *>(parameter(index)); }

private:
    void setCategory(int category) { setCategory(static_cast<Category>(category)); }
    void setConnectors(int connectors) { setConnectors(static_cast<Connectors>(connectors)); }
    void setShape(int shape) { setShape(static_cast<Shape>(shape)); }

    class Private;
    Private *const d;
};

} // namespace QtItches

Q_DECLARE_OPERATORS_FOR_FLAGS(QtItches::Block::Connectors)

#endif // QTITCHESBLOCK_H