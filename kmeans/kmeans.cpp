#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "kfunctions.h"
using namespace std;


int main(){
  // read in the data!
  ifstream data;
  data.open("iris.data");

  if(!data){                       //terminate if error opening file
    cout << "Unable to open file";
    exit(1); 
  }

  //arraylist of flowers goes here
  vector<k_means> list;
  
  
  for ( string line; getline(data, line);){
    k_means flower = new k_means; 
    //add the flower to the array list
    
    int item = 0;
    
    
    string delimiter = ",";

    //Iterate through the line
    size_t pos = 0;
    string token;
    while((pos = line.find(delimiter)) != string::npos){
      token = s.substr(0, pos);
      //add the token to the node in the list
      switch (item){
      case 0: flower::sep_len = token;
	break;
      case 1: flower:: sep_wid = token;
	break;
      case 2: flower:: pet_len = token;
	break;
      case 3: flower::pet_wid = token;
	break;
      case 4: flower::species = token;
	break;
      }
      s.erase(0, pos + delimiter.length());
      item++;
    }
    list.push_back(flower);
  }
  
}
