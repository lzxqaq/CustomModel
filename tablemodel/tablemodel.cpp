#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

TableModel::TableModel(const QStringList& headers, QObject *parent)
    : QAbstractTableModel(parent)
{
    m_headers = headers;
}

TableModel::~TableModel()
{
    clear();
}

// 获取表头数据
QVariant TableModel::headerData(int section, Qt::Orientation orientation,
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
QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    if (role == Qt::DisplayRole || role == Qt::EditRole || role == Qt::BackgroundRole)
    {
        int row = index.row();
        int col = index.column();
        return m_cells[row][col];
    }
    else if (role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    return QVariant();
}

bool TableModel::setData(const QModelIndex &index,
                         const QVariant &value, int role)
{
    if (index.isValid()) {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            m_cells[index.row()][index.column()] = value;
        }
        QVector<int> roles((role == Qt::DisplayRole) ?
                               QVector<int>({Qt::DisplayRole, Qt::EditRole}) :
                               QVector<int>({role}));

        //发出信号 通知 data函数重新读取数据

        if(role == Qt::BackgroundRole)
        {
            emit dataChanged(createIndex(index.row(), 0) ,createIndex(index.row(), columnCount()), roles);
        }
        else
        {
            emit dataChanged(index, index, roles);
        }

        return true;
    }
    return false;
}

bool TableModel::setHeaderData(int section, Qt::Orientation orientaion,
                               const QVariant &value, int role)
{
    if (role != Qt::EditRole && orientaion == Qt::Horizontal) {
        m_headers.replace(section, value.toString());
        emit headerDataChanged(Qt::Horizontal, section, section);
        return true;
    }
    return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
    {
        return Qt::ItemIsEnabled;
    }
    //保留原来已经存在的那些标记。
    return QAbstractTableModel::flags(index) |= Qt::ItemIsEditable;
}



// 获取索引parent下有多少行
int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_cells.size();
}

// 返回索引parent下有多少列
int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_headers.size();
}


void TableModel::clear()
{
    beginResetModel();

    m_cells.clear();

    endResetModel();

}

QList<QVariantList> TableModel::cells() const
{
    return m_cells;
}

void TableModel::setCells(const QList<QVariantList> &cells)
{
    m_cells = cells;
}


bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count -1);

    //未验证
    for (int i = 0; i < count; i++)
    {
        QVariantList newRow;
        m_cells.append(newRow);
    }

    endInsertRows();
    return true;
}
bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int rows = this->rowCount(parent);
    if (rows <= 0 || rows < row + count)
    {
        return false;
    }
    beginRemoveRows(parent, row, row + count - 1);

    //未验证
    for (int i = 0; i < count; i++)
    {
        m_cells.removeAt(row);
    }

    endRemoveRows();
    return true;
}
bool TableModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    return QAbstractTableModel::insertColumns(column, count, parent);
}
bool TableModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    return QAbstractTableModel::removeColumns(column, count, parent);
}

QModelIndex TableModel::index(int row, int column, const QModelIndex &parent) const
{
    return hasIndex(row, column, parent) ? createIndex(row, column) : QModelIndex();
}







