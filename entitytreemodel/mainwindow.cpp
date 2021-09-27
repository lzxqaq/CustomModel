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
    headers << "id" << "parentId" << "属性1" << "属性2" << "属性3" << "属性4" << "属性5";
    m_treeModel = new TreeModel(headers, m_treeView);
    m_treeView->setModel(m_treeModel);

    int parentID = -1;
    TreeItem *parent = m_treeModel->root();
    TreeItem *item = Q_NULLPTR;
    QHash<int, TreeItem*> TreeItems;
    TreeNode *node = Q_NULLPTR;

    if (data.size() > 0)
    {
        node = new TreeNode();
        node->setId(data.at(0).at(0).toInt());
        node->setParentId(data.at(0).at(1).toInt());
        node->setProperty1(data.at(0).at(2).toString());
        node->setProperty2(data.at(0).at(3).toString());
        node->setProperty3(data.at(0).at(4).toString());
        node->setProperty4(data.at(0).at(5).toString());
        node->setProperty5(data.at(0).at(6).toString());

        item = new TreeItem(parent);
        item->setPtr(node);
        parentID = node->id();
        parent = item;
    }
    else
    {
        return ;
    }

    for (int i = 1; i < data.size(); i++)
    {
        node = new TreeNode();
        node->setId(data.at(i).at(0).toInt());
        node->setParentId(data.at(i).at(1).toInt());
        node->setProperty1(data.at(i).at(2).toString());
        node->setProperty2(data.at(i).at(3).toString());
        node->setProperty3(data.at(i).at(4).toString());
        node->setProperty4(data.at(i).at(5).toString());
        node->setProperty5(data.at(i).at(6).toString());

        if (parentID != node->parentId())
        {
            parentID = node->parentId();
            parent = TreeItems.value(parentID);
        }

        if(parent == Q_NULLPTR)
        {
            continue;
        }

        item = new TreeItem(parent);
        item->setPtr(node);

        TreeItems.insert(node->id(), item);
    }

    QTime end = QTime::currentTime();
    m_treeView->expandToDepth(0);

    qDebug() <<"time" << begin.msecsTo(end);

}

