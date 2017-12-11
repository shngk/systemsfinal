#include <DisplayTree.h>
#include "ui_DisplayTree.h"
#include <QtOpenGL>
#include <iostream>
#include <QScrollArea>

vector<node*> tree;
node* root;
int dep;
int w=1280;
int h=800;
int size=90;
std::vector<std::string> attributes;
int c=0;
QPainter p;

void paintNode(QPainter &p, int x, int y,node* cur);
void paintTree(QPainter &p,int x, int y,int d,node* cur);

void printTree(node *r){

    if(r->left == nullptr && r->right == nullptr){
        cout << r->median << endl;
        c++;
    }
    else{

        cout << r->median << endl;
        c++;
        printTree(r->left);
        printTree(r->right);
    }
}

void MainWindow::getRoot(node* r,int d){
    //cout<<"calling getRoot"<<endl;
    root = r;
    dep=d;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(w,h);

    paintEvent paint = new paintEvent;

}


void MainWindow::getAttributes(std::vector<std::string> att){
    attributes=att;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void QWidget::paintEvent(QPaintEvent*){

    p.begin(this);
    QRectF bg(0,0,w,h);
    p.fillRect(bg,Qt::white);
    paintTree(p,w/2,0,dep-1,root);
    p.end();

}


void paintTree(QPainter &p,int x, int y,int d, node* cur){
    if(cur->left==nullptr && cur->left==nullptr){
        paintNode(p,x-size,y,cur);
    }else{
        paintNode(p,x-(size/2),y,cur);
        p.drawLine(x-((size/2)*pow(2,d)),y+size,x+((size/2)*pow(2,d)),y+size);
        paintTree(p,x-((size/2)*pow(2,d)),y+size,d-1,cur->left);
        paintTree(p,x+((size/2)*pow(2,d)),y+size,d-1,cur->right);
    }
}

void paintNode(QPainter &p, int x, int y,node* cur){
    //printTree(root);
    p.drawEllipse(x+(size/6),y+(size/9),size*2/3,size*2/3);
    p.drawLine(x+(size/2),y,x+(size/2),y+(size/9));
    QRectF rectangle(x,y+(size*2/9),size,size*4/9);
    p.fillRect(rectangle,Qt::white);
    QString text=QString::fromStdString(attributes[cur->attributeIndex]);
    text.append("\n");
    text.append(QString::fromStdString(to_string(cur->median)));
    p.drawText(rectangle,Qt::AlignCenter,text);
    if(cur->left!=nullptr && cur->right!=nullptr){
        p.drawLine(x+(size/2),y+(size*7/9),x+(size/2),y+size);
    }
}

