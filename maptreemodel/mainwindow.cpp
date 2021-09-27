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

    QList<QVariantMap> data;


    QVariantMap root;
    root.insert("id", 1);
    root.insert("parentId", 0);
    root.insert("property1", "第一层");
    root.insert("property2", "属性2");
    root.insert("property3", "属性3");
    root.insert("property4", "属性4");
    root.insert("property5", "属性5");
    data.append(root);


    int id = 2;
    for (; id < 1000; id++)
    {
        QVariantMap map;
        map.insert("id", id);
        map.insert("parentId", 1);
        map.insert("property1", "第二层");
        map.insert("property2", "属性2");
        map.insert("property3", "属性3");
        map.insert("property4", "属性4");
        map.insert("property5", "属性5");
        data.append(map);
    }

    int j = 2;
    for (; id < 1000000; id++)
    {
        QVariantMap map;
        map.insert("id", id);
        map.insert("parentId", j++);
        map.insert("property1", "第三层");
        map.insert("property2", "属性2");
        map.insert("property3", "属性3");
        map.insert("property4", "属性4");
        map.insert("property5", "属性5");
        data.append(map);
        if (j >= 1000)
        {
            j = 2;
        }
    }


    QStringList headers;
    headers << "ID" << "ParentID" << "属性1" << "属性2" << "属性3" << "属性4" << "属性5";
    QStringList headerKeys;
    headerKeys << "id" << "parentId" << "property1" << "property2" << "property3" << "property4" << "property5";
    m_treeModel = new TreeModel(headers, m_treeView);
    m_treeModel->setHeaderKeys(headerKeys);
    m_treeView->setModel(m_treeModel);


    QTime begin = QTime::currentTime();


    begin = QTime::currentTime();



    int parentID = -1;
    TreeItem *parent = m_treeModel->root();
    TreeItem *item = Q_NULLPTR;
    QHash<int, TreeItem*> TreeItems;

    if (data.size() > 0)
    {

        item = new TreeItem(m_treeModel, parent);
        item->setDataMap(data.at(0));

        TreeItems.insert(data.at(0).value("id").toInt(), item);
    }
    else
    {
        return ;
    }

    parentID = data.at(0).value("parentId").toInt();
    parent = item;

    for (int i = 1; i < data.size(); i++)
    {
        if (parentID != data.at(i).value("parentId").toInt())
        {
            parentID = data.at(i).value("parentId").toInt();
            parent = TreeItems.value(parentID);
        }

        if(parent == Q_NULLPTR)
        {
            continue;
        }

        item = new TreeItem(m_treeModel, parent);
        item->setDataMap(data.at(i));

        TreeItems.insert(data.at(i).value("id").toInt(), item);
    }

    QTime end = QTime::currentTime();

    m_treeView->expandToDepth(0);


    qDebug() <<"time" << begin.msecsTo(end);

}

