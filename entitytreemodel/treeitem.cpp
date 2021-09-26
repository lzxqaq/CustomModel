#include "treeitem.h"

TreeItem::TreeItem(TreeItem *parent)
    : m_parent(parent), m_row(-1)
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

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        BaseNode *ptr = this->ptr();
        if(ptr == Q_NULLPTR)
        {
            return QVariant();
        }
        return ptr->data(column);
    }
    else
    {
        return QVariant();
    }
}
// 设置本节点第column列的数据
void TreeItem::setData(int column, const QVariant &value, int role)
{

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        BaseNode *ptr = this->ptr();
        if(ptr == Q_NULLPTR)
        {
            return ;
        }

        ptr->setData(column, value);
    }
}






