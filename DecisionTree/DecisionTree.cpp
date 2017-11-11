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

double getGain(vector<vector<double>> data,vector<int> count);
double getEntropy(vector<vector<double>> data,vector<int> count);

int main()
{
    ifstream dataset;
    dataset.open("../iris.data");
    string line;
    if (dataset.is_open()) {

        int key_flag = 0;
        int key = 0;
        int num_key = -1;
        string temp;
        vector<string> key_vector;
        vector<vector<double>> data;
        vector<int> key_num;
        while (!dataset.eof()) {
            vector<double> each;
            getline(dataset, line);
            size_t pos = 0;
            string token;
            string delimiter = ",";
            int deli = 0;
            while((pos = line.find(delimiter)) != string::npos){
                token = line.substr(0,pos);
                each.push_back(stod(token, NULL));
                //each.push_back(token);
                line.erase(0,pos+delimiter.length());
                deli = 1;
            }

            if(key_flag==0){
                num_key++;
                temp = line;
                key = 0;
                key_flag = 1;
                key_vector.push_back(line);
            }
            if(line != temp){
                temp = line;
                key++;
                key_vector.push_back(line);
                key_num.push_back(num_key);
                num_key = 1;
            }
            else{
                num_key++;
            }
            if(deli == 1) {
                each.push_back(key);
                data.push_back(each);
            }


        }
        for(int j = 0; j < (int)data.size(); j++){
            for(int i = 0; i < (int)data[j].size(); i++){
                cout << data[j][i] << " ";
            }
            cout << endl;
        }

        for(int i = 0; i < (int) key_vector.size(); i++){
            cout << key_vector[i] << " ";
        }
        cout << endl;

        for(int i = 0; i < (int) key_num.size(); i++){
            cout << key_num[i] << " ";
        }

   }
   else{
        cout << "fail" << endl;
   }
   dataset.close();
   return 0;


}

double getGain(vector<vector<double>> data,vector<int> count,int attribute){
	double entropy=getEntropy(data,count);
	double gain=entropy;
	double value=1;
	for(int i=0;i<data.size();i++){
		data[i][attribute];
	}
}

double getEntropy(vector<vector<double>> data,vector<int> count){
	double entropy=0.0;
	for(int i=0;i<count.size();i++){
		entropy-=vector[i]/data.size()*log2((double)vector[i]/data.size());
	}
}


