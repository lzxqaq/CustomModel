#include "treeitem.h"
#include "treemodel.h"

TreeItem::TreeItem(TreeModel *model, TreeItem *parent)
    : m_parent(parent), m_row(-1), m_model(model)
{
    if(parent != Q_NULLPTR) {
        this->m_row = parent->m_children.size();
        parent->m_children.append(this);
    }
}

TreeItem::~TreeItem()
{
    removeChildren();
}

// 在本节点下添加子节点
void TreeItem::addChild(TreeItem *item)
{
    if(item == Q_NULLPTR) {
        return;
    }

    if(!m_children.contains(item)) {
        item->m_row = m_children.size();
        m_children.append(item);
        item->m_parent = this;
    }
}

void TreeItem::addChild(TreeItem *item, int index)
{
    if(item == Q_NULLPTR || index > m_children.size())
    {
        return;
    }

    if(!m_children.contains(item))
    {
        item->m_row = index;
        m_children.insert(index, item);
        item->m_parent = this;
    }
    for(int i = index + 1; i < m_children.size(); i++)
    {
        this->child(i)->setRow(i);
    }
}

void TreeItem::removeChild(TreeItem* item)
{
    int current = item->row();

    m_children.removeOne(item);

    for(int i = current; i < childCount(); i++)
    {
        this->child(i)->setRow(i);
    }
}

void TreeItem::removeChild(int row)
{
    if (row >=0 && row < m_children.size())
    {
        m_children.removeAt(row);
    }

    for(int i = row; i < childCount(); i++)
    {
       this->child(i)->setRow(i);
    }
}

// 清空所有子节点
void TreeItem::removeChildren()
{
    qDeleteAll(m_children);
    m_children.clear();
}

// 获取本节点第column列的数据
QVariant TreeItem::data(int column, int role) const
{
    QStringList &keys = m_model->m_headerKeys;
//    if (column >= keys.size())
//    {
//        return QVariant();
//    }
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        return m_data.value(keys.at(column));
    }
    else
    {
        return QVariant();
    }
}
// 设置本节点第column列的数据
void TreeItem::setData(int column, const QVariant &value, int role)
{
    QStringList keys = m_model->m_headerKeys;
    if (column >= keys.size())
    {
        return ;
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        m_data.insert(keys.at(column), value);
    }
}

void TreeItem::setDataMap(const QVariantMap &value)
{
    m_data = QVariantMap(value);
}

QVariantMap TreeItem::dataMap() const
{
    return m_data;
}






