#ifndef QTICHESUTILS_H
#define QTICHESUTILS_H

#include <QHash>

#define QTITCHES_DATAROLE(Enum) \
    Q_ENUM(Enum) \
    inline QHash<int, QByteArray> roleNames() const override { return QtItches::Core::roleNamesFromEnum<Enum>(); }

namespace QtItches {
namespace Core {

QHash<int, QByteArray> roleNamesFromEnum(const QMetaObject *metaObject, const char *enumName);
const char *valueToKey(const QMetaObject *metaObject, const char *enumName, int value);

template<typename T>
inline QHash<int, QByteArray> roleNamesFromEnum(typename std::enable_if<std::is_enum<T>::value>::type * = {})
{
    static const auto roleNames = roleNamesFromEnum(qt_getEnumMetaObject(T{}), qt_getEnumName(T{}));
    return roleNames;
}

template<typename T>
inline const char *valueToKey(T value, typename std::enable_if<std::is_enum<T>::value>::type * = {})
{
    return valueToKey(qt_getEnumMetaObject(T{}), qt_getEnumName(T{}), value);
}

} // namespace Core
} // namespace QtItches

#endif // QTICHESUTILS_H
