#include <DisplayTree.h>
#include "ui_DisplayTree.h"
#include <QtOpenGL>
#include <iostream>

vector<node*> tree;
node* root;
int dep;
int w=800;
int h=1000;
std::vector<std::string> attributes;
int c=0;

void paintNode(QPainter &p, int x, int y,bool isLeaf);
void paintTree(QPainter &p,int x, int y,node* cur);

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

void MainWindow::getRoot(node* r){
    root = r;
    cout << "getroot" << endl;
    //printTree(r);
    //printTree(r);
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(w,h);

}


void MainWindow::getTree(vector<node*> &t,int d){
    tree = t;
    dep=d;
    //cout<<dep<<endl;
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
    cout << "paint" << " " << c << endl;
    QPainter p;
    p.begin(this);
    paintTree(p,w/2,10,root);
    printTree(root);
    p.end();
}

void paintTree(QPainter &p,int x, int y,node* cur){
    if(cur->left==nullptr && cur->left==nullptr){
        paintNode(p,x-45,y,true);
    }else{
        paintNode(p,x+45,y,false);
        paintTree(p,x-90,y+90,cur->left);
        paintTree(p,x+90,y+90,cur->right);
    }
}

void paintNode(QPainter &p, int x, int y,bool isLeaf){
    p.drawEllipse(x+15,y+10,60,60);
    p.drawLine(x+45,y,x+45,y+10);
    QRectF rectangle(x,y+20,90,40);
    p.fillRect(rectangle,Qt::white);
    if(!isLeaf){
        p.drawLine(x+45,y+70,x+45,y+90);
    }

}

