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

using namespace std;

struct entry{
    string type;
    int num_type;
    vector<double> attributes;
};

class node{
public:
	node(){
		node::attributeIndex=-1;
		node::median=-1;
		node::left=NULL;
		node::right=NULL;
	}
	int attributeIndex;
	double median;
	node* left;
	node* right;
};

void read_data(ifstream &dataset, vector<entry*> &data);
double getGain(vector<entry*> &set, int attIndex);
bool entryCmp(entry e1,entry e2);
double getEntropy(vector<entry*> &set, int attIndex);
bool diff(vector<entry*> &set);
void buildTree(vector<entry*> &set, node* root);
vector<entry*> getSubSet(vector<entry*> &set);

int typeCount;
int curAttIndex;
node root;

int main()
{
    ifstream dataset;
    dataset.open("./DecisionTree/iris.data");
    if (dataset.is_open()) {
       vector<entry*> data;
       read_data(dataset, data);
       node root;
       buildTree(data, &root);
    }
    else{
         cout << "fail" << endl;
    }
    dataset.close();
    return 0;


}

void read_data(ifstream &dataset, vector<entry*> &data){
    int num = 0;
    while (!dataset.eof()) {
        string line;
        string token;
        string delimiter = ",";
        getline(dataset, line);
        size_t pos = 0;
         entry* new_row=new entry;
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
    typeCount=num;
}

void buildTree(vector<entry*> &set, node *root){
	if(diff(set)){
		int attIndex=0;
		double gainMax=0;
		for(int i=0;i<set[0]->attributes.size();i++){
			curAttIndex=i;
			//cout << curAttIndex << endl;
			double gain=getGain(set,i);
			//cout << gain << endl;
			if(gain>gainMax){
				gain=gainMax;
				attIndex=i;
			}
		}
		//cout << attIndex << endl;
		//cout << gainMax << endl;
		curAttIndex=attIndex;
		vector<entry*> sub1,sub2=getSubSet(set);
		node* left=new node;
		node* right=new node;
		left->attributeIndex=curAttIndex;
		right->attributeIndex=curAttIndex;
		root->left=left;
		root->right=right;
		root->median=sub2[0]->attributes[curAttIndex];
		buildTree(sub1,left);
		buildTree(sub2,right);
	}
}

bool diff(vector<entry*> &set){
	int type=set[0]->num_type;
	for(int i=0;i<set.size();i++){
		if(set[i]->num_type!=type){
			return true;
		}
	}
	return false;
}

double getGain(vector<entry*> &set, int attIndex){
	double infoGain=getEntropy(set,attIndex);
	/*for(int i=0;i<set.size();i++){
		cout << set[i].attributes[curAttIndex] << endl;
	}*/
	sort(set.begin(),set.end(),entryCmp);
	/*cout << "sorted" << endl;
	for(int i=0;i<set.size();i++){
			cout << set[i].attributes[curAttIndex] << endl;
		}*/
	vector<entry*> sub1,sub2=getSubSet(set);
	cout << sub1.size() << endl;
	cout << sub2.size() << endl;
	infoGain=infoGain-(sub1.size()/set.size())*getEntropy(sub1,attIndex)-(sub2.size()/set.size())*getEntropy(sub2,attIndex);
	cout << infoGain << endl;
	return infoGain;
}

double getEntropy(vector<entry*> &set, int attIndex){
	double entropy=0;
	vector<int> count (typeCount);
	for(int i=0;i<set.size();i++){
		count[set[i]->num_type]++;
	}
	for(int i=0;i<count.size();i++){
		entropy-=((double)count[i]/set.size())*log2((double)count[i]/set.size());
	}
	return entropy;
}

vector<entry*> getSubSet(vector<entry*> &set){
	cout << "getting subSet" << endl;
	vector<entry*> sub1,sub2;
	for(int i=0;i<set.size();i++){
		if(i<=set.size()/2){
			sub1.push_back(set[i]);
		}else{
			sub2.push_back(set[i]);
		}
	}
	return sub1,sub2;
}

bool entryCmp(entry* e1,entry* e2){
	cout << "compare" << endl;
	cout << e1->attributes[curAttIndex] << endl;
	cout << e2->attributes[curAttIndex] << endl;
	return (bool)(e1->attributes[curAttIndex]<e2->attributes[curAttIndex]);
}




