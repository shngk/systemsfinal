#include <stdlib.h>
#include <fstream>
#include <vector>
#include <iostream>
#include "kfunctions.h"
#include "kfunctions.cpp"

using namespace std;
using std::vector;


int main(){
  // read in the data!
  ifstream data;
  data.open("iris.data");

  if(!data){                       //terminate if error opening file
    cout << "Unable to open file\n";
    exit(1); 
  }

  //arraylist of flowers goes here
  vector<vector<string> > list;  
  
  for ( string line; getline(data, line);){
    vector<string> flower;      
    
    string delimiter = ",";

    // iterate through the line
    size_t pos = 0;
    string token;

    while((pos = line.find(delimiter)) != string::npos){
      token = line.substr(0, pos);
      //add the token to the flower in the list
      flower.push_back(token);
      line.erase(0, pos + delimiter.length());
    }
    // for adding the species name to vector item
    token = line;
    flower.push_back(token);
    
    list.push_back(flower);
    
  }
  data.close();

  /* KMEANS ALGORITHM */
  // inspired by pseudocode from:
  // stanford.edu/~cpiech/cs221/handouts/kmeans.html
  // trying to get species clusterong on petal length & petal width

  // initialize centroids randomly
  centroid *cluster1 = get_random_centroid();
  centroid *cluster2 = get_random_centroid();
  centroid *cluster3 = get_random_centroid();
  
  // initialize book-keeping variables
  vector<centroid> oldCentroids;
  int iterations = 0;

  // running the algorithm
  while(iterations < 5) { //need to figure out how to know when we're done
    // // save old centroids for convergence test
    oldCentroids.push_back(*cluster1);
    oldCentroids.push_back(*cluster2);
    oldCentroids.push_back(*cluster3);
   
    // // assign labels to each datapoint based on centroids
    assign_pts(list, cluster1, cluster2, cluster3);
    
    // // assign centroids based on datapoint labels
    cluster1 = calculate_centroid(cluster1);
    cluster2 = calculate_centroid(cluster2);
    cluster3 = calculate_centroid(cluster3);

    iterations++;
  }
}
