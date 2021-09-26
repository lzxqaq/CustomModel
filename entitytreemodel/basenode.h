#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>

class BaseNode : public QObject
{
    Q_OBJECT
public:
    virtual QVariant data(int column) const = 0;
    virtual void setData(int column, const QVariant &value) = 0;
};

#endif // ENTITY_H
