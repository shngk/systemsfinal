#include "DisplayTree.h"
#include "ui_DisplayTree.h"
#include <QtOpenGL>
#include <iostream>

node* root;

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
    p.begin(this);
    p.end();
}
void MainWindow::getRoot(node* r){
    root = r;
    cout << "hahaha I'm root."<< r->median << endl;
}
