#include "decisiontree.h"
#include "DisplayTree.h"


int main(int argc, char *argv[]){
    ifstream dataset;
    dataset.open("../DecisionTree/iris.data");
    if (dataset.is_open()) {
       vector<string> names = {"Sepal Length", "Sepal Width", "Petal Length", "Petal Width"};
       vector<entry*> data;
       read_data(dataset, data);
       root = new node;
       buildTree(data, root);
       cout<<"DONE"<<endl;

       QApplication a(argc, argv);
       MainWindow w;
       w.show();

       freeTree(root);
       return a.exec();
    }
    else{
         cout << "fail" << endl;
    }
    dataset.close();

}
