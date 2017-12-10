#ifndef DISPLAYTREE_H
#define DISPLAYTREE_H

#include <QMainWindow>
#include <DecisionTree.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void getRoot(node* r);

private:
    Ui::MainWindow *ui;
};

#endif // DISPLAYTREE_H
