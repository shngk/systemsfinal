/* implements function prototypes declared in kfunctions.h
 */

#include <iostream>
#include "kfunctions.h"
#include <math.h>
#include <algorithm> 

using namespace std;
using std::vector;

class centroid{
public:
  double x;
  double y;
  
  vector<vector<string> > elements; 
};


/* GET_RANDOM CENTROID: Returns a random centroid within
the plane of data */
centroid* get_random_centroid(int x_max, int y_max){
  double x; // represents petal length, range from 0-x_max
  double y; // represents petal width, range from 0-y_max
  
  x = rand() % (x_max + 1);
  y = rand() % (y_max + 1);
  
  centroid *cent = new centroid();
  cent->x = x;
  cent->y = y;

  return cent;
}

/* ASSIGN_PTS: takes the vector of data and three centroids
and assigns each item in the vector to one of the 3 centroids */
void assign_pts(vector<vector<string> > data, centroid *c1, centroid *c2, centroid *c3, int x, int y){
  // for each item in data, calculate its distance from each centroid and
  // add that item to the vector contained in the centroid it is closest to
  unsigned int i;

  
  for(i = 0; i < data.size() - 1; i++){
    double d1;
    double d2;
    double d3;
    
    // calculate distance from each centroid
    double data_x = atof(data[i][x].c_str());
    double data_y = atof(data[i][y].c_str());
    
    d1 = sqrt(pow((data_x - c1->x), 2) + pow((data_y - c1->y), 2));
    d2 = sqrt(pow((data_x - c2->x), 2) + pow((data_y - c2->y), 2));
    d3 = sqrt(pow((data_x - c3->x), 2) + pow((data_y - c3->y), 2));

    
    // check which distance has the smallest value
    // add the item to the appropriate centroid
    if (d1 <= d2 && d1 <= d3){
      c1->elements.push_back(data[i]);
    }
    else if(d2 <= d1 && d2 <= d3){
      c2->elements.push_back(data[i]);
    }
    else if(d3 <= d1 && d3 <= d2){
      c3->elements.push_back(data[i]);
    }
  }
}


/* CALCULATE_CENTROID: averages the x and y coordinates of each
data element in the list of the previous centroid passed. If a 
centroid has no elements it will call get_random_centroid() */
centroid * calculate_centroid(centroid *c, int x, int y, int x_max, int y_max){
  // iterate through each centroids elements and average
  // their x values and y values to get the new centroid
  centroid *cent = new centroid();
  double x_mean = 0;
  double y_mean = 0;

  unsigned int i;
  unsigned int c_size = c->elements.size();

  for(i = 0; i < c_size; i++){
    x_mean += atof(c->elements[i][x].c_str());
    y_mean += atof(c->elements[i][y].c_str());
  }
  
  //If no data in a centroid
  if(c->elements.size() == 0){
    centroid * temp = get_random_centroid(x_max, y_max);
    x_mean = temp->x;
    y_mean = temp->y;
  }
  else{
    x_mean = (x_mean / c_size);
    y_mean = (y_mean / c_size);
  }
  cent->x = x_mean;
  cent->y = y_mean;

  printf("centroid = %f : %f\n", cent->x, cent->y);

  // return the new centroid
  return cent;
}


void print_cluster(centroid * c){
  unsigned int i;
  unsigned int j;

  if(c->elements.size() == 0){
    printf("Sorry! No elements\n");
  }
  
  for(i = 0; i < c->elements.size(); i++){
    for(j = 0; j < c->elements[i].size(); j++){
      printf("%s ", c->elements[i][j].c_str());
    }
    printf("\n");
  }
}

int compare(centroid *c1, centroid *c2){
  vector<double> list1;
  vector<double> list2;

  unsigned int s = c1->elements[0].size() - 1;
  
  // copy id #s from c1->elements into list1
  for(unsigned int i = 0; i < c1->elements.size(); i++){
    list1.push_back(atof(c1->elements[i][s].c_str())); 
  }
  
  // copy id #s from c1->elements into list2
  for(unsigned int i = 0; i < c2->elements.size(); i++){
    list2.push_back(atof(c2->elements[i][s].c_str()));
  }

  // sort lists
  std::sort(list1.begin(), list1.end());
  std::sort(list2.begin(), list2.end());
  
  // comment this out when done:
  // printing the sorted lists to check that this method works correctly:
  /*  cout << "Do we make it this far?\n The list is: " << list1.size() << " elements\n";
  for(unsigned int i = 0; i < list1.size(); i++){
    cout << "list1: \n";
    cout << list1[i];
    cout << "\n";
    }*/
  
  int the_same = 0;
  // compare the lists
  if(list1.size() == list2.size()){
    unsigned int num_same = 0;  //the number of elements that match in the list
    for (unsigned int i = 0; i < list1.size(); i++){
      if(list1[i] == list2[i])
	num_same++;
    }
    if(num_same == list1.size()) //If all the elements in the list are the same
      the_same = 1;
  }

  
  if(the_same){
    // return 0 if true
    return 1;
  }
  else{
    // return -1 if false
    return 0;
  }
}
