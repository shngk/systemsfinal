#include <DisplayTree.h>
#include "ui_DisplayTree.h"
#include <QtOpenGL>
#include <iostream>
#include <QScrollArea>

vector<node*> tree;
node* root;
int dep;
int w=7500;
int h=800;
int size=60;
std::vector<std::string> attributes;
int c=0;
QPainter p;

void paintNode(QPainter &p, int x, int y,node* cur);
void paintLeaf(QPainter &p, int x, int y, node *cur);
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
<<<<<<< HEAD
    paintTree(p,w/2,0,dep-1,root);
=======
    paintTree(p,w/2,10,dep-2,root);
>>>>>>> 97bf14da524d0306bf5b363fd41e6eb55f49f209
    p.end();

}


void paintTree(QPainter &p,int x, int y,int d, node* cur){
    if(cur->left==nullptr && cur->left==nullptr){
        paintLeaf(p,x-size,y,cur);
    }else{
        paintNode(p,x-(size/2),y,cur);
        p.drawLine(x-((size/2)*pow(2,d)),y+size+30,x+((size/2)*pow(2,d)),y+size+30);
        paintTree(p,x-((size/2)*pow(2,d)),y+size+30,d-1,cur->left);
        paintTree(p,x+((size/2)*pow(2,d)),y+size+30,d-1,cur->right);
    }
}

void paintNode(QPainter &p, int x, int y,node* cur){
    p.drawEllipse(x,y+10,size,size);
    p.drawLine(x+(size/2),y,x+(size/2),y+10);
    QRectF rectangle(x-(size/6),y+(10+size/6),size*4/3,size*2/3);
    p.fillRect(rectangle,Qt::white);
    QString text=QString::fromStdString(attributes[cur->attributeIndex]);
    text.append("\n");
    text.append(QString::fromStdString(to_string(cur->median)));
    p.drawText(rectangle,Qt::AlignCenter,text);
    p.drawLine(x+(size/2),y+(10+size),x+(size/2),y+size+30);
}

void paintLeaf(QPainter &p, int x, int y,node* cur){
    p.drawEllipse(x+(size/2),y+10,size,size);
    p.drawLine(x+(size),y,x+(size),y+10);
    QRectF rectangle(x+(size/2),y+(10+size/6),size,size*2/3);
    p.fillRect(rectangle,Qt::white);
    std::string str=cur->type;
    int i = str.find("-");
    QString text=QString::fromStdString(str.substr(0,i+1));
    text.append("\n");
    text.append(QString::fromStdString(str.substr(i+1,str.length())));
    p.drawText(rectangle,Qt::AlignCenter,text);
}

