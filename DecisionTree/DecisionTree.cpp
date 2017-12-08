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
	node* left;
	node* right;
};

int typeCount;
int curAttIndex;
node root;

struct entrycmp{
    bool operator() (const entry *e1, const entry *e2){
       /*cout << "compare" << endl;
       cout << e1->attributes[curAttIndex] << endl;
       cout << e2->attributes[curAttIndex] << endl;*/
       return (e1->attributes[curAttIndex] < e2->attributes[curAttIndex]);
    }
};

void read_data(ifstream &dataset, vector<entry*> &data);
double getGain(vector<entry*> &set, int attIndex);
bool entryCmp(entry* e1,entry* e2);
double getEntropy(vector<entry*> &set);
bool diff(vector<entry*> &set);
void buildTree(vector<entry*> &set, node* root);
vector< vector<entry*> > getSubSet(vector<entry*> &set);


int main()
{
    ifstream dataset;
    dataset.open("../DecisionTree/iris.data");
    if (dataset.is_open()) {
       vector<entry*> data;
       read_data(dataset, data);
       node *root=new node;
       buildTree(data, root);
       /*for(int i = 0; i < (int)data.size(); i++){
           cout << data[i]->attributes[0] << " "<< data[i]->attributes[1] << " " << data[i]->attributes[2] << " " ;
           cout << data[i]->num_type << " "<< data[i]->type << endl;
       }*/
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
        entry* new_row = new entry;
        if(line[0] != 0){
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
		int attIndex=0;
		double gainMax=0;
        for(int i=0;i<(int) set[0]->attributes.size();i++){
			curAttIndex=i;
			//cout << curAttIndex << endl;
			double gain=getGain(set,i);
			cout << "gain: ";
			cout <<gain<<endl;
			if(gain>gainMax){
				gain=gainMax;
				attIndex=i;
			}
		}
		//cout << attIndex << endl;
		//cout << gainMax << endl;
		/*curAttIndex=attIndex;
		vector< vector<entry*> > temp=getSubSet(set);
		vector<entry*> sub1=temp[0];
		vector<entry*> sub2=temp[1];
		node* left=new node;
		node* right=new node;
		left->attributeIndex=curAttIndex;
		right->attributeIndex=curAttIndex;
		root->left=left;
		root->right=right;
		root->median=sub2[0]->attributes[curAttIndex];
		buildTree(sub1,left);
		buildTree(sub2,right);*/
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

double getGain(vector<entry*> &set, int attIndex){
	double infoGain=getEntropy(set);
	/*for(int i=0;i<set.size();i++){
		cout << set[i].attributes[curAttIndex] << endl;
	}*/
    /*for(int i = 0; i < (int)set.size(); i++){
        cout << set[i]->attributes[0] << " "<< set[i]->attributes[1] << " " << set[i]->attributes[2] << " " ;
        cout << set[i]->num_type << " "<< set[i]->type << endl;
    }*/

    stable_sort(set.begin(), set.end(), entrycmp());

    cout << "sorted" << endl;
	for(int i=0;i<set.size();i++){
            cout << set[i]->attributes[curAttIndex] << endl;
    }

	//vector< vector<entry*> > temp=getSubSet(set);
	//vector<entry*> sub1=temp[0];
	//vector<entry*> sub2=temp[1];
	//cout << sub1.size() << endl;
	//cout << sub2.size() << endl;
	//infoGain=infoGain-(sub1.size()/set.size())*getEntropy(sub1)-(sub2.size()/set.size())*getEntropy(sub2);
	//cout << infoGain << endl;
	return infoGain;
}

double getEntropy(vector<entry*> &set){
	double entropy=0;
	vector<int> count (typeCount);
    for(int i=0;i< (int) set.size();i++){
		count[set[i]->num_type]++;
	}

    for(int i=0;i<(int)count.size();i++){
		cout << count[i] << endl;
		entropy-=((double)count[i]/set.size())*log2((double)count[i]/set.size());
	}
	cout << "getting entropy" << endl;
	cout << entropy << endl;
	cout << "" << endl;
	return entropy;
}

vector< vector<entry*> > getSubSet(vector<entry*> &set){
	//cout << "getting subSet" << endl;
    vector<entry*> sub1;
    vector<entry*> sub2;
    for(int i=0;i<(int) set.size();i++){
        if(i<=(int)set.size()/2){
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

bool entryCmp(entry *e1,entry *e2){
    cout << "compare" << endl;
    cout << e1->attributes[curAttIndex] << endl;
    cout << e2->attributes[curAttIndex] << endl;
    return (bool)(e1->attributes[curAttIndex] < e2->attributes[curAttIndex]);
}







