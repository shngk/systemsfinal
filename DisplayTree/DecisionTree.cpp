#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <array>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "DisplayTree.h"
#include <QApplication>

using namespace std;

class entry{
public:
    string type;
    int num_type;
    vector<double> attributes;
};

class node{
public:
    int attributeIndex;
    double median;
    string type;
    node* left;
    node* right;
};

int typeCount;
int curAttIndex;
node root;

struct entrycmp{
    bool operator() (const entry *e1, const entry *e2){
        //cout << "compare" << endl;
        //cout << e1->attributes[curAttIndex] << endl;
        //cout << e2->attributes[curAttIndex] << endl;
       return (e1->attributes[curAttIndex] < e2->attributes[curAttIndex]);
    }
};

void read_data(ifstream &dataset, vector<entry*> &data);
double getGain(vector<entry*> &set);
//bool entryCmp(entry* e1,entry* e2);
double getEntropy(vector<entry*> &set);
bool diff(vector<entry*> &set);
void buildTree(vector<entry*> &set, node* root);
vector< vector<entry*> > getSubSet(vector<entry*> &set);
void printSet(vector<entry *> &set);
void freeTree(node* root);

int main(int argc, char *argv[]){
    ifstream dataset;
    dataset.open("../DecisionTree/iris.data");
    if (dataset.is_open()) {
       vector<entry*> data;
       read_data(dataset, data);
       node* root = new node;
       buildTree(data, root);
       cout<<"DONE"<<endl;

       QApplication a(argc, argv);
       MainWindow w;
       w.show();

       freeTree(root);

       return a.exec();
       //return 0;
    }
    else{
         cout << "fail" << endl;
    }
    dataset.close();




}
void free_data(vector<entry*> data){
    for(int i = 0; i < (int)data.size(); i++){
        delete data[i];
    }
}

void freeTreeHelper(node *&cur){
    if (cur != nullptr){
        if (cur->left == nullptr && cur->right == nullptr){
            delete cur;
            cur = nullptr;
        }
        else{
            freeTreeHelper(cur->right);
            freeTreeHelper(cur->left);
        }
    }
}

//free the memory associated with the tree whose root
//node is represented by the given pointer.
void freeTree(node* root) {
    while (root != nullptr){
        freeTreeHelper(root);
    }
}

void read_data(ifstream &dataset, vector<entry*> &data){
    int num = 0;
    while (!dataset.eof()) {
        string line;
        string token;
        string delimiter = ",";
        getline(dataset, line);
        size_t pos = 0;

        if(line[0] != 0){
            entry* new_row = new entry;
            while((pos = line.find(delimiter)) != string::npos){
              token = line.substr(0,pos);
              double d = stod(token, NULL);
              new_row->attributes.push_back(d);
              line.erase(0,pos+delimiter.length());
            }
            if(data.size() != 0 && data[data.size()-1]->type != line){
             num++;
            }
            new_row->type = line;
            new_row->num_type = num;
            data.push_back(new_row);
        }
    }
    typeCount=num;
}


void buildTree(vector<entry*> &set, node* root){
    if(diff(set)){
        cout<<"set is difference"<<endl;
        printSet(set);
        int attIndex=0;
        double gainMax=0;
        for(int i=0;i<(int) set[0]->attributes.size();i++){
            curAttIndex=i;
            cout << "curAttIndex" <<": "<<curAttIndex<< endl;
            double gain=getGain(set);
            cout << "gain: "<<gain<<endl;
            if(gain>gainMax){
                gainMax=gain;
                attIndex=i;
            }
        }
        curAttIndex=attIndex;
        cout<<"classifying according to: "<<curAttIndex<<endl;
        stable_sort(set.begin(), set.end(), entrycmp());
        vector< vector<entry*> > temp=getSubSet(set);
        vector<entry*> sub1=temp[0];
        vector<entry*> sub2=temp[1];
        node* left=new node;
        node* right=new node;
        //left->attributeIndex=curAttIndex;
        //right->attributeIndex=curAttIndex;
        root->left=left;
        root->right=right;
        root->median=sub2[0]->attributes[curAttIndex];
        root->attributeIndex=curAttIndex;
        cout<<"median: "<<root->median<<endl;
        cout<<"sub1: "<<sub1.size()<<endl;
        printSet(sub1);
        cout<<"sub2: "<<sub2.size()<<endl;
        printSet(sub2);
        buildTree(sub1,left);
        buildTree(sub2,right);
    }else{
        root->type=set[0]->type;
    }
}

bool diff(vector<entry*> &set){
    int type=set[0]->num_type;

    for(int i=0;i< (int) set.size();i++){
        if(set[i]->num_type!=type){
            return true;
        }
    }
    return false;
}

double getGain(vector<entry*> &set){
    double infoGain=getEntropy(set);
    stable_sort(set.begin(), set.end(), entrycmp());
    vector< vector<entry*> > temp=getSubSet(set);
    vector<entry*> sub1=temp[0];
    vector<entry*> sub2=temp[1];
    infoGain=infoGain-((double)sub1.size()/set.size())*getEntropy(sub1)-((double)sub2.size()/set.size())*getEntropy(sub2);
    return infoGain;
}

double getEntropy(vector<entry*> &set){
    double entropy=0;
    vector<int> count (typeCount);
    for(int i=0;i< (int) set.size();i++){
        count[set[i]->num_type]++;
    }

    for(int i=0;i<(int)count.size();i++){
        if(count[i]!=0){
        entropy=entropy-((double)count[i]/(int)set.size())*log2((double)count[i]/(int)set.size());
        }
    }
    return entropy;
}

vector< vector<entry*> > getSubSet(vector<entry*> &set){
    //cout << "getting subSet" << endl;
    vector<entry*> sub1;
    vector<entry*> sub2;
    for(int i=0;i<(int)set.size();i++){
        if(i<(int)set.size()/2){
            sub1.push_back(set[i]);
        }else{
            sub2.push_back(set[i]);
        }
    }
    vector< vector<entry*> > ret;
    ret.push_back(sub1);
    ret.push_back(sub2);
    return ret;
}

void printSet(vector<entry*> &set){
    for(int i=0;i<(int)set.size();i++){
        vector<double> cur=set[i]->attributes;
        for(int j=0;j<(int)cur.size();j++){
            cout<<cur[j]<<",";
        }
        cout<<set[i]->num_type<<endl;
    }
}
