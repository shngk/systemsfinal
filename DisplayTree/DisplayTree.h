#ifndef DISPLAYTREE_H
#define DISPLAYTREE_H

#include <QMainWindow>

class node{
public:
    int attributeIndex;
    double median;
    std::string type;
    node* left;
    node* right;
};

node r;

void passRoot(node root){
    r=root;
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // DISPLAYTREE_H
