#include "mainwindow.h"
#include <QHeaderView>
#include <QtDebug>
#include <QTime>
#include <QHBoxLayout>

#include "treeitem.h"
#include "treemodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(500, 500);
    m_treeView = new QTreeView(this);

    m_treeView->setSelectionBehavior(QTreeView::SelectRows);			//一次选中整行
    m_treeView->setSelectionMode(QTreeView::SingleSelection);        //单选，配合上面的整行就是一次选单行
    m_treeView->setFocusPolicy(Qt::NoFocus);                         //去掉鼠标移到单元格上时的虚线框
    m_treeView->header()->setStretchLastSection(true);               //最后一列自适应宽度

    setCentralWidget(m_treeView);
    init();
}

MainWindow::~MainWindow()
{

}

void MainWindow::init()
{
    QList<QVariantList> data;
    QVariantList root;
    root << 1 << 0 << "第一层" << "属性2" << "属性3" << "属性4" << "属性5";
    data.append(root);


    int id = 2;
    for (; id < 1000; id++)
    {
        QVariantList list;
        list << id << 1 << "第二" << "属性2" << "属性3" << "属性4" << "属性5";
        data.append(list);
    }

    int j = 2;
    for (; id < 100000; id++)
    {
        QVariantList list;
        list << id << j++ << "第三" << "属性2" << "属性3" << "属性4" << "属性5";
        data.append(list);
        if (j >= 1000)
        {
            j = 2;
        }
    }

    QTime begin = QTime::currentTime();



    QStringList headers;
    headers <<"ID" << "ParentID" << "属性1" << "属性2" << "属性3" << "属性4" << "属性5";

    m_treeModel = new TreeModel(headers, m_treeView);
    m_treeView->setModel(m_treeModel);

    int parentID = -1;
    TreeItem *parent = m_treeModel->root();
    TreeItem *item = Q_NULLPTR;
    QHash<int, TreeItem*> TreeItems;

    if (data.size() > 0)
    {

        item = new TreeItem(m_treeModel, parent);
        QVariantList row;
        foreach (auto cell, data.at(0))
        {
            row << cell;
        }
        item->setDataList(row);

        TreeItems.insert(data.at(0).at(0).toInt(), item);
    }
    else
    {
        return ;
    }

    parentID = data.at(0).at(1).toInt();
    parent = item;

    for (int i = 1; i < data.size(); i++)
    {
        if (parentID != data.at(i).at(1).toInt())
        {
            parentID = data.at(i).at(1).toInt();
            parent = TreeItems.value(parentID);
        }

        if(parent == Q_NULLPTR)
        {
            continue;
        }

        item = new TreeItem(m_treeModel, parent);
        QVariantList row;
        foreach (auto cell, data.at(i))
        {
            row << cell;
        }
        item->setDataList(row);

        TreeItems.insert(data.at(i).at(0).toInt(), item);
    }

    QTime end = QTime::currentTime();
    m_treeView->expandToDepth(0);

    qDebug() <<"time" << begin.msecsTo(end);

}

