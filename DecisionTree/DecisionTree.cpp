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

struct each_row{
    string type;
    vector<double> attributes;
};

void read_data(ifstream &dataset, vector<each_row> &data);



int main()
{
    ifstream dataset;
    dataset.open("../iris.data");

    if (dataset.is_open()) {
       vector<each_row> data;
       read_data(dataset, data);
       /*for(int i = 0; i < data.size(); i++){
           cout << data[i].attributes[0] << " "<< data[i].attributes[1] << " " << data[i].attributes[2] ;
           cout << data[i].type << endl;
       }*/
    }
    else{
         cout << "fail" << endl;
    }
    dataset.close();
    return 0;


}

void read_data(ifstream &dataset, vector<each_row> &data){



    while (!dataset.eof()) {
        string line;
        string token;
        string delimiter = ",";
        getline(dataset, line);
        size_t pos = 0;

         each_row new_row;
         while((pos = line.find(delimiter)) != string::npos){
              token = line.substr(0,pos);
              double d = stod(token, NULL);
              new_row.attributes.push_back(d);
              line.erase(0,pos+delimiter.length());

         }
         new_row.type = line;
         data.push_back(new_row);
    }
}



