#ifndef TREEMODEL_H
#define TREEMODEL_H
#include <QAbstractItemModel>

class TreeItem;

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:

    TreeModel(QObject *parent = Q_NULLPTR);
    explicit TreeModel(const QStringList& headers, QObject *parent = nullptr);
    ~TreeModel() override;

    //只读模型实现
    Qt::ItemFlags flags(const QModelIndex &index) const override;
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
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    //自定义模型索引
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    TreeItem *itemFromIndex(const QModelIndex &index) const;
    QModelIndex indexFromItem(TreeItem* item);
    void clear();
    TreeItem *root();

    QStringList headerKeys() const;
    void setHeaderKeys(const QStringList &headerKeys);

private:
    QStringList m_headers;
    QStringList m_headerKeys;

    TreeItem* m_rootItem;
    friend TreeItem;

};

#endif // TREEMODEL_H
