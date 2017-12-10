#include "DisplayTree.h"


int main(int argc, char *argv[]){
    ifstream dataset;
    dataset.open("../DecisionTree/iris.data");
    if (dataset.is_open()) {
       vector<string> names = {"Sepal Length", "Sepal Width", "Petal Length", "Petal Width"};
       vector<entry*> data;
       int typeCount = 0;
       read_data(dataset, data, typeCount);
       node *root = new node;
       buildTree(data, root, typeCount);
       vector<node*> tree;
       //nodeList(root,tree);
       //cout<<tree.size()<<endl;
       cout<<"DONE"<<endl;

       QApplication a(argc, argv);
       MainWindow w;
       w.getTree(tree);
       w.getAttributes(names);
       w.show();

       freeTree(root);
       return a.exec();
    }
    else{
         cout << "fail" << endl;
    }
    dataset.close();

}
