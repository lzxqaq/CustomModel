#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QAbstractTableModel>


class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    TableModel(QObject *parent = Q_NULLPTR);
    explicit TableModel(const QStringList& headers, QObject *parent = nullptr);
    ~TableModel() override;

    //只读模型实现
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    //设置列的图标
    void setColIcons(int displayCol, const QVariantList &values, const QStringList &icons, int sourceCol = -1);

    //为编辑实现
    bool setData(const QModelIndex &index, const QVariant &value, int role = 0)  override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value,
                       int role = Qt::EditRole) override;

    //为插入和删除实现
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;


    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

    void clear();



    QList<QVariantList> cells() const;
    void setCells(const QList<QVariantList> &cells);

private:
    QStringList m_headers;
    QList<QVariantList> m_cells;
};

#endif // TABLEMODEL_H
