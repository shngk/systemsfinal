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



