#include <stdlib.h>
#include <fstream>
#include <vector>
#include <iostream>
#include "kfunctions.h"

using namespace std;
using std::vector;


int main(){
  // read in the data!
  ifstream data;
  data.open("iris.data");

  if(!data){                       //terminate if error opening file
    cout << "Unable to open file";
    exit(1); 
  }

  //arraylist of flowers goes here
  vector<k_node> list;
  
  
  for ( string line; getline(data, line);){
    k_node flower = new k_node; 
    
    int item = 0;
    
    
    string delimiter = ",";

    //Iterate through the line
    size_t pos = 0;
    string token;
    while((pos = line.find(delimiter)) != string::npos){
      token = line.substr(0, pos);
      //add the token to the node in the list
      switch (item){
      case 0: flower.sep_len = atof(token.c_str());
	break;
      case 1: flower.sep_wid = atof(token.c_str());
	break;
      case 2: flower.pet_len = atof(token.c_str());
	break;
      case 3: flower.pet_wid = atof(token.c_str());
	break;
      case 4: flower.species = token;
	break;
      }
      line.erase(0, pos + delimiter.length());
      item++;
    }
    list.push_back(flower);
  }
  
}
