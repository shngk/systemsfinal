/* CSCI 241: Final Project
 * Synthia Wang, Han Shao, Sheng Kao, Rebecca Lawrence
 * DecisionTree.cpp contains the functions to read data from dataset and build the decision tree.
 *
 * Note: DecisionTree.cpp can be compiled through Terminal.
 * (This version does not contain main function, DecisionTree.cpp in DecisionTree folder works)
 *
 * @author Synthia Wang, Han Shao
 */

#include "DecisionTree.h"

int curAttIndex;

/* compare operator for stable_sort
 */
struct entrycmp{
    bool operator() (const entry *e1, const entry *e2){
       return (e1->attributes[curAttIndex] < e2->attributes[curAttIndex]);
    }
};

/* frees tree
 */
void freeTree(node* root) {
    if (root != nullptr){
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
}

/* takes dataset file, empty vector of data, and 0 of type,
 * to add each row to data, and count the number of types
 */
void read_data(ifstream &dataset, vector<entry*> &data, int &typeCount){
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

/* takes vector set, root node, and number of types,
 * to build the tree
 */
void buildTree(vector<entry*> &set, node* root,  int &typeCount){
    if(diff(set)){
        int attIndex=0;
        double gainMax=0;
        for(int i=0;i<(int) set[0]->attributes.size();i++){
            curAttIndex=i;
            //cout << "curAttIndex" <<": "<<curAttIndex<< endl;
            double gain=getGain(set, typeCount);
            //cout << "gain: "<<gain<<endl;
            if(gain>gainMax){
                gainMax=gain;
                attIndex=i;
            }
        }
        curAttIndex=attIndex;
        //cout<<"classifying according to: "<<curAttIndex<<endl;
        stable_sort(set.begin(), set.end(), entrycmp());
        vector< vector<entry*> > temp=getSubSet(set);
        vector<entry*> sub1=temp[0];
        vector<entry*> sub2=temp[1];
        node* left=new node;
        node* right=new node;       
        root->left=left;
        root->right=right;
        root->median=sub2[0]->attributes[curAttIndex];
        root->attributeIndex=curAttIndex;
        //cout<<"median: "<<root->median<<endl;
        //cout<<"sub1: "<<sub1.size()<<endl;
        //printSet(sub1);
        //cout<<"sub2: "<<sub2.size()<<endl;
        //printSet(sub2);
        buildTree(sub1,left, typeCount);
        buildTree(sub2,right, typeCount);
    }else{
        root->type=set[0]->type;
        root->left = nullptr;
        root->right = nullptr;
        root->median=-1;
    }
}

/*takes one set to check whether each element's type if same or not
 */
bool diff(vector<entry*> &set){
    int type=set[0]->num_type;

    for(int i=0;i< (int) set.size();i++){
        if(set[i]->num_type!=type){
            return true;
        }
    }
    return false;
}

/*takes one set and number of types to calculate information gain
 */
double getGain(vector<entry*> &set, int &typeCount){
    double infoGain=getEntropy(set,  typeCount);
    stable_sort(set.begin(), set.end(), entrycmp());
    vector< vector<entry*> > temp=getSubSet(set);
    vector<entry*> sub1=temp[0];
    vector<entry*> sub2=temp[1];
    infoGain=infoGain-((double)sub1.size()/set.size())*getEntropy(sub1,  typeCount)-((double)sub2.size()/set.size())*getEntropy(sub2, typeCount);
    return infoGain;
}

/*takes one set and number of types to calculate entropy
 */
double getEntropy(vector<entry*> &set, int &typeCount){
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

/*takes one set and returns vector of subsets based on median
 */
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

/*takes root node to get the depth of the tree
 */
int getDepth(node* cur){
    if(cur->left==nullptr || cur->right==nullptr){
        return 1;
    }else{
        int d1=getDepth(cur->left);
        int d2=getDepth(cur->right);
        if(d1>d2){
            return d1+1;
        }else{
            return d2+1;
        }
    }
}

/*Test Function: takes a vector and prints it
 */
void printSet(vector<entry*> &set){
    for(int i=0;i<(int)set.size();i++){
        vector<double> cur=set[i]->attributes;
        for(int j=0;j<(int)cur.size();j++){
            cout<<cur[j]<<",";
        }
        cout<<set[i]->num_type<<endl;
    }
}
