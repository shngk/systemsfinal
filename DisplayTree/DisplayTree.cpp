#include "DisplayTree.h"
#include "ui_DisplayTree.h"
#include <QtOpenGL>

node* root;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void QWidget::paintEvent(QPaintEvent *)
{
    QPainter p;
}
void MainWindow::getRoot(node* r){
    root = r;
    cout << "hahaha I'm root."<< r->median << endl;
}
