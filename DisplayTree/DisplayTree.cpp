/* CSCI 241: Final Project
 * Synthia Wang, Han Shao, Sheng Kao, Rebecca Lawrence
 * DisplayTree.cpp takes root from main.cpp and prints the tree in MainWindow.
 *
 * Note: DisplayTree.cpp must be compiled by Qt Creator since we used the QT GUI library.
 *
 * @author Synthia Wang, Han Shao
 */

#include <DisplayTree.h>
#include "ui_DisplayTree.h"
#include <QtOpenGL>
#include <iostream>


//width of the MainWindow
const int w=7500;
//height of the MainWindow
const int h=800;
//size of one node
const int size=60;
//depth of the tree
int dep;

node* root;
std::vector<std::string> attributes;


void paintNode(QPainter &p, int x, int y,node* cur);
void paintLeaf(QPainter &p, int x, int y, node *cur);
void paintTree(QPainter &p,int x, int y,int d,node* cur);

/*Test function: prints median of each node.
 */
void printTree(node *r){

    if(r->left == nullptr && r->right == nullptr){
        cout << r->median << endl;

    }
    else{

        cout << r->median << endl;

        printTree(r->left);
        printTree(r->right);
    }
}

/*gets root and depth from main.cpp
 */
void MainWindow::getRoot(node* r,int d){
    root = r;
    dep=d;
}

/*initializes MainWinow
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(w,h);

}

/*gets vector of attributes from main.cpp
 */
void MainWindow::getAttributes(std::vector<std::string> att){
    attributes=att;
}

/*free MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/*paintEvent changes the color of backgroud and calls paintTree.
 */
void QWidget::paintEvent(QPaintEvent*){
    QPainter p;
    p.begin(this);
    QRectF bg(0,0,w,h);
    p.fillRect(bg,Qt::white);
    paintTree(p,w/2,0,dep-2,root);
    p.end();

}

/* takes QPainter p, x, y, depth of tree, and current node,
 * if current node is a leaf, calls paintLeaf, else if current node is not a leaf,
 * calls paintNode, draw the horizontal line and calls paintTree recursivelly.
 */
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

/* takes QPainter p, x, y, and current node,
 * draws the circle, lines, the rectangle, and prints median and attribute.
 */
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

/* takes QPainter p, x, y, and current node,
 * draws the circle, lines, the rectangle, and prints class.
 */
void paintLeaf(QPainter &p, int x, int y,node* cur){
    p.drawEllipse(x+(size/2),y+10,size,size);
    p.drawLine(x+(size),y,x+(size),y+10);
    QRectF rectangle(x+(size/2)-1,y+(10+size/6),size+2,size*2/3);
    p.fillRect(rectangle,Qt::white);
    std::string str=cur->type;
    int i = str.find("-");
    QString text=QString::fromStdString(str.substr(0,i+1));
    text.append("\n");
    text.append(QString::fromStdString(str.substr(i+1,str.length())));
    p.drawText(rectangle,Qt::AlignCenter,text);
}

