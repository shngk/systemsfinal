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
void read_data(ifstream &dataset, vector<string> &key_vector,
               vector<vector<double>> &data, vector<int> &key_num);



int main()
{
    ifstream dataset;
    dataset.open("../iris.data");

    if (dataset.is_open()) {
       map<vector<double>, string> data;
       vector<map<double, int>> attributes;


    }
    else{
         cout << "fail" << endl;
    }
    dataset.close();
    return 0;


}

void read_data(ifstream &dataset, map<vector<double>, string> data, vector<map<double, int>> attributes){

    int num_in_row = 0;
    int first_row = 0;

    while (!dataset.eof()) {
        string line;
        string token;
        string delimiter = ",";
        vector<double> each;
        getline(dataset, line);
        size_t pos = 0;
        int index = 0;

        if (first_row == 0){
            first_row = 1;
            string temp = line;
            while((pos = line.find(delimiter)) != string::npos){
                num_in_row++;
                line.erase(0,pos+delimiter.length());
            }
            line = temp;
        }

        for(int i = 0; i< num_in_row; i++){
            map<double, int> count_each_column;
            attributes.push_back(count_each_column);
        }


         while((pos = line.find(delimiter)) != string::npos){
              token = line.substr(0,pos);
              double d = stod(token, NULL);
              each.push_back(d);
              line.erase(0,pos+delimiter.length());
              for (int i = 0; i < num_in_row; i++){

                  if(index == i){
                      attributes[index][d]++;
                  }
              }
              index++;

         }
         data[each] = line;


    }

}



