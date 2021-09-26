#ifndef TREENODE_H
#define TREENODE_H

#include <QObject>

#include "basenode.h"

class TreeNode : public BaseNode
{
public:
    TreeNode(){}

    QVariant data(int column) const;
    void setData(int column, const QVariant &value);

public:
    int id() const;
    void setId(int id);

    int parentId() const;
    void setParentId(int parentId);

    QString property1() const;
    void setProperty1(const QString &property1);

    QString property2() const;
    void setProperty2(const QString &property2);

    QString property3() const;
    void setProperty3(const QString &property3);

    QString property4() const;
    void setProperty4(const QString &property4);

    QString property5() const;
    void setProperty5(const QString &property5);

    QVariantMap propertyList() const;
    void setPropertyList(const QVariantMap &propertyList);

private:
    int m_id;
    int m_parentId;
    QString m_property1;
    QString m_property2;
    QString m_property3;
    QString m_property4;
    QString m_property5;
};

#endif // TREENODE_H
