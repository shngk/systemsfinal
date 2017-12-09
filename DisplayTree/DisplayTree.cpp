#include "DisplayTree.h"
#include "ui_DisplayTree.h"
#include <QtOpenGL>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,600);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void QWidget::paintEvent(QPaintEvent*){
    QPainter p;
    std::cout<<r.median<<endl;
    p.begin(this);
    p.end();
}

