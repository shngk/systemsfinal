#include <DisplayTree.h>
#include "ui_DisplayTree.h"
#include <QtOpenGL>
#include <iostream>

vector<node*> tree;
std::vector<std::string> attributes;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,600);
}


void MainWindow::getTree(vector<node*> &t){
    tree = t;
    //cout<<t.size()<<endl;
    /*for(int i=0;i<(int)tree.size();i++){
        cout<<tree[i]->median<<endl;
    }*/
}

void MainWindow::getAttributes(std::vector<std::string> att){
    attributes=att;
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

