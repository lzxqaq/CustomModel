#include "treenode.h"
#include <QVariant>


QVariant TreeNode::data(int column) const
{
    switch (column) {
    case 0:
        return m_id;
    case 1:
        return m_parentId;
    case 2:
        return m_property1;
    case 3:
        return m_property2;
    case 4:
        return m_property3;
    case 5:
        return m_property4;
    case 6:
        return m_property5;
    default:
        return QVariant();
    }
}

void TreeNode::setData(int column, const QVariant &value)
{
    switch (column) {
    case 0:
        m_id = value.toInt();
        break;
    case 1:
        m_parentId = value.toInt();
        break;
    case 2:
        m_property1 = value.toString();
        break;
    case 3:
        m_property2 = value.toString();
        break;
    case 4:
        m_property3 = value.toString();
        break;
    case 5:
        m_property4 = value.toString();
        break;
    case 6:
        m_property5 = value.toString();
        break;
    default:
        break;
    }
}

int TreeNode::id() const
{
    return m_id;
}

void TreeNode::setId(int id)
{
    m_id = id;
}

int TreeNode::parentId() const
{
    return m_parentId;
}

void TreeNode::setParentId(int parentId)
{
    m_parentId = parentId;
}

QString TreeNode::property1() const
{
    return m_property1;
}

void TreeNode::setProperty1(const QString &property1)
{
    m_property1 = property1;
}

QString TreeNode::property2() const
{
    return m_property2;
}

void TreeNode::setProperty2(const QString &property2)
{
    m_property2 = property2;
}

QString TreeNode::property3() const
{
    return m_property3;
}

void TreeNode::setProperty3(const QString &property3)
{
    m_property3 = property3;
}

QString TreeNode::property4() const
{
    return m_property4;
}

void TreeNode::setProperty4(const QString &property4)
{
    m_property4 = property4;
}

QString TreeNode::property5() const
{
    return m_property5;
}

void TreeNode::setProperty5(const QString &property5)
{
    m_property5 = property5;
}


