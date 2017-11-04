#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    ifstream dataset;
    dataset.open("../iris.data");
    char output[100];
    if (dataset.is_open()) {
    while (!dataset.eof()) {


       dataset >> output;
       cout<< output << endl;


    }
   }
   else{
        cout << "fail" << endl;
   }
   dataset.close();
   return 0;


}
