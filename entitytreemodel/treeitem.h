#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QColor>
#include "basenode.h"

class TreeItem
{
public:
    explicit TreeItem(TreeItem *parent = nullptr);
    ~TreeItem();

    void addChild(TreeItem *item);
    void addChild(TreeItem *item, int index);
    void removeChild(TreeItem* item);
    void removeChild(int row);
    void removeChildren();

    TreeItem *child(int row) { return m_children.value(row, Q_NULLPTR); }
    TreeItem *parent() { return m_parent; }

    int childCount() const { return m_children.count(); }

    QVariant data(int column, int role = 0) const;
    void setData(int column, const QVariant &value, int role = Qt::EditRole);
    //设置、获取节点存的数据指针
    void setPtr(BaseNode* p){ m_ptr = p; }
    BaseNode* ptr() const { return m_ptr; }

    // 保存该节点是其父节点的第几个子节点，查询优化所用
    void setRow(int row) { m_row = row; }
    // 返回本节点位于父节点下第几个子节点
    int row() const { return m_row; }



private:
    QList<TreeItem*> m_children;// 子节点
    TreeItem *m_parent;// 父节点
    BaseNode* m_ptr;// 存储数据的指针

    int m_row;// 此item位于父节点中第几个
};
#endif // TREEITEM_H
