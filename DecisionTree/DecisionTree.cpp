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

int main()
{
    ifstream dataset;
    dataset.open("../iris.data");
    char output[100];
    string line;
    if (dataset.is_open()) {
        while (!dataset.eof()) {
            map<string, vector<double>> data;
            vector<double> each;
            getline(dataset, line);
            size_t pos = 0;
            string token;
            string delimiter = ",";

            while((pos = line.find(delimiter)) != string::npos){
                token = line.substr(0,pos);
                each.push_back(stod(token, NULL));
                line.erase(0,pos+delimiter.length());
            }
            for(int i = 0; i <each.size(); i++){
                cout << each[i] << " ";
            }
            cout << token ;
            cout << endl;


        }
   }
   else{
        cout << "fail" << endl;
   }
   dataset.close();
   return 0;


}
