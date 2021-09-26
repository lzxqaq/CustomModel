#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QColor>

class TreeModel;

class TreeItem
{
public:
    explicit TreeItem(TreeModel *model, TreeItem *parent = nullptr);
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

    //设置、获取节点存的数据
    void setDataMap(const QVariantMap &value);
    QVariantMap dataMap() const;

    // 保存该节点是其父节点的第几个子节点，查询优化所用
    void setRow(int row) { m_row = row; }
    // 返回本节点位于父节点下第几个子节点
    int row() const { return m_row; }

private:
    QList<TreeItem*> m_children;// 子节点
    TreeItem *m_parent;// 父节点
    QVariantMap m_data;// 存储数据

    int m_row;// 此item位于父节点中第几个

    TreeModel *m_model;
    friend TreeModel;
};
#endif // TREEITEM_H
