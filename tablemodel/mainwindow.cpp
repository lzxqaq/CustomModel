#include "mainwindow.h"
#include <QHeaderView>
#include <QtDebug>
#include <QTime>
#include <QHBoxLayout>

#include "tablemodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(500, 500);
    m_tableView = new QTableView(this);
    setCentralWidget(m_tableView);
    init();
}

MainWindow::~MainWindow()
{

}

void MainWindow::init()
{

    QList<QVariantList> data;
    QVariantList row;
    row << "属性1" << "属性2" << "属性3" << "属性4" << "属性5";

    for(int i = 0; i < 1000000; i++)
    {
        data << row;
    }

    QTime begin = QTime::currentTime();

    QStringList headers;
    headers << "表头1" << "表头2" << "表头3" << "表头4" << "表头5";
    m_tableModel = new TableModel(headers, m_tableView);
    m_tableView->setModel(m_tableModel);
    m_tableModel->setCells(data);

    QTime end = QTime::currentTime();

    qDebug() <<"time" << begin.msecsTo(end);

}

