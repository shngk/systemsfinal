/* CSCI 241: Final Project
 * Synthia Wang, Han Shao, Sheng Kao, Rebecca Lawrence
 * main.cpp imports dataset, builds tree, and displays tree.
 *
 * Note: main.cpp must be compiled by Qt Creator since we used the QT GUI library.
 *
 * @author Synthia Wang, Han Shao
 */
#include "DisplayTree.h"
#include <QApplication>

int main(int argc, char *argv[]){
    ifstream dataset;
    //open dataset
    dataset.open("../DecisionTree/iris.data");
    //open dataset successfully
    if (dataset.is_open()) {
       //vector of names of attributes
       vector<string> names = {"Sepal Length", "Sepal Width", "Petal Length", "Petal Width"};
       //initializes dataset
       vector<entry*> data;
       //number of different types
       int typeCount = 0;
       //reads data from dataset
       read_data(dataset, data, typeCount);
       //inirializes the root node
       node *root = new node;
       //builds tree based on dataset
       buildTree(data, root, typeCount);
       //gets the depth of the tree
       int depth=getDepth(root);


       /*Display Tree
        */
       //opens a QApplicarion
       QApplication a(argc, argv);
       //creates a new MainWindow
       MainWindow w;
       //passes root to DispalyTree.cpp
       w.getRoot(root,depth);
       //passes vector of attributes to DisplayTree.cpp
       w.getAttributes(names);
       //shows the MainWindow
       w.show();

       //executes QApplication a
       int status = a.exec();
       //frees tree
       freeTree(root);
       //close dataset
       dataset.close();
       //return the status of execution of a
       return status;
    }
    //open the dataset unseccesfully
    else{
         cout << "fail" << endl;
    }   
}
