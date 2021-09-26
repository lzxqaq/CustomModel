#include "treemodel.h"
#include "treeitem.h"

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    m_rootItem = new TreeItem();
}

TreeModel::TreeModel(const QStringList& headers, QObject *parent)
    : QAbstractItemModel(parent)
{
    m_headers = headers;
    m_rootItem = new TreeItem();
}

TreeModel::~TreeModel()
{
    clear();
    delete m_rootItem;
}

TreeItem *TreeModel::itemFromIndex(const QModelIndex &index) const
{
    if (index.isValid())
    {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        return item;
    }
    return m_rootItem;
}

TreeItem *TreeModel::root()
{
    return m_rootItem;
}

// 获取表头数据
QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if(role == Qt::DisplayRole)
        {
            return m_headers.at(section);
        }
    }
    return QVariant();
}



// 获取index.row行，index.column列数据
QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    TreeItem *item = itemFromIndex(index);
    if (role == Qt::DisplayRole || role == Qt::EditRole || role == Qt::BackgroundRole)
    {
        return item->data(index.column(), role);
    }
    return QVariant();
}

bool TreeModel::setData(const QModelIndex &index,
                        const QVariant &value, int role)
{
    if (index.isValid()) {
        TreeItem *item = itemFromIndex(index);
        item->setData(index.column(), value, role);

        QVector<int> roles((role == Qt::DisplayRole) ?
                               QVector<int>({Qt::DisplayRole, Qt::EditRole}) :
                               QVector<int>({role}));

        //发出信号 通知 data函数重新读取数据

        if(role == Qt::BackgroundRole)
        {
            emit dataChanged(createIndex(item->row(), 0, item),
                             createIndex(item->row(), columnCount() - 1, item), roles);
        }
        else
        {
            emit dataChanged(index, index, roles);
        }

        return true;
    }
    return false;
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientaion,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole && orientaion == Qt::Horizontal) {
        m_headers.replace(section, value.toString());
        emit headerDataChanged(Qt::Horizontal, section, section);
        return true;
    }
    return false;
}

// 在parent节点下，第row行，第column列位置上创建索引
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem = itemFromIndex(parent);
    TreeItem *item = parentItem->child(row);
    if (item)
        return createIndex(row, column, item);
    else
        return QModelIndex();
}

// 创建index的父索引
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *item = itemFromIndex(index);
    TreeItem *parentItem = item->parent();

    if (parentItem == m_rootItem)
        return QModelIndex();
    return createIndex(parentItem->row(), 0, parentItem);
}

// 获取索引parent下有多少行
int TreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    TreeItem* item = itemFromIndex(parent);
    return item->childCount();
}

// 返回索引parent下有多少列
int TreeModel::columnCount(const QModelIndex &parent) const
{
    return m_headers.size();
}

QModelIndex TreeModel::indexFromItem(TreeItem *item)
{
    if (item && item->parent()) {
        return createIndex(item->row(),0,item);
    }
    return QModelIndex();
}

void TreeModel::clear()
{
    beginResetModel();

    m_rootItem->removeChildren();

    endResetModel();

}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{

    if(!index.isValid())
    {
        return Qt::ItemIsEnabled;
    }
    //保留原来已经存在的那些标记。
    return QAbstractItemModel::flags(index) |= Qt::ItemIsEditable;
}
//暂时只能在最后一行插入
bool TreeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count -1);
    TreeItem* parentItem = itemFromIndex(parent);
    for(int i =  0; i < count; i++)
    {
        new TreeItem(parentItem);
    }
    endInsertRows();
    return true;
}
bool TreeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int rows = this->rowCount(parent);
    if (rows <= 0 || rows < row + count)
    {
       return false;
    }
    beginRemoveRows(parent, row, row + count - 1);
    TreeItem* parentItem = itemFromIndex(parent);
    for(int i = 0; i < count; i++)
    {
        parentItem->removeChild(row);
    }
    endRemoveRows();
    return true;
}
bool TreeModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    return QAbstractItemModel::insertColumns(column, count, parent);
}
bool TreeModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    return QAbstractItemModel::removeColumns(column, count, parent);
}







