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


void read_data(ifstream &dataset, vector<entry*> &data, int &typeCount);
double getGain(vector<entry*> &set,  int &typeCount);
double getEntropy(vector<entry*> &set, int &typeCount);
bool diff(vector<entry*> &set);
void buildTree(vector<entry*> &set, node* root, int &typeCount);
vector< vector<entry*> > getSubSet(vector<entry*> &set);
void printSet(vector<entry *> &set);
void freeTree(node* root);
