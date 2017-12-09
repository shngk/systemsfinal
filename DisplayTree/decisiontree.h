#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#endif // DECISIONTREE_H

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

extern node* root;
extern int typeCount;
extern int curAttIndex;

struct entrycmp{
    bool operator() (const entry *e1, const entry *e2){
       return (e1->attributes[curAttIndex] < e2->attributes[curAttIndex]);
    }
};

void read_data(ifstream &dataset, vector<entry*> &data);
double getGain(vector<entry*> &set);
double getEntropy(vector<entry*> &set);
bool diff(vector<entry*> &set);
void buildTree(vector<entry*> &set, node* root);
vector< vector<entry*> > getSubSet(vector<entry*> &set);
void printSet(vector<entry *> &set);
void freeTree(node* root);
