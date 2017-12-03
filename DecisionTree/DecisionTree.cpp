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

void read_data(ifstream &dataset, vector<entry> &data);



int main()
{
    ifstream dataset;
    dataset.open("../iris.data");

    if (dataset.is_open()) {
       vector<entry> data;
       read_data(dataset, data);
       /*for(int i = 0; i < (int)data.size(); i++){
           cout << data[i].attributes[0] << " "<< data[i].attributes[1] << " " << data[i].attributes[2] << " " ;
           cout << data[i].num_type << " "<< data[i].type << endl;
       }*/
    }
    else{
         cout << "fail" << endl;
    }
    dataset.close();
    return 0;


}

void read_data(ifstream &dataset, vector<entry> &data){


    int num = 0;
    while (!dataset.eof()) {

        string line;
        string token;
        string delimiter = ",";
        getline(dataset, line);
        size_t pos = 0;

         entry new_row;
         while((pos = line.find(delimiter)) != string::npos){
              token = line.substr(0,pos);
              double d = stod(token, NULL);
              new_row.attributes.push_back(d);
              line.erase(0,pos+delimiter.length());

         }



         if(data.size() != 0 && data[data.size()-1].type != line){
             num++;
         }
         new_row.type = line;
         new_row.num_type = num;
         data.push_back(new_row);
    }
}

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
	vector<double> attributes;
	int type;
};

class node{
public:
	int attributeIndex;
	double median;
	node left;
	node right;
};

int typeCount;
int curAttIndex;
node root;


void buildTree(vector<entry> &set, node &root){
	if(diff(set)){
		int attIndex=0;
		double gainMax=0;
		for(int i=0;i<set[0].attributes.size();i++){
			curAttIndex=i;
			double gain=getGain(set,i);
			if(gain>gainMax){
				gain=gainMax;
				attIndex=i;
			}
		}
		curAttIndex=attIndex;
		vector<entry> sub1,sub2=getSubSet(set);
		node left,right;
		left.attributeIndex=curAttIndex;
		right.attributeIndex=curAttIndex;
		root.left=left;
		root.right=right;
		root.median=sub2[0].attributes[curAttIndex];
		buildTree(sub1,left);
		buildTree(sub2,right);
	}
}

bool diff(vector<entry> &set){
	int type=set[0].type;
	for(entry i:set){
		if(i.type!=type){
			return true;
		}
	}
	return false;
}

double getEntropy(vector<entry> &set, int attIndex){
	double entropy=0;
	vector<int> count (typeCount);
	for(entry i :set){
		count[i.type]++;
	}
	for(int n:count){
		entropy-=(n/set.size())*log2(n/set.size());
	}
	return entropy;
}

double getGain(vector<entry> &set, int attIndex){
	double infoGain=getEntropy(set,attIndex);
	sort(set.begin(),set.end(),entryCmp);
	vector<entry> sub1,sub2=getSubSet(set);
	infoGain=infoGain-(sub1.size()/set.size())*getEntropy(sub1,attIndex)-(sub2.size()/set.size())*getEntropy(sub2,attIndex);
	return infoGain;
}

double getSubSet(vector<entry> &set){
	vector<entry> sub1,sub2;
	for(int i=0;i<set.size();i++){
		if(i<=set.size()/2){
			sub1.push_back(set[i]);
		}else{
			sub2.push_back(set[i]);
		}
	}
	return sub1,sub2;
}

bool entryCmp(entry e1,entry e2){
	return e1.attributes[curAttIndex]<e2.attributes[curAttIndex];
}

